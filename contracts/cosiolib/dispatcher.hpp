#pragma once
#include <cosiolib/print.hpp>
#include <cosiolib/action.hpp>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <boost/mp11/tuple.hpp>
#define N(X) ::cosio::string_to_name(#X)
#define N16(X) ::cosio::string_to_namex(#X)

namespace cosio {
   template<typename Contract, typename FirstAction>
   bool dispatch( uint64_t code, uint64_t act ) {
      if( code == FirstAction::get_account() && FirstAction::get_name() == act ) {
         Contract().on( unpack_action_data<FirstAction>() );
         return true;
      }
      return false;
   }


   /**
    * This method will dynamically dispatch an incoming set of actions to
    *
    * ```
    * static Contract::on( ActionType )
    * ```
    *
    * For this to work the Actions must be dervied from the 
    *
    */
   template<typename Contract, typename FirstAction, typename SecondAction, typename... Actions>
   bool dispatch( uint64_t code, uint64_t act ) {
      if( code == FirstAction::get_account() && FirstAction::get_name() == act ) {
         Contract().on( unpack_action_data<FirstAction>() );
         return true;
      }
      return cosio::dispatch<Contract,SecondAction,Actions...>( code, act );
   }

   template<typename T, typename Q, typename... Args>
   bool execute_action( T* obj, void (Q::*func)(Args...)  ) {
      size_t size = action_data_size();

      //using malloc/free here potentially is not exception-safe, although WASM doesn't support exceptions
      constexpr size_t max_stack_buffer_size = 512;
      void* buffer = nullptr;
      if( size > 0 ) {
         buffer = max_stack_buffer_size < size ? malloc(size) : alloca(size);
         read_action_data( buffer, size );
      }

      auto args = unpack<std::tuple<std::decay_t<Args>...>>( (char*)buffer, size );

      if ( max_stack_buffer_size < size ) {
         free(buffer);
      }

      auto f2 = [&]( auto... a ){  
         (obj->*func)( a... ); 
      };

      boost::mp11::tuple_apply( f2, args );
      return true;
   }

#define COSIO_API_CALL( r, OP, elem ) \
   case ::cosio::string_to_name( BOOST_PP_STRINGIZE(elem) ): \
      cosio::execute_action( &thiscontract, &OP::elem ); \
      break;

#define COSIO_API( TYPE,  MEMBERS ) \
   BOOST_PP_SEQ_FOR_EACH( COSIO_API_CALL, TYPE, MEMBERS )

#define COSIO_ABI( TYPE, MEMBERS ) \
extern "C" { \
   void apply( uint64_t _receiver, uint64_t code, uint64_t action ) { \
      auto self = _receiver; \
      auto receiver = cosio::current_receiver();\
      auto contract_name = cosio::current_contract_name();\
      if( action == N(onerror)) { \
         /* onerror is only valid if it is for the "eosio" code account and authorized by "eosio"'s "active permission */ \
         contento_assert(contract_name == N16(eosio), "onerror action's are only valid from the \"eosio\" system account"); \
      } \
      if( contract_name == receiver || action == N(onerror) ) { \
         TYPE thiscontract( receiver ); \
         switch( action ) { \
            COSIO_API( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of thiscontract to run: contento_exit(0); */ \
      } \
   } \
} \


   /*
   template<typename T>
   struct dispatcher {
      dispatcher( account_name code ):_contract(code){}

      template<typename FuncPtr>
      void dispatch( account_name action, FuncPtr ) {
      }

      T contract;
   };

   void dispatch( account_name code, account_name action, 
   */

}
