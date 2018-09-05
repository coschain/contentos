#ifdef IS_TEST_NET2
#include <boost/test/unit_test.hpp>

#include <contento/protocol/exceptions.hpp>

#include <contento/chain/database.hpp>
#include <contento/chain/database_exceptions.hpp>
#include <contento/chain/contento_objects.hpp>

#include "../common/database_fixture.hpp"
#include <iostream>
#include <stdexcept>



using namespace contento;
using namespace contento::chain;
using namespace contento::protocol;


BOOST_FIXTURE_TEST_SUITE( cntentos_operation_tests, clean_database_fixture )

BOOST_AUTO_TEST_CASE( account_create_authorities_test )
{
    try
    {
        BOOST_TEST_MESSAGE( "Testing: account_create_authorities" );
        account_create_operation op;
        op.creator = "alice";
        op.new_account_name = "bob";

        flat_set< account_name_type > auths;
        flat_set< account_name_type > expected;

        BOOST_TEST_MESSAGE( "--- Testing owner authority" );
        op.get_required_owner_authorities( auths );
        BOOST_REQUIRE( auths == expected );

        BOOST_TEST_MESSAGE( "--- Testing active authority" );
        expected.insert( "alice" );
        op.get_required_active_authorities( auths );
        BOOST_REQUIRE( auths == expected );

        BOOST_TEST_MESSAGE( "--- Testing posting authority" );
        expected.clear();
        auths.clear();
        op.get_required_posting_authorities( auths );
        BOOST_REQUIRE( auths == expected );
    }
    FC_LOG_AND_RETHROW()
}


