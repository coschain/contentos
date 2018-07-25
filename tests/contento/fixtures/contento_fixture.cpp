//
//  contento_global_fixture.cpp
//  contento_test
//
//  Created by 戴硕 on 2018/5/23.
//

#include <contento/app/api.hpp>
#include <contento/app/database_api.hpp>
#include "contento_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;
using namespace fc::rpc;
using namespace contento::app;

namespace contento { namespace test {

    contento_fixture::contento_fixture()
    {
        init_councillors();
        init_apis();
        init_rpc();
    }
    
    contento_fixture::~contento_fixture()
    {
        
    }

    vm_operation create_setcode(const name& contract_name, const bytes& code){
        return vm_operation {
            contract_name,
            setcode{
                .account    = contract_name,
                .vmtype     = 0,
                .vmverson   = 0,
                .code       = code
            }
        };
    }
    vm_operation create_setabi(const name& contract_name, const abi_def& code){
        return vm_operation {
            contract_name,
            setabi{
                .account    = contract_name,
                .abi        = fc::raw::pack(abi)
            }
        };
    }
    
    void contento_fixture::init_apis()
    {
        app.register_api_factory< login_api >( "login_api" );
        app.register_api_factory< database_api >( "database_api" );
        app.register_api_factory< network_node_api >( "network_node_api" );
        app.register_api_factory< network_broadcast_api >( "network_broadcast_api" );
        api_names.push_back("login_api");
        api_names.push_back("database_api");
        api_names.push_back("network_node_api");
        api_names.push_back("network_broadcast_api");
    }
    
    void contento_fixture::init_rpc()
    {
        ws_server = std::make_shared<fc::http::websocket_server>();
        ws_server->on_connection([&]( const fc::http::websocket_connection_ptr& c ) {
            std::shared_ptr< api_session_data > session = std::make_shared<api_session_data>();
            session->wsc = std::make_shared<fc::rpc::websocket_api_connection>(*c);
            session->httpc = nullptr;
            for( const std::string& name : api_names )
            {
                api_context ctx( app, name, session );
                fc::api_ptr api = app.create_api_by_name( ctx );
                if (api) {
                    session->api_map[name] = api;
                    api->register_api( *session->wsc );
                }
            }
            c->set_session_data( session );
        } );
        ws_server->listen( CONTENTO_WEBSOCKET_RPC_PORT );
        ws_server->start_accept();
        
        ws_client = std::make_shared<fc::http::websocket_client>();
        auto con = ws_client->connect(std::string("ws://localhost:") + std::to_string(CONTENTO_WEBSOCKET_RPC_PORT));
        ws_conn = std::make_shared<websocket_api_connection>(*con);
        ws_conn->get_remote_api<login_api>();
    }
    
    fc::variant contento_fixture::rpc(std::string api, std::string method, fc::variants args)
    {
        fc::variant result;
        fc::variant api_id = ws_conn->send_call(0, "get_api_by_name", { api });
        if ( !api_id.is_null() )
        {
            result = ws_conn->send_call( api_id.as_uint64(), method, args);
        }
        return result;
    }

    void contento_fixture::init_councillors()
    {
        try {
            for( int i = 0; i < get_councillor_count(); i++ )
            {
                std::string acc_name = get_councillor_account_name(i);
                fc::ecc::private_key private_key = generate_private_key(acc_name);
                public_key_type public_key = private_key.get_public_key();
                
                account_create( acc_name, public_key );
                councillor_private_keys.push_back(private_key);
            }
            validate_database();
        }
        catch ( const fc::exception& e )
        {
            edump( (e.to_detail_string()) );
            throw;
        }
    }
    
    fc::ecc::private_key contento_fixture::get_councillor_private_key(int which)
    {
        FC_ASSERT(which >= 0 && which < get_councillor_count());
        return councillor_private_keys[which];
    }
    
    int contento_fixture::get_councillor_count()
    {
        return CONTENTO_COUNCILLOR_COUNT;
    }
    
    std::string contento_fixture::get_councillor_account_name(int which)
    {
        FC_ASSERT(which >= 0 && which < get_councillor_count());
        return std::string(CONTENTO_COUNCILLOR_NAME) + (which? std::to_string(which) : "");
    }
}}
