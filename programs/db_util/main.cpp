#include <iostream>
#include <boost/filesystem.hpp>
#include <dorothy/database.hpp>

// if not in debug mode, should use fc_assert replaces assert.
// but it would introduce fc library, it's huge.
// so i just set ndebug to enable assert.
// #define NDEBUG

// // namespace bfs = boost::filesystem;
// using bprinter::TablePrinter;
// namespace dorothy {

//     // pimpl 这里 initialize_indexes 可能经常变，这部分单独抽出来放在 impl 里面
//     // class database_impl
//     // {
//     //     public:
//     //         database_impl(database& self);

//     //         void initialize_indexes();

//     //         database& _self;

//     // };

//     typedef contento::chain::dynamic_global_property_index dynamic_global_property_index;
//     typedef contento::chain::dynamic_global_reward_property_index dynamic_global_reward_property_index;
//     typedef contento::chain::comment_index comment_index;
//     typedef contento::chain::account_index account_index;
//     typedef std::pair<std::string, uint> column;


//     class printer
//     {
//         public:
//             template<typename Iterator>
//             void print(TablePrinter& tp, Iterator current)
//             {
//                 tp << current -> id._id << std::string(current -> name) << current -> balance.to_string()
//                     << current -> vesting_shares.to_string() << current -> next_vesting_withdrawal.sec_since_epoch()
//                     << std::string(current -> to_withdraw) << std::string(current -> withdrawn);
//             }
//     };



//     class database:  public chainbase::database 
//     {
//         public:
//             database();
//             ~database();

//             void open(const boost::filesystem::path& dir);
//             void close();

//             void initialize_indexes();

//             void query(std::string& sql );

//             void query_dynamic_global_property();
//             void query_dynamic_global_reward_property();
//             void query_comment(const hsql::SelectStatement* stmt);
//             void query_account();

//             // void _print_comment(TablePrinter& tp, )
            
//             // template<typename index_type, typename by_tag>
//             // const typename boost::multi_index::index<index_type, by_tag>::type& query_index() const
//             // {
//             //     return _chain_db -> get_index<index_type>().indices().template get<by_tag>();
//             // }

//             void print_header(TablePrinter& tp, std::vector<column>& column );

//             template<typename index_type, typename by_tag, typename printer>
//             void print_body(TablePrinter& tp)
//             {
//                 const auto& idx = _chain_db -> get_index<index_type>().indices().template get<by_tag>();
//                 for(auto current=idx.begin(); current != idx.end(); ++current)
//                 {
//                     printer p = printer();
//                     p.template print<decltype(current)>(tp, current);
//                 } 
//             }
            

//             // database_impl& _self;
//             std::shared_ptr<chainbase::database> _chain_db;
//     };

//     database::database()
//     : _chain_db(std::make_shared<chainbase::database>()){}

//     database::~database()
//     {
//         if(_chain_db)
//         {
//            _chain_db->close();
//         }
//     }

//     void database::initialize_indexes()
//     {
//        _chain_db -> add_index<dynamic_global_property_index>(); 
//        _chain_db -> add_index<dynamic_global_reward_property_index>();
//        _chain_db -> add_index<comment_index>();
//        _chain_db -> add_index<account_index>();
//     }



//     void database::open(const boost::filesystem::path& dir)
//     {
//         _chain_db->open(dir);
//         initialize_indexes();
//     }

//     void database::print_header(TablePrinter& tp, std::vector<column>& columns )
//     {
//         uint span(0);
//         uint length(0);
//         // to require the minium column size
//         for(auto iter=columns.begin(); iter!=columns.end();++iter){
//             if(iter -> second == 0){
//                 length = (iter -> first).length();
//                 span = ((length >= 4) ? length: 4);
//             }
//             else{
//                 span = iter -> second;
//             }
//             tp.AddColumn(iter->first, span);
//         }
//         tp.PrintHeader();
//     }

//     // template<typename index_type, typename by_tag>
//     // void database::print_body(TablePrinter& tp, std::vector<column>& columns)
//     // {
//     //     const auto& idx = _chain_db -> get_index<index_type>().indices().template get<by_tag>();

//     // }

//     void database::query_dynamic_global_property()
//     {

//         TablePrinter tp(&std::cout);

//         std::vector<column> columns = {
//             {"id", 0}, {"head_block_number", 0}, {"time", 10}, {"current_witness", 0}, {"virtual_supply", 20},
//             {"current_supply", 20}, {"vesting_shares", 0}, {"last_irrversible_block", 00}
//         };
       
//         print_header(tp, columns);

//         _chain_db->with_read_lock( [&]()
//         {
//             const auto& idx = _chain_db -> get_index<dynamic_global_property_index>().indices();

//             for(auto current=idx.begin(); current != idx.end(); ++current){

