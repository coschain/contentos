
#include <dorothy/database.hpp>
#include <dorothy/printer.hpp>
#include "hsql/util/sqlhelper.h"

#define NDEBUG

// using bprinter::TablePrinter;
namespace dorothy {

    database::database()
    : _chain_db(std::make_shared<chainbase::database>()){}

    database::~database()
    {
        if(_chain_db)
        {
           _chain_db->close();
        }
    }

    void database::initialize_indexes()
    {
       _chain_db -> add_index<dynamic_global_property_index>(); 
       _chain_db -> add_index<dynamic_global_reward_property_index>();
       _chain_db -> add_index<comment_index>();
       _chain_db -> add_index<account_index>();
    }



    void database::open(const boost::filesystem::path& dir)
    {
        _chain_db->open(dir);
        initialize_indexes();
    }

    void database::catch_expression(Expr* expr, std::vector<Expr*>& expr_v){
        if(expr == nullptr) return;
        if(expr -> opType == OperatorType::kOpEquals)
            expr_v.push_back(expr);
        catch_expression(expr->expr, expr_v);
        catch_expression(expr->expr2, expr_v);
    }

    void database::print_header(TablePrinter& tp, std::vector<column>& columns )
    {
        uint span(0);
        uint length(0);
        // to require the minium column size
        for(auto iter=columns.begin(); iter!=columns.end();++iter){
            if(iter -> second == 0){
                length = (iter -> first).length();
                span = ((length >= 4) ? length: 4);
            }
            else{
                span = iter -> second;
            }
            tp.AddColumn(iter->first, span);
        }
        tp.PrintHeader();
    }

    void database::print_footer(TablePrinter& tp)
    {
        tp.PrintFooter();
    }

    template<typename index_type, typename by_tag, typename printer, typename compare_key>
    void database::print_body(TablePrinter& tp, compare_key&& key)
    {
        const auto& idx = _chain_db -> template get_index<index_type>().indices().template get<by_tag>();
        auto itr = idx.find(std::forward<compare_key>(key));
        if(itr != idx.end())
        {
            printer p = printer();
            p.template print<decltype(itr)>(tp, itr); 
        }
    }

    template<typename index_type, typename by_tag, typename printer>
    void database::print_body(TablePrinter& tp)
    {
        const auto& idx = _chain_db -> template get_index<index_type>().indices().template get<by_tag>();
        for(auto current=idx.begin(); current != idx.end(); ++current)
        {
            printer p = printer();
            p.template print<decltype(current)>(tp, current);
        } 
    } 

    void database::query_dynamic_global_property(const hsql::SelectStatement* stmt)
    {
        TablePrinter _tp(&std::cout);
        std::vector<column> columns = {
            {"id", 0}, {"head_block_number", 0}, {"time", 10}, {"current_witness", 0}, {"virtual_supply", 20},
            {"current_supply", 20}, {"vesting_shares", 0}, {"last_irrversible_block", 00}
        };
       
        print_header(_tp, columns);

        _chain_db->with_read_lock( [&]()
        {
            print_body<dynamic_global_property_index, contento::chain::by_id, dorothy::DynamicGlobalPropertyPrinter>(_tp);
        });
        print_footer(_tp);
    }

    void database::query_dynamic_global_reward_property(const hsql::SelectStatement* stmt)
    {
        TablePrinter _tp(&std::cout);
        std::vector<column> columns = {
            {"id", 0}, {"subject_reward_balance", 0}, {"subject_recent_claims", 0}, 
            {"comment_reward_balance", 0}, {"comment_recent_claims", 0}, {"other_reward_balance", 0},
            {"tick", 5}, {"subject_last_update", 0}, {"comment_last_update", 0}
        };
        print_header(_tp, columns);
        _chain_db->with_read_lock( [&]()
        {
            print_body<dynamic_global_reward_property_index, contento::chain::by_id, dorothy::DynamicGlobalRewardPropertyPrinter>(_tp);
        });
        print_footer(_tp); 
    } 

