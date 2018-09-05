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
         print( "\n Hello, ", namex{user} );
      }
    
    //@abi action
    void save(){
        
    }
    
    //@abi action
    void withdraw(account_name account, const asset& value){
        
        pay_prohibited();
       
        asset cb;
        get_contract_balance(cb);
        print("\n before withdraw  contract balance is : ",cb.amount);

        // transfer contract balance to user's account
        transfer(&account,value);
        
        asset cb2;
        get_contract_balance(cb2);
        print("\n after withdraw  contract balance is : ",cb2.amount);
    }
};

COSIO_ABI( hello, (hi)(withdraw))
