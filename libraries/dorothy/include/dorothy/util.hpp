# pragma once
#include "hsql/sql/Expr.h"

namespace dorothy {

    typedef hsql::Expr Expr;

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
}
