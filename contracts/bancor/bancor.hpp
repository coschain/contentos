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
   typedef cosio::generic_currency< cosio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef cosio::generic_currency< cosio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef cosio::generic_currency< cosio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

