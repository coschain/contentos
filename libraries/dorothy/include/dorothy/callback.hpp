#pragma once

#include <fc/variant.hpp>
#include <dorothy/util.hpp>
#include <contento/chain/account_object.hpp>
#include <iostream>
#include <algorithm>
#include <boost/interprocess/allocators/allocator.hpp>
#include <fc/exception/exception.hpp>

namespace dorothy {
    
    typedef contento::chain::account_object account_object;
    
    
    auto cmp_default = [](fc::variant& v, const std::vector<Condition>& conditions){return true;};
    
    auto cmp_conditions = [](fc::variant& v, const std::vector<Condition>& conditions){
        std::vector<bool> results;
        for(Condition con: conditions){
            const char* name = con.name;
            try {
                switch(con.conType){
                    case ConditionType::conString:
                        if(v[name].as_string() == con.val.as_string())
                            results.push_back(true);
                        else
                            results.push_back(false);
                        break;
                    case ConditionType::conInt:
                        if(v[name].as_int64() == con.val.as_int64())
                            results.push_back(true);
                        else
                            results.push_back(false);
                        break;
                    default:
                        results.push_back(false);
                        break;
                }
            }
            catch (const fc::key_not_found_exception&){
                std::cerr << "select condition not found: " << name << std::endl;
                throw;
            }
        }
        if ( std::all_of(results.begin(), results.end(), [](bool result){return result;}) )
             return true;
        else
            return false;
    };
}
