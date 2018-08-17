# pragma once
#include "hsql/sql/Expr.h"
#include <iostream>
#include <fc/variant.hpp>


namespace dorothy {

    using Expr = hsql::Expr;
    using OperatorType = hsql::OperatorType;

    enum ConditionType {
        conNull,
        conString,
        conFloat,
        conInt,
    };
    
//    struct Condition {
//        ConditionType conType;
//        char* name;
//        char* sval;
//        float fval;
//        int64_t ival;
//    };
    
    struct Condition {
        ConditionType conType=ConditionType::conNull;
        char* name;
        fc::variant val;
    };
    
    Condition make_condition(Expr* , Expr* );
    
    void catch_expression(Expr*, std::vector<Expr*>& );
}
