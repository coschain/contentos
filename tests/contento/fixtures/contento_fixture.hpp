//
//  contento_global_fixture.hpp
//  contento_test
//
//  Created by 戴硕 on 2018/5/23.
//

#ifndef contento_global_fixture_hpp
#define contento_global_fixture_hpp

#include <contento/app/api.hpp>
#include "../../common/database_fixture.hpp"
#include <contento/protocol/types.hpp>
#include <contento/protocol/contento_operations.hpp>
#include <contento/chain/abi_def.hpp>

using namespace contento::chain;
using namespace contento::protocol;

#define CONTENTO_COUNCILLOR_NAME    "councillor"
#define CONTENTO_COUNCILLOR_COUNT   (5)
#define CONTENTO_WEBSOCKET_RPC_PORT     (58678)


namespace contento { namespace test {
    
    class contento_fixture : public clean_database_fixture
    {
    public:
        contento_fixture();
        ~contento_fixture();

        fc::ecc::private_key get_councillor_private_key(int which);
        static int get_councillor_count();
        static std::string get_councillor_account_name(int which);
        vm_operation create_setcode(const name& contract_name, const bytes& code);
        vm_operation create_setabi(const name& contract_name, const abi_def& code);
        

        fc::variant rpc(std::string api, std::string method, fc::variants args = fc::variants());
        
    protected:
        void init_councillors();
        void init_apis();
        void init_rpc();
    
    protected:
        std::vector<fc::ecc::private_key> councillor_private_keys;
        std::vector<std::string> api_names;
        std::shared_ptr<fc::http::websocket_server> ws_server;
        std::shared_ptr<fc::http::websocket_client> ws_client;
        std::shared_ptr<fc::rpc::websocket_api_connection> ws_conn;
    };
    
}}

#endif /* contento_global_fixture_hpp */
