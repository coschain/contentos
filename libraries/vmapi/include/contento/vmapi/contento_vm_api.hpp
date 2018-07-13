#pragma once

#include <contento/chain/database.hpp>
#include <contento/chain/contento_objects.hpp>
#include <contento/chain/contento_object_types.hpp>
#include <contento/app/state.hpp>
#include <contento/app/api_context.hpp>


#include <fc/api.hpp>
#include <fc/optional.hpp>
#include <fc/variant_object.hpp>

#include <fc/network/ip.hpp>

#include <boost/container/flat_set.hpp>

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace contento { namespace app {

using namespace contento::chain;
using namespace contento::protocol;
using namespace std;


class contento_vm_api_impl;


/**
 * @brief The contento_vm_api class implements the RPC API for the vm-chain about content.
 *
 */
class contento_vm_api
{
   public:
      contento_vm_api(const contento::app::api_context& ctx);
      ~contento_vm_api();


      //////////////
      // Accounts //
      //////////////

      vector< extended_account > get_accounts( vector< string > names ) const;

      /**
       * @brief Get the total number of accounts registered with the blockchain
       */
      uint64_t get_account_count()const;

      ////////////////////////////
      // Handlers - not exposed //
      ////////////////////////////
      void on_api_startup();

   private:

      std::shared_ptr< contento_vm_api_impl >   my;
};

} }

FC_API(contento::app::contento_vm_api,
      (get_accounts)
      (get_account_count)
)


