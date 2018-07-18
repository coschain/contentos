#include <eosio/testing/tester.hpp>

#include "eosio.token.wast.hpp"
#include "eosio.token.abi.hpp"

using namespace eosio::chain;
using namespace eosio::testing;

transaction_trace_ptr create_currency( tester& tester, name contract, name manager, asset maxsupply ) {
    auto act =  mutable_variant_object()
    ("issuer",       manager )
    ("maximum_supply", maxsupply );
    
    return tester.push_action(contract, N(create), contract, act );
}

transaction_trace_ptr issue( tester& tester, name to, const asset& amount, name manager = config::system_account_name ) {
    return tester.push_action( N(eosio.token), N(issue), manager, mutable_variant_object()
                             ("to",      to )
                             ("quantity", amount )
                             ("memo", "")
                             );
}

transaction_trace_ptr transfer( tester& tester, name from, name to, const string& amount, name manager = config::system_account_name ) {
    return tester.push_action( N(eosio.token), N(transfer), manager, mutable_variant_object()
                             ("from",    from)
                             ("to",      to )
                             ("quantity", asset::from_string(amount) )
                             ("memo", "")
                             );
}

#define CORE_AMOUNT(s)  (s " " CORE_SYMBOL_NAME)

void test_eosio() {
    tester tester;
    
    // create account for eos.token, alice & bob
    tester.create_accounts( { N(eosio.token), N(alice), N(bob) } );
    
    // push eosio.token contract
    tester.set_code( N(eosio.token), eosio_token_wast );
    tester.set_abi( N(eosio.token), eosio_token_abi );
    
    transaction_trace_ptr trace_ptr = nullptr;
    
    // create system token with max supply limit of 10 billion
    trace_ptr = create_currency( tester, N(eosio.token), config::system_account_name, core_from_string("10000000000.0000") );
    
    // eosio issues 1 billion tokens
    trace_ptr = issue( tester, config::system_account_name, core_from_string("1000000000.0000"));
    
    // eosio -> alice: 10k
    trace_ptr = transfer( tester, config::system_account_name, N(alice), CORE_AMOUNT("10000.0000") );
    
    // alice -> bob: 3k
    // bob -> alice: 2.5k
    trace_ptr = transfer( tester, N(alice), N(bob), CORE_AMOUNT("3000.0000"), N(alice) );
    trace_ptr = transfer( tester, N(bob), N(alice), CORE_AMOUNT("2500.0000"), N(bob) );
}

int main(int argc, char** argv) {
    test_eosio();
    return 0;
}
