#pragma once
#include <boost/signals2/signal.hpp>

#include <eosio/chain/abi_serializer.hpp>
#include <contento/chain/account_object.hpp>

namespace chainbase {
   class database;
}


namespace eosio { namespace chain {

   struct controller_impl;
   using chainbase::database;
   using boost::signals2::signal;

   class dynamic_global_property_object;
   class global_property_object;
   class account_object;
   using apply_handler = std::function<void(apply_context&)>;

   ////class fork_database;

   class controller {
      public:

         controller();
         ~controller();

         void startup();


         chainbase::database& db()const;

         ////fork_database& fork_db()const;

         const account_object&                 get_account( account_name n )const;
         const global_property_object&         get_global_properties()const;
         const dynamic_global_property_object& get_dynamic_global_properties()const;

         void validate_referenced_accounts( const transaction& t )const;
         void validate_expiration( const transaction& t )const;
         void validate_tapos( const transaction& t )const;


         bool skip_auth_check()const;

         bool contracts_console()const;

         chain_id_type get_chain_id()const;

         signal<void(const block_state_ptr&)>          irreversible_block;
         signal<void(const transaction_metadata_ptr&)> accepted_transaction;
         signal<void(const transaction_trace_ptr&)>    applied_transaction;
         signal<void(const int&)>                      bad_alloc;

         /*
         signal<void()>                                  pre_apply_block;
         signal<void()>                                  post_apply_block;
         signal<void()>                                  abort_apply_block;
         signal<void(const transaction_metadata_ptr&)>   pre_apply_transaction;
         signal<void(const transaction_trace_ptr&)>      post_apply_transaction;
         signal<void(const transaction_trace_ptr&)>  pre_apply_action;
         signal<void(const transaction_trace_ptr&)>  post_apply_action;
         */

         const apply_handler* find_apply_handler( account_name contract, scope_name scope, action_name act )const;
         wasm_interface& get_wasm_interface();


         optional<abi_serializer> get_abi_serializer( account_name n )const {
            if( n.good() ) {
               try {
                  const auto& a = get_account( n );
                  abi_def abi;
                  if( abi_serializer::to_abi( a.abi, abi ))
                     return abi_serializer( abi );
               } FC_CAPTURE_AND_LOG((n))
            }
            return optional<abi_serializer>();
         }

         template<typename T>
         fc::variant to_variant_with_abi( const T& obj ) {
            fc::variant pretty_output;
            abi_serializer::to_variant( obj, pretty_output, [&]( account_name n ){ return get_abi_serializer( n ); });
            return pretty_output;
         }

      private:

         std::unique_ptr<controller_impl> my;

   };

} }  /// eosio::chain

FC_REFLECT( eosio::chain::controller::config,
            (actor_whitelist)
            (actor_blacklist)
            (contract_whitelist)
            (contract_blacklist)
            (blocks_dir)
            (state_dir)
            (state_size)
            (reversible_cache_size)
            (read_only)
            (force_all_checks)
            (contracts_console)
            (genesis)
            (wasm_runtime)
          )
