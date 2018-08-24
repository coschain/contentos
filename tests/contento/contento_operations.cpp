// #ifdef IS_TEST_NET
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

BOOST_FIXTURE_TEST_SUITE( contentos_operation_tests, clean_database_fixture )

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

        auto vest_shares = gpo.total_vesting_shares;
        auto vests = gpo.total_vesting_fund_coc;

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

// BOOST_AUTO_TEST_CASE( subject_authority_test )
// {
//     try{
//         BOOST_TEST_MESSAGE( "Testing: subject_authorities" );
//         ACTORS( (alice)(bob) );
//         generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );

//         comment_operation op;
//         op.author = "alice";
//         op.permlink = "lorem";
//         op.category = "poem";
//         op.title = "Lorem Ipsum";
//         op.body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
//         op.json_metadata = "{\"foo\":\"bar\"}";

//         signed_transaction tx;
//         tx.operations.push_back( op );
//         tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );

//         BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_posting_auth );

//         BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
//         tx.sign( alice_post_key, db.get_chain_id() );
//         tx.sign( alice_post_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

//         BOOST_TEST_MESSAGE( "--- Test success with post signature" );
//         tx.signatures.clear();
//         tx.sign( alice_post_key, db.get_chain_id() );
//         db.push_transaction( tx, 0 );

//         BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
//         tx.sign( bob_private_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_irrelevant_sig );

//         BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the creator's authority" );
//         tx.signatures.clear();
//         tx.sign( bob_private_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_posting_auth );

//         validate_database();

//     }
//      FC_LOG_AND_RETHROW()
// }

// BOOST_AUTO_TEST_CASE( comment_authority_test )
// {
//     try{
//         BOOST_TEST_MESSAGE( "Testing: comment_authorities" );
//         ACTORS( (alice)(bob) );
//         generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );

//         // push a subject
//         comment_operation sop;
//         sop.author = "alice";
//         sop.permlink = "lorem";
//         sop.category = "poem";
//         sop.title = "Lorem Ipsum";
//         sop.body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
//         sop.json_metadata = "{\"foo\":\"bar\"}";

//         signed_transaction tx;
//         tx.operations.push_back( sop );
//         tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
//         tx.sign( alice_post_key, db.get_chain_id() );
//         db.push_transaction( tx, 0 );
//         generate_blocks( 60 / CONTENTO_BLOCK_INTERVAL );


//         tx.signatures.clear();
//         tx.operations.clear();

//         comment_operation op;
//         op.parent_author =  "alice";
//         op.parent_permlink = "lorem";
//         op.author = "bob";
//         op.permlink = "lorem2";
//         op.body = "Lorem ipsum dolor sit amet";
//         tx.operations.push_back( op );
//         tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION ); 

//         BOOST_TEST_MESSAGE( "--- Test failure when no signatures" );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_missing_posting_auth );

//         BOOST_TEST_MESSAGE( "--- Test failure when duplicate signatures" );
//         tx.sign( bob_post_key, db.get_chain_id() );
//         tx.sign( bob_post_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), protocol::tx_duplicate_sig );

//         BOOST_TEST_MESSAGE( "--- Test success with post signature" );
//         tx.signatures.clear();
//         tx.sign( bob_post_key, db.get_chain_id() );
//         db.push_transaction( tx, 0 );

//         BOOST_TEST_MESSAGE( "--- Test failure when signed by an additional signature not in the creator's authority" );
//         tx.sign( alice_private_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_irrelevant_sig );

//         BOOST_TEST_MESSAGE( "--- Test failure when signed by a signature not in the creator's authority" );
//         tx.signatures.clear();
//         tx.sign( alice_private_key, db.get_chain_id() );
//         CONTENTO_REQUIRE_THROW( db.push_transaction( tx, database::skip_transaction_dupe_check ), protocol::tx_missing_posting_auth );

//         validate_database();

