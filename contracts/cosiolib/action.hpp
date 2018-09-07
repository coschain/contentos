/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once
#include <cosiolib/action.h>
#include <cosiolib/datastream.hpp>
#include <cosiolib/serialize.hpp>

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/facilities/overload.hpp>

namespace cosio {

   /**
    * @defgroup actioncppapi Action C++ API
    * @ingroup actionapi
    * @brief Type-safe C++ wrapers for Action C API
    *
    * @note There are some methods from the @ref actioncapi that can be used directly from C++
    *
    * @{
    */

   /**
    *
    *  This method unpacks the current action at type T.
    *
    *  @brief Interpret the action body as type T
    *
    *  Example:
    *  @code
    *  struct dummy_action {
    *    char a; //1
    *    unsigned long long b; //8
    *    int  c; //4
    *
    *    COSLIB_SERIALIZE( dummy_action, (a)(b)(c) )
    *  };
    *  dummy_action msg = unpack_action_data<dummy_action>();
    *  @endcode
    */
   template<typename T>
   T unpack_action_data() {
      constexpr size_t max_stack_buffer_size = 512;
      size_t size = action_data_size();
      char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
      read_action_data( buffer, size );
      return unpack<T>( buffer, size );
   }

  //  using ::require_auth;
  //  using ::require_recipient;

   /**
    *  All of the listed accounts will be added to the set of accounts to be notified
    *
    *  This helper method enables you to add multiple accounts to accounts to be notified list with a single
    *  call rather than having to call the similar C API multiple times.
    *
    *  @note action.code is also considered as part of the set of notified accounts
    *
    *  @brief Verify specified accounts exist in the set of notified accounts
    *
    *  Example:
    *  @code
    *  require_recipient(N(Account1), N(Account2), N(Account3)); // throws exception if any of them not in set.
    *  @endcode
    */
   template<typename... accounts>
   void require_recipient( account_name name, accounts... remaining_accounts ){
      // require_recipient( name );
      // require_recipient( remaining_accounts... );
   }


   namex current_receiver() {
     namex_ receiver;
     current_receiver(&receiver);
     return receiver;
   }

   namex current_contract_name() {
     namex_ contract_name;
     current_contract_name(&contract_name);
     return contract_name;
   }

   namex current_caller() {
     namex_ caller;
     current_caller(&caller);
     return caller;
   }

   /**
    * This is the packed representation of an action along with
    * meta-data about the authorization levels.
    */
   struct action {
      account_name               caller;
      account_name               contract_name;
      action_name                name;
      bytes                      data;

      action() = default;

      /**
       *  @tparam Action - a type derived from action_meta<Scope,Name>
       *  @param value - will be serialized via pack into data
       */
      template<typename Action>
      action(const account_name &c, const Action& value ) {
         contract_name       = Action::get_account();
         name          = Action::get_name();
         caller        = c;
         data          = pack(value);
      }

      /**
       *  @tparam T - the type of the action data
       *  @param c - the caller of the action
       *  @param a - name of the contract account
       *  @param n - name of the action
       *  @param value - will be serialized via pack into data
       */
      template<typename T>
      action( const account_name &c, account_name a, action_name n, T&& value )
      :caller(c), contract_name(a), name(n), data(pack(std::forward<T>(value))) {}

      COSLIB_SERIALIZE( action, (caller)(contract_name)(name)(data) )

      void send() const {
         auto serialize = pack(*this);
         ::send_inline(serialize.data(), serialize.size());
      }

      /**
       * Retrieve the unpacked data as T
       * @tparam T expected type of data
       * @return the action data
       */
      template<typename T>
      T data_as() {
         contento_assert( name == T::get_name(), "Invalid name" );
         contento_assert( contract_name == T::get_account(), "Invalid account" );
         return unpack<T>( &data[0], data.size() );
      }

   };

   template<uint64_t Account, uint64_t Name>
   struct action_meta {
      static uint64_t get_account() { return Account; }
      static uint64_t get_name()  { return Name; }
   };

   template<typename... Args>
   void dispatch_inline( account_name caller,
                         account_name code, 
                         action_name act,
                         std::tuple<Args...> args ) {
      action( caller, code, act, std::move(args) ).send();
   }

   template<typename, uint64_t>
   struct inline_dispatcher;

   template<typename T, uint64_t Name, typename... Args>
   struct inline_dispatcher<void(T::*)(Args...), Name> {
      static void call(account_name caller, account_name code, std::tuple<Args...> args) {
         dispatch_inline(caller, code, Name, std::move(args));
      }
   };

 ///@} actioncpp api

} // namespace cosio

#define INLINE_ACTION_SENDER3( CONTRACT_CLASS, FUNCTION_NAME, ACTION_NAME  )\
::cosio::inline_dispatcher<decltype(&CONTRACT_CLASS::FUNCTION_NAME), ACTION_NAME>::call

#define INLINE_ACTION_SENDER2( CONTRACT_CLASS, NAME )\
INLINE_ACTION_SENDER3( CONTRACT_CLASS, NAME, ::cosio::string_to_name(#NAME) )

#define INLINE_ACTION_SENDER(...) BOOST_PP_OVERLOAD(INLINE_ACTION_SENDER,__VA_ARGS__)(__VA_ARGS__)

#define SEND_INLINE_ACTION( CONTRACT, NAME, ... )\
INLINE_ACTION_SENDER(std::decay_t<decltype(CONTRACT)>, NAME)( (CONTRACT).get_self(),\
BOOST_PP_TUPLE_ENUM(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__)) );


#define ACTION( CODE, NAME ) struct NAME : ::cosio::action_meta<CODE, ::cosio::string_to_name(#NAME) >
