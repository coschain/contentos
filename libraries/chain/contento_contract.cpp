/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <contento/chain/contento_contract.hpp>

#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/contract_types.hpp>

#include <contento/chain/wasm_interface.hpp>

#include <fc/compress/zlib.hpp>

#include <contento/chain/contract_balance_object.hpp>


namespace contento { namespace chain {

void apply_contento_setcode(apply_context& context) {

   auto& db = context.db;
   auto  act = context.op.as<setcode>();
   // TODOO: context.require_authorization(act.account);

   FC_ASSERT( act.vmtype == 0 );
   FC_ASSERT( act.vmversion == 0 );

   if(act.compression != 0){
       std::string compressed(act.code.begin(), act.code.end());
       std::string uncompressed = fc::zlib_decompress( compressed );
       auto code = bytes(uncompressed.begin(), uncompressed.end());
       act.code = code;
   }

   fc::sha256 code_id; /// default ID == 0

   if( act.code.size() > 0 ) {
     code_id = fc::sha256::hash( act.code.data(), (uint32_t)act.code.size() );
     wasm_interface::validate(context.control, act.code);
   }

   const auto& account = db.get<account_object,by_name>(act.account);
    // todo: get contract from contract_map
   int64_t code_size = (int64_t)act.code.size();
   int64_t old_size  = account.all_contract.get_contract_code_size() * config::setcode_ram_bytes_multiplier;
   int64_t new_size  = code_size * config::setcode_ram_bytes_multiplier;

   FC_ASSERT( account.all_contract.get_code_version(act.contract) != code_id, "contract is already running this version of code" );

    // todo: set contract to contract_map
   db.modify( account, [&]( auto& a ) {
      /** TODO: consider whether a microsecond level local timestamp is sufficient to detect code version changes*/
      // TODO: update setcode message to include the hash, then validate it in validate
       // TODO: a.last_code_update = context.control.pending_block_time();
       a.all_contract.add_contract_code(act.contract,code_id,act.code,code_size);

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

    if(act.compression != 0){
        std::string compressed(act.abi.begin(), act.abi.end());
        std::string uncompressed = fc::zlib_decompress( compressed );
        auto code = bytes(uncompressed.begin(), uncompressed.end());
        act.abi = code;
    }

   int64_t abi_size = act.abi.size();
 // todo: get contract from contract_map
    int64_t old_size = account.all_contract.get_contract_abi_size();
   int64_t new_size = abi_size;
// todo: set contract to contract_map
   db.modify( account, [&]( auto& a ) {
       a.all_contract.add_contract_abi(act.contract,act.abi,abi_size);
   });
    // todo: contract bank need change, because contract name can be same
     const auto& by_bank_name_idx = db.get_index< contract_balance_index >().indices().get< by_name >();
    auto bank_itr = by_bank_name_idx.find( context.op.caller );
    if(bank_itr == by_bank_name_idx.end()){
        db.create< contract_balance_object > ([&]( auto& cbo ) {
            // here is system contract, contract_name is system pre-defined, actual target contract name is in the caller
            cbo.contract_name = context.op.caller;
        } );
    }
   
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
