#include <iostream>
#include <cassert>
#include <boost/filesystem.hpp>
#include "hsql/SQLParser.h"
#include "hsql/sql/statements.h"
#include "hsql/sql/Expr.h"
#include "table_printer.h"
#include "hsql/util/sqlhelper.h"
#include <dorothy/util.hpp>
#include <dorothy/callback.hpp>
#include <contento/chain/global_property_object.hpp>
#include <contento/chain/global_reward_property_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/chain/account_object.hpp>
#include <fc/variant.hpp>

using bprinter::TablePrinter;

using namespace contento::chain;

typedef std::pair<std::string, uint> column;

namespace dorothy {
    using hsql::OperatorType;

    typedef hsql::Expr Expr;
    
   
    

    class database {
        public:

            database();
            ~database();

            void open(const boost::filesystem::path& );
            void close();

            void initialize_indexes();
        
            void add_callback_by_conditions(std::string&& table, std::string&& conditions, std::function<bool(fc::variant&, const std::vector<Condition>&)>);
        
            template<typename INDEX, typename TAG> void initialize_index(std::string&&, std::string&&);
        
            
            void query(const std::string& );
        
        template<typename INDEX, typename TAG> void query_table(const hsql::SelectStatement*, const std::string, const std::vector<std::string>&, const std::vector<Condition>&);
        
            void print_columns(std::vector<fc::variant>&, const std::vector<std::string>& );
        
            std::shared_ptr<chainbase::database> _chain_db;
            std::vector<std::string> _table_names;
            std::map<std::string, std::function<void(const hsql::SelectStatement*, const std::string, const std::vector<std::string>&, const std::vector<Condition>&)>> _tables;
            std::map<std::string, std::vector<std::string>> _selected_fields;
            std::map<std::string, std::function<bool(fc::variant&, const std::vector<Condition>&)>> _callback_by_conditions;
        
        private:
            void _print_header(TablePrinter&, std::vector<std::pair<fc::string, fc::string>>&, std::map<fc::string, std::size_t>&, const std::vector<std::string>&) const;
            void _print_body(TablePrinter&, std::vector<std::vector<std::pair<fc::string, fc::string>>>&, const std::vector<std::string>&) const;
            void _print_footer(TablePrinter&) const;
        
            void _parse_fields(const hsql::SelectStatement*, std::vector<std::string>&);
            // copy Condition into vector is ok here. It's tiny.
            void _parse_conditions(const hsql::SelectStatement*, std::vector<Condition>&);
            void _catch_expression(Expr*, std::vector<Expr*>& );

    };
}
