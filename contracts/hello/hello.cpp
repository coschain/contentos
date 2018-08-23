#include <cosiolib/contract_bank.h>
#include <cosiolib/chain.h>
#include <cosiolib/cosio.hpp>
#include <cosiolib/asset.hpp>
using cosio::asset;

using namespace cosio;

class hello : public cosio::contract {
  public:
      using contract::contract;

      //@abi action
      void hi( account_name user ) {
          print("\n ====== enter contract hi function ====== \n");

           int64_t cb = get_contract_balance();
          print("contract balance is : ", cb);

          int64_t value = get_value();

          print("\n values is :", value);
         print( "\n Hello, ", name{user} );
          print("\n ====== exit contract hi function ====== \n");
      }
    
    //@abi action
    void withdraw(account_name user, const asset& value){
        print("111");
        pay_prohibited();
         int64_t cb = get_contract_balance();
        print("\n before withdraw  contract balance is : ",cb);

        // transfer contract balance to user's account
        transfer(user,value);
        
         int64_t cb2 = get_contract_balance();
        print("\n after withdraw  contract balance is : ",cb2);
    }
};

COSIO_ABI( hello, (hi)(withdraw))