BOOST_AUTO_TEST_CASE( account_create_test )
{
    try
    {
        BOOST_TEST_MESSAGE( "Testing: account_create" );

        signed_transaction tx;
        private_key_type priv_key = generate_private_key( "alice" );

        const account_object& init = db.get_account( CONTENTO_INIT_MINER_NAME );
        asset init_starting_balance = init.balance;
        BOOST_REQUIRE(init_starting_balance > asset(0, COC_SYMBOL));

        BOOST_TEST_MESSAGE( "Testing: account_create" );
        const auto& gpo = db.get_dynamic_global_properties();

        account_create_operation op;

        op.fee = asset( 100, COC_SYMBOL );
        op.new_account_name = "alice";
        op.creator = CONTENTO_INIT_MINER_NAME;
        op.owner = authority( 1, priv_key.get_public_key(), 1 );
        op.active = authority( 2, priv_key.get_public_key(), 2 );
        op.memo_key = priv_key.get_public_key();
        op.json_metadata = "{\"foo\":\"bar\"}";

        BOOST_TEST_MESSAGE( "--- Test normal account creation" );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( init_account_priv_key, db.get_chain_id() );
        tx.validate();
        db.push_transaction( tx, 0 );

        const account_object& acct = db.get_account( "alice" );
        const account_authority_object& acct_auth = db.get< account_authority_object, by_account >( "alice" );

//        auto vest_shares = gpo.total_vesting_shares;
//        auto vests = gpo.total_vesting_fund_coc;

        BOOST_REQUIRE( acct.name == "alice" );
        BOOST_REQUIRE( acct_auth.owner == authority( 1, priv_key.get_public_key(), 1 ) );
        BOOST_REQUIRE( acct_auth.active == authority( 2, priv_key.get_public_key(), 2 ) );
        BOOST_REQUIRE( acct.memo_key == priv_key.get_public_key() );
        BOOST_REQUIRE( acct.proxy == "" );
        BOOST_REQUIRE( acct.created == db.head_block_time() );
        BOOST_REQUIRE( acct.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( acct.vesting_shares.amount.value == ASSET( "0.100 VESTS" ).amount.value);
        BOOST_REQUIRE( acct.id._id == acct_auth.id._id );

        BOOST_REQUIRE( acct.vesting_withdraw_rate.amount.value == ASSET( "0.000 VESTS" ).amount.value );
        BOOST_REQUIRE( ( init_starting_balance - ASSET( "0.100 COC" ) ).amount.value == init.balance.amount.value );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test failure of duplicate account creation" );
        BOOST_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), fc::exception );

        BOOST_REQUIRE( acct.name == "alice" );
        BOOST_REQUIRE( acct_auth.owner == authority( 1, priv_key.get_public_key(), 1 ) );
        BOOST_REQUIRE( acct_auth.active == authority( 2, priv_key.get_public_key(), 2 ) );
        BOOST_REQUIRE( acct.memo_key == priv_key.get_public_key() );
        BOOST_REQUIRE( acct.proxy == "" );
        BOOST_REQUIRE( acct.created == db.head_block_time() );
        BOOST_REQUIRE( acct.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( acct.vesting_shares.amount.value == ASSET( "0.100 VESTS" ).amount.value);
        BOOST_REQUIRE( acct.id._id == acct_auth.id._id );

        BOOST_REQUIRE( acct.vesting_withdraw_rate.amount.value == ASSET( "0.000 VESTS" ).amount.value );
        BOOST_REQUIRE( ( init_starting_balance - ASSET( "0.100 COC" ) ).amount.value == init.balance.amount.value );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test failure when creator cannot cover fee" );
        tx.signatures.clear();
        tx.operations.clear();
        op.fee = asset( db.get_account( CONTENTO_INIT_MINER_NAME ).balance.amount + 1, COC_SYMBOL );
        op.new_account_name = "bob";
        tx.operations.push_back( op );
        tx.sign( init_account_priv_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );
        validate_database();
    }
     FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( transfer_authority_test )
{
    try {
        ACTORS( (alice)(bob) )
        fund( "alice", 10000 );

        BOOST_TEST_MESSAGE( "Testing: transfer_authorities" );

        transfer_operation op;
        op.from = "alice";
        op.to = "bob";
        op.amount = ASSET( "2.500 COC" );

        signed_transaction tx;
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );

        BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_active_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the account's authority" );
        tx.sign( alice_post_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_active_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
        tx.signatures.clear();
        // the alice private key came from ACTOR MARCO extend
        tx.sign( alice_private_key, db.get_chain_id() );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_irrelevant_sig );

        BOOST_TEST_MESSAGE( "--- Test success with witness signature" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( transfer_test )
{
    try {
        ACTORS( (alice)(bob) )
        fund( "alice", 10000 );

        BOOST_TEST_MESSAGE( "Testing: transfer" );

        BOOST_REQUIRE( alice.balance.amount.value == ASSET( "10.000 COC" ).amount.value );
        BOOST_REQUIRE( bob.balance.amount.value == ASSET(" 0.000 COC" ).amount.value );

        signed_transaction tx;
        transfer_operation op;

        op.from = "alice";
        op.to = "bob";
        op.amount = ASSET( "5.000 COC" );

        BOOST_TEST_MESSAGE( "--- Test normal transaction" );
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        BOOST_REQUIRE( alice.balance.amount.value == ASSET( "5.000 COC" ).amount.value );
        BOOST_REQUIRE( bob.balance.amount.value == ASSET( "5.000 COC" ).amount.value );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Generating a block" );
        generate_block();

        const auto& new_alice = db.get_account( "alice" );
        const auto& new_bob = db.get_account( "bob" );

        BOOST_REQUIRE( new_alice.balance.amount.value == ASSET( "5.000 COC" ).amount.value );
        BOOST_REQUIRE( new_bob.balance.amount.value == ASSET( "5.000 COC" ).amount.value );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test emptying an account" );
        tx.signatures.clear();
        tx.operations.clear();
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, database::skip_transaction_dupe_check );

        BOOST_REQUIRE( new_alice.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( new_bob.balance.amount.value == ASSET( "10.000 COC" ).amount.value );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test transferring non-existent funds" );
        tx.signatures.clear();
        tx.operations.clear();
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), fc::exception );

        BOOST_REQUIRE( new_alice.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( new_bob.balance.amount.value == ASSET( "10.000 COC" ).amount.value );
        validate_database();

    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( subject_authority_test )
{
    try{
        BOOST_TEST_MESSAGE( "Testing: subject_authorities" );
        ACTORS( (alice)(bob) );
        generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );

        comment_operation op;
        op.author = "alice";
        op.permlink = "lorem";
        op.category = "poem";
        op.title = "Lorem Ipsum";
        op.body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
        op.json_metadata = "{\"foo\":\"bar\"}";

        signed_transaction tx;
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );

        BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_posting_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
        tx.sign( alice_post_key, db.get_chain_id() );
        tx.sign( alice_post_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

        BOOST_TEST_MESSAGE( "--- Test success with post signature" );
        tx.signatures.clear();
        tx.sign( alice_post_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_irrelevant_sig );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the creator's authority" );
        tx.signatures.clear();
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_posting_auth );

        validate_database();

    }
     FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( comment_authority_test )
{
    try{
        BOOST_TEST_MESSAGE( "Testing: comment_authorities" );
        ACTORS( (alice)(bob) );
        generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );

        // push a subject
        comment_operation sop;
        sop.author = "alice";
        sop.permlink = "lorem";
        sop.category = "poem";
        sop.title = "Lorem Ipsum";
        sop.body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
        sop.json_metadata = "{\"foo\":\"bar\"}";

        signed_transaction tx;
        tx.operations.push_back( sop );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_post_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );
        generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );


        tx.signatures.clear();
        tx.operations.clear();

        comment_operation op;
        op.parent_author =  "alice";
        op.parent_permlink = "lorem";
        op.author = "bob";
        op.permlink = "lorem2";
        op.body = "Lorem ipsum dolor sit amet";
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );

        BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_posting_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
        tx.sign( bob_post_key, db.get_chain_id() );
        tx.sign( bob_post_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

        BOOST_TEST_MESSAGE( "--- Test success with post signature" );
        tx.signatures.clear();
        tx.sign( bob_post_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_irrelevant_sig );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the creator's authority" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_posting_auth );

        validate_database();

    }
     FC_LOG_AND_RETHROW()
}


