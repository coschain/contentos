#include <eosiolib/eosio.hpp>
#include <eosiolib/contract_bank.h>
#include <eosiolib/chain.h>
using namespace eosio;

class hello : public eosio::contract {
  public:
      using contract::contract;

      //@abi action
      void hi( account_name user ) {
          print(" ====== enter contract hi function ====== \n");

           int64_t cb = get_contract_balance();
          print("contract balance is : ", cb);

          int64_t value = get_value();

          print("\n values is :", value);
         print( "\n Hello, ", name{user} );
          print(" ====== exit contract hi function ====== \n");
      }
    
    //@abi action
    void withdraw(account_name user, int64_t value){
         int64_t cb = get_contract_balance();
        print("\n before withdraw  contract balance is : ",cb);

        // transfer contract balance to user's account
        //transfer(user,value);
        
        print("\n after withdraw  contract balance is : ",cb);
    }
};

EOSIO_ABI( hello, (hi)(withdraw))
