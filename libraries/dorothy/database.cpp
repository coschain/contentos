
#include <dorothy/database.hpp>
#include "hsql/util/sqlhelper.h"
#include <fc/io/json.hpp>

#define NDEBUG

namespace fc {

    void extract(const variant_object& o, std::vector<std::pair<string, string>>&);
    void extract(const variant& v, std::vector<std::pair<string, string>>&);
    

    void extract(const variant_object& o, std::vector<std::pair<string, string>>& entities)
    {
        auto itr = o.begin();
        
        while( itr != o.end() )
        {
            string key{itr->key()};
            string value{json::to_string(itr->value())};
            if(value.front() == '"' && value.back() == '"'){
                value = value.substr(1, value.length()-2);
            }
            entities.push_back(std::make_pair(key, value));
            ++itr;
        }
    }
    
    void extract(const variant& v, std::vector<std::pair<string, string>>& entities)
    {
        assert(v.get_type() == variant::object_type);
        const variant_object& o =  v.get_object();
        extract(o, entities);
        return;
    }
}

template< class T >
using decay_t = typename std::decay<T>::type;

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
    
    void database::open(const boost::filesystem::path& dir)
    {
        _chain_db->open(dir);
        initialize_indexes();
        initialize_indexed_query();
    }
    
    void database::close()
    {
        if(_chain_db)
        {
            _chain_db->close();
        }
    }

    void database::initialize_indexes()
    {
        initialize_index<account_index, by_id>("account", "id");
        initialize_index<account_index, by_name>("account", "name");
        initialize_index<account_index, by_next_vesting_withdrawal>("account", "next_vesting_withdrawal");
        initialize_index<account_index, by_last_post>("account", "last_post");
        initialize_index<account_index, by_balance>("account", "balance");
        initialize_index<account_index, by_vesting_shares>("account", "vesting_shares");
        initialize_index<account_index, by_post_count>("account", "post_count");
        initialize_index<account_index, by_vote_count>("account", "vote_count");
        initialize_index<admin_index, by_id>("admin", "id");
        initialize_index<admin_index, by_name>("admin", "name");
        initialize_index<owner_authority_history_index, by_id>("owner_authority_history", "id");
        initialize_index<owner_authority_history_index, by_account>("owner_authority_history", "account");
        initialize_index<block_summary_index, by_id>("block_summary", "id");
        initialize_index<comment_index, by_id>("comment", "id");
        initialize_index<comment_index, by_cashout_time>("comment", "cashout_time");
        initialize_index<comment_index, by_permlink>("comment", "permlink");
        initialize_index<comment_index, by_root>("comment", "root");
        initialize_index<comment_index, by_parent>("comment", "parent");
        initialize_index<comment_index, by_last_update>("comment", "last_update");
        initialize_index<comment_index, by_author_last_update>("comment", "author_last_update");
        initialize_index<comment_vote_index, by_id>("comment_vote", "id");
        initialize_index<comment_vote_index, by_comment_voter>("comment_vote", "comment_voter");
        initialize_index<comment_vote_index, by_voter_comment>("comment_vote", "voter_comment");
        initialize_index<comment_vote_index, by_voter_last_update>("comment_vote", "voter_last_update");
        initialize_index<comment_vote_index, by_comment_weight_voter>("comment_vote", "comment_weight_voter");

        // cc: the comment_report's attribute reports could not be reflect.
        // should implement visit method in report_info_type
        
//        initialize_index<comment_report_index, by_id>("comment_report", "id");
//        initialize_index<comment_report_index, by_comment>("comment_report", "comment");
//        initialize_index<comment_report_index, by_total_credit>("comment_report", "total_credit");
//        initialize_index<comment_report_index, by_last_update>("comment_report", "last_update");
        
        initialize_index<dynamic_global_property_index, by_id>("global_property", "id");
        initialize_index<dynamic_global_reward_property_index, by_id>("global_reward_property", "id");
        initialize_index<operation_index, by_location>("operation", "id");
        initialize_index<operation_index, by_transaction_id>("operation", "transaction_id");
        initialize_index<operation_index, by_location>("operation", "location");
        initialize_index<transaction_index, by_id>("transaction", "id");
        initialize_index<transaction_index, by_trx_id>("transaction", "trx_id");
        initialize_index<transaction_index, by_expiration>("transaction", "expiration");
        initialize_index<witness_index, by_id>("witness", "id");
        initialize_index<witness_index, by_name>("witness", "name");
        initialize_index<witness_index, by_schedule_time>("witness", "virtual_scheduled_time");
        initialize_index<witness_vote_index, by_id>("witness_vote", "id");
        initialize_index<witness_vote_index, by_account_witness>("witness_vote", "account_witness");
        initialize_index<witness_vote_index, by_witness_account>("witness_vote", "witness_account");
        initialize_index<witness_schedule_index, by_id>("witness_schedule", "id");
        
    }
    
    void database::initialize_indexed_query(){
        add_indexed_query<account_index, by_id, account_id_type>("account", "id");
        add_indexed_query<account_index, by_name, account_name_type>("account", "name");
        add_indexed_query<account_index, by_next_vesting_withdrawal, contento::time_point_sec>("account", "next_vesting_withdrawal", "id");
        add_indexed_query<account_index, by_balance, asset>("account", "balance", "id");
        add_indexed_query<account_index, by_vesting_shares, asset>("account", "vesting_shares", "id");
        add_indexed_query<admin_index, by_id, admin_id_type>("admin", "id");
        add_indexed_query<admin_index, by_name, account_name_type>("admin", "name");
        add_indexed_query<owner_authority_history_index, by_id, owner_authority_history_id_type>("owner_authority_history", "id");
        add_indexed_query<comment_index, by_id, comment_id_type>("comment", "id");
        add_indexed_query<comment_index, by_cashout_time, contento::time_point_sec>("comment", "cashout_time", "id");
        add_indexed_query<comment_index, by_permlink, account_name_type>("comment", "author", "permlink");
        add_indexed_query<comment_index, by_root, comment_id_type>("comment", "root_comment", "id");
        add_indexed_query<comment_vote_index, by_id, comment_vote_id_type>("comment_vote", "id");
        add_indexed_query<comment_vote_index, by_comment_voter, comment_id_type>("comment_vote", "comment", "voter");
        add_indexed_query<comment_vote_index, by_voter_comment, account_id_type>("comment_vote", "voter", "comment");
        add_indexed_query<operation_index, by_id, operation_id_type>("operation", "id");
        add_indexed_query<operation_index, by_transaction_id, transaction_id_type>("operation", "trx_id", "id");
        add_indexed_query<transaction_index, by_id, transaction_object_id_type>("transaction", "id");
        add_indexed_query<witness_index, by_id, witness_id_type>("witness", "id");
        add_indexed_query<witness_index, by_name, account_name_type>("witness", "name");
        add_indexed_query<witness_index, by_schedule_time, fc::uint128>("witness", "virtual_scheduled_time", "id");
        add_indexed_query<witness_vote_index, by_id, witness_vote_id_type>("witness_vote", "id");
        add_indexed_query<witness_vote_index, by_account_witness, account_id_type>("witness_vote", "account", "witness");
        add_indexed_query<witness_vote_index, by_witness_account, witness_id_type>("witness_vote", "witness", "account");
        add_indexed_query<witness_schedule_index, by_id, witness_schedule_id_type>("witness_schedule", "id");
    }
    
    // the where-clause conditions could contain one key or two keys
    // alway the first key as main key to be used in lower-bound for querying process.
    template<typename INDEX, typename TAG, typename KEY_TYPE>
    void database::add_indexed_query(std::string&& table_name, std::string&& main_key)
    {
        auto find_table_name = std::find(_table_names.begin(), _table_names.end(), table_name);
        if(find_table_name == _table_names.end()){
            std::cerr << "table " << table_name << " didn't register" << std::endl;
            return;
        }
        else{
            auto key = table_name + "|" + main_key;
            auto f = [this, main_key](const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::vector<Condition>& conditions){return query_indexed_table<INDEX, TAG, KEY_TYPE>(stmt, table_name, fields, main_key, conditions);};
            _indexed_tables[key] = f;
        }
    }
    
    template<typename INDEX, typename TAG, typename KEY_TYPE>
    void database::add_indexed_query(std::string&& table_name, std::string&& main_key, std::string&& second_key)
    {
        auto find_table_name = std::find(_table_names.begin(), _table_names.end(), table_name);
        if(find_table_name == _table_names.end()){
            std::cerr << "table " << table_name << " didn't register" << std::endl;
            return;
        }
        else{
            // in practical, as using union index, passing main key only is ok.
            // and of course, keys order is not importance.
            auto key0 = table_name + "|" + main_key;
            auto key1 = table_name + "|" + main_key + "|" + second_key;
            auto key2 = table_name + "|" + second_key + "|" + main_key;
            auto f = [this, main_key](const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::vector<Condition>& conditions){return query_indexed_table<INDEX, TAG, KEY_TYPE>(stmt, table_name, fields, main_key, conditions);};
            _indexed_tables[key0] = f;
            _indexed_tables[key1] = f;
            _indexed_tables[key2] = f;
        }
    }
    
    
    template<typename INDEX, typename TAG>
    void database::initialize_index(std::string&& table_name, std::string&& tag_name)
    {
        auto find_table_name = std::find(_table_names.begin(), _table_names.end(), table_name);
        if(find_table_name == _table_names.end()){
            _table_names.push_back(table_name);
            _chain_db -> add_index<INDEX>();
        }
        auto key = table_name + "|" + tag_name;
        auto f = [this](const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::vector<Condition>& conditions){return query_table<INDEX, TAG>(stmt, table_name, fields, conditions);};
        _tables[key] = f;
    }
    
    
    void database::query(const std::string& sql){
        hsql::SQLParserResult result;
        hsql::SQLParser::parse(sql, &result);
        
        assert(result.getStatement(0)->type() == hsql::kStmtSelect);
        const auto* stmt = (const hsql::SelectStatement*)result.getStatement(0);
        
        std::string table_name{stmt -> fromTable -> getName()};
        
        std::string order_by;
        
        std::vector<std::string> fields;
        std::vector<Condition> conditions;
        
        _parse_fields(stmt, fields);
        _parse_conditions(stmt, conditions);
        
        
        // when using indexed search, the order by argument will be ignored.
        // otherwise, the normol searching mode will be active.
        if(!conditions.empty())
        {
            std::string indexed_table_key = table_name;
            for(auto c: conditions)
                indexed_table_key += ("|" + std::string(c.name));
            
            auto choose_indexed_search = _indexed_tables.find(indexed_table_key);
            if (choose_indexed_search != _indexed_tables.end()){
                auto query_indexed_functor = _indexed_tables.at(indexed_table_key);
                query_indexed_functor(stmt, table_name, fields, conditions);
                return;
            }
        }
        
        if (stmt->order != nullptr)
            order_by = stmt -> order -> at(0) -> expr -> name;
        else
            order_by = "id";
        
        auto table_key = table_name + "|" + order_by;

        auto itr = _tables.find(table_key);

        if(itr == _tables.end()) {
            auto find_table_name = std::find(_table_names.begin(), _table_names.end(), table_name);
            if(find_table_name == _table_names.end())
                std::cerr << "the table: " << table_name << " doesn't exist" << std::endl;
            else
                std::cerr << "the order condition: " << order_by << "is invalid" << std::endl;
        } else {
            auto query_functor = _tables.at(table_key);
            query_functor(stmt, table_name, fields, conditions);
        }
    }


    template<typename INDEX, typename TAG>
    void database::query_table(const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::vector<Condition>& conditions)
    {

        const auto& idx = _chain_db ->get_index<INDEX>().indices().template get<TAG>();
        std::vector<fc::variant> columns;
        // lower_bound could do some filter. But it's hard to adapt any situation.
        // so I instead it from searching whole table.

        try {
            auto callback = (conditions.empty())? cmp_default : cmp_conditions;

            auto current = idx.begin();
            if(current != idx.end()) {
                for(; current != idx.end(); ++current)
                {
                    fc::variant v;
                    fc::to_variant((*current), v);
                    if(callback(v, conditions))
                        columns.push_back(v);
                }
                if(columns.empty())
                    std::cerr << "no items match the conditions" << std::endl;
                else
                    print_columns(columns, fields);
            }
            else{
                std::cerr << "empty" << std::endl;
            }
        }
        catch (const fc::key_not_found_exception&){}
    }
    
    template<typename INDEX, typename TAG, typename KEY_TYPE>
    void database::query_indexed_table(const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::string main_key, const std::vector<Condition>& conditions)
    {

        const auto& idx = _chain_db ->get_index<INDEX>().indices().template get<TAG>();
        std::vector<fc::variant> columns;
        
        Condition con;
        
        for(auto c: conditions){
            if(std::string(c.name) == main_key)
                con = c;
        }
        
        if(con.conType == ConditionType::conNull){
            std::cerr << "could not find" << main_key  << "in conditions" << std::endl;
            return;
        }
        
        auto callback = (conditions.empty())? cmp_default : cmp_conditions;
        
        try {
            KEY_TYPE k;
            fc::from_variant(con.val, k);
            auto current = idx.lower_bound(k);
            if(current != idx.end()){
                for(;current != idx.end();++current)
                {
                    fc::variant v;
                    fc::to_variant((*current), v);
                    if(v[main_key.c_str()].as_string() != con.val.as_string())
                        break;
                    if(callback(v, conditions))
                        columns.push_back(v);
                }
            }
            else {
                std::cerr << "empty" << std::endl;
            }

            if(columns.empty())
                std::cerr << "no items match the conditions" << std::endl;
            else
                print_columns(columns, fields);
        }
        catch (const fc::key_not_found_exception&){}

    }
    
    void database::print_columns(std::vector<fc::variant>& columns, const std::vector<std::string>& fields)
    {
        TablePrinter _tp(&std::cout);
        
        std::vector<std::vector<std::pair<fc::string, fc::string>>> entities;
        
        // can pass longest_value into function `extract` to save walking over expansing.
        // but which make the function dirty.
        std::map<fc::string, std::size_t> longest_values;

        for(auto current = columns.begin();current != columns.end();++current)
        {
            std::vector<std::pair<fc::string, fc::string>> vs;
            fc::extract(*current, vs);
            entities.push_back(vs);
        }
        
        for(auto row = entities.begin();row != entities.end();++row)
        {
            for(auto itr = row->begin();itr != row->end();++itr){
                auto key = itr -> first;
                auto value = itr -> second;
                auto it = longest_values.find(key);
                if(it == longest_values.end()){
                    auto length = (value.length() > key.length()) ? value.length(): key.length();
                    longest_values[key] = length > 4 ? length : 4;
                }
                else{
                    auto length = value.length();
                    if(length > longest_values[key])
                        longest_values[key] = length ;
                }
            }
        }
        
        _print_header(_tp, entities[0], longest_values, fields);
        _print_body(_tp, entities, fields);
        _print_footer(_tp);
        
    }
    
    
    void database::_print_header(TablePrinter& tp, std::vector<std::pair<fc::string, fc::string>>& entities, std::map<fc::string, std::size_t>& length_map, const std::vector<std::string>& fields) const
    {
        for(auto pair=entities.begin();pair != entities.end(); ++pair){
            auto key = pair -> first;
            if(!fields.empty()){
                auto should_display = std::find(fields.begin(), fields.end(), key);
                if (should_display == fields.end())
                    continue;
            }
            auto span = length_map[key];
            tp.AddColumn(key, span);
        }
        tp.PrintHeader();
    }
    
    void database::_print_body(TablePrinter& tp, std::vector<std::vector<std::pair<fc::string, fc::string>>>& entities, const std::vector<std::string>& fields) const
    {
        for(auto row=entities.begin();row != entities.end();++row){
            for(auto pair = row -> begin(); pair != row -> end(); ++ pair){
                auto key = pair -> first;
                if(!fields.empty()){
                    auto should_display = std::find(fields.begin(), fields.end(), key);
                    if (should_display == fields.end())
                        continue;
                }
                auto value = pair -> second;
                tp << value;
            }
        }
    }
    
    void database::_print_footer(TablePrinter& tp) const
    {
        tp.PrintFooter();
    }
    
    void database::_parse_fields(const hsql::SelectStatement* stmt, std::vector<std::string>& fields)
    {
        for (Expr* expr : *stmt->selectList){
            if(expr->type == hsql::ExprType::kExprStar){
                fields.push_back("*");
            }else if (expr->type == hsql::ExprType::kExprColumnRef) {
                fields.push_back(std::string(expr->name));
            }
        }
        
        auto is_star_in = std::find(fields.begin(), fields.end(), "*");
        
        if(is_star_in != fields.end()){
            fields.clear();
        }
    }
    
    void database::_parse_conditions(const hsql::SelectStatement * stmt, std::vector<Condition> & conditions)
    {
        std::vector<Expr*> expr_v;
        if (stmt -> whereClause != nullptr) {
            catch_expression(stmt -> whereClause, expr_v);
        }
        for(Expr* expr:expr_v){
            conditions.push_back(make_condition(expr->expr, expr->expr2));
        }
        
        std::sort(conditions.begin(), conditions.end(), [](Condition x, Condition y){
            return std::strcmp(x.name, y.name) < 0;
        });
    }
    


}
