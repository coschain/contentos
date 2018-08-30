#pragma once

#include <contento/protocol/asset.hpp>

namespace contento { namespace chain { namespace util {

using contento::protocol::asset;
using contento::protocol::price;

inline asset to_sbd( const price& p, const asset& steem )
{
//    FC_ASSERT( steem.symbol == STEEM_SYMBOL );
//    if( p.is_null() )
//       return asset( 0, SBD_SYMBOL );
//    return steem * p;
    return asset(0, COC_SYMBOL);
}

inline asset to_steem( const price& p, const asset& sbd )
{
//    FC_ASSERT( sbd.symbol == SBD_SYMBOL );
//    if( p.is_null() )
//       return asset( 0, STEEM_SYMBOL );
//    return sbd * p;
    return asset(0, COC_SYMBOL);
}

} } }
