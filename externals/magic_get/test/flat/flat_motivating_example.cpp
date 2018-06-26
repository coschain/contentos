// requires: C++14
#include <iostream>
#include "boost/pfr.hpp"

struct my_struct { // no ostream operator defined!
    int i;
    char c;
    double d;
};

int main() {
    using namespace boost::pfr::flat_ops; // ostream operator out-of-the-box for all PODs!

    my_struct s{100, 'H', 3.141593};
    std::cout << "my_struct has " << boost::pfr::flat_tuple_size<my_struct>::value
        << " fields: " << s << "\n";
}
