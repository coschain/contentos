/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once

#include <cosiolib/cosio.hpp>
#include <cosiolib/token.hpp>
#include <cosiolib/reflect.hpp>
#include <cosiolib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef eosio::generic_currency< eosio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef eosio::generic_currency< eosio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef eosio::generic_currency< eosio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

