#include <eosio/vm/apply_context.hpp>
#include <eosio/vm/transaction_context.hpp>
#include <eosio/vm/exceptions.hpp>
//#include <eosio/chain/generated_transaction_object.hpp>
#include <eosio/chain/global_property_object.hpp>

namespace eosio { namespace chain {

   transaction_context::transaction_context( controller& c,
                                             const signed_transaction& t,
                                             const transaction_id_type& trx_id,
                                             fc::time_point s )
   :control(c)
   ,trx(t)
   ,id(trx_id)
   ,undo_session(c.db().start_undo_session(true))
   ,trace(std::make_shared<transaction_trace>())
   ,start(s)
   ,net_usage(trace->net_usage)
   ,pseudo_start(s)
   {
      trace->id = id;
      executed.reserve( trx.total_actions() );
      FC_ASSERT( trx.transaction_extensions.size() == 0, "we don't support any extensions yet" );
   }

   void transaction_context::init()
   {    
   }

   void transaction_context::exec() {
      FC_ASSERT( is_initialized, "must first initialize" );

      if( apply_context_free ) {
        //// Y
        //  for( const auto& act : trx.context_free_actions ) {
        //     trace->action_traces.emplace_back();
        //     dispatch_action( trace->action_traces.back(), act, true );
        //  }
      }

      ////Y if( delay == fc::microseconds() ) {
         for( const auto& act : trx.actions ) {
            trace->action_traces.emplace_back();
            dispatch_action( trace->action_traces.back(), act );
         }
         ////Y
    //   } else {
    //      schedule_transaction();
    //   }
   }

   void transaction_context::finalize() {
      
   }

   void transaction_context::squash() {
      undo_session.squash();
   }


   void transaction_context::check_net_usage()const {
      
   }

   void transaction_context::checktime()const {
      
   }

   void transaction_context::pause_billing_timer() {

   }

   void transaction_context::resume_billing_timer() {

   }

   void transaction_context::validate_cpu_usage_to_bill( int64_t billed_us, bool check_minimum )const {
      
   }

   void transaction_context::add_ram_usage( account_name account, int64_t ram_delta ) {

   }

   void transaction_context::dispatch_action( action_trace& trace, const action& a, account_name receiver, bool context_free, uint32_t recurse_depth ) {
      apply_context  acontext( control, *this, a, recurse_depth );
      acontext.context_free = context_free;
      acontext.receiver     = receiver;

      try {
         acontext.exec();
      } catch( ... ) {
         trace = move(acontext.trace);
         throw;
      }

      trace = move(acontext.trace);
   }
} } /// eosio::chain