    void database::query_comment(const hsql::SelectStatement* stmt)
    {
        TablePrinter _tp(&std::cout);
        std::string field;
        if (stmt->order != nullptr) {
            field = stmt -> order -> at(0) -> expr -> name;
        }
        else {
            field = "id";
        }
        std::vector<Expr*> expr_v;
        if (stmt -> whereClause != nullptr) {
            catch_expression(stmt -> whereClause, expr_v);
        }
        std::vector<column> columns = {
            {"id", 0}, {"is_subject", 0}, {"parent_author", 0}, {"parent_permlink", 0}, {"author", 15},
            {"permlink", 20}, {"title", 20}, 
            {"net_rshares", 10}, 
            {"created", 10}, {"cashout_time", 10}
        };
        print_header(_tp, columns);
        _chain_db->with_read_lock( [&]()
        {
            if(field == "id"){
                if (expr_v.empty()) 
                    print_body<comment_index, contento::chain::by_id, dorothy::CommentPrinter>(_tp);
                else {
                    Expr* e = expr_v.at(0);
                    std::string field = e -> expr -> name;
                    assert(field == "id");
                    int value = e -> expr2 -> ival;
                    print_body<comment_index, contento::chain::by_id, dorothy::CommentPrinter>(_tp, value); 
                }
            }
            else if (field == "cashout_time")
                print_body<comment_index, contento::chain::by_cashout_time, dorothy::CommentPrinter>(_tp);
            else if (field == "permlink")
                print_body<comment_index, contento::chain::by_permlink, dorothy::CommentPrinter>(_tp); 
            else if (field == "root")
                print_body<comment_index, contento::chain::by_root, dorothy::CommentPrinter>(_tp);
            else if (field == "parent")
                print_body<comment_index, contento::chain::by_parent, dorothy::CommentPrinter>(_tp);
            else
                std::cout << "invalid order key\n";
        });
        print_footer(_tp);

    }

    void database::query_account(const hsql::SelectStatement* stmt)
    {
        TablePrinter _tp(&std::cout);
        std::string field;
        if (stmt->order != nullptr) {
            field = stmt -> order -> at(0) -> expr -> name;
        }
        else {
            field = "id";
        }

        std::vector<Expr*> expr_v;
        if (stmt -> whereClause != nullptr) {
            catch_expression(stmt -> whereClause, expr_v);
        }
        std::vector<column> columns = {
            {"id", 0}, {"name", 12}, {"balance", 15}, {"vesting_shares", 15}, 
            {"next_vesting_withdrawal", 10}, {"to_withdraw", 10}, {"withdrawn", 10}
        };
        print_header(_tp, columns);
        _chain_db->with_read_lock( [&]()
        {
            if(field=="id"){
                if (expr_v.empty())
                    print_body<account_index, contento::chain::by_id, dorothy::AccountPrinter>(_tp);
                else{
                    Expr* e = expr_v.at(0);
                    std::string field = e -> expr -> name;
                    assert(field == "id");
                    int value = e -> expr2 -> ival;
                    print_body<account_index, contento::chain::by_id, dorothy::AccountPrinter>(_tp, value);
                }
            }
            else if (field == "name"){
                if (expr_v.empty())
                    print_body<account_index, contento::chain::by_name, dorothy::AccountPrinter>(_tp);
                else {
                    Expr* e = expr_v.at(0);
                    std::string field = e -> expr -> name;
                     assert(field == "name");
                     std::string value = e -> expr2 -> name;
                    print_body<account_index, contento::chain::by_name, dorothy::AccountPrinter>(_tp, value);
                }
            }
             else if (field == "balance")
                 print_body<account_index, contento::chain::by_balance, dorothy::AccountPrinter>(_tp);
             else if (field == "vesting_shares")
                 print_body<account_index, contento::chain::by_vesting_shares, dorothy::AccountPrinter>(_tp);
             else
                std::cout << "invalid order key\n";
        });
        print_footer(_tp);
    }


    void database::query(std::string& sql)
    {
        hsql::SQLParserResult result;
        hsql::SQLParser::parse(sql, &result);
        // std::string a("dynamic_property");

        // just process the first statement and no more
        
        assert(result.getStatement(0)->type() == hsql::kStmtSelect);
        const auto* stmt = (const hsql::SelectStatement*)result.getStatement(0);
        //hsql::printSelectStatementInfo(stmt, 0);
        // std::string table_name(stmt -> fromTable -> getName());
        // if (table_name == "property"){
        //     query_dynamic_global_property(stmt);
        // }else if (table_name == "reward_property") {
        //     query_dynamic_global_reward_property(stmt);
        // } else if (table_name == "comment") {
        //     query_comment(stmt);
        // } else if(table_name == "account") {
        query_account(stmt);
        // }else {
        //      std::cerr << "unknown table:" + table_name << "\n";
        // }

    }

    void database::close()
    {
        if(_chain_db)
        {
           _chain_db->close();
        } 
    }
}
