//#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/protocol/types.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/chain/abi_def.hpp>
#include <contento/chain/contract_types.hpp>
#include <contento/chain/wast_to_wasm.hpp>

#include <fc/io/fstream.hpp>

#include "fixtures/contento_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::test;

vm_operation create_setcode(const name& contract_name, const bytes& code) {
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
vm_operation create_setabi(const name& contract_name, const abi_def& abi) {
    return vm_operation {
        contract_name,
        setabi{
            .account    = contract_name,
            .abi        = fc::raw::pack(abi)
        }
    };
}

bytes get_code() {
    std::string wast;
    fc::read_file_contents("/Users/jesse/eos/build/contracts/hello/hello.wast", wast);
    vector<uint8_t> wasm = wast_to_wasm(wast);
    return bytes(wasm.begin(), wasm.end());
}

static void set_code(database &db, fc::ecc::private_key key, const name& contract_name) {
    signed_transaction tx;
    vm_operation vop = create_setcode(contract_name, get_code());

    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

BOOST_FIXTURE_TEST_SUITE( vm, contento_fixture )

BOOST_AUTO_TEST_CASE( setcodes )
{
    ACTORS((contento)(hello));
    //fund("hello", 100);
    set_code(db, hello_private_key, N(hello));
    
    //BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
    //BOOST_REQUIRE_NO_THROW( set_code(db, hector_post_key, N(hector), code) );
    
    //BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    
}

BOOST_AUTO_TEST_SUITE_END()

//#endif // IS_TEST_NET
