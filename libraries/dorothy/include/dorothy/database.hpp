#include <iostream>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <boost/filesystem.hpp>
#include "hsql/SQLParser.h"
#include "hsql/sql/statements.h"
#include "hsql/sql/Expr.h"
#include "table_printer.h"
#include "hsql/util/sqlhelper.h"
#include <dorothy/util.hpp>
#include <dorothy/callback.hpp>
#include <dorothy/meta.hpp>
#include <contento/chain/global_property_object.hpp>
#include <contento/chain/global_reward_property_object.hpp>
#include <contento/chain/comment_object.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/block_summary_object.hpp>
#include <contento/chain/history_object.hpp>
#include <contento/chain/transaction_object.hpp>
#include <contento/chain/witness_objects.hpp>



using bprinter::TablePrinter;

using namespace contento::chain;

typedef std::pair<std::string, uint> column;

namespace dorothy {
    
    class database {
        public:

            database();
            ~database();

            void open(const boost::filesystem::path& );
            void close();

            void initialize_indexes();
        
            template<typename INDEX, typename TAG, typename MainKeyType> void pre_initialize_index(std::string&, std::vector<std::string>&, std::true_type);
        
            template<typename INDEX, typename TAG, typename MainKeyType> void pre_initialize_index(std::string&, std::vector<std::string>&, std::false_type);
        
            template<typename INDEX, typename TAG> void initialize_index(std::string&, std::string&);

            template<typename INDEX, typename TAG, typename KEY_TYPE>
            void boost_index(std::string&, std::string&, std::vector<std::string>&);
            
            void query(const std::string& );
        
            template<typename INDEX, typename TAG> void query_table(const hsql::SelectStatement*, const std::string, const std::vector<std::string>&, const std::vector<Condition>&);
        
            template<typename INDEX, typename TAG, typename KEY_TYPE> void query_indexed_table(const hsql::SelectStatement* , const std::string , const std::vector<std::string>& , const std::string , const std::vector<Condition>&);
        
            void print_columns(std::vector<fc::variant>&, const std::vector<std::string>& );
        
            std::shared_ptr<chainbase::database> _chain_db;
            std::vector<std::string> _table_names;
            std::map<std::string, std::function<void(const hsql::SelectStatement*, const std::string, const std::vector<std::string>&,const std::vector<Condition>&)>> _tables;
        
            std::map<std::string, std::function<void(const hsql::SelectStatement*, const std::string, const std::vector<std::string>&,const std::vector<Condition>&)>> _indexed_tables;
        
            std::map<std::string, std::vector<std::string>> _selected_fields;
        
        private:
            void _print_header(TablePrinter&, std::vector<std::pair<fc::string, fc::string>>&, std::map<fc::string, std::size_t>&, const std::vector<std::string>&) const;
            void _print_body(TablePrinter&, std::vector<std::vector<std::pair<fc::string, fc::string>>>&, const std::vector<std::string>&) const;
            void _print_footer(TablePrinter&) const;
        
            void _parse_fields(const hsql::SelectStatement*, std::vector<std::string>&);
            // copy Condition into vector is ok here. It's tiny.
            void _parse_conditions(const hsql::SelectStatement*, std::vector<Condition>&);
    };
    
    template<typename T> char test_composite_key(int T::key_extractor_tuple::*);
    template<typename T> int test_composite_key(...);
    
    template<typename T>
    struct is_composite_key{
        static const bool yes = sizeof(test_composite_key<T>(0)) == sizeof(char);
    };
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database *, std::true_type);
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database *, std::false_type);
    
    template<typename MultiIndexContainer, typename members_or_composite_key, typename index_type>
    void choose_member_or_composite(database *);
    
    template<typename T> char test_hash_index(int T::hasher::*);
    template<typename T> int test_hash_index(...);
    
    template<typename T>
    struct is_hash_index{
        static const bool yes = sizeof(test_hash_index<T>(0)) == sizeof(char);
    };
    
//    template<typename MultiIndexContainer, typename Tag, typename MainKeyType>
//    void choose_hash_or_order_index(database *, std::string&, std::vector<std::string>&, std::true_type);
//
//    template<typename MultiIndexContainer, typename Tag, typename MainKeyType>
//    void choose_hash_or_order_index(database *, std::string&, std::vector<std::string>&, std::false_type);
    
    template<typename MultiIndexContainer, typename Tag, typename MainKeyType, typename IndexType>
    void choose_hash_or_order_index(database * , std::string&, std::vector<std::string>& );
    
    template<typename MultiIndexContainer, typename Tag, typename MainKeyType, typename IndexType>
    void initialize_from_metadata(database *, std::string&);
    
    template<typename MultiIndexContainer>
    struct initialize
    {
        initialize(database* db):db(db){}
        
        template< typename U > void operator()(U x)
        {
            using index_type = typename MultiIndexContainer::template nth_index<x>::type;
            using members_or_composite_key = typename index_type::key_from_value;
            choose_member_or_composite<MultiIndexContainer, members_or_composite_key, index_type>(db);
        }
        
        database* db;
    };
    
    template<typename MultiIndexContainer>
    struct bootstrap
    {
        void operator()(database* db)
        {
            using size = typename MultiIndexContainer::index_type_list::size;
            boost::mpl::for_each< boost::mpl::range_c<int,0,size::value> >( initialize<MultiIndexContainer>(db) );
        }
    };


    #define REGISTER(MultiIndex) {bootstrap<MultiIndex> _T;_T(this);}

}
