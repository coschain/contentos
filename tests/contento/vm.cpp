//#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/protocol/types.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/chain/abi_def.hpp>
#include <contento/chain/contract_types.hpp>

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

static void set_code(database &db, fc::ecc::private_key key, const name& contract_name, const bytes& code) {
    signed_transaction tx;
    vm_operation vop = create_setcode(contract_name, code);

    tx.operations.push_back(vop);
    tx.set_expiration( db.head_block_time() + 30 );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

BOOST_FIXTURE_TEST_SUITE( vm, contento_fixture )

BOOST_AUTO_TEST_CASE( setcode )
{
    ACTORS((alice)(bob)(charlie));
    fund("alice", 100);
    bytes code; // TODOO:
    set_code(db, alice_post_key, N(alice), code);
    
    //BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
    //BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(0), get_councillor_private_key(0), "user3", admin_type::comment_delete, true) );
    
    //BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    
}

BOOST_AUTO_TEST_SUITE_END()

//#endif // IS_TEST_NET
