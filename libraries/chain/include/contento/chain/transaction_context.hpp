#pragma once
#include <contento/chain/controller.hpp>
#include <contento/protocol/transaction.hpp>
#include <utility>
#include <fc/exception/exception.hpp>

namespace contento { namespace chain {
    
   using bill_type = std::pair<int64_t, uint64_t>;

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

         inline void add_net_usage( uint64_t u ) { }

         void check_net_usage()const;

         void checktime()const;

         void pause_billing_timer();
         void resume_billing_timer();

         void add_ram_usage( account_name account, int64_t ram_delta );
         void add_wasm_price( account_name account, uint64_t price );
         void init_bill(uint64_t max_gas, uint64_t ram_to_gas, uint64_t wasm_to_gas);
         void add_paid_gas(uint64_t paid_gas);
         uint64_t gas() const;
         uint64_t gas_paid() const;
         bool has_vm_error() const;
         const fc::exception_ptr vm_error() const;
         void set_vm_error(fc::exception_ptr e );

         void set_vm_console(const std::string& s);
         const std::string& get_vm_console() const;

         void apply( const vm_operation& op, account_name account, account_name receiver, bool context_free = false, uint32_t recurse_depth = 0 );
         inline void apply( const vm_operation& op, bool context_free = false ) {
            apply(op, op.contract_name, context_free);
         };
       
       inline void set_payable_flag(){
           accept_pay = true;
       };
       
       inline bool get_payable_flag(){
           return accept_pay;
       }
      private:

         friend struct controller_impl;
         friend class apply_context;

      /// Fields:
      public:

         controller&                   control;
         const signed_transaction&     trx;
         transaction_id_type           id;
         fc::time_point                start;


         fc::time_point                published;

        // vector<action_receipt>        executed;
        //  flat_set<account_name>        bill_to_accounts;
        //  flat_set<account_name>        validate_ram_usage;

        //  fc::time_point                deadline = fc::time_point::maximum();
        //  fc::microseconds              leeway = fc::microseconds(3000);

      private:
         bool                          is_initialized = false;

       bill_type                      bill = {0, 0};
       uint64_t                       max_gas = 0;
       uint64_t                       ram_to_gas = 1;
       uint64_t                       wasm_to_gas = 1;
       uint64_t                       paid_gas = 0;
       bool                           vm_error_occurred = false;
       fc::exception_ptr              vm_exc;
       std::string                    vm_console;

         fc::time_point                _deadline;
       bool                             accept_pay = false;
   };

} }
