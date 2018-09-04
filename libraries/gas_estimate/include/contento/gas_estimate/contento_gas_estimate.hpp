#pragma once

#include <contento/app/api_context.hpp>
#include <contento/protocol/asset.hpp>
#include <contento/protocol/transaction.hpp>
#include <fc/api.hpp>
#include <memory>

namespace contento { namespace gas_estimate {

    using namespace contento::protocol;
    using namespace contento::app;

    class contento_gas_estimate_api_impl;


    /**
     * @brief contento_gas_estimate_api implements the RPC API for the gas fee estimation.
     */
    class contento_gas_estimate_api {
    public:
        contento_gas_estimate_api(const api_context& ctx);
        ~contento_gas_estimate_api();

        void on_api_startup();
        
        asset estimated_gas_fee( const signed_transaction& trx );

    private:
        std::shared_ptr< contento_gas_estimate_api_impl >   my;
    };

} } // contento::gas_estimate

FC_API(contento::gas_estimate::contento_gas_estimate_api,
      (estimated_gas_fee)
)
