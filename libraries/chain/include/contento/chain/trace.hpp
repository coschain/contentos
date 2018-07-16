/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <contento/chain/action.hpp>
#include <contento/chain/action_receipt.hpp>

namespace contento { namespace chain {

   struct base_action_trace {
      base_action_trace( const action_receipt& r ):receipt(r){}
      base_action_trace(){}

      action_receipt       receipt;
      action               act;
      fc::microseconds     elapsed;
      uint64_t             cpu_usage = 0;
      string               console;

      uint64_t             total_cpu_usage = 0; /// total of inline_traces[x].cpu_usage + cpu_usage
      transaction_id_type  trx_id; ///< the transaction that generated this action
   };

   struct action_trace : public base_action_trace {
      using base_action_trace::base_action_trace;

      vector<action_trace> inline_traces;
   };

} }  /// namespace contento::chain

FC_REFLECT( contento::chain::base_action_trace,
                    (receipt)(act)(elapsed)(cpu_usage)(console)(total_cpu_usage)(trx_id) )

FC_REFLECT_DERIVED( contento::chain::action_trace,
                    (contento::chain::base_action_trace), (inline_traces) )
