#include <iostream>
#include <cassert>
#include <boost/filesystem.hpp>
#include "hsql/SQLParser.h"
#include "hsql/sql/statements.h"
#include "hsql/sql/Expr.h"
#include "table_printer.h"
#include "hsql/util/sqlhelper.h"

#include <contento/chain/global_property_object.hpp>
#include <contento/chain/global_reward_property_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/chain/account_object.hpp>

using bprinter::TablePrinter;

using namespace contento::chain;

//typedef chain::dynamic_global_property_index dynamic_global_property_index;
//typedef chain::dynamic_global_reward_property_index dynamic_global_reward_property_index;
//typedef chain::comment_index comment_index;
//typedef chain::account_index account_index;
typedef std::pair<std::string, uint> column;

namespace dorothy {
    using hsql::OperatorType;

    typedef hsql::Expr Expr;
    
    template<typename TAG>
    struct tag { typedef TAG type; };
    

    class database {
        public:

            database();
            ~database();

            void open(const boost::filesystem::path& );
            void close();

            void initialize_indexes();
        
            template<typename INDEX, typename TAG> void initialize_index(std::string&&, std::string&&);
        
            
            void query(const std::string& );
        
            template<typename INDEX, typename TAG> void query_table(const hsql::SelectStatement*, const std::vector<std::string>& );
        
            void print_columns(std::vector<fc::variant>&, const std::vector<std::string>& );
        
            std::shared_ptr<chainbase::database> _chain_db;
            std::vector<std::string> _table_names;
            std::map<std::string, std::function<void(const hsql::SelectStatement*,  std::vector<std::string>&)>> _tables;
            std::map<std::string, std::vector<std::string>> _selected_fields;
        
        private:
            void _print_header(TablePrinter&, std::vector<std::pair<fc::string, fc::string>>&, std::map<fc::string, std::size_t>&, const std::vector<std::string>&) const;
            void _print_body(TablePrinter&, std::vector<std::vector<std::pair<fc::string, fc::string>>>&, const std::vector<std::string>&) const;
            void _print_footer(TablePrinter&) const;

    };
}
