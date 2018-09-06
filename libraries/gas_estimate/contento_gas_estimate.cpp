#include <contento/gas_estimate/contento_gas_estimate.hpp>
#include <contento/app/api_context.hpp>
#include <contento/app/application.hpp>
#include <contento/chain/config.hpp>
#include <contento/chain/database.hpp>
#include <contento/protocol/asset.hpp>
#include <contento/protocol/transaction.hpp>
#include <fc/api.hpp>
#include <memory>


namespace contento { namespace gas_estimate {
    
    using namespace contento::chain;

    class contento_gas_estimate_api_impl : public std::enable_shared_from_this<contento_gas_estimate_api_impl>
    {
    public:
        contento_gas_estimate_api_impl( const api_context& ctx ): _db(ctx.app.chain_database()) { }
        ~contento_gas_estimate_api_impl() { }

        void set_current_working_thread() {
            _thread = &fc::thread::current();
        }

        asset _estimated_gas_fee( const signed_transaction& trx ) {
            FC_ASSERT(_thread && _thread->is_current(), "incorrect thread invoking.");
            transaction_wrapper trx_wrapper = _db->test_push_transaction(trx);
            return asset(trx_wrapper.invoice.gas_usage / config::gas_per_coc);
        }

        asset estimated_gas_fee( const signed_transaction& trx ) {
            FC_ASSERT(_thread, "contento_gas_estimate_api not initialized properly.");
            if (_thread->is_current()) {
                return _estimated_gas_fee(trx);
            } else {
                return _thread->async([&](){ return _estimated_gas_fee(trx); }, "thread invoking _estimated_gas_fee").wait();
            }
        }
        
    private:
        std::shared_ptr<database> _db;
        fc::thread *_thread;
    };
    
    /////////////////////////
    
    contento_gas_estimate_api::contento_gas_estimate_api( const api_context& ctx )
        : my( new contento_gas_estimate_api_impl(ctx) )
    {
        wlog("creating gas_estimate_api ${x}", ("x", int64_t(this)) );
    }
    
    contento_gas_estimate_api::~contento_gas_estimate_api()
    {
        wlog("freeing gas_estimate_api ${x}", ("x", int64_t(this)) );
    }

    void contento_gas_estimate_api::on_api_startup() { 
        my->set_current_working_thread();
    }
    
    asset contento_gas_estimate_api::estimated_gas_fee(const signed_transaction &trx)
    {
        return my->estimated_gas_fee(trx);
    }

} } 
