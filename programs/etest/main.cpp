#include <eosio/testing/tester.hpp>

void test_eosio() {
    eosio::testing::tester test;
   
    // generate a random account name
    srand(time(0));
    std::string rand_name;
    for (int i = 0; i < 12; i++) {
        rand_name += 'a' + rand() % 26;
    }
    eosio::chain::account_name acc(rand_name);
    
    // create the account
    test.create_account(acc);
    test.produce_blocks(10);
    
    // query the account object from database
    auto acc_obj = test.control->get_account(acc);
    std::cout << acc_obj.name.to_string() << " created." << std::endl;
}

int main(int argc, char** argv) {
    test_eosio();
    return 0;
}