//                 tp << (current->id._id) << (current -> head_block_number) << (current -> time.sec_since_epoch()) << 
//                 (std::string(current -> current_witness)) << (current -> virtual_supply.to_string()) << 
//                 (current ->current_supply.to_string()) << (current -> total_vesting_shares.to_string()) << 
//                 (current -> last_irreversible_block_num);
//             }
//         });
//         tp.PrintFooter();
//     }

//     void database::query_comment(const hsql::SelectStatement* stmt)
//     {
//         TablePrinter tp(&std::cout);
//         std::string field;
//         if (stmt->order != nullptr) {
//             field = stmt -> order -> at(0) -> expr -> name;
//         }
//         else {
//             field = "id";
//         }

//         // if(field == "id")
//         std::vector<column> columns = {
//             {"id", 0}, {"is_subject", 0}, {"parent_author", 0}, {"parent_permlink", 0}, {"author", 15},
//             {"permlink", 20}, {"title", 20}, 
//             {"net_rshares", 10}, 
//             {"created", 10}, {"cashout_time", 10}
//         };
//         print_header(tp, columns);
//         _chain_db->with_read_lock( [&]()
//         {

//             // print_body<comment_index, contento::chain::by_id>();
//             const auto& idx = _chain_db -> get_index<comment_index>().indices();
//             // const auto& idx = query_index<comment_index, contento::chain::by_id>();
//             // idx = idx.get<by_account>;
//             for(auto current=idx.begin(); current != idx.end(); ++current){
//                 tp << (current->id._id);
//                 (current -> root_comment == current -> id) ? tp << "Yes":tp << "No";
//                 tp << std::string(current -> parent_author) << current -> parent_permlink << 
//                 std::string(current -> author) << current -> permlink << current -> title 
//                 << std::string(current -> net_rshares)
//                 << current -> created.sec_since_epoch() << current -> cashout_time.sec_since_epoch();
//             }
//         });
//         tp.PrintFooter();

//     }

//     void database::query_account()
//     {
//         TablePrinter tp(&std::cout);
//         std::vector<column> columns = {
//             {"id", 0}, {"name", 12}, {"balance", 15}, {"vesting_shares", 15}, 
//             {"next_vesting_withdrawal", 10}, {"to_withdraw", 10}, {"withdrawn", 10}
//         };
//         print_header(tp, columns);
//         _chain_db->with_read_lock( [&]()
//         {
//             // const auto& idx = _chain_db -> get_index<account_index>().indices();
//             // for(auto current=idx.begin(); current != idx.end(); ++current){
//             //     // tp << current -> id._id << std::string(current -> name) << current -> balance.to_string()
//             //     // << current -> vesting_shares.to_string() << current -> next_vesting_withdrawal.sec_since_epoch()
//             //     // << std::string(current -> to_withdraw) << std::string(current -> withdrawn);
//             //     _print_account_line<>(tp, current);
//             // } 
//             print_body<account_index, contento::chain::by_id, dorothy::printer>(tp);
//         });
//         tp.PrintFooter();
//     }

//     void database::query_dynamic_global_reward_property()
//     {
//         // _chain_db->with_read_lock( [&]()
//         // {

//         // }); 
//     }

//     void database::query(std::string& sql)
//     {
//         hsql::SQLParserResult result;
//         hsql::SQLParser::parse(sql, &result);
//         // std::string a("dynamic_property");

//         // just process the first statement and no more
        
//         assert(result.getStatement(0)->type() == hsql::kStmtSelect);
//         const auto* stmt = (const hsql::SelectStatement*)result.getStatement(0);
//         // printStatementInfo(stmt);
//         // std::string field(((const hsql::SelectStatement*)stmt)->order->at(0)->expr->name);
//         std::string field(stmt -> order -> at(0) -> expr -> name);
//         std::cout << field << "\n";
//         // query_account(stmt);
//         query_account();
//         // std::string table_name(((const hsql::SelectStatement*)stmt) -> fromTable -> getName());
//         // if (table_name == "dynamic_global_property"){
//         //     query_dynamic_global_property();
//         // }else if (table_name == "dynamic_global_reward_property") {
//         //     query_dynamic_global_reward_property();
//         // } else if (table_name == "comment") {
//         //     query_comment();
//         // } else if(table_name == "account") {
//         //     query_account();
//         // }
//         // else {
//         //      std::cerr << "unknown table:" + table_name << "\n";

//         // }

//     }

//     void database::close()
//     {
//         if(_chain_db)
//         {
//            _chain_db->close();
//         } 
//     }

// }

int main(int argc, char** argv) {

    std::cerr << "------------------------------------------------------\n\n";
    std::cerr << "            start db querying\n\n";                       
    std::cerr << "------------------------------------------------------\n";
    boost::filesystem::path dir("/Users/aprocysanae/contento/steem-stable/build/programs/steemd/Debug/witness_node_data_dir/blockchain");
    dorothy::database database;
    database.open(dir);
    std::string sql("select * from account order by id");
    database.query(sql);
    database.close();
}