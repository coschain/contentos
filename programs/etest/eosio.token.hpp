/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class token : public contract {
      public:
         token( account_name self ):contract(self){}

         void create( account_name issuer,
                      asset        maximum_supply);

         void issue( account_name to, asset quantity, string memo );

         void transfer( account_name from,
                        account_name to,
                        asset        quantity,
                        string       memo );
      
      
         inline asset get_supply( symbol_name sym )const;
         
         inline asset get_balance( account_name owner, symbol_name sym )const;
         
         void testcb( account_name name );
         void testchain( account_name name );
         void testfloat( account_name name );
         void testcrypto( account_name name );
         void testprint( account_name name );
       void testsystemapi( account_name name );
       void testmem( account_name name );
       void testdb( account_name name );
       void testtrxauth( account_name name );
       void testtrx( account_name name );
       
       
      private:
         struct account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.name(); }
         };

         struct currency_stats {
            asset          supply;
            asset          max_supply;
            account_name   issuer;

            uint64_t primary_key()const { return supply.symbol.name(); }
         };
       
       struct record {
           uint64_t    primary;
           uint64_t    secondary_1;
           uint128_t   secondary_2;
           key256   secondary_3;
           double      secondary_4;
           long double secondary_5;
           string      data;
           
           uint64_t primary_key() const { return primary; }
           uint64_t get_secondary_1() const { return secondary_1; }
           uint128_t get_secondary_2() const { return secondary_2; }
           key256 get_secondary_3() const { return secondary_3; }
           double get_secondary_4() const { return secondary_4; }
           long double get_secondary_5() const { return secondary_5; }
           
           EOSLIB_SERIALIZE( record, (primary)(secondary_1)(secondary_2)(secondary_3)(secondary_4)(secondary_5)(data) )
       };

         typedef eosio::multi_index<N(accounts), account> accounts;
         typedef eosio::multi_index<N(stat), currency_stats> stats;
       
       
       typedef multi_index<N(records), record,
           indexed_by< N(bysecondary1), const_mem_fun<record, uint64_t, &record::get_secondary_1> >,
           indexed_by< N(bysecondary2), const_mem_fun<record, uint128_t, &record::get_secondary_2> >,
           indexed_by< N(bysecondary3), const_mem_fun<record, key256, &record::get_secondary_3> >,
           indexed_by< N(bysecondary4), const_mem_fun<record, double, &record::get_secondary_4> >,
           indexed_by< N(bysecondary5), const_mem_fun<record, long double, &record::get_secondary_5> >
       > records;

         void sub_balance( account_name owner, asset value );
         void add_balance( account_name owner, asset value, account_name ram_payer );

      public:
         struct transfer_args {
            account_name  from;
            account_name  to;
            asset         quantity;
            string        memo;
         };
   };

   asset token::get_supply( symbol_name sym )const
   {
      stats statstable( _self, sym );
      const auto& st = statstable.get( sym );
      return st.supply;
   }

   asset token::get_balance( account_name owner, symbol_name sym )const
   {
      accounts accountstable( _self, owner );
      const auto& ac = accountstable.get( sym );
      return ac.balance;
   }

} /// namespace eosio
