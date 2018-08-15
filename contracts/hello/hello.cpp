#include <eosiolib/eosio.hpp>
#include <eosiolib/contract_bank.h>
#include <eosiolib/chain.h>
using namespace eosio;

#pragma pack(push, 1)
struct producers {
   char len;
   account_name producers[21];
};
#pragma pack(pop)


class hello : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
          int64_t value = get_value();

          print("values is :", value);
         print( "Hello, ", name{user} );
      }
};

EOSIO_ABI( hello, (hi) )
