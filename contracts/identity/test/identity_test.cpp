#include <cosiolib/action.h>
#include <cosiolib/contract.hpp>
#include <cosiolib/dispatcher.hpp>
#include <identity/interface.hpp>

namespace identity_test {
   
   using cosio::action_meta;
   using cosio::singleton;
   using std::string;
   using std::vector;

   class contract : public cosio::contract {
      public:
         static constexpr uint64_t code = N(identitytest);
         typedef singleton<N(result), uint64_t> result_table;

         using cosio::contract::contract;

         void getowner( const uint64_t identity ) {
            identity::interface iface( N(identity) );
            account_name owner = iface.get_owner_for_identity(get_current_caller(), identity);
            result_table( code, 0 ).set( owner, code ); //use scope = 0 for simplicity
         }

         void getidentity( const account_name account ) {
            identity::interface iface( N(identity) );
            identity::identity_name idnt = iface.get_identity_for_account(get_current_caller(), account);
            result_table( code, 0 ).set(idnt, code ); //use scope = 0 for simplicity
         }
   };

} /// namespace identity

COSIO_ABI( identity_test::contract, (getowner)(getidentity) );
