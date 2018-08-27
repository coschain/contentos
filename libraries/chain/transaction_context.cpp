#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>
#include <contento/chain/exceptions.hpp>
#include <contento/chain/global_property_object.hpp>

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
    //   auto now = fc::time_point::now();
    //   if( BOOST_UNLIKELY( now > _deadline ) ) {
    //      // edump((now-start)(now-pseudo_start));
    //      if( billed_cpu_time_us > 0 || deadline_exception_code == deadline_exception::code_value ) {
    //         EOS_THROW( deadline_exception, "deadline exceeded", ("now", now)("deadline", _deadline)("start", start) );
    //      } else if( deadline_exception_code == block_cpu_usage_exceeded::code_value ) {
    //         EOS_THROW( block_cpu_usage_exceeded,
    //                    "not enough time left in block to complete executing transaction",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      } else if( deadline_exception_code == tx_cpu_usage_exceeded::code_value ) {
    //         EOS_THROW( tx_cpu_usage_exceeded,
    //                    "transaction was executing for too long",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      } else if( deadline_exception_code == leeway_deadline_exception::code_value ) {
    //         EOS_THROW( leeway_deadline_exception,
    //                    "the transaction was unable to complete by deadline, "
    //                    "but it is possible it could have succeeded if it were allowed to run to completion",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      }
    //      FC_ASSERT( false, "unexpected deadline exception code" );
    //   }
       
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

   void transaction_context::apply( const vm_operation& op, account_name receiver, bool context_free, uint32_t recurse_depth ) {
      apply_context  acontext( control, *this, op, recurse_depth );
      acontext.context_free = context_free;
      acontext.receiver     = receiver;

      acontext.exec();
   }

} } /// contento::chain
