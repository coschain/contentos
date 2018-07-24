/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/types.h>
#include <eosiolib/content.h>
#include <vector>
#include <string>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/datastream.hpp>
#include <eosiolib/serialize.hpp>
//#include <eosiolib/public_key.hpp>

namespace eosio {

using std::vector;
using std::string;
using eosio::asset;
using share_type = int64_t;
using account_id_type = int64_t;
using account_name_type = std::string;
using public_key_type = ::public_key;

struct account_obj_vmi
{
  account_obj_vmi(){}

  account_id_type   id;

  account_name_type name;
  // authority         owner;
  // authority         active;
  // authority         posting;
  public_key_type   memo_key;
  string            json_metadata;
  account_name_type proxy;

  time_point_sec    last_owner_update;
  time_point_sec    last_account_update;

  time_point_sec    created;
  account_name_type recovery_account;
  uint32_t          comment_count = 0;
  uint32_t          lifetime_vote_count = 0;
  uint32_t          post_count = 0;

  bool              can_vote = false;
  uint16_t          voting_power = 0;
  time_point_sec    last_vote_time;

  asset             balance;
  asset             savings_balance;

  uint8_t           savings_withdraw_requests = 0;

  asset             reward_steem_balance;
  asset             reward_vesting_balance;
  asset             reward_vesting_steem;

  share_type        curation_rewards;
  share_type        posting_rewards;

  asset             vesting_shares;
  asset             delegated_vesting_shares;
  asset             received_vesting_shares;
  asset             vesting_withdraw_rate;
  time_point_sec    next_vesting_withdrawal;
  share_type        withdrawn;
  share_type        to_withdraw;
  uint16_t          withdraw_routes = 0;


  uint16_t          witnesses_voted_for;

  share_type        average_bandwidth = 0;
  share_type        lifetime_bandwidth = 0;
  time_point_sec    last_bandwidth_update;

  share_type        average_market_bandwidth = 0;
  share_type        lifetime_market_bandwidth = 0;
  time_point_sec    last_market_bandwidth_update;

  time_point_sec    last_post;
  time_point_sec    last_root_post;

  EOSLIB_SERIALIZE( account_obj_vmi,
           (id)
           (name)
           (memo_key)
           (json_metadata)
           (proxy)
           (last_account_update)
           (created)
           (comment_count)
           (lifetime_vote_count)
           (post_count)
           (can_vote)
           (voting_power)
           (last_vote_time)
           (balance)
           (savings_balance)
           (savings_withdraw_requests)
           (reward_steem_balance)
           (reward_vesting_balance)(reward_vesting_steem)
           (vesting_shares)
           (delegated_vesting_shares)(received_vesting_shares)
           (vesting_withdraw_rate)(next_vesting_withdrawal)(withdrawn)(to_withdraw)(withdraw_routes)
           (curation_rewards)
           (posting_rewards)
           (witnesses_voted_for)
           (last_post)
          (last_root_post)
           )

};



#define DEFAULT_OUT_BUFFER_LENGTH 10*1024

#define STUB_API(RetType, params )  \
        datastream<size_t> dss; \
        dss << api_name() << string( __FUNCTION__ ) params;  \
        std::vector<char>  vec_in(dss.tellp()); \
        datastream<const char*> ds(vec_in.data(), vec_in.size()); \
        ds << api_name() << string( __FUNCTION__ ) params; \
        std::vector<char>  vec_out(DEFAULT_OUT_BUFFER_LENGTH);  \
        int ret_length = on_content_call( vec_in.data(), vec_in.size(), vec_out.data(), DEFAULT_OUT_BUFFER_LENGTH); \
        if ( ret_length > DEFAULT_OUT_BUFFER_LENGTH ){  \
            vec_out.resize(ret_length); \
            ret_length = on_content_call( vec_in.data(), vec_in.size(), vec_out.data(), ret_length);  \
        } \
        return unpack<RetType>(vec_out.data(), ret_length);  \


class contento_vm_api
{
   public:
      contento_vm_api(){

      }
      ~contento_vm_api(){

      }

      std::string api_name() const{
        return std::string("contento_vm_api");
      }
      //////////////
      // Accounts //
      //////////////

      vector< account_obj_vmi > get_accounts( vector< string > names ) const{
        STUB_API( vector< account_obj_vmi >, << names );
      }

      account_obj_vmi get_account( string name ) const{
        STUB_API(account_obj_vmi, << name );
      }

      /**
       * @brief Get the total number of accounts registered with the blockchain
       */
      uint64_t get_account_count()const{
          STUB_API(uint64_t, );
      }
};
  
}
