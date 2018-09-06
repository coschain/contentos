#pragma once

#include <contento/chain/config.hpp>
#include <contento/chain/types.hpp>

namespace contento { namespace chain {

using action_name    = contento::chain::action_name;

struct setcode {
   account_name                     account;
   uint8_t                          vmtype = 0;
   uint8_t                          vmversion = 0;
   uint8_t                          compression=0;
   bytes                            code;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setcode);
   }
};

struct setabi {
   account_name                     account;
   uint8_t                          compression=0;
   bytes                            abi;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setabi);
   }
};


struct onerror {
   uint128_t      sender_id;
   bytes          sent_trx;

   onerror( uint128_t sid, const char* data, size_t len )
   :sender_id(sid),sent_trx(data,data+len){}

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(onerror);
   }
};

} } /// namespace contento::chain

FC_REFLECT( contento::chain::setcode                          , (account)(vmtype)(vmversion)(compression)(code) )
FC_REFLECT( contento::chain::setabi                           , (account)(compression)(abi) )
FC_REFLECT( contento::chain::onerror                          , (sender_id)(sent_trx) )
