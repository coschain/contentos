
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
        REGISTER(account_index);
        REGISTER(admin_index);
        REGISTER(owner_authority_history_index);
        REGISTER(block_summary_index);
        REGISTER(comment_index);
        REGISTER(comment_vote_index);
        REGISTER(dynamic_global_property_index);
        REGISTER(dynamic_global_reward_property_index);
        REGISTER(operation_index);
        REGISTER(transaction_index);
        REGISTER(witness_index);
        REGISTER(witness_vote_index);
        REGISTER(witness_schedule_index);
    }
    
    // hash_index is true_type otherwise false_type
    template<typename INDEX, typename TAG, typename MainKeyType>
    void database::pre_initialize_index(std::string& table_name, std::vector<std::string>& keys, std::true_type)
    {
        if(keys.empty()) return;
        initialize_index<INDEX, TAG>(table_name, keys[0]);
    }
    
    template<typename INDEX, typename TAG, typename MainKeyType>
    void database::pre_initialize_index(std::string& table_name, std::vector<std::string>& keys, std::false_type)
    {
        if(keys.empty()) return;
        initialize_index<INDEX, TAG>(table_name, keys[0]);
        boost_index<INDEX, TAG, MainKeyType>(table_name, keys[0], keys);
    }
    
    template<typename INDEX, typename TAG>
    void database::initialize_index(std::string& table_name, std::string& tag_name)
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
    
    template<typename INDEX, typename TAG, typename KEY_TYPE>
    void database::boost_index(std::string& table_name, std::string& main_key, std::vector<std::string>& keys)
    {
        auto find_table_name = std::find(_table_names.begin(), _table_names.end(), table_name);
        if(find_table_name == _table_names.end()){
            std::cerr << "table " << table_name << " didn't register" << std::endl;
            return;
        }
        std::sort(keys.begin(), keys.end());
        size_t size = keys.size();
        auto f = [this, main_key](const hsql::SelectStatement* stmt, const std::string table_name, const std::vector<std::string>& fields, const std::vector<Condition>& conditions){return query_indexed_table<INDEX, TAG, KEY_TYPE>(stmt, table_name, fields, main_key, conditions);};
        do{
            std::stringstream ss;
            for(size_t i = 0;i < size;i++){
                ss << "|";
                ss << keys[i];
            }
            std::string key = table_name + ss.str();
            _indexed_tables[key] = f;
        } while(std::next_permutation(keys.begin(), keys.end()));
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
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database * db, std::true_type){
        using iterator = typename index_type::iterator;
        using tag_type = typename tag_from_iterator<MultiIndexContainer,iterator>::type;
        using main_key_type = typename boost::multi_index::detail::nth_key_from_value<members_or_composite_key, 0>::type::result_type;
        std::string  members_str = boost::core::demangle(typeid(members_or_composite_key).name());
        initialize_from_metadata<MultiIndexContainer, tag_type, main_key_type, index_type>(db, members_str);
    }
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database * db, std::false_type){
        using iterator = typename index_type::iterator;
        using tag_type = typename tag_from_iterator<MultiIndexContainer,iterator>::type;
        using main_key_type = typename members_or_composite_key::result_type;
        std::string  members_str = boost::core::demangle(typeid(members_or_composite_key).name());
        initialize_from_metadata<MultiIndexContainer, tag_type, main_key_type, index_type>(db, members_str);
    }
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database * db) {
        choose_member_or_composite<MultiIndexContainer, members_or_composite_key, index_type>
        (db, std::integral_constant<bool, is_composite_key<members_or_composite_key>::yes>());
    }
    
    template<typename MultiIndexContainer, typename Tag, typename MainKeyType, typename IndexType>
    void choose_hash_or_order_index(database * db, std::string& table_name, std::vector<std::string>& keys){
        db->pre_initialize_index<MultiIndexContainer, Tag, MainKeyType>(table_name, keys, std::integral_constant<bool, is_hash_index<IndexType>::yes>());
    }
    
    template<typename MultiIndexContainer, typename Tag, typename MainKeyType, typename IndexType>
    void initialize_from_metadata(database* db, std::string& metadata)
    {
        std::regex member_regex("&\\((.+?)::(.+?)::(.+?)_object::(.+?)\\)");
        auto words_begin =
        std::sregex_iterator(metadata.begin(), metadata.end(), member_regex);
        auto words_end = std::sregex_iterator();
        std::string table_name;
        std::vector<std::string> keys;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            table_name = match[3].str();
            keys.push_back( match[4].str());
        }
        choose_hash_or_order_index<MultiIndexContainer, Tag, MainKeyType, IndexType>(db, table_name, keys);
    }
}
