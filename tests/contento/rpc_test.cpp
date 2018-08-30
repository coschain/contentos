#ifdef IS_TEST_NET_2

#include <boost/test/unit_test.hpp>
#include "fixtures/contento_fixture.hpp"

using namespace contento::test;

BOOST_FIXTURE_TEST_SUITE( rpc_test_demo, contento_fixture )

BOOST_AUTO_TEST_CASE( demo )
{
    fc::variant r;
    
    r = rpc("login_api", "get_api_by_name", {"login_api"});
    BOOST_REQUIRE_EQUAL( r.as_uint64(), 0 );
    
    r = rpc("database_api", "get_accounts", fc::json::from_string("[ [\"initminer\"] ]").get_array());
    BOOST_REQUIRE_EQUAL( r.get_array().front()["name"].as_string(), "initminer" );
    
    r = rpc("database_api", "get_dynamic_global_properties");
    BOOST_REQUIRE_EQUAL( r["current_witness"].as_string(), "initminer" );
}

BOOST_AUTO_TEST_SUITE_END()

#endif // IS_TEST_NET
