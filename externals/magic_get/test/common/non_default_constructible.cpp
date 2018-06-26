// Copyright (c) 2017 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_PFR_TEST_PRECISE
#   include <boost/pfr/precise/tuple_size.hpp>
#elif defined(BOOST_PFR_TEST_FLAT)
#   include <boost/pfr/flat/tuple_size.hpp>
#else
#   error Misused test
#endif

struct X {
    X(int) {}
};
struct S { X x0; X x1; int x2; X x3; };

int main() {
#ifdef BOOST_PFR_TEST_PRECISE
    static_assert(boost::pfr::tuple_size_v<S> == 4, "");

    struct S5_0 { int x0; int x1; int x2; int x3; X x4; };
    static_assert(boost::pfr::tuple_size_v<S5_0> == 5, "");

    struct S5_1 { X x0; int x1; int x2; int x3; int x4; };
    static_assert(boost::pfr::tuple_size_v<S5_1> == 5, "");

    struct S5_2 { int x0; int x1; X x2; int x3; int x4; };
    static_assert(boost::pfr::tuple_size_v<S5_2> == 5, "");

    struct S5_3 { int x0; int x1; X x2; int x3; X x4; };
    static_assert(boost::pfr::tuple_size_v<S5_3> == 5, "");

    struct S5_4 { X x0; X x1; X x2; X x3; X x4; };
    static_assert(boost::pfr::tuple_size_v<S5_4> == 5, "");

    struct S6 { X x0; X x1; X x2; X x3; X x4;  X x5;};
    static_assert(boost::pfr::tuple_size_v<S6> == 6, "");
#elif defined(BOOST_PFR_TEST_FLAT)
    return boost::pfr::flat_tuple_size_v<S>;
#endif
}