//     }
//      FC_LOG_AND_RETHROW()
// }


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

        // const comment_object& alice_subject = db.get_comment( "alice", string( "lorem" ) );

        // BOOST_REQUIRE( alice_subject.author == op.author );
        // BOOST_REQUIRE( to_string( alice_subject.permlink ) == op.permlink );
        // BOOST_REQUIRE( to_string( alice_subject.parent_permlink ) == op.parent_permlink );
        // BOOST_REQUIRE( alice_subject.last_update == db.head_block_time() );
        // BOOST_REQUIRE( alice_subject.created == db.head_block_time() );
        // BOOST_REQUIRE( alice_subject.net_rshares.value == 0 );
        // BOOST_REQUIRE( alice_subject.abs_rshares.value == 0 );
        // BOOST_REQUIRE( alice_subject.cashout_time == fc::time_point_sec( db.head_block_time() + fc::seconds( CONTENTO_CASHOUT_WINDOW_SECONDS ) ) );
        // BOOST_REQUIRE( to_string( alice_subject.title ) == op.title );
        // BOOST_REQUIRE( to_string( alice_subject.body ) == op.body );

        // validate_database();

        // BOOST_TEST_MESSAGE( "--- Test Bob posting a subject on a non-existent subject" );
        // op.author = "bob";
        // op.permlink = "ipsum";
        // op.parent_author = "alice";
        // op.parent_permlink = "foobar";

        // tx.signatures.clear();
        // tx.operations.clear();
        // tx.operations.push_back( op );
        // tx.sign( bob_private_key, db.get_chain_id() );
        // CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

        // BOOST_TEST_MESSAGE( "--- Test Bob posting a comment on Alice's subject" );
        // op.parent_permlink = "lorem";

        // tx.signatures.clear();
        // tx.operations.clear();
        // tx.operations.push_back( op );
        // tx.sign( bob_private_key, db.get_chain_id() );
        // db.push_transaction( tx, 0 );

        // const comment_object& bob_comment = db.get_comment( "bob", string( "ipsum" ) );

        // BOOST_REQUIRE( bob_comment.author == op.author );
        // BOOST_REQUIRE( to_string( bob_comment.permlink ) == op.permlink );
        // BOOST_REQUIRE( bob_comment.parent_author == op.parent_author );
        // BOOST_REQUIRE( to_string( bob_comment.parent_permlink ) == op.parent_permlink );
        // BOOST_REQUIRE( bob_comment.last_update == db.head_block_time() );
        // BOOST_REQUIRE( bob_comment.created == db.head_block_time() );
        // BOOST_REQUIRE( bob_comment.net_rshares.value == 0 );
        // BOOST_REQUIRE( bob_comment.abs_rshares.value == 0 );
        // BOOST_REQUIRE( bob_comment.cashout_time == bob_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        // BOOST_REQUIRE( bob_comment.root_comment == alice_subject.id );
        // validate_database();

        // BOOST_TEST_MESSAGE( "--- Test Sam posting a comment on Bob's comment" );

        // op.author = "sam";
        // op.permlink = "dolor";
        // op.parent_author = "bob";
        // op.parent_permlink = "ipsum";

        // tx.signatures.clear();
        // tx.operations.clear();
        // tx.operations.push_back( op );
        // tx.sign( sam_private_key, db.get_chain_id() );
        // db.push_transaction( tx, 0 );

        // const comment_object& sam_comment = db.get_comment( "sam", string( "dolor" ) );

        // BOOST_REQUIRE( sam_comment.author == op.author );
        // BOOST_REQUIRE( to_string( sam_comment.permlink ) == op.permlink );
        // BOOST_REQUIRE( sam_comment.parent_author == op.parent_author );
        // BOOST_REQUIRE( to_string( sam_comment.parent_permlink ) == op.parent_permlink );
        // BOOST_REQUIRE( sam_comment.last_update == db.head_block_time() );
        // BOOST_REQUIRE( sam_comment.created == db.head_block_time() );
        // BOOST_REQUIRE( sam_comment.net_rshares.value == 0 );
        // BOOST_REQUIRE( sam_comment.abs_rshares.value == 0 );
        // BOOST_REQUIRE( sam_comment.cashout_time == sam_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        // BOOST_REQUIRE( sam_comment.root_comment == alice_subject.id );
        // validate_database();

        // generate_blocks( 60 * 5 / CONTENTO_BLOCK_INTERVAL + 1 );

        // BOOST_TEST_MESSAGE( "--- Test modifying a comment" );
        // const auto& mod_sam_comment = db.get_comment( "sam", string( "dolor" ) );
        // const auto& mod_bob_comment = db.get_comment( "bob", string( "ipsum" ) );
        // const auto& mod_alice_comment = db.get_comment( "alice", string( "lorem" ) );
        // fc::time_point_sec created = mod_sam_comment.created;

        // db.modify( mod_sam_comment, [&]( comment_object& com )
        // {
        //     com.net_rshares = 10;
        //     com.abs_rshares = 10;
        // });

        // tx.signatures.clear();
        // tx.operations.clear();
        // op.title = "foo";
        // op.body = "bar";
        // op.json_metadata = "{\"bar\":\"foo\"}";
        // tx.operations.push_back( op );
        // tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        // tx.sign( sam_private_key, db.get_chain_id() );
        // db.push_transaction( tx, 0 );

        // BOOST_REQUIRE( mod_sam_comment.author == op.author );
        // BOOST_REQUIRE( to_string( mod_sam_comment.permlink ) == op.permlink );
        // BOOST_REQUIRE( mod_sam_comment.parent_author == op.parent_author );
        // BOOST_REQUIRE( to_string( mod_sam_comment.parent_permlink ) == op.parent_permlink );
        // BOOST_REQUIRE( mod_sam_comment.last_update == db.head_block_time() );
        // BOOST_REQUIRE( mod_sam_comment.created == created );
        // BOOST_REQUIRE( mod_sam_comment.cashout_time == mod_sam_comment.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
        // validate_database();

        // BOOST_TEST_MESSAGE( "--- Test spam subjects" );

        // op.permlink = "sit";
        // op.category = "poem";
        // op.parent_permlink = "";
        // op.parent_author = "";
        // tx.operations.clear();
        // tx.signatures.clear();
        // tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        // tx.operations.push_back( op );
        // tx.sign( sam_private_key, db.get_chain_id() );
        // db.push_transaction( tx, 0 );

        // generate_blocks( 60 * 5 / CONTENTO_BLOCK_INTERVAL );

        // op.permlink = "amet";
        // tx.operations.clear();
        // tx.signatures.clear();
        // tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        // tx.operations.push_back( op );
        // tx.sign( sam_private_key, db.get_chain_id() );
        CONTENTO_REQUIRE_THROW( db.push_transaction( tx, 0 ), fc::exception );

        validate_database();

        generate_block();
        db.push_transaction( tx, 0 );
        validate_database();
    }
    FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_SUITE_END()
// #endif