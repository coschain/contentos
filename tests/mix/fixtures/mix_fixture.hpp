#ifndef mix_fixture_hpp
#define mix_fixture_hpp

#include <contento/app/api.hpp>
#include "../../common/database_fixture.hpp"

using namespace contento::chain;
using namespace contento::protocol;

namespace contento { namespace test {

    class mix_fixture : public clean_database_fixture
    {
        public:
            mix_fixture();
            ~mix_fixture();
    };
    
}}

#endif /* contento_global_fixture_hpp */
