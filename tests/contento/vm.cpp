//#ifdef IS_TEST_NET
#include <regex>
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/chain/abi_serializer.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/protocol/types.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/chain/abi_def.hpp>
#include <contento/chain/contract_types.hpp>
#include <contento/chain/wast_to_wasm.hpp>

#include <fc/io/fstream.hpp>
#include <fc/io/json.hpp>

#include "fixtures/contento_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::test;

vm_operation create_setcode(const namex& contract_name, const bytes& code) {
    return vm_operation {
        contract_name,
        setcode{
            .account    = contract_name,
            .vmtype     = 0,
            .vmversion  = 0,
            .code       = code
        }
    };
}
vm_operation create_setabi(const namex& contract_name, const abi_def& abi) {
    return vm_operation {
        contract_name,
        setabi{
            .account    = contract_name,
            .abi        = fc::raw::pack(abi)
        }
    };
}

bytes get_code(const std::string& wast_path) {
    std::string wast;
    fc::read_file_contents(wast_path, wast);
    vector<uint8_t> wasm = wast_to_wasm(wast);
    return bytes(wasm.begin(), wasm.end());
}

static void set_code(database &db, fc::ecc::private_key key, const namex& contract_name, const std::string& wast_path) {
    signed_transaction tx;
    vm_operation vop = create_setcode(contract_name, get_code(wast_path));

    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

static void set_abi(database &db, fc::ecc::private_key key, const namex& contract_name, const std::string& abi_path) {
   signed_transaction tx;
   vm_operation vop = create_setabi(contract_name, fc::json::from_file(abi_path).as<abi_def>());
    
    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

fc::variant json_from_file_or_string(const string& file_or_str, fc::json::parse_type ptype = fc::json::legacy_parser)
{
   std::regex r("^[ \t]*[\{\[]");
   if ( !std::regex_search(file_or_str, r) && fc::is_regular_file(file_or_str) ) {
      return fc::json::from_file(file_or_str, ptype);
   } else {
      return fc::json::from_string(file_or_str, ptype);
   }
}

bytes param_to_bin(database &db, namex contract_name, name action_name, std::string param) {
   fc::variant action_args_var;
   if( !param.empty() ) {
      try {
         action_args_var = json_from_file_or_string(param, fc::json::relaxed_parser);
      } catch (const fc::exception& e) {
         elog("Caught exception while parsing action data: ${param}:  ${e}", ("param", param)("e", e.to_detail_string()) );
         throw;
      }
   }

   const auto contract_acc = db.get_account(contract_name);
   abi_def abi;
   bytes result;
   if(abi_serializer::to_abi(contract_acc.abi, abi)) {
      abi_serializer abis(abi);
      auto action_type = abis.get_action_type(action_name);
      FC_ASSERT( !action_type.empty(), "unknown action ${action} in contract ${contract}", 
                                       ("action", action_name)("contract", contract_name) );
                                    
      try {
         result = abis.variant_to_binary(action_type, action_args_var);
      } catch (const fc::exception& e) {
         elog("Caught exception while serializing action data: ${param}:  ${e}", ("param", param)("e", e.to_detail_string()) );
         throw;
      }  
   } else {
      FC_ASSERT(false, "No ABI found for contract: ${contract}", ("contract", contract_name));
   }   
   return result;                        
}

static void push_action(database &db, fc::ecc::private_key key, 
                        const namex& caller, const namex& contract_name, 
                        const name& action_name, const std::string& action_param) {
   bytes bin = param_to_bin(db, contract_name, action_name, action_param);
   signed_transaction tx;
   vm_operation vop = vm_operation(caller, contract_name, action_name, bin);
    
    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

BOOST_FIXTURE_TEST_SUITE( vm, contento_fixture )

BOOST_AUTO_TEST_CASE( setcodes )
{
    ACTORS((contento)(hello)(buttnaked));
    //fund("hello", 100);
    set_code(db, hello_private_key, N(hello), "../contracts/hello/hello.wast");
    set_abi(db, hello_private_key, N(hello), "../contracts/hello/hello.abi");

    push_action(db, buttnaked_private_key, N(buttnaked), N(hello), N(hi), "[\"buttnaked\"]");
    push_action(db, hello_private_key, N(hello), N(hello), N(hi), "[\"buttnaked\"]");
    
    //BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
    //BOOST_REQUIRE_NO_THROW( set_code(db, hector_post_key, N(hector), code) );
    
    //BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    
}

BOOST_AUTO_TEST_SUITE_END()

//#endif // IS_TEST_NET
