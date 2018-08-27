#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>
#include <contento/chain/exceptions.hpp>
#include <contento/chain/config.hpp>
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
   }

   void transaction_context::pause_billing_timer() {
   }

   void transaction_context::resume_billing_timer() {
   }

   void transaction_context::add_ram_usage( account_name account, int64_t ram_delta ) {
      
   }

   void transaction_context::apply( const vm_operation& op, account_name receiver, bool context_free, uint32_t recurse_depth ) {
      apply_context  acontext( control, *this, op, recurse_depth );
      acontext.context_free = context_free;
      acontext.receiver     = receiver;

      acontext.exec();
   }

} } /// contento::chain
