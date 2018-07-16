/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <contento/chain/types.hpp>
#include <contento/chain/contract_types.hpp>

namespace contento { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_contento_newaccount(apply_context&);
   void apply_contento_updateauth(apply_context&);
   void apply_contento_deleteauth(apply_context&);
   void apply_contento_linkauth(apply_context&);
   void apply_contento_unlinkauth(apply_context&);

   /*
   void apply_contento_postrecovery(apply_context&);
   void apply_contento_passrecovery(apply_context&);
   void apply_contento_vetorecovery(apply_context&);
   */

   void apply_contento_setcode(apply_context&);
   void apply_contento_setabi(apply_context&);

   void apply_contento_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace contento::chain
