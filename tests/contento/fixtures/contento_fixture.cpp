//
//  contento_global_fixture.cpp
//  contento_test
//
//  Created by 戴硕 on 2018/5/23.
//

#include "contento_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;


namespace contento { namespace test {

    contento_fixture::contento_fixture()
    {
        init_councillors();
    }
    
    contento_fixture::~contento_fixture()
    {
        
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

    signed_transaction& contento_fixture::sign_trx(signed_transaction &tx, fc::ecc::private_key &key)
    {
        tx.sign(key, db.get_chain_id());
        tx.set_expiration( db.head_block_time() + CONTENTO_MAX_TIME_UNTIL_EXPIRATION );
        return tx;
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
