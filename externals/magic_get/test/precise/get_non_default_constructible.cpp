// Copyright (c) 2017 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/pfr/precise.hpp>
#include <boost/core/lightweight_test.hpp>

template <class T>
struct non_default_constructible {
    T val_;

    non_default_constructible() = delete;
    template <class U> non_default_constructible(U&& v){}
};

struct Foo {
    non_default_constructible<int> a;
};

int main() {
#if BOOST_PFR_USE_LOOPHOLE || BOOST_PFR_USE_CPP17
    Foo f{0};
    f.a.val_ = 5;

    BOOST_TEST_EQ(boost::pfr::get<0>(f).val_, 5);
    return boost::report_errors();
#endif
}
