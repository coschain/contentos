#pragma once

#include <fc/variant.hpp>
#include <dorothy/util.hpp>
#include <contento/chain/account_object.hpp>
#include <iostream>
#include <boost/interprocess/allocators/allocator.hpp>

namespace dorothy {
    
    typedef contento::chain::account_object account_object;
    
    
    auto cmp_default = [](fc::variant& v, const std::vector<Condition>& conditions){return true;};
    
    auto cmp_account_id = [](fc::variant& v, const std::vector<Condition>& conditions){
        return (v["id"].as_int64() == conditions[0].ival) ? true : false;
    };

    auto cmp_account_name = [](fc::variant& v, const std::vector<Condition>& conditions){
        return (v["name"].as_string() == std::string(conditions[0].sval)) ? true : false;
    };
}