BOOST_AUTO_TEST_CASE( comment_test )
{
    try
    {
        BOOST_TEST_MESSAGE( "Testing: subject" );

        ACTORS( (alice)(bob)(sam) )
        generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );

        comment_operation op;
        op.author = "alice";
        op.permlink = "lorem";
        op.category = "poem";
        op.title = "Lorem Ipsum";
        op.body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
        op.json_metadata = "{\"foo\":\"bar\"}";

        signed_transaction tx;
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );

        // BOOST_TEST_MESSAGE( "--- Test Alice posting a subject" );
        tx.operations.push_back( op );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        const comment_object& alice_subject = db.get_comment( "alice", string( "lorem" ) );

        BOOST_REQUIRE( alice_subject.author == op.author );
        BOOST_REQUIRE( to_string( alice_subject.permlink ) == op.permlink );
        BOOST_REQUIRE( to_string( alice_subject.parent_permlink ) == op.parent_permlink );
        BOOST_REQUIRE( alice_subject.last_update == db.head_block_time() );
        BOOST_REQUIRE( alice_subject.created == db.head_block_time() );
        BOOST_REQUIRE( alice_subject.net_rshares.value == 0 );
        BOOST_REQUIRE( alice_subject.abs_rshares.value == 0 );
        BOOST_REQUIRE( alice_subject.cashout_time == fc::time_point_sec( db.head_block_time() + fc::seconds( CONTENTO_CASHOUT_WINDOW_SECONDS ) ) );
        BOOST_REQUIRE( to_string( alice_subject.title ) == op.title );
        BOOST_REQUIRE( to_string( alice_subject.body ) == op.body );

        validate_database();

        BOOST_TEST_MESSAGE( "--- Test Bob posting a subject on a non-existent subject" );
        op.author = "bob";
        op.permlink = "ipsum";
        op.parent_author = "alice";
        op.parent_permlink = "foobar";

        tx.signatures.clear();
        tx.operations.clear();
        tx.operations.push_back( op );
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

        BOOST_TEST_MESSAGE( "--- Test Bob posting a comment on Alice's subject" );
        op.parent_permlink = "lorem";

        tx.signatures.clear();
        tx.operations.clear();
        tx.operations.push_back( op );
        tx.sign( bob_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        const comment_object& bob_comment = db.get_comment( "bob", string( "ipsum" ) );

        BOOST_REQUIRE( bob_comment.author == op.author );
        BOOST_REQUIRE( to_string( bob_comment.permlink ) == op.permlink );
        BOOST_REQUIRE( bob_comment.parent_author == op.parent_author );
        BOOST_REQUIRE( to_string( bob_comment.parent_permlink ) == op.parent_permlink );
        BOOST_REQUIRE( bob_comment.last_update == db.head_block_time() );
        BOOST_REQUIRE( bob_comment.created == db.head_block_time() );
        BOOST_REQUIRE( bob_comment.net_rshares.value == 0 );
        BOOST_REQUIRE( bob_comment.abs_rshares.value == 0 );
        BOOST_REQUIRE( bob_comment.cashout_time == bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        BOOST_REQUIRE( bob_comment.root_comment == alice_subject.id );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test Sam posting a comment on Bob's comment" );

        op.author = "sam";
        op.permlink = "dolor";
        op.parent_author = "bob";
        op.parent_permlink = "ipsum";

        tx.signatures.clear();
        tx.operations.clear();
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        const comment_object& sam_comment = db.get_comment( "sam", string( "dolor" ) );

        BOOST_REQUIRE( sam_comment.author == op.author );
        BOOST_REQUIRE( to_string( sam_comment.permlink ) == op.permlink );
        BOOST_REQUIRE( sam_comment.parent_author == op.parent_author );
        BOOST_REQUIRE( to_string( sam_comment.parent_permlink ) == op.parent_permlink );
        BOOST_REQUIRE( sam_comment.last_update == db.head_block_time() );
        BOOST_REQUIRE( sam_comment.created == db.head_block_time() );
        BOOST_REQUIRE( sam_comment.net_rshares.value == 0 );
        BOOST_REQUIRE( sam_comment.abs_rshares.value == 0 );
        BOOST_REQUIRE( sam_comment.cashout_time == sam_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        BOOST_REQUIRE( sam_comment.root_comment == alice_subject.id );
        validate_database();

        generate_blocks( 60 * 5 / CONTENTO_BLOCK_INTERVAL + 1 );

        BOOST_TEST_MESSAGE( "--- Test modifying a comment" );
        const auto& mod_sam_comment = db.get_comment( "sam", string( "dolor" ) );
        // const auto& mod_bob_comment = db.get_comment( "bob", string( "ipsum" ) );
        // const auto& mod_alice_comment = db.get_comment( "alice", string( "lorem" ) );
        fc::time_point_sec created = mod_sam_comment.created;

        db.modify( mod_sam_comment, [&]( comment_object& com )
        {
            com.net_rshares = 10;
            com.abs_rshares = 10;
        });

        tx.signatures.clear();
        tx.operations.clear();
        op.title = "foo";
        op.body = "bar";
        op.json_metadata = "{\"bar\":\"foo\"}";
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( sam_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        BOOST_REQUIRE( mod_sam_comment.author == op.author );
        BOOST_REQUIRE( to_string( mod_sam_comment.permlink ) == op.permlink );
        BOOST_REQUIRE( mod_sam_comment.parent_author == op.parent_author );
        BOOST_REQUIRE( to_string( mod_sam_comment.parent_permlink ) == op.parent_permlink );
        BOOST_REQUIRE( mod_sam_comment.last_update == db.head_block_time() );
        BOOST_REQUIRE( mod_sam_comment.created == created );
        BOOST_REQUIRE( mod_sam_comment.cashout_time == mod_sam_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test spam subjects" );

        op.permlink = "sit";
        op.category = "poem";
        op.parent_permlink = "";
        op.parent_author = "";
        tx.operations.clear();
        tx.signatures.clear();
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        generate_blocks( 60 * 4 / CONTENTO_BLOCK_INTERVAL );

        op.permlink = "amet";
        tx.operations.clear();
        tx.signatures.clear();
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception);
        validate_database();

        generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL);

        db.push_transaction( tx, 0 );
        validate_database();

        BOOST_TEST_MESSAGE( "--- Test spam comments" );
        generate_blocks( 21 / CONTENTO_BLOCK_INTERVAL);

        op.permlink = "comamet";
        op.parent_permlink = "amet";
        op.parent_author = "sam";
        tx.operations.clear();
        tx.signatures.clear();
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );
        generate_block();
        tx.operations.clear();
        tx.signatures.clear();
        op.permlink = "comamet2";
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception);

        generate_blocks( 21 / CONTENTO_BLOCK_INTERVAL);
        validate_database();
        tx.operations.clear();
        tx.signatures.clear();
        op.permlink = "comamet3";
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );
        tx.sign( sam_private_key, db.get_chain_id() );

        db.push_transaction( tx, 0 );

    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( comment_delete_test )
{
    try {
        BOOST_TEST_MESSAGE( "Testing: comment_delete_test" );
        ACTORS( (alice) )
        generate_block();

        vest( "alice", ASSET( "1000.000 COC" ) );

        generate_block();

        signed_transaction tx;
        comment_operation comment;

        comment.author = "alice";
        comment.permlink = "test1";
        comment.title = "test";
        comment.body = "foo bar";
        comment.category = "article";

        tx.operations.push_back( comment );
        tx.set_expiration( db.head_block_time() + CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        BOOST_TEST_MESSAGE( "--- Test failure deleting a comment past cashout" );
        generate_blocks( CONTENTO_MIN_ROOT_COMMENT_INTERVAL.to_seconds() / CONTENTO_BLOCK_INTERVAL );

        tx.clear();
        tx.operations.push_back( comment );
        tx.set_expiration( db.head_block_time() + CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        generate_blocks( CONTENTO_CASHOUT_WINDOW_SECONDS / CONTENTO_BLOCK_INTERVAL );
        BOOST_REQUIRE( db.get_comment( "alice", string( "test1" ) ).cashout_time == fc::time_point_sec::maximum() );

        delete_comment_operation op;
        op.author = "alice";
        op.permlink = "test1";

        tx.clear();
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::assert_exception );


        BOOST_TEST_MESSAGE( "--- Test failure deleting a comment with a reply" );

        comment.permlink = "test2";
        comment.parent_author = "alice";
        comment.parent_permlink = "test1";
        tx.clear();
        tx.operations.push_back( comment );
        tx.set_expiration( db.head_block_time() + CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        generate_blocks( CONTENTO_MIN_ROOT_COMMENT_INTERVAL.to_seconds() / CONTENTO_BLOCK_INTERVAL );
        comment.permlink = "test3";
        comment.parent_permlink = "test2";
        tx.clear();
        tx.operations.push_back( comment );
        tx.set_expiration( db.head_block_time() + CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        op.permlink = "test2";
        tx.clear();
        tx.operations.push_back( op );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::assert_exception );

        validate_database();
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( vote_test )
{
   try
   {
        BOOST_TEST_MESSAGE( "Testing: vote_test" );

        ACTORS( (alice)(bob)(sam)(dave) )
        generate_block();

        vest( "alice", ASSET( "10.000 COC" ) );
        validate_database();
        vest( "bob" , ASSET( "10.000 COC" ) );
        vest( "sam" , ASSET( "10.000 COC" ) );
        vest( "dave" , ASSET( "10.000 COC" ) );
        generate_block();

        const auto& vote_idx = db.get_index< comment_vote_index >().indices().get< by_comment_voter >();

        {
            const auto& alice = db.get_account( "alice" );

            signed_transaction tx;
            comment_operation comment_op;
            comment_op.author = "alice";
            comment_op.permlink = "foo";
            comment_op.category = "test";
            comment_op.title = "bar";
            comment_op.body = "foo bar";
            tx.operations.push_back( comment_op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            BOOST_TEST_MESSAGE( "--- Testing voting on a non-existent comment" );

            tx.operations.clear();
            tx.signatures.clear();

            vote_operation op;
            op.voter = "alice";
            op.author = "bob";
            op.permlink = "foo";
            op.weight = CONTENTO_100_PERCENT;
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );

            CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

            validate_database();

            BOOST_TEST_MESSAGE( "--- Testing voting with a weight of 0" );

            op.weight = (int16_t) 0;
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );

            CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

            validate_database();

            BOOST_TEST_MESSAGE( "--- Testing success" );

            auto old_voting_power = alice.voting_power;

            op.weight = CONTENTO_100_PERCENT;
            op.author = "alice";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );

            db.push_transaction( tx, 0 );

            auto& alice_comment = db.get_comment( "alice", string( "foo" ) );
            auto itr = vote_idx.find( std::make_tuple( alice_comment.id, alice.id ) );
            int64_t max_vote_denom = ( db.get_dynamic_global_properties().vote_power_reserve_rate * CONTENTO_VOTE_REGENERATION_SECONDS ) / (60*60*24);

            BOOST_REQUIRE( alice.voting_power == old_voting_power - ( ( old_voting_power + max_vote_denom - 1 ) / max_vote_denom ) );
            BOOST_REQUIRE( alice.last_vote_time == db.head_block_time() );
            BOOST_REQUIRE( alice_comment.net_rshares.value == alice.vesting_shares.amount.value * ( old_voting_power - alice.voting_power ) / CONTENTO_100_PERCENT );
            BOOST_REQUIRE( alice_comment.cashout_time == alice_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( itr->rshares == alice.vesting_shares.amount.value * ( old_voting_power - alice.voting_power ) / CONTENTO_100_PERCENT );
            BOOST_REQUIRE( itr != vote_idx.end() );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test reduced power for quick voting" );

            generate_blocks( db.head_block_time() + CONTENTO_MIN_VOTE_INTERVAL_SEC );

            old_voting_power = db.get_account( "alice" ).voting_power;

            comment_op.author = "bob";
            comment_op.permlink = "foo";
            comment_op.title = "bar";
            comment_op.body = "foo bar";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( comment_op );
            tx.sign( bob_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            op.weight = CONTENTO_100_PERCENT / 2;
            op.voter = "alice";
            op.author = "bob";
            op.permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            const auto& bob_comment = db.get_comment( "bob", string( "foo" ) );
            itr = vote_idx.find( std::make_tuple( bob_comment.id, alice.id ) );

            BOOST_REQUIRE( db.get_account( "alice" ).voting_power == old_voting_power - ( ( old_voting_power + max_vote_denom - 1 ) * CONTENTO_100_PERCENT / ( 2 * max_vote_denom * CONTENTO_100_PERCENT ) ) );
            BOOST_REQUIRE( bob_comment.net_rshares.value == alice.vesting_shares.amount.value * ( old_voting_power - db.get_account( "alice" ).voting_power ) / CONTENTO_100_PERCENT );
            BOOST_REQUIRE( bob_comment.cashout_time == bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( itr != vote_idx.end() );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test payout time extension on vote" );

            old_voting_power = db.get_account( "bob" ).voting_power;
            auto old_abs_rshares = db.get_comment( "alice", string( "foo" ) ).abs_rshares.value;

            generate_blocks( db.head_block_time() + fc::seconds( ( CONTENTO_CASHOUT_WINDOW_SECONDS / 2 ) ), true );

            const auto& new_bob = db.get_account( "bob" );
            const auto& new_alice_comment = db.get_comment( "alice", string( "foo" ) );

            op.weight = CONTENTO_100_PERCENT;
            op.voter = "bob";
            op.author = "alice";
            op.permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( bob_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            itr = vote_idx.find( std::make_tuple( new_alice_comment.id, new_bob.id ) );
            auto new_cashout_time = db.head_block_time().sec_since_epoch() + CONTENTO_CASHOUT_WINDOW_SECONDS;

            BOOST_REQUIRE( new_bob.voting_power == CONTENTO_100_PERCENT - ( ( CONTENTO_100_PERCENT + max_vote_denom - 1 ) / max_vote_denom ) );
            BOOST_REQUIRE( new_alice_comment.net_rshares.value == old_abs_rshares + new_bob.vesting_shares.amount.value * ( old_voting_power - new_bob.voting_power ) / CONTENTO_100_PERCENT );
            BOOST_REQUIRE( new_alice_comment.cashout_time == new_alice_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( itr != vote_idx.end() );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test negative vote" );

            const auto& new_sam = db.get_account( "sam" );
            const auto& new_bob_comment = db.get_comment( "bob", string( "foo" ) );

            old_abs_rshares = new_bob_comment.abs_rshares.value;

            op.weight = -1 * CONTENTO_100_PERCENT / 2;
            op.voter = "sam";
            op.author = "bob";
            op.permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( sam_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            itr = vote_idx.find( std::make_tuple( new_bob_comment.id, new_sam.id ) );
            new_cashout_time = db.head_block_time().sec_since_epoch() + CONTENTO_CASHOUT_WINDOW_SECONDS;
            auto sam_weight = ( ( fc::uint128_t( new_sam.vesting_shares.amount.value ) * ( ( CONTENTO_100_PERCENT + max_vote_denom - 1 ) / ( 2 * max_vote_denom ) ) ) / CONTENTO_100_PERCENT ).to_uint64();

            BOOST_REQUIRE( new_sam.voting_power == CONTENTO_100_PERCENT - ( ( CONTENTO_100_PERCENT + max_vote_denom - 1 ) / ( 2 * max_vote_denom ) ) );
            BOOST_REQUIRE( new_bob_comment.net_rshares.value == old_abs_rshares - sam_weight );
            BOOST_REQUIRE( new_bob_comment.abs_rshares.value == old_abs_rshares + sam_weight );
            BOOST_REQUIRE( new_bob_comment.cashout_time == new_bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( itr != vote_idx.end() );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test nested voting on nested comments" );

            old_abs_rshares = new_alice_comment.children_abs_rshares.value;
            int64_t regenerated_power = (CONTENTO_100_PERCENT * ( db.head_block_time() - db.get_account( "alice").last_vote_time ).to_seconds() ) / CONTENTO_VOTE_REGENERATION_SECONDS;
            int64_t used_power = ( db.get_account( "alice" ).voting_power + regenerated_power + max_vote_denom - 1 ) / max_vote_denom;

            comment_op.author = "sam";
            comment_op.permlink = "foo";
            comment_op.title = "bar";
            comment_op.body = "foo bar";
            comment_op.parent_author = "alice";
            comment_op.parent_permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( comment_op );
            tx.sign( sam_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            op.weight = CONTENTO_100_PERCENT;
            op.voter = "alice";
            op.author = "sam";
            op.permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            auto new_rshares = ( ( fc::uint128_t( db.get_account( "alice" ).vesting_shares.amount.value ) * used_power ) / CONTENTO_100_PERCENT ).to_uint64();

            BOOST_REQUIRE( db.get_comment( "alice", string( "foo" ) ).cashout_time == db.get_comment( "alice", string( "foo" ) ).created + CONTENTO_CASHOUT_WINDOW_SECONDS );

            validate_database();

            BOOST_TEST_MESSAGE( "--- Test increasing vote rshares" );

            generate_blocks( db.head_block_time() + CONTENTO_MIN_VOTE_INTERVAL_SEC );

            auto new_alice = db.get_account( "alice" );
            auto alice_bob_vote = vote_idx.find( std::make_tuple( new_bob_comment.id, new_alice.id ) );
            auto old_vote_rshares = alice_bob_vote->rshares;
            auto old_net_rshares = new_bob_comment.net_rshares.value;
            old_abs_rshares = new_bob_comment.abs_rshares.value;
            used_power = ( ( CONTENTO_1_PERCENT * 25 * ( new_alice.voting_power ) / CONTENTO_100_PERCENT ) + max_vote_denom - 1 ) / max_vote_denom;
            auto alice_voting_power = new_alice.voting_power - used_power;

            op.voter = "alice";
            op.weight = CONTENTO_1_PERCENT * 25;
            op.author = "bob";
            op.permlink = "foo";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            alice_bob_vote = vote_idx.find( std::make_tuple( new_bob_comment.id, new_alice.id ) );

            new_rshares = ( ( fc::uint128_t( new_alice.vesting_shares.amount.value ) * used_power ) / CONTENTO_100_PERCENT ).to_uint64();

            BOOST_REQUIRE( new_bob_comment.net_rshares == old_net_rshares - old_vote_rshares + new_rshares );
            BOOST_REQUIRE( new_bob_comment.abs_rshares == old_abs_rshares + new_rshares );
            BOOST_REQUIRE( new_bob_comment.cashout_time == new_bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( alice_bob_vote->rshares == new_rshares );
            BOOST_REQUIRE( alice_bob_vote->last_update == db.head_block_time() );
            BOOST_REQUIRE( alice_bob_vote->vote_percent == op.weight );
            BOOST_REQUIRE( db.get_account( "alice" ).voting_power == alice_voting_power );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test decreasing vote rshares" );

            generate_blocks( db.head_block_time() + CONTENTO_MIN_VOTE_INTERVAL_SEC );

            old_vote_rshares = new_rshares;
            old_net_rshares = new_bob_comment.net_rshares.value;
            old_abs_rshares = new_bob_comment.abs_rshares.value;
            used_power = ( uint64_t( CONTENTO_1_PERCENT ) * 75 * uint64_t( alice_voting_power ) ) / CONTENTO_100_PERCENT;
            used_power = ( used_power + max_vote_denom - 1 ) / max_vote_denom;
            alice_voting_power -= used_power;

            op.weight = CONTENTO_1_PERCENT * -75;
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            alice_bob_vote = vote_idx.find( std::make_tuple( new_bob_comment.id, new_alice.id ) );

            new_rshares = ( ( fc::uint128_t( new_alice.vesting_shares.amount.value ) * used_power ) / CONTENTO_100_PERCENT ).to_uint64();

            BOOST_REQUIRE( new_bob_comment.net_rshares == old_net_rshares - old_vote_rshares - new_rshares );
            BOOST_REQUIRE( new_bob_comment.abs_rshares == old_abs_rshares + new_rshares );
            BOOST_REQUIRE( new_bob_comment.cashout_time == new_bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( alice_bob_vote->rshares == -1 * new_rshares );
            BOOST_REQUIRE( alice_bob_vote->last_update == db.head_block_time() );
            BOOST_REQUIRE( alice_bob_vote->vote_percent == op.weight );
            BOOST_REQUIRE( db.get_account( "alice" ).voting_power == alice_voting_power );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test changing a vote to 0 weight (aka: removing a vote)" );

            generate_blocks( db.head_block_time() + CONTENTO_MIN_VOTE_INTERVAL_SEC );

            old_vote_rshares = alice_bob_vote->rshares;
            old_net_rshares = new_bob_comment.net_rshares.value;
            old_abs_rshares = new_bob_comment.abs_rshares.value;

            op.weight = 0;
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            alice_bob_vote = vote_idx.find( std::make_tuple( new_bob_comment.id, new_alice.id ) );

            BOOST_REQUIRE( new_bob_comment.net_rshares == old_net_rshares - old_vote_rshares );
            BOOST_REQUIRE( new_bob_comment.abs_rshares == old_abs_rshares );
            BOOST_REQUIRE( new_bob_comment.cashout_time == new_bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
            BOOST_REQUIRE( alice_bob_vote->rshares == 0 );
            BOOST_REQUIRE( alice_bob_vote->last_update == db.head_block_time() );
            BOOST_REQUIRE( alice_bob_vote->vote_percent == op.weight );
            BOOST_REQUIRE( db.get_account( "alice" ).voting_power == alice_voting_power );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test failure when increasing rshares within lockout period" );

            generate_blocks( fc::time_point_sec( ( new_bob_comment.cashout_time - CONTENTO_UPVOTE_LOCKOUT_HF17 ).sec_since_epoch() + CONTENTO_BLOCK_INTERVAL ), true );

            op.weight = CONTENTO_100_PERCENT;
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );

            CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test success when reducing rshares within lockout period" );

            op.weight = -1 * CONTENTO_100_PERCENT;
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test failure with a new vote within lockout period" );

            op.weight = CONTENTO_100_PERCENT;
            op.voter = "dave";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back( op );
            tx.sign( dave_private_key, db.get_chain_id() );
            CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );
            validate_database();
            }

            validate_database();
   }
   FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( transfer_to_vesting_authorities_test )
{
    try {
        ACTORS( (alice)(bob) )
        fund( "alice", 10000 );

        BOOST_TEST_MESSAGE( "Testing: transfer_to_vesting_authorities" );

        transfer_to_vesting_operation op;
        op.from = "alice";
        op.to = "bob";
        op.amount = ASSET( "2.500 COC" );

        signed_transaction tx;
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.operations.push_back( op );

        BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_active_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the account's authority" );
        tx.sign( alice_post_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_active_auth );

        BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

        BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_irrelevant_sig );

        BOOST_TEST_MESSAGE( "--- Test success with from signature" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        validate_database();
    }
    FC_LOG_AND_RETHROW()
}


BOOST_AUTO_TEST_CASE( transfer_to_vesting_test)
{
    try {
        BOOST_TEST_MESSAGE( "Testing: transfer_to_vesting_apply" );
        
        const auto& gpo = db.get_dynamic_global_properties();

        ACTORS( (alice)(bob) )
        fund( "alice", 10000 );

       

        BOOST_REQUIRE( alice.balance == ASSET( "10.000 COC" ) );

        auto shares = asset( gpo.total_vesting_shares.amount, VESTS_SYMBOL );
        auto coc = asset( gpo.total_coc.amount, COC_SYMBOL );
        auto alice_shares = alice.vesting_shares;
        auto bob_shares = bob.vesting_shares;

        transfer_to_vesting_operation op;
        op.from = "alice";
        op.to = "";
        op.amount = ASSET( "7.500 COC" );

        signed_transaction tx;
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        auto new_vest = op.amount * gpo.get_vesting_share_price();
        alice_shares += new_vest;
        shares += new_vest;
        coc -= op.amount;

        BOOST_REQUIRE( alice.balance.amount.value == ASSET( "2.500 COC" ).amount.value );
        BOOST_REQUIRE( alice.vesting_shares.amount.value == alice_shares.amount.value );
        BOOST_REQUIRE( gpo.total_coc.amount.value == coc.amount.value );
        BOOST_REQUIRE( gpo.total_vesting_shares.amount.value == shares.amount.value );
        validate_database();

        op.to = "bob";
        op.amount = asset( 2000, COC_SYMBOL );
        tx.operations.clear();
        tx.signatures.clear();
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, 0 );

        new_vest = asset( op.amount.amount, VESTS_SYMBOL );
        shares += new_vest;
        coc -= op.amount;
        bob_shares += new_vest;

        BOOST_REQUIRE( alice.balance.amount.value == ASSET( "0.500 COC" ).amount.value );
        BOOST_REQUIRE( alice.vesting_shares.amount.value == alice_shares.amount.value );
        BOOST_REQUIRE( bob.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( bob.vesting_shares.amount.value == bob_shares.amount.value );
        BOOST_REQUIRE( gpo.total_coc.amount.value == coc.amount.value );
        BOOST_REQUIRE( gpo.total_vesting_shares.amount.value == shares.amount.value );
        validate_database();

        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), fc::exception );

        BOOST_REQUIRE( alice.balance.amount.value == ASSET( "0.500 COC" ).amount.value );
        BOOST_REQUIRE( alice.vesting_shares.amount.value == alice_shares.amount.value );
        BOOST_REQUIRE( bob.balance.amount.value == ASSET( "0.000 COC" ).amount.value );
        BOOST_REQUIRE( bob.vesting_shares.amount.value == bob_shares.amount.value );
        BOOST_REQUIRE( gpo.total_coc.amount.value == coc.amount.value );
        BOOST_REQUIRE( gpo.total_vesting_shares.amount.value == shares.amount.value );
        validate_database();
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( convert_from_vesting_authorities_test){
    try {
        BOOST_TEST_MESSAGE( "Testing: convert_from_vesting_authorities" );
        
        ACTORS( (alice)(bob) )
        fund( "alice", 10000 );
        vest( "alice", 10000 );
        
        convert_from_vesting_operation op;
        op.account = "alice";
        op.vesting_shares = ASSET( "1.000 VESTS" );
        
        signed_transaction tx;
        tx.operations.push_back( op );
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        
        BOOST_TEST_MESSAGE( "--- Test failure when no signature." );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_active_auth );
        
        BOOST_TEST_MESSAGE( "--- Test success with account signature" );
        tx.sign( alice_private_key, db.get_chain_id() );
        db.push_transaction( tx, database::skip_transaction_dupe_check );
        
        BOOST_TEST_MESSAGE( "--- Test failure with duplicate signature" );
        tx.sign( alice_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_duplicate_sig );
        
        BOOST_TEST_MESSAGE( "--- Test failure with additional incorrect signature" );
        tx.signatures.clear();
        tx.sign( alice_private_key, db.get_chain_id() );
        tx.sign( bob_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_irrelevant_sig );
        
        BOOST_TEST_MESSAGE( "--- Test failure with incorrect signature" );
        tx.signatures.clear();
        tx.sign( alice_post_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_active_auth );
        
        validate_database();
    }
     FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( convert_from_vesting_test){
    try {
        BOOST_TEST_MESSAGE( "Testing: withdraw_vesting_apply" );
        
        ACTORS( (alice) )
        generate_block();
        vest( "alice", ASSET( "10.000 COC" ) );
        
        BOOST_TEST_MESSAGE( "--- Test convert from existing VESTS" );
        
        {
            const auto& alice = db.get_account( "alice" );
            
            convert_from_vesting_operation op;
            op.account = "alice";
            op.vesting_shares = asset( alice.vesting_shares.amount / 2, VESTS_SYMBOL );
            
            auto old_vesting_shares = alice.vesting_shares;
            
            signed_transaction tx;
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            
            BOOST_REQUIRE( alice.vesting_shares.amount.value == old_vesting_shares.amount.value );
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == ( old_vesting_shares.amount / ( CONTENTO_VESTING_WITHDRAW_INTERVALS * 2 ) ).value );
            BOOST_REQUIRE( alice.to_withdraw.value == op.vesting_shares.amount.value );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == db.head_block_time() + CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS );
            validate_database();
            
            BOOST_TEST_MESSAGE( "--- Test changing vesting converting" );
            tx.operations.clear();
            tx.signatures.clear();

            op.vesting_shares = asset( alice.vesting_shares.amount / 3, VESTS_SYMBOL );
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            BOOST_REQUIRE( alice.vesting_shares.amount.value == old_vesting_shares.amount.value );
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == ( old_vesting_shares.amount / ( CONTENTO_VESTING_WITHDRAW_INTERVALS * 3 ) ).value );
            BOOST_REQUIRE( alice.to_withdraw.value == op.vesting_shares.amount.value );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == db.head_block_time() + CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test converting more vests than available" );
            auto old_withdraw_amount = alice.to_withdraw;
            tx.operations.clear();
            tx.signatures.clear();

            op.vesting_shares = asset( alice.vesting_shares.amount * 2, VESTS_SYMBOL );
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

            BOOST_REQUIRE( alice.vesting_shares.amount.value == old_vesting_shares.amount.value );
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == ( old_vesting_shares.amount / ( CONTENTO_VESTING_WITHDRAW_INTERVALS * 3 ) ).value );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == db.head_block_time() + CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS );
            validate_database();

            BOOST_TEST_MESSAGE( "--- Test vest 0 to reset vesting converting" );
            tx.operations.clear();
            tx.signatures.clear();

            op.vesting_shares = asset( 0, VESTS_SYMBOL );
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            BOOST_REQUIRE( alice.vesting_shares.amount.value == old_vesting_shares.amount.value );
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == 0 );
            BOOST_REQUIRE( alice.to_withdraw.value == 0 );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == fc::time_point_sec::maximum() );
            
            validate_database();
            
            BOOST_TEST_MESSAGE( " ---- Test converting time arrival");
            tx.operations.clear();
            tx.signatures.clear();
            
            old_vesting_shares = alice.vesting_shares;
            auto old_balance = alice.balance;
            
            generate_block();
            
            op.vesting_shares = asset( alice.vesting_shares.amount / 2, VESTS_SYMBOL );
            tx.operations.push_back( op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            
            generate_blocks(db.head_block_time() + CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS);
            
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == op.vesting_shares.amount.value / CONTENTO_VESTING_WITHDRAW_INTERVALS );
            BOOST_REQUIRE( alice.vesting_shares.amount.value == (old_vesting_shares.amount.value - alice.vesting_withdraw_rate.amount.value) );
            BOOST_REQUIRE( alice.to_withdraw.value == op.vesting_shares.amount.value );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == db.head_block_time() + CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS );
            BOOST_REQUIRE( alice.withdrawn.value == alice.vesting_withdraw_rate.amount.value);
            BOOST_REQUIRE( alice.balance.amount.value == old_balance.amount.value + alice.vesting_withdraw_rate.amount.value);
            
            validate_database();
            
            BOOST_TEST_MESSAGE( " ---- Test converting finished");
            
            generate_blocks(CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS * 13 / CONTENTO_BLOCK_INTERVAL);
            
            BOOST_REQUIRE( alice.vesting_withdraw_rate.amount.value == 0 );
            BOOST_REQUIRE( alice.vesting_shares.amount.value == (old_vesting_shares.amount.value - op.vesting_shares.amount.value) );
            BOOST_REQUIRE( alice.next_vesting_withdrawal == fc::time_point_sec::maximum() );
            BOOST_REQUIRE( alice.withdrawn.value == op.vesting_shares.amount.value);
            BOOST_REQUIRE( alice.balance.amount.value == old_balance.amount.value + op.vesting_shares.amount.value);
            
            validate_database();
        }
        validate_database();
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( rewards_test){
    try {
        BOOST_TEST_MESSAGE( "Testing: reward_test" );
        
        ACTORS( (alice)(bob)(sam)(dave) )
        generate_block();
        
        vest( "alice", ASSET( "10.000 COC" ) );
        vest( "bob" , ASSET( "10.000 COC" ) );
        vest( "sam" , ASSET( "10.000 COC" ) );
        vest( "dave" , ASSET( "10.000 COC" ) );
        validate_database();
        generate_block();
        
        {
            const auto& alice = db.get_account( "alice" );
            const auto& bob = db.get_account("bob");
            const auto& sam = db.get_account("sam");
            
            signed_transaction tx;
            comment_operation comment_op;
            comment_op.author = "alice";
            comment_op.permlink = "ab";
            comment_op.category = "test";
            comment_op.title = "ab problem";
            comment_op.body = "ab problem";
            tx.operations.push_back( comment_op );
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( alice_post_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            
            // post subject
            generate_block();
            
            
            comment_op.author = "sam";
            comment_op.permlink = "abr";
            comment_op.parent_author = "alice";
            comment_op.parent_permlink = "ab";
            tx.operations.clear();
            tx.signatures.clear();
            tx.operations.push_back(comment_op);
            tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
            tx.sign( sam_post_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            
            auto cashout_time = db.head_block_time() + CONTENTO_CASHOUT_WINDOW_SECONDS;
            
            
            const auto& gpro = db.get_dynamic_global_reward_properties();
            
            vote_operation op;
            op.voter = "alice";
            op.author = "alice";
            op.permlink = "ab";
            op.weight = CONTENTO_100_PERCENT;

            tx.operations.clear();
            tx.signatures.clear();

            tx.operations.push_back( op );
            tx.sign( alice_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 ); 
            

            tx.operations.clear();
            tx.signatures.clear();

            op.voter = "bob";
            tx.operations.push_back( op );
            tx.sign( bob_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );
            
            generate_block();
            
            op.voter = "sam";
            op.author = "sam";
            op.permlink = "abr";
            
            tx.operations.clear();
            tx.signatures.clear();
            
            tx.operations.push_back( op );
            tx.sign( sam_private_key, db.get_chain_id() );
            db.push_transaction( tx, 0 );

            // hard to caculate how many reward in reward pool.
            auto old_alice_vesting_shares = alice.vesting_shares;
            auto old_bob_vesting_shares = bob.vesting_shares;
            
            generate_block();
            
            BOOST_REQUIRE(alice.vesting_shares.amount.value == old_alice_vesting_shares.amount.value);
            BOOST_REQUIRE(bob.vesting_shares.amount.value == old_bob_vesting_shares.amount.value);
            
            generate_blocks(cashout_time);
            
            BOOST_REQUIRE(alice.vesting_shares.amount.value > old_alice_vesting_shares.amount.value);
            BOOST_REQUIRE(bob.vesting_shares.amount.value == old_bob_vesting_shares.amount.value);
        
            BOOST_REQUIRE(gpro.subject_reward_balance.amount.value == 0);
            
            auto old_comment_reward_balance = gpro.comment_reward_balance;
            auto old_sam_vesting_shares = sam.vesting_shares;
            
            // here, because of the curves are different, so comment_reward_balance won't drop to zero
            generate_block();
            
            BOOST_REQUIRE(gpro.comment_reward_balance.amount.value < old_comment_reward_balance.amount.value);
            BOOST_REQUIRE(sam.vesting_shares.amount.value > old_sam_vesting_shares.amount.value);
            
        }
        
        validate_database();
        
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_SUITE_END()
#endif
