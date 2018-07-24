#pragma once

#include <contento/chain/database.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/contento_object_types.hpp>


#include <fc/optional.hpp>
#include <fc/variant_object.hpp>

#include <map>
#include <memory>
#include <vector>

namespace contento { namespace vmi {

using namespace contento::chain;
using namespace contento::protocol;

using namespace std;


   struct account_obj_vmi
   {
      account_obj_vmi(){}
      account_obj_vmi( const chain::account_object& a ) :
         id( a.id._id ),
         name( a.name ),
         memo_key( a.memo_key ),
         json_metadata( to_string( a.json_metadata ) ),
         proxy( a.proxy ),
         last_account_update( a.last_account_update ),
         created( a.created ),
         recovery_account( a.recovery_account ),
         comment_count( a.comment_count ),
         lifetime_vote_count( a.lifetime_vote_count ),
         post_count( a.post_count ),
         can_vote( a.can_vote ),
         voting_power( a.voting_power ),
         last_vote_time( a.last_vote_time ),
         balance( a.balance ),
         savings_balance( a.savings_balance ),
         savings_withdraw_requests( a.savings_withdraw_requests ),
         reward_steem_balance( a.reward_steem_balance ),
         reward_vesting_balance( a.reward_vesting_balance ),
         reward_vesting_steem( a.reward_vesting_steem ),
         curation_rewards( a.curation_rewards ),
         posting_rewards( a.posting_rewards ),
         vesting_shares( a.vesting_shares ),
         delegated_vesting_shares( a.delegated_vesting_shares ),
         received_vesting_shares( a.received_vesting_shares ),
         vesting_withdraw_rate( a.vesting_withdraw_rate ),
         next_vesting_withdrawal( a.next_vesting_withdrawal ),
         withdrawn( a.withdrawn ),
         to_withdraw( a.to_withdraw ),
         withdraw_routes( a.withdraw_routes ),
         witnesses_voted_for( a.witnesses_voted_for ),
         last_post( a.last_post ),
         last_root_post( a.last_root_post )
         {

         }

         int64_t   id;

         account_name_type name;
//         authority         owner;
//         authority         active;
//         authority         posting;
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

   };

} }

FC_REFLECT( contento::vmi::account_obj_vmi,
           (id)
           //(name)(memo_key)(json_metadata)(proxy)
//           (last_account_update)
//           (created)
//           (comment_count)(lifetime_vote_count)(post_count)(can_vote)(voting_power)(last_vote_time)
//           (balance)
//           (savings_balance)
//           (savings_withdraw_requests)
//           (reward_steem_balance)
//           (reward_vesting_balance)(reward_vesting_steem)
//           (vesting_shares)(delegated_vesting_shares)(received_vesting_shares)
//           (vesting_withdraw_rate)(next_vesting_withdrawal)(withdrawn)(to_withdraw)(withdraw_routes)
//           (curation_rewards)
//           (posting_rewards)
//           (witnesses_voted_for)
//           (last_post)
           (last_root_post)
           )


