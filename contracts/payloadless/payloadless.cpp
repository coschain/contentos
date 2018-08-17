#include <cosiolib/cosio.hpp>
#include <cosiolib/print.hpp>
using namespace cosio;

class payloadless : public cosio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

COSIO_ABI( payloadless, (doit) )
