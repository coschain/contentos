
#include <dorothy/database.hpp>
#include <fc/variant.hpp>
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
        initialize_index<account_index, by_id>("account", "id");
        initialize_index<account_index, by_name>("account", "name");
        initialize_index<account_index, by_next_vesting_withdrawal>("account", "next_vesting_withdrawal");
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
        auto f = [this](const hsql::SelectStatement* stmt, const std::vector<std::string>& fields){return query_table<INDEX, TAG>(stmt, fields);};
        _tables[key] = f;
    }
    
    
    void database::query(const std::string& sql){
        hsql::SQLParserResult result;
        hsql::SQLParser::parse(sql, &result);
        
        assert(result.getStatement(0)->type() == hsql::kStmtSelect);
        const auto* stmt = (const hsql::SelectStatement*)result.getStatement(0);
        
        std::string table_name{stmt -> fromTable -> getName()};
        
        std::string order_by;
        
        if (stmt->order != nullptr) {
            order_by = stmt -> order -> at(0) -> expr -> name;
        }
        else {
            order_by = "id";
        }
        
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
            
            std::vector<std::string> fields;
            
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
               
            query_functor(stmt, fields);
               
            
        }
    }

    template<typename INDEX, typename TAG>
    void database::query_table(const hsql::SelectStatement* stmt, const std::vector<std::string>& fields)
    {
        
        const auto& idx = _chain_db ->get_index<INDEX>().indices().template get<TAG>();

        std::vector<fc::variant> columns;
        auto current = idx.begin();
        if(current != idx.end()) {
            for(current=idx.begin(); current != idx.end(); ++current)
            {
                fc::variant v;
                fc::to_variant((*current), v);
                columns.push_back(v);
            }
            print_columns(columns, fields);
        }
        else{
            std::cout << "empty" << std::endl;
        }

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
                if(it == longest_values.end())
                    longest_values[key] = value.length() > 4 ? value.length() : 4;
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

}
