//#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <contento/chain/account_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/protocol/contento_operations.hpp>

#include "include/mix_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::mixtest;

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

BOOST_FIXTURE_TEST_SUITE( trx_receipt, mix_fixture )

    //1.正常值测试
    //2.边缘值测试
    //3.非法值测试
BOOST_AUTO_TEST_CASE( normal )
{
    //填写要花费的gas
    //发起虚拟机交易
    //检查receipt中的消耗gas，消耗相应gas
    //检查自己的COS余额，减少gas对应COS
    
    //填写要花费的gas
    //发起普通交易
    //检查receipt中的消耗gas，不应消耗gas
    //检查自己的COS余额，不变
   
    //
}

BOOST_AUTO_TEST_CASE( invalid ) 
{
    //填写要花费的gas
    //发起虚拟机交易，执行非法操作（未执行vm就失败）
    //验证交易失败 #怎么知道交易失败？有返回值？
    //检查receipt中的消耗gas，不应消耗gas
    //检查自己的COS余额，不变
    
    //填写要花费的gas
    //发起虚拟机交易，执行非法操作（已执行vm后失败）
    //验证交易失败
    //检查receipt中的消耗gas，消耗相应gas
    //检查自己的COS余额，减少

    //填写要花费的gas，gas=0
    //发起虚拟机交易
    //验证交易失败，gas不足
    //检查自己的COS余额

    //填写要花费的gas，gas=MAX_INT
    //发起虚拟机交易
    //检查receipt中的消耗gas
    //检查自己的COS余额，减少gas对应COS

    //填写要花费的gas，gas<require
    //发起虚拟机交易
    //验证交易失败，gas不足
    //检查receipt中的消耗gas，应该消耗一部分
    //检查自己的COS余额，应该减少一部分
}

BOOST_AUTO_TEST_CASE( testtwo )
{
    // alice published a post. bob replied.  ACTORS((alice)(bob));
    ACTORS((alice)(bob));
    post_comment(db, "alice", "a002", "hello", "world", "", "life", alice_post_key);
    post_comment(db, "bob", "b002", "", "nice post", "alice", "a002", bob_post_key);
    BOOST_TEST_REQUIRE( comment_exists(db, "alice", "a002") );
    BOOST_TEST_REQUIRE( comment_exists(db, "bob", "b002") );
    
    // report fee should be valid and affordable.
    /*
    ACTORS((user1));
    fund("user1", 100);
    BOOST_REQUIRE_THROW( report_comment(db, "user1", "alice", "a002", "0.000 TESTS", "porn", false, false, user1_private_key), fc::exception );
    */
}

BOOST_AUTO_TEST_SUITE_END()

//#endif // IS_TEST_NET
