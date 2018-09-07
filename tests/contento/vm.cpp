#ifdef IS_TEST_NET
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
#include <contento/protocol/exceptions.hpp>

#include <fc/io/fstream.hpp>
#include <fc/io/json.hpp>
#include <fc/compress/zlib.hpp>

#include "fixtures/contento_fixture.hpp"
#include <contento/chain/contract_balance_object.hpp>

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::test;

vm_operation create_setcode(const name& contract_name, const uint8_t compression, const bytes& code) {
    return vm_operation {
        contract_name,
        setcode{
            .account    = contract_name,
            .vmtype     = 0,
            .vmversion  = 0,
            .compression = compression,
            .code       = code
        }
    };
}
vm_operation create_setabi(const name& contract_name, const uint8_t compression, const bytes& abi) {
    return vm_operation {
        contract_name,
        setabi{
            .account    = contract_name,
            .compression = compression,
            .abi        = abi
        }
    };
}

bytes get_code(const std::string& wast_path) {
    std::string wast;
    fc::read_file_contents(wast_path, wast);
    vector<uint8_t> wasm = wast_to_wasm(wast);
    return bytes(wasm.begin(), wasm.end());
}

static transaction_invoice set_code(database &db, fc::ecc::private_key key, const name& contract_name, const std::string& wast_path) {
    signed_transaction tx;

    auto wasm = get_code(wast_path);
    uint8_t compression = 0;
    
    bytes bytes_wasm;

    if(wasm.size() > MAX_UNCOMPRESSION_SIZE){
        std::string uncompressed(wasm.begin(), wasm.end());
        std::string compressed = fc::zlib_compress(uncompressed);
        compression = 1;
        bytes_wasm = bytes(compressed.begin(), compressed.end());
    }
    else {
         bytes_wasm = bytes( wasm.begin(), wasm.end());
    }
    vm_operation vop = create_setcode(contract_name, compression, bytes_wasm);

    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    return PUSH_TX( db, tx );
}

