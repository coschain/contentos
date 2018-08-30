/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <contento/chain/contento_contract.hpp>
#include <contento/chain/contract_table_objects.hpp>

#include <contento/chain/controller.hpp>
//#include <contento/chain/transaction_context.hpp>
#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>
#include <contento/chain/exceptions.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/contract_types.hpp>

#include <contento/chain/wasm_interface.hpp>
#include <contento/chain/abi_serializer.hpp>


namespace contento { namespace chain {

void apply_contento_setcode(apply_context& context) {

   auto& db = context.db;
   auto  act = context.op.as<setcode>();
   // TODOO: context.require_authorization(act.account);

   FC_ASSERT( act.vmtype == 0 );
   FC_ASSERT( act.vmversion == 0 );

   fc::sha256 code_id; /// default ID == 0

   if( act.code.size() > 0 ) {
     code_id = fc::sha256::hash( act.code.data(), (uint32_t)act.code.size() );
     wasm_interface::validate(context.control, act.code);
   }

   const auto& account = db.get<account_object,by_name>(act.account);

   int64_t code_size = (int64_t)act.code.size();
   int64_t old_size  = (int64_t)account.code.size() * config::setcode_ram_bytes_multiplier;
   int64_t new_size  = code_size * config::setcode_ram_bytes_multiplier;

   FC_ASSERT( account.code_version != code_id, "contract is already running this version of code" );

   db.modify( account, [&]( auto& a ) {
      /** TODO: consider whether a microsecond level local timestamp is sufficient to detect code version changes*/
      // TODO: update setcode message to include the hash, then validate it in validate
       // TODO: a.last_code_update = context.control.pending_block_time();
      a.code_version = code_id;
      a.code.resize( code_size );
      if( code_size > 0 )
         memcpy( (void*)a.code.data(), act.code.data(), code_size );

   });

    /* TODOO:
   const auto& account_sequence = db.get<account_sequence_object, by_name>(act.account);
   db.modify( account_sequence, [&]( auto& aso ) {
      aso.code_sequence += 1;
   });*/


    if (new_size != old_size) {
      context.trx_context.add_ram_usage( act.account, new_size - old_size );
   }
}

void apply_contento_setabi(apply_context& context) {
   auto& db  = context.db;
   auto  act = context.op.as<setabi>();

   // TODOO: context.require_authorization(act.account);

   const auto& account = db.get<account_object,by_name>(act.account);

   int64_t abi_size = act.abi.size();

   int64_t old_size = (int64_t)account.abi.size();
   int64_t new_size = abi_size;

   db.modify( account, [&]( auto& a ) {
      a.abi.resize( abi_size );
      if( abi_size > 0 )
         memcpy( (void*)a.abi.data(), act.abi.data(), abi_size );
   });
    /* TODOO:
   const auto& account_sequence = db.get<account_sequence_object, by_name>(act.account);
   db.modify( account_sequence, [&]( auto& aso ) {
      aso.abi_sequence += 1;
   });
     */

   if (new_size != old_size) {
      context.trx_context.add_ram_usage( act.account, new_size - old_size );
   }
}

} } // namespace contento::chain
