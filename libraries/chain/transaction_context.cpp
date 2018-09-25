#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>
#include <contento/chain/config.hpp>

namespace contento { namespace chain {

   transaction_context::transaction_context( controller& c,
                                             const signed_transaction& t,
                                             const transaction_id_type& trx_id,
                                             fc::time_point s )
   :control(c)
   ,trx(t)
   ,id(trx_id)
   ,start(s)
   {
      FC_ASSERT( trx.extensions.size() == 0, "we don't support any extensions yet" );
   }

   void transaction_context::init( )
   {
      is_initialized = true;
       _deadline = start + fc::microseconds(config::max_trx_duration);
   }

   void transaction_context::exec() {
      FC_ASSERT( is_initialized, "must first initialize" );
   }

   void transaction_context::finalize() {
      FC_ASSERT( is_initialized, "must first initialize" );
   }


   void transaction_context::check_net_usage()const {
   }

   void transaction_context::checktime()const {
      // auto now = fc::time_point::now();
      // if( BOOST_UNLIKELY( now > _deadline ) ) {
      //    FC_ASSERT( false, "transaction execution duration exceeds limit" );
      // }
       
       FC_ASSERT( gas() <= max_gas, "out of gas" );
   }

   void transaction_context::pause_billing_timer() {
   }

   void transaction_context::resume_billing_timer() {
   }

   void transaction_context::add_ram_usage( account_name account, int64_t ram_delta ) {
       bill.first += ram_delta;
   }
    
    void transaction_context::add_wasm_price( account_name account, uint64_t price ) {
        bill.second += price;
    }
    
    void transaction_context::init_bill(uint64_t max_gas, uint64_t ram_to_gas, uint64_t wasm_to_gas) {
        this->bill.first = 0;
        this->bill.second = 0;
        this->max_gas = max_gas;
        this->ram_to_gas = ram_to_gas;
        this->wasm_to_gas = wasm_to_gas;
    }

    uint64_t transaction_context::gas() const {
        uint64_t gas = wasm_to_gas * bill.second;
        if (bill.first > 0) {
            gas += ram_to_gas * (uint64_t)bill.first;
        }
        return gas;
    }
    
    void transaction_context::add_paid_gas(uint64_t paid_gas) {
        this->paid_gas += paid_gas;
    }
    
    uint64_t transaction_context::gas_paid() const {
        return this->paid_gas;
    }
    
    bool transaction_context::has_vm_error() const {
        return vm_error_occurred;
    }

    const fc::exception_ptr transaction_context::vm_error() const {
        return vm_exc;
    }
    
    void transaction_context::set_vm_error(fc::exception_ptr e ) {
        vm_error_occurred = true;
        vm_exc = e;
    }

    void transaction_context::set_vm_console(const std::string& s) {
        vm_console = s;
    }

    const std::string& transaction_context::get_vm_console() const {
        return vm_console;
    }

   void transaction_context::apply( const vm_operation& op, account_name account, account_name contract_name, bool context_free, uint32_t recurse_depth ) {
      apply_context  acontext( control, *this, op, recurse_depth );
      acontext.context_free = context_free;
      // acontext.account     = account;
      // acontext.receiver     = contract_name;

      acontext.exec();
   }

} } /// contento::chain
