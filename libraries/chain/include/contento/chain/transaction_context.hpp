#pragma once
#include <contento/chain/controller.hpp>
#include <contento/protocol/contento_operations.hpp>

namespace contento { namespace chain {

   class transaction_context {
      private:
         void init();

      public:

         transaction_context( controller& c,
                              const signed_transaction& t,
                              const transaction_id_type& trx_id,
                              fc::time_point start = fc::time_point::now() );

         void exec();
         void finalize();
         void squash();

         inline void add_net_usage( uint64_t u ) { }

         void check_net_usage()const;

         void checktime()const;

         void pause_billing_timer();
         void resume_billing_timer();

         void add_ram_usage( account_name account, int64_t ram_delta );

         void apply( const vm_operation& op, account_name receiver, bool context_free = false, uint32_t recurse_depth = 0 );
         inline void apply( const vm_operation& op, bool context_free = false ) {
            apply(op, op.contract_name, context_free);
         };
      private:

         friend struct controller_impl;
         friend class apply_context;

      /// Fields:
      public:

         controller&                   control;
         const signed_transaction&     trx;
         transaction_id_type           id;
         chainbase::database::session  undo_session;
         //transaction_trace_ptr         trace;
         fc::time_point                start;

         fc::time_point                published;


        // vector<action_receipt>        executed;
        //  flat_set<account_name>        bill_to_accounts;
        //  flat_set<account_name>        validate_ram_usage;

        //  fc::time_point                deadline = fc::time_point::maximum();
        //  fc::microseconds              leeway = fc::microseconds(3000);

      private:
         bool                          is_initialized = false;
   };

} }