# pragma once
#include "hsql/sql/Expr.h"
#include <iostream>


namespace dorothy {

    using Expr = hsql::Expr;
    using OperatorType = hsql::OperatorType;

    enum ConditionType {
        conNull,
        conString,
        conFloat,
        conInt,
    };
    
    struct Condition {
        ConditionType conType;
        char* name;
        char* sval;
        float fval;
        int64_t ival;
    };
    
    Condition make_condition(Expr* , Expr* );
    
    void catch_expression(Expr*, std::vector<Expr*>& );
}
