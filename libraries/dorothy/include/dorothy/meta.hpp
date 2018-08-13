#pragma once

#include <iostream>
#include <regex>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/core/demangle.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

namespace dorothy {
    template<typename Map,typename Index>
    struct add_to_iterator_to_tag_map:
    boost::mpl::fold<
        typename Index::tag_list,
        Map,
        boost::mpl::insert<
        boost::mpl::_1,
        boost::mpl::pair<typename Index::iterator,boost::mpl::_2>
        >
    >
    {};

    template<typename MultiIndexContainer>
    struct iterator_to_tag_map:
    boost::mpl::fold<
        typename MultiIndexContainer::index_type_list,
        boost::mpl::map<>,
        add_to_iterator_to_tag_map<boost::mpl::_1,boost::mpl::_2>
    >
    {};

    template<typename MultiIndexContainer,typename Iterator>
    struct tag_from_iterator:
    boost::mpl::at<
        typename iterator_to_tag_map<MultiIndexContainer>::type,
        Iterator
    >
    {};

}
