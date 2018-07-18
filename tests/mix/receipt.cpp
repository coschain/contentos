#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/protocol/contento_operations.hpp>

#include "fixtures/mix_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::test;

static uint64_t inc_time() {
    static uint64_t t = 30;
    return ++t;
}

// to post a comment
static void post_comment(database &db, std::string author, std::string permlink, std::string title, std::string body, std::string parent_author, std::string parent_permlink, fc::ecc::private_key key)
{
    signed_transaction tx;
    comment_operation comment;
    comment.author = author;
    comment.permlink = permlink;
    comment.title = title;
    comment.body = body;
    comment.json_metadata = "";
    comment.parent_author = parent_author;
    comment.parent_permlink = parent_permlink;
    tx.operations.push_back(comment);
    tx.set_expiration( db.head_block_time() + inc_time() );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

static bool comment_exists(database &db, std::string author, std::string permlink)
{
    return db.find_comment(account_name_type(author), permlink) != 0;
}

BOOST_FIXTURE_TEST_SUITE( trx_return_type, mix_fixture )

BOOST_AUTO_TEST_CASE( robustness )
{
    // alice published a post. bob replied.  ACTORS((alice)(bob));
    post_comment(db, "alice", "a002", "hello", "world", "", "life", alice_post_key);
    post_comment(db, "bob", "b002", "", "nice post", "alice", "a002", bob_post_key);
    BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a002") );
    BOOST_TEST_REQUIRE( comment_exists(db, "bob", "b002") );
    
    // report fee should be valid and affordable.
    ACTORS((user1));
    fund("user1", 100);
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "a002", "0.000 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "a002", "-0.000 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "a002", "-1.234 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "a002", "1000000000.000 TESTS", "porn", false, false, user1_private_key), fc::exception );
}

BOOST_AUTO_TEST_SUITE_END()

#endif // IS_TEST_NET
