#pragma once

#include <contento/protocol/authority.hpp>
#include <contento/protocol/contento_operations.hpp>

#include <contento/chain/contento_object_types.hpp>

#include <boost/multi_index/composite_key.hpp>
#include <boost/multiprecision/cpp_int.hpp>


namespace contento { namespace chain {

   using contento::protocol::asset;
   using contento::protocol::price;
   using contento::protocol::asset_symbol_type;

   typedef protocol::fixed_string_16 reward_fund_name_type;

   /**
    *  This object is used to track pending requests to convert sbd to steem
    */
   class convert_request_object : public object< convert_request_object_type, convert_request_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         convert_request_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         convert_request_object(){}

         id_type           id;

         account_name_type owner;
         uint32_t          requestid = 0; ///< id set by owner, the owner,requestid pair must be unique
         asset             amount;
         time_point_sec    conversion_date; ///< at this time the feed_history_median_price * amount
   };

    
    
    class withdraw_vesting_object: public object< withdraw_vesting_object_type, withdraw_vesting_object>
    {
        public:
            template< typename Constructor, typename Allocator >
            withdraw_vesting_object( Constructor&& c, allocator< Allocator > a )
            {
                c( *this );
            }
        
            withdraw_vesting_object(){}
        
            id_type  id;
        
            account_id_type   account;
            asset             vesting_shares;
    };


   class decline_voting_rights_request_object : public object< decline_voting_rights_request_object_type, decline_voting_rights_request_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         decline_voting_rights_request_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         decline_voting_rights_request_object(){}

         id_type           id;

         account_id_type   account;
         time_point_sec    effective_date;
   };

   enum curve_id
   {
      quadratic,
      quadratic_curation,
      linear,
      square_root
   };

   class reward_fund_object : public object< reward_fund_object_type, reward_fund_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         reward_fund_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         reward_fund_object() {}

         reward_fund_id_type     id;
         reward_fund_name_type   name;
         asset                   reward_balance = asset( 0, COS_SYMBOL );
         fc::uint128_t           recent_claims = 0;
         time_point_sec          last_update;
         uint128_t               content_constant = 0;
         uint16_t                percent_curation_rewards = 0;
         uint16_t                percent_content_rewards = 0;
         curve_id                author_reward_curve = linear;
         curve_id                curation_reward_curve = square_root;
   };

   struct by_price;
   struct by_expiration;
   struct by_account;

   struct by_owner;
   struct by_conversion_date;
   typedef multi_index_container<
      convert_request_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< convert_request_object, convert_request_id_type, &convert_request_object::id > >,
         ordered_unique< tag< by_conversion_date >,
            composite_key< convert_request_object,
               member< convert_request_object, time_point_sec, &convert_request_object::conversion_date >,
               member< convert_request_object, convert_request_id_type, &convert_request_object::id >
            >
         >,
         ordered_unique< tag< by_owner >,
            composite_key< convert_request_object,
               member< convert_request_object, account_name_type, &convert_request_object::owner >,
               member< convert_request_object, uint32_t, &convert_request_object::requestid >
            >
         >
      >,
      allocator< convert_request_object >
   > convert_request_index;

   struct by_owner;
   struct by_volume_weight;

   struct by_withdraw_route;
   struct by_destination;
    
    typedef multi_index_container<
        withdraw_vesting_object,
        indexed_by<
            ordered_unique< tag< by_id >, member< withdraw_vesting_object, withdraw_vesting_id_type, &withdraw_vesting_object::id > >,
            ordered_unique< tag< by_account >, member< withdraw_vesting_object, account_id_type, &withdraw_vesting_object::account > >
        >,
        allocator< withdraw_vesting_object >
    > withdraw_vesting_index;

   struct by_from_id;
   struct by_to;
   struct by_agent;
   struct by_ratification_deadline;
   struct by_sbd_balance;

   struct by_from_rid;
   struct by_to_complete;
   struct by_complete_from_rid;

   struct by_account;
   struct by_effective_date;
   typedef multi_index_container<
      decline_voting_rights_request_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< decline_voting_rights_request_object, decline_voting_rights_request_id_type, &decline_voting_rights_request_object::id > >,
         ordered_unique< tag< by_account >,
            member< decline_voting_rights_request_object, account_id_type, &decline_voting_rights_request_object::account >
         >,
         ordered_unique< tag< by_effective_date >,
            composite_key< decline_voting_rights_request_object,
               member< decline_voting_rights_request_object, time_point_sec, &decline_voting_rights_request_object::effective_date >,
               member< decline_voting_rights_request_object, account_id_type, &decline_voting_rights_request_object::account >
            >,
            composite_key_compare< std::less< time_point_sec >, std::less< account_id_type > >
         >
      >,
      allocator< decline_voting_rights_request_object >
   > decline_voting_rights_request_index;

   struct by_name;
   typedef multi_index_container<
      reward_fund_object,
      indexed_by<
         ordered_unique< tag< by_id >, member< reward_fund_object, reward_fund_id_type, &reward_fund_object::id > >,
         ordered_unique< tag< by_name >, member< reward_fund_object, reward_fund_name_type, &reward_fund_object::name > >
      >,
      allocator< reward_fund_object >
   > reward_fund_index;

} } // contento::chain

#include <contento/chain/comment_object.hpp>
#include <contento/chain/account_object.hpp>

FC_REFLECT_ENUM( contento::chain::curve_id,
                  (quadratic)(quadratic_curation)(linear)(square_root))

FC_REFLECT( contento::chain::withdraw_vesting_object,
           (id)(account)(vesting_shares))
CHAINBASE_SET_INDEX_TYPE( contento::chain::withdraw_vesting_object, contento::chain::withdraw_vesting_index )

FC_REFLECT( contento::chain::convert_request_object,
             (id)(owner)(requestid)(amount)(conversion_date) )
CHAINBASE_SET_INDEX_TYPE( contento::chain::convert_request_object, contento::chain::convert_request_index )


FC_REFLECT( contento::chain::decline_voting_rights_request_object,
             (id)(account)(effective_date) )
CHAINBASE_SET_INDEX_TYPE( contento::chain::decline_voting_rights_request_object, contento::chain::decline_voting_rights_request_index )

FC_REFLECT( contento::chain::reward_fund_object,
            (id)
            (name)
            (reward_balance)
            (recent_claims)
            (last_update)
            (content_constant)
            (percent_curation_rewards)
            (percent_content_rewards)
            (author_reward_curve)
            (curation_reward_curve)
         )
CHAINBASE_SET_INDEX_TYPE( contento::chain::reward_fund_object, contento::chain::reward_fund_index )
