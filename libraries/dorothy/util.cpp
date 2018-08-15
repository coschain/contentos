#include <dorothy/util.hpp>


namespace dorothy {
     Condition make_condition(Expr* left, Expr* right){
        Condition condition;
        condition.name = left -> name;
        
        switch(right->type){
            case hsql::ExprType::kExprLiteralString:
                condition.conType = ConditionType::conString;
                condition.sval = right -> name;
                break;
            case hsql::ExprType::kExprLiteralInt:
                condition.conType = ConditionType::conInt;
                condition.ival = right -> ival;
                break;
            case hsql::ExprType::kExprLiteralFloat:
                condition.conType = ConditionType::conFloat;
                condition.fval = right -> fval;
                break;
            default:
                condition.conType = ConditionType::conNull;
                break;
        }
        return condition;
    }
    
    void catch_expression(Expr* expr, std::vector<Expr*>& expr_v){
        if(expr == nullptr) return;
        if(expr -> opType == OperatorType::kOpEquals)
            expr_v.push_back(expr);
        catch_expression(expr->expr, expr_v);
        catch_expression(expr->expr2, expr_v);
    }

}
