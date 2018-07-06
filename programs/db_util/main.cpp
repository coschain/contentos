#include <iostream>
#include <boost/filesystem.hpp>
#include <dorothy/database.hpp>

int main(int argc, char** argv) {

    std::cerr << "------------------------------------------------------\n\n";
    std::cerr << "            start db querying\n\n";                       
    std::cerr << "------------------------------------------------------\n";
    boost::filesystem::path dir("/Users/aprocysanae/contento/steem-stable/build/programs/steemd/Debug/witness_node_data_dir/blockchain");
    dorothy::database database;
    database.open(dir);

    // std::string sql("select * from account where name = 'initminer'  order by name");
    // database.query(sql);
    std::string sql;
    std::cout << "\n>> ";
    while (std::getline(std::cin, sql))
    {
        database.query(sql);
        std::cout << "\n>> "; 
    }
    database.close();
    std::cout << "quit";
}
