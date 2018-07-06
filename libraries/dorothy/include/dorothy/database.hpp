#include <iostream>
#include <cassert>
#include <boost/filesystem.hpp>
#include "hsql/SQLParser.h"
#include "hsql/sql/statements.h"
#include "hsql/sql/Expr.h"
#include "table_printer.h"

#include <contento/chain/global_property_object.hpp>
#include <contento/chain/global_reward_property_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/chain/account_object.hpp>

using bprinter::TablePrinter;

typedef contento::chain::dynamic_global_property_index dynamic_global_property_index;
typedef contento::chain::dynamic_global_reward_property_index dynamic_global_reward_property_index;
typedef contento::chain::comment_index comment_index;
typedef contento::chain::account_index account_index;
typedef std::pair<std::string, uint> column;

namespace dorothy {
    using hsql::OperatorType;

    typedef hsql::Expr Expr;

    class database {
        public:
            database();
            ~database();

            void open(const boost::filesystem::path& dir);
            void close();

            void catch_expression(Expr* expr, std::vector<Expr*>& expr_v);

            void initialize_indexes();

            void query(std::string& sql );

            void query_dynamic_global_property(const hsql::SelectStatement* stmt);
            void query_dynamic_global_reward_property(const hsql::SelectStatement* stmt);
            void query_comment(const hsql::SelectStatement* stmt);
            void query_account(const hsql::SelectStatement* stmt);

            void print_header(TablePrinter& tp, std::vector<column>& column );

            template<typename index_type, typename by_tag, typename printer>
            void print_body(TablePrinter& tp);

            template<typename index_type, typename by_tag,  typename printer, typename compare_key>
            void print_body(TablePrinter& tp, compare_key&& key);

            void print_footer(TablePrinter& tp);
            
            std::shared_ptr<chainbase::database> _chain_db;
    };
}