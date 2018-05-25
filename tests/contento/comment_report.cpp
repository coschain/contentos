#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/protocol/contento_operations.hpp>

#include "fixtures/contento_fixture.hpp"

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

// to report a comment
static void report_comment(database &db, std::string reporter, std::string author, std::string permlink, std::string credit, std::string tag, bool ack, bool approved, fc::ecc::private_key key)
{
    signed_transaction tx;
    comment_report_operation report;
    report.reporter = reporter;
    report.author = author;
    report.permlink = permlink;
    report.credit = ASSET( credit );
    report.tag = tag;
    report.is_ack = ack;
    report.approved = approved;
    tx.operations.push_back(report);
    tx.set_expiration( db.head_block_time() + inc_time() );
    tx.sign(key, db.get_chain_id());
    PUSH_TX( db, tx );
}

// to grant or deny admin authority to an account
static void grant_admin(database &db, std::string councillor, fc::ecc::private_key councillor_key, std::string account_name, admin_type type, bool grant_or_deny)
{
    signed_transaction tx;
    admin_grant_operation grant;
    grant.creator = councillor;
    grant.nominee = account_name;
    grant.type = type;
    grant.is_grant = grant_or_deny;
    tx.operations.push_back(grant);
    tx.set_expiration( db.head_block_time() + inc_time() );
    tx.sign(councillor_key, db.get_chain_id());
    PUSH_TX( db, tx );
}

static bool comment_exists(database &db, std::string author, std::string permlink)
{
    return db.find_comment(account_name_type(author), permlink) != 0;
}

BOOST_FIXTURE_TEST_SUITE( comment_report, contento_fixture )

BOOST_AUTO_TEST_CASE( correctness )
{
    // alice published a post. bob replied to alice, and charlie replied to bob.
    ACTORS((alice)(bob)(charlie));
    post_comment(db, "alice", "a001", "hello", "world", "", "life", alice_post_key);
    post_comment(db, "bob", "b001", "", "nice post", "alice", "a001", bob_post_key);
    post_comment(db, "charlie", "c001", "", "yes it is", "bob", "b001", charlie_post_key);
    BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    BOOST_TEST_REQUIRE( comment_exists(db, "bob", "b001") );
    BOOST_TEST_REQUIRE( comment_exists(db, "charlie", "c001") );
    
    // user1 and user2 could report bob, 'coz everyone can report as long as she offorded the credits.
    ACTORS((user1)(user2));
    fund("user1", 100);
    fund("user2", 100);
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user1", "bob", "b001", "1.000 TESTS", "porn", false, false, user1_private_key) );
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user2", "bob", "b001", "2.000 TESTS", "drug", false, false, user2_private_key) );
    
    // user3 must fail to approve the report, since she was not authorized.
    ACTORS((user3));
    fund("user3", 100);
    BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
    
    // grant comment_delete authority to user3
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(0), get_councillor_private_key(0), "user3", admin_type::comment_delete, true) );
    
    // user3 needs authorities from more councillors
    BOOST_REQUIRE_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key), fc::exception );
    
    // user3 should be authorized by at least 3 councillors
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(1), get_councillor_private_key(1), "user3", admin_type::comment_delete, true) );
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(2), get_councillor_private_key(2), "user3", admin_type::comment_delete, true) );
    
    // user3 should be able to judge the report now
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user3", "bob", "b001", "1.000 TESTS", "porn", true, true, user3_private_key) );
    
    // bob's comment and its replies should be gone. alice's post survived.
    BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
    BOOST_TEST_REQUIRE( !comment_exists(db, "bob", "b001") );
    BOOST_TEST_REQUIRE( !comment_exists(db, "charlie", "c001") );
    
    //
    // TODO: check report awards...
    //
    
    // user1 reported @alice/a001
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user1", "alice", "a001", "1.000 TESTS", "porn", false, false, user1_private_key) );
    
    // take user3's comment_delete authority away, and give her commercial authority.
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(0), get_councillor_private_key(0), "user3", admin_type::comment_delete, false) );
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(0), get_councillor_private_key(0), "user3", admin_type::commercial, true) );
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(1), get_councillor_private_key(1), "user3", admin_type::commercial, true) );
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(2), get_councillor_private_key(2), "user3", admin_type::commercial, true) );
    
    // user3 should be lack of authority to judge a report now
    BOOST_REQUIRE_THROW( report_comment(db, "user3", "alice", "a001", "0.000 TESTS", "", true, false, user3_private_key), fc::exception );
    
    // make user3 comment_delete admin again.
    BOOST_REQUIRE_NO_THROW( grant_admin(db, get_councillor_account_name(4), get_councillor_private_key(4), "user3", admin_type::comment_delete, true) );
    
    // admin (i.e. user3) should be able to reject the report for free
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user3", "alice", "a001", "0.000 TESTS", "", true, false, user3_private_key) );
    BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a001") );
}

BOOST_AUTO_TEST_CASE( robustness )
{
    // alice published a post. bob replied.
    ACTORS((alice)(bob));
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
    
    // you cannot report non-existing comments
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "bob", "a002", "0.001 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "b002", "0.001 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "nobody", "xxxxx", "0.001 TESTS", "porn", false, false, user1_private_key), fc::exception );
    BOOST_REQUIRE_NO_THROW( report_comment(db, "user1", "alice", "a002", "0.001 TESTS", "porn", false, false, user1_private_key) );
}

BOOST_AUTO_TEST_SUITE_END()

#endif // IS_TEST_NET