static transaction_invoice set_abi(database &db, fc::ecc::private_key key, const name& contract_name, const std::string& abi_path) {
    signed_transaction tx;

    auto abi = fc::raw::pack(fc::json::from_file(abi_path).as<abi_def>());
    uint8_t compression = 0;

    if(abi.size() > MAX_UNCOMPRESSION_SIZE){
        std::string uncompressed(abi.begin(), abi.end());
        std::string compressed = fc::zlib_compress(uncompressed);
        compression = 1;
        abi = bytes(compressed.begin(), compressed.end());
    }

    vm_operation vop = create_setabi(contract_name, compression, abi);
    
    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    return PUSH_TX( db, tx );
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

bytes param_to_bin(database &db, name contract_name, name action_name, std::string param) {
   fc::variant action_args_var;
   if( !param.empty() ) {
      try {
         action_args_var = json_from_file_or_string(param, fc::json::relaxed_parser);
      } catch (const fc::exception& e) {
         elog("Caught exception while parsing action data: ${param}:  ${e}", ("param", param)("e", e.to_detail_string()) );
         throw;
      }
   }
    //
    if(param == "[\"hello\",\"50 COC\"]"){
        asset s;
        fc::from_variant( action_args_var[1], s );
        
        std::string h;
//        account_name
         //fc::from_variant( action_args_var[0], h );
    }
    
    //
    

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

static transaction_invoice push_action_no_throw(database &db, fc::ecc::private_key key, 
                        const name& caller, const name& contract_name, 
                        const name& action_name, const std::string& action_param, const asset& v) {
   bytes bin = param_to_bin(db, contract_name, action_name, action_param);
   signed_transaction tx;
   vm_operation vop = vm_operation(caller, contract_name, action_name, bin);
    vop.value = v;
    
    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    return PUSH_TX( db, tx );
}

static transaction_invoice push_action(database &db, fc::ecc::private_key key, 
                        const name& caller, const name& contract_name, 
                        const name& action_name, const std::string& action_param, const asset& v) {
    transaction_invoice invoice = push_action_no_throw(db, key, caller, contract_name, action_name, action_param, v);
    if (invoice.vm_error) {
        throw fc::exception(invoice.vm_error_code, "vm_operation_exception");
    }
    return invoice;
}

BOOST_FIXTURE_TEST_SUITE( vm, clean_database_fixture )

BOOST_AUTO_TEST_CASE( hello )
{
    try{
    ACTORS((contento)(hello)(buttnaked));
    
    //fund("hello", 100);
    
    fund("hello", 5000);
    fund("buttnaked", 5000);
    
    set_code(db, hello_private_key, N(hello), "./contracts/hello/hello.wast");
    set_abi(db, hello_private_key, N(hello), "./contracts/hello/hello.abi");

    asset v;
    push_action(db, buttnaked_private_key, N(buttnaked), N(hello), N(hi), "[\"test1\"]",v);
    push_action(db, hello_private_key, N(hello), N(hello), N(hi), "[\"test2\"]",v);

        //set_code(db, buttnaked_private_key, N(buttnaked), "../../tests/contento/contracts/table.wast");
        //set_abi(db, buttnaked_private_key, N(buttnaked), "../../tests/contento/contracts/table.abi");
        
        //BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
        //BOOST_REQUIRE_NO_THROW( set_code(db, hector_post_key, N(hector), code) );
        
        //BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    }
    FC_LOG_AND_RETHROW()
}

    BOOST_AUTO_TEST_CASE( contract_bank_correct )
    {
        try{
        ACTORS((contento)(user1)(user2));
        fund("user1", 50000);//50.000 coc
        const account_object& acct1 = db.get_account( "user1" );
        BOOST_REQUIRE( acct1.balance.amount.value == 50000 );

        fund("user2", 50000);//50.000 coc
        const account_object& acct2 = db.get_account( "user2" );
        BOOST_REQUIRE( acct2.balance.amount.value == 50000 );
        
        set_code(db, user1_private_key, N(user1), "./contracts/hello/hello.wast");
        set_abi(db, user1_private_key, N(user1), "./contracts/hello/hello.abi");
        
        // user2 send coc to contract
        asset v1 = asset::from_string( "39.997 COC" ); // save function consume 0.003 coc, send value consume 0.01 COC, self keep 10000, send to contract 39997
        BOOST_REQUIRE_NO_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(save), "", v1));
        
        // check send result
        const account_object& acct3 = db.get_account( "user2" );
        BOOST_REQUIRE( acct3.balance.amount.value < 10000 ); // self keep 10000 + withdraw 10000 - some gas
        const contract_balance_object& cbo1 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo1.coc_balance.amount.value == 39997 );

        // user2 withdraw 10 coc back
        string a = "[\"user2\",\"10.000 COC\"]";
        asset v2;
        BOOST_REQUIRE_NO_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(withdraw), a,v2));
        
        // check withdraw result
        const account_object& acct4 = db.get_account( "user2" );
        BOOST_REQUIRE( acct4.balance.amount.value < 20000 );  // ??? how much gas?
        const contract_balance_object& cbo2 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo2.coc_balance.amount.value == 29997 );
        
        // user2 send invalid coc to contract, should failed and exception
        auto origin_user = acct4.balance.amount.value;
        auto origin_contract = cbo2.coc_balance.amount.value;

        asset v3 = asset::from_string( "2000.000 COC" );
            BOOST_REQUIRE_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(save), "", v3),fc::exception);
        const account_object& acct5 = db.get_account( "user2" );
        BOOST_REQUIRE( acct5.balance.amount.value < origin_user );// consume gas
        const contract_balance_object& cbo3 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo3.coc_balance.amount.value == origin_contract );


        // user2 withdraw invalid coc from contract, should failed and exception
        a = "[\"user2\",\"2000.000 COC\"]";
        asset v4;
        origin_user = acct5.balance.amount.value;
        BOOST_REQUIRE_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(withdraw), a, v4),fc::exception);
        const account_object& acct6 = db.get_account( "user2" );
        BOOST_REQUIRE( acct6.balance.amount.value < origin_user );// consume gas
        const contract_balance_object& cbo4 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo4.coc_balance.amount.value == origin_contract );

        // user2 send coc to contract by a payprohibited api, should failed and exception
        a = "[\"user2\",\"5.000 COC\"]";
        asset v5 = asset::from_string( "5.000 COC" );
        origin_user = acct6.balance.amount.value;
            BOOST_REQUIRE_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(withdraw), a, v5),fc::exception);
        const account_object& acct7 = db.get_account( "user2" );
        BOOST_REQUIRE( acct7.balance.amount.value < origin_user);// consume gas
        const contract_balance_object& cbo5 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo5.coc_balance.amount.value == origin_contract );

        // user2 send 0 coc to contract by a payprohibited api, it's ok, and withdraw should success
        a = "[\"user2\",\"5.000 COC\"]";
        asset v6 = asset::from_string( "0.000 COC" );
        BOOST_REQUIRE_NO_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(withdraw), a, v6));
        const account_object& acct8 = db.get_account( "user2" );
        BOOST_REQUIRE( acct8.balance.amount.value < 25000 );  // ??? how much gas?
        const contract_balance_object& cbo6 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo6.coc_balance.amount.value == origin_contract - 5000 );

        // user withdraw coc to a no exist user, should failed and exception
         a = "[\"user12345\",\"10.000 COC\"]";
        asset v7;
        origin_user = acct8.balance.amount.value;
            BOOST_REQUIRE_THROW(push_action(db, user2_private_key, N(user2), N(user1), N(withdraw), a,v7),fc::exception);
        const account_object& acct9 = db.get_account( "user2" );
        BOOST_REQUIRE( acct9.balance.amount.value < origin_user );// consume gas
        const contract_balance_object& cbo7 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo7.coc_balance.amount.value == origin_contract - 5000);
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( contract_bank_robust )
{
    try {
        ACTORS((contento)(user1));
        fund("user1", 50000);//50.000 coc
        const account_object& acct1 = db.get_account( "user1" );
        BOOST_REQUIRE( acct1.balance.amount.value == 50000 );
        
        set_code(db, user1_private_key, N(user1), "./contracts/hello/hello.wast");
        set_abi(db, user1_private_key, N(user1), "./contracts/hello/hello.abi");
        
        // user1 send coc to no exist contract, its throw exception at param_to_bin before vm excute
        asset v1 = asset::from_string( "10.000 COC" );
        BOOST_REQUIRE_THROW(push_action(db, user1_private_key, N(user1), N(somecontract), N(save), "", v1),fc::exception);
        
        //  user1 withdraw coc from no exist contract, its throw exception at param_to_bin before vm excute
        string a = "[\"user1\",\"10.000 COC\"]";
        asset v2;
        BOOST_REQUIRE_THROW(push_action(db, user1_private_key, N(user1), N(somecontract), N(withdraw), a, v2),fc::exception);
        
        // pre send coc to contract
        asset v3 = asset::from_string( "40.000 COC" );
        BOOST_REQUIRE_NO_THROW(push_action(db, user1_private_key, N(user1), N(user1), N(save), "", v3));
        const contract_balance_object& cbo3 = db.get_contract_account( "user1" );// user1 is contract name
        BOOST_REQUIRE( cbo3.coc_balance.amount.value == 40000 );

        // no exist user send coc to contract, it's throw exception at verify_authority, before vm excute
        asset v4 = asset::from_string( "10.000 COC" );
        BOOST_REQUIRE_THROW(push_action(db, user1_private_key, N(someuser), N(user1), N(save), "", v4),fc::exception);
        
        // no exist user withdraw coc from contract, it's throw exception at verify_authority, before vm excute
        a = "[\"user1\",\"50.000 COC\"]";
        asset v5;
        BOOST_REQUIRE_THROW(push_action(db, user1_private_key, N(someuser), N(user1), N(withdraw), a, v5),fc::exception);
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( contract_require_auth )
{
    try{
        ACTORS((contento)(hello));
        fund("hello", 50000);//50.000 coc
        const account_object& acct1 = db.get_account( "hello" );
        BOOST_REQUIRE( acct1.balance.amount.value == 50000 );
        
        set_code(db, hello_private_key, N(hello), "./contracts/hello/hello.wast");
        set_abi(db, hello_private_key, N(hello), "./contracts/hello/hello.abi");
        
        asset v;
        push_action(db, hello_private_key, N(hello), N(hello), N(test_auth), "",v);
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( storage )
{
   try {
   ACTORS((contento)(hello)(buttnaked)(storage));
   //fund("hello", 100);

   fund("hello", 5000);
   fund("buttnaked", 5000);
   fund("storage", 5000);

   set_code(db, storage_private_key, N(storage), "./contracts/storage/storage.wast");
   set_abi(db, storage_private_key, N(storage), "./contracts/storage/storage.abi");
   
   asset v;
   push_action(db, storage_private_key, N(storage), N(storage), N(placeoffer),
        "[ \"storage\", \"3.000 COC\", \"921e0c66a8866ca0037fbb628acd5f63f3ba119962c9f5ca68d54b5a70292f36\" ]",v);
   BOOST_REQUIRE_THROW(
      push_action(db, hello_private_key, N(hello), N(storage), N(placeoffer),
                 "[ \"storage\", \"3.000 COC\", \"921e0c66a8866ca0037fbb628acd5f63f3ba119962c9f5ca68d54b5a70292f36\" ]",v), 
      fc::exception
   );
   push_action(db, storage_private_key, N(storage), N(storage), N(canceloffer), 
        "[\"921e0c66a8866ca0037fbb628acd5f63f3ba119962c9f5ca68d54b5a70292f36\"]",v);
   push_action(db, hello_private_key, N(hello), N(storage), N(placeoffer), 
               "[ \"hello\", \"3.000 COC\", \"921e0c66a8866ca0037fbb628acd5f63f3ba119962c9f5ca68d54b5a70292f36\" ]",v);

   }
   FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_SUITE_END()

#endif // IS_TEST_NET
