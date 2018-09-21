#pragma once
#include <contento/protocol/base.hpp>
#include <contento/protocol/block_header.hpp>
#include <contento/protocol/asset.hpp>

#include <fc/utf8.hpp>

namespace contento { namespace protocol {



   struct comment_reward_operation : public virtual_operation
   {
      comment_reward_operation(){}
      comment_reward_operation( const account_name_type& a, const string& pl, const asset& p )
         :author(a), permlink(pl), payout(p){}

      account_name_type author;
      string            permlink;
      asset             payout;
   };
    
    struct subject_reward_operation : public virtual_operation
    {
        subject_reward_operation(){}
        subject_reward_operation( const account_name_type& a, const string& pl, const asset& p )
        :author(a), permlink(pl), payout(p){}
        
        account_name_type author;
        string            permlink;
        asset             payout;
    };


   struct fill_vesting_withdraw_operation : public virtual_operation
   {
      fill_vesting_withdraw_operation(){}
      fill_vesting_withdraw_operation( const string& f, const string& t, const asset& w, const asset& d )
         :from_account(f), to_account(t), withdrawn(w), deposited(d) {}

      account_name_type from_account;
      account_name_type to_account;
      asset             withdrawn;
      asset             deposited;
   };


   struct shutdown_witness_operation : public virtual_operation
   {
      shutdown_witness_operation(){}
      shutdown_witness_operation( const string& o ):owner(o) {}

      account_name_type owner;
   };


   struct hardfork_operation : public virtual_operation
   {
      hardfork_operation() {}
      hardfork_operation( uint32_t hf_id ) : hardfork_id( hf_id ) {}

      uint32_t         hardfork_id = 0;
   };

   struct comment_payout_update_operation : public virtual_operation
   {
      comment_payout_update_operation() {}
      comment_payout_update_operation( const account_name_type& a, const string& p ) : author( a ), permlink( p ) {}

      account_name_type author;
      string            permlink;
   };
    
    struct subject_payout_update_operation : public virtual_operation
    {
        subject_payout_update_operation() {}
        subject_payout_update_operation( const account_name_type& a, const string& p ) : author( a ), permlink( p ) {}
        
        account_name_type author;
        string            permlink;
    };

   struct return_vesting_delegation_operation : public virtual_operation
   {
      return_vesting_delegation_operation() {}
      return_vesting_delegation_operation( const account_name_type& a, const asset& v ) : account( a ), vesting_shares( v ) {}

      account_name_type account;
      asset             vesting_shares;
   };

   struct producer_reward_operation : public virtual_operation
   {
      producer_reward_operation(){}
      producer_reward_operation( const string& p, const asset& v ) : producer( p ), vesting_shares( v ) {}

      account_name_type producer;
      asset             vesting_shares;

   };

} } //contento::protocol

FC_REFLECT( contento::protocol::comment_reward_operation, (author)(permlink)(payout) )
FC_REFLECT( contento::protocol::subject_reward_operation, (author)(permlink)(payout) )
FC_REFLECT( contento::protocol::fill_vesting_withdraw_operation, (from_account)(to_account)(withdrawn)(deposited) )
FC_REFLECT( contento::protocol::shutdown_witness_operation, (owner) )
FC_REFLECT( contento::protocol::hardfork_operation, (hardfork_id) )
FC_REFLECT( contento::protocol::comment_payout_update_operation, (author)(permlink) )
FC_REFLECT( contento::protocol::subject_payout_update_operation, (author)(permlink) )
FC_REFLECT( contento::protocol::return_vesting_delegation_operation, (account)(vesting_shares) )
FC_REFLECT( contento::protocol::producer_reward_operation, (producer)(vesting_shares) )
