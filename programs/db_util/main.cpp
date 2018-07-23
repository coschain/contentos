#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <dorothy/database.hpp>
#include <fc/filesystem.hpp>


namespace bpo = boost::program_options;

int main(int argc, char** argv) {

    bpo::options_description app_options("db_util");
    app_options.add_options()
            ("help,h", "Print this help message and exit.")
            ("data-dir,d", bpo::value<boost::filesystem::path>()->default_value("witness_node_data_dir"), "Directory containing databases, configuration file, etc.")
            ("version,v", "Print steemd version and exit.");

    bpo::variables_map options;
    
    bpo::store(bpo::parse_command_line(argc, argv, app_options), options);

    if( options.count("version") )
    {
        std::cout << "version: " << "0.1.2" << "\n";
        return 0;
    }

    if( options.count("help") )
    {
        std::cout << "using -d to point the blockchain dir then use it as a normal readonly db client." << "\n";
        return 0;
    }

    fc::path data_dir;
    if( options.count("data-dir") )
    {
        data_dir = options["data-dir"].as<boost::filesystem::path>();
        if( data_dir.is_relative() )
            data_dir = fc::current_path() / data_dir;
    }
    else {
        std::cerr << "please point the data dir contains contento's blockchain." << "\n";
        return 0;
    }
    if( !fc::exists(data_dir) ){
        std::cerr << "please point the data dir contains contento's blockchain." << "\n";
        return 0;
    }

    fc::path blockchain_dir;

    blockchain_dir = data_dir /  "blockchain";

    if( !fc::exists(blockchain_dir) ){
        std::cerr << "please point the data dir contains contento's blockchain." << "\n";
        return 0;
    }

    std::cerr << "------------------------------------------------------\n\n";
    std::cerr << "            start db querying\n\n";                       
    std::cerr << "------------------------------------------------------\n";
    dorothy::database database;
    database.open(blockchain_dir);

//     std::string sql("select * from account where name='null'");
//     database.query(sql);
    std::string sql;
    std::cout << "\n>> ";
    while (std::getline(std::cin, sql))
    {
        database.query(sql);
        std::cout << "\n>> ";
    }
    database.close();
    std::cout << "db_util quit" << std::endl;
}
