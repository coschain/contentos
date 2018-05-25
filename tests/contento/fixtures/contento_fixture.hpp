//
//  contento_global_fixture.hpp
//  contento_test
//
//  Created by 戴硕 on 2018/5/23.
//

#ifndef contento_global_fixture_hpp
#define contento_global_fixture_hpp

#include "../../common/database_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;

#define CONTENTO_COUNCILLOR_NAME    "councillor"
#define CONTENTO_COUNCILLOR_COUNT   (5)

namespace contento { namespace test {
    
    class contento_fixture : public clean_database_fixture
    {
    public:
        contento_fixture();
        ~contento_fixture();

        signed_transaction& sign_trx(signed_transaction &tx, fc::ecc::private_key &key);
        
        fc::ecc::private_key get_councillor_private_key(int which);
        static int get_councillor_count();
        static std::string get_councillor_account_name(int which);
        
    private:
        void init_councillors();
    
    private:
        std::vector<fc::ecc::private_key> councillor_private_keys;
    };
    
}}

#endif /* contento_global_fixture_hpp */
