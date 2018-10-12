#include <cosiolib/cosio.hpp>

using namespace cosio;

class hello : public cosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", namex{user} );
      }
};

COSIO_ABI( hello, (hi) )
