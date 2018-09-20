#pragma once
#include <contento/protocol/base.hpp>
#include <contento/protocol/block_header.hpp>
#include <contento/protocol/asset.hpp>
#include <contento/protocol/types.hpp>

#include <fc/utf8.hpp>
#include <fc/crypto/equihash.hpp>

#include <utility>

namespace contento { namespace protocol {


   inline void validate_account_name( const string& name )
   {
      FC_ASSERT( is_valid_account_name( name ), "Account name ${n} is invalid", ("n", name) );
   }

   inline void validate_councillor_name( const string& name ) {
      FC_ASSERT( is_councillor( name ), "Invalid councillor name: ${n}", ("n", name) );
   }

   inline void validate_permlink( const string& permlink )
   {
      FC_ASSERT( permlink.size() < CONTENTO_MAX_PERMLINK_LENGTH, "permlink is too long" );
      FC_ASSERT( fc::is_utf8( permlink ), "permlink not formatted in UTF8" );
   }
   
   struct admin_grant_operation : public base_operation 
   {
      account_name_type creator;
      account_name_type nominee;

      int type;
      bool is_grant;

      void validate() const;
      void get_required_active_authorities( flat_set<account_name_type>& a ) const 
      { 
         a.insert(creator); 
      }
   };

   struct comment_report_operation : public base_operation
   {
      account_name_type reporter;

      account_name_type author;
      string            permlink;

      asset credit;
      string tag;

      // true if this op is from admin user
      // otherwise if it is from common user. i.e. this is a report action waiting
      // for admin to approve
      bool is_ack; 
      // true if the report is accepted.
      // false if this is a malicious report, reporter will be punished
      bool approved;

      void validate() const;
      void get_required_posting_authorities( flat_set<account_name_type>& a ) const 
      { 
         a.insert(reporter); 
      }

      void get_required_admin( vector< std::pair<account_name_type, admin_type> >& admins ) const 
      {
         if( is_ack )
         {
            admins.push_back(std::make_pair(reporter, admin_type::comment_delete));
         }
      }
   };

   struct account_create_operation : public base_operation
   {
      asset             fee;
      account_name_type creator;
      account_name_type new_account_name;
      authority         owner;
      authority         active;
      authority         posting;
      public_key_type   memo_key;
      string            json_metadata;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(creator); }
   };


   struct account_create_with_delegation_operation : public base_operation
   {
      asset             fee;
      asset             delegation;
      account_name_type creator;
      account_name_type new_account_name;
      authority         owner;
      authority         active;
      authority         posting;
      public_key_type   memo_key;
      string            json_metadata;

      extensions_type   extensions;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(creator); }
   };


   struct account_update_operation : public base_operation
   {
      account_name_type             account;
      optional< authority >         owner;
      optional< authority >         active;
      optional< authority >         posting;
      public_key_type               memo_key;
      string                        json_metadata;

      void validate()const;

      void get_required_owner_authorities( flat_set<account_name_type>& a )const
      { if( owner ) a.insert( account ); }

      void get_required_active_authorities( flat_set<account_name_type>& a )const
      { if( !owner ) a.insert( account ); }
   };


    struct comment_operation : public base_operation
    {
        account_name_type parent_author;
        string            parent_permlink;
        string            category;
        account_name_type author;
        string            permlink;
        string            title;
        string            body;
        string            json_metadata;
        void validate()const;
        void get_required_posting_authorities( flat_set<account_name_type>& a )const{ a.insert(author); }
    };


   struct beneficiary_route_type
   {
      beneficiary_route_type() {}
      beneficiary_route_type( const account_name_type& a, const uint16_t& w ) : account( a ), weight( w ){}

      account_name_type account;
      uint16_t          weight;

      // For use by std::sort such that the route is sorted first by name (ascending)
      bool operator < ( const beneficiary_route_type& o )const { return account < o.account; }
   };
/*
   struct report_info_type
   {
      report_info_type() {}
      report_info_type(const account_name_type& acc, asset credit, string tag)
            : reporter(acc), credit(credit), tag(tag) {}

      account_name_type  reporter;
      asset            credit;
      string    tag;
   };*/

   struct comment_payout_beneficiaries
   {
      vector< beneficiary_route_type > beneficiaries;

      void validate()const;
   };

   typedef static_variant<
            comment_payout_beneficiaries
           > comment_options_extension;

   typedef flat_set< comment_options_extension > comment_options_extensions_type;

   /**
    *  Authors of posts may not want all of the benefits that come from creating a post. This
    *  operation allows authors to update properties associated with their post.
    *
    *  The max_accepted_payout may be decreased, but never increased.
    *  The percent_steem_dollars may be decreased, but never increased
    *
    */
   struct comment_options_operation : public base_operation
   {
      account_name_type author;
      string            permlink;

      asset             max_accepted_payout    = asset( 1000000000, COS_SYMBOL);       /// SBD value of the maximum payout this post will receive
      uint16_t          percent_steem_dollars  = CONTENTO_100_PERCENT; /// the percent of Steem Dollars to key, unkept amounts will be received as Steem Power
      bool              allow_votes            = true;      /// allows a post to receive votes;
      bool              allow_curation_rewards = true; /// allows voters to recieve curation rewards. Rewards return to reward fund.
      comment_options_extensions_type extensions;

      void validate()const;
      void get_required_posting_authorities( flat_set<account_name_type>& a )const{ a.insert(author); }
   };


   struct challenge_authority_operation : public base_operation
   {
      account_name_type challenger;
      account_name_type challenged;
      bool              require_owner = false;

      void validate()const;

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(challenger); }
   };

   struct prove_authority_operation : public base_operation
   {
      account_name_type challenged;
      bool              require_owner = false;

      void validate()const;

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ if( !require_owner ) a.insert(challenged); }
      void get_required_owner_authorities( flat_set<account_name_type>& a )const{  if(  require_owner ) a.insert(challenged); }
   };


   struct delete_comment_operation : public base_operation
   {
      account_name_type author;
      string            permlink;

      void validate()const;
      void get_required_posting_authorities( flat_set<account_name_type>& a )const{ a.insert(author); }
   };


   struct vote_operation : public base_operation
   {
      account_name_type    voter;
      account_name_type    author;
      string               permlink;
      int16_t              weight = 0;

      void validate()const;
      void get_required_posting_authorities( flat_set<account_name_type>& a )const{ a.insert(voter); }
   };


   /**
    * @ingroup operations
    *
    * @brief Transfers STEEM from one account to another.
    */
   struct transfer_operation : public base_operation
   {
      account_name_type from;
      /// Account to transfer asset to
      account_name_type to;
      /// The amount of asset to transfer from @ref from to @ref to
      asset             amount;

      /// The memo is plain-text, any encryption on the memo is up to
      /// a higher level protocol.
      string            memo;

      void              validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ if(amount.symbol != VESTS_SYMBOL) a.insert(from); }
      void get_required_owner_authorities( flat_set<account_name_type>& a )const { if(amount.symbol == VESTS_SYMBOL) a.insert(from); }
   };

   /**
    *  This operation converts STEEM into VFS (Vesting Fund Shares) at
    *  the current exchange rate. With this operation it is possible to
    *  give another account vesting shares so that faucets can
    *  pre-fund new accounts with vesting shares.
    */
   struct transfer_to_vesting_operation : public base_operation
   {
      account_name_type from;
      account_name_type to; ///< if null, then same as from
      asset             amount; ///< must be STEEM

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(from); }
   };
    

    struct convert_from_vesting_operation: public base_operation
    {
        account_name_type account;
        asset             vesting_shares;
        
        void validate() const;
        void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(account); }
    };


   /**
    * Allows an account to setup a vesting withdraw but with the additional
    * request for the funds to be transferred directly to another account's
    * balance rather than the withdrawing account. In addition, those funds
    * can be immediately vested again, circumventing the conversion from
    * vests to steem and back, guaranteeing they maintain their value.
    */
   struct set_withdraw_vesting_route_operation : public base_operation
   {
      account_name_type from_account;
      account_name_type to_account;
      uint16_t          percent = 0;
      bool              auto_vest = false;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( from_account ); }
   };


   /**
    * Witnesses must vote on how to set certain chain properties to ensure a smooth
    * and well functioning network.  Any time @owner is in the active set of witnesses these
    * properties will be used to control the blockchain configuration.
    */
   struct chain_properties
   {
      /**
       *  This fee, paid in STEEM, is converted into VESTING SHARES for the new account. Accounts
       *  without vesting shares cannot earn usage rations and therefore are powerless. This minimum
       *  fee requires all accounts to have some kind of commitment to the network that includes the
       *  ability to vote and make transactions.
       */
      asset             account_creation_fee =
         asset( CONTENTO_MIN_ACCOUNT_CREATION_FEE, COS_SYMBOL );

      /**
       *  This witnesses vote for the maximum_block_size which is used by the network
       *  to tune rate limiting and capacity
       */
      uint32_t          maximum_block_size = CONTENTO_MIN_BLOCK_SIZE_LIMIT * 2;
      uint16_t          sbd_interest_rate  = CONTENTO_DEFAULT_SBD_INTEREST_RATE;

      void validate()const
      {
         FC_ASSERT( account_creation_fee.amount >= CONTENTO_MIN_ACCOUNT_CREATION_FEE);
         FC_ASSERT( maximum_block_size >= CONTENTO_MIN_BLOCK_SIZE_LIMIT);
         FC_ASSERT( sbd_interest_rate >= 0 );
         FC_ASSERT( sbd_interest_rate <= CONTENTO_100_PERCENT );
      }
   };


   /**
    *  Users who wish to become a witness must pay a fee acceptable to
    *  the current witnesses to apply for the position and allow voting
    *  to begin.
    *
    *  If the owner isn't a witness they will become a witness.  Witnesses
    *  are charged a fee equal to 1 weeks worth of witness pay which in
    *  turn is derived from the current share supply.  The fee is
    *  only applied if the owner is not already a witness.
    *
    *  If the block_signing_key is null then the witness is removed from
    *  contention.  The network will pick the top 21 witnesses for
    *  producing blocks.
    */
   struct witness_update_operation : public base_operation
   {
      account_name_type owner;
      string            url;
      public_key_type   block_signing_key;
      chain_properties  props;
      asset             fee; ///< the fee paid to register a new witness, should be 10x current block production pay

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(owner); }
   };


   /**
    * All accounts with a VFS can vote for or against any witness.
    *
    * If a proxy is specified then all existing votes are removed.
    */
   struct account_witness_vote_operation : public base_operation
   {
      account_name_type account;
      account_name_type witness;
      bool              approve = true;

      void validate() const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(account); }
   };


   struct account_witness_proxy_operation : public base_operation
   {
      account_name_type account;
      account_name_type proxy;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(account); }
   };


   /**
    * @brief provides a generic way to add higher level protocols on top of witness consensus
    * @ingroup operations
    *
    * There is no validation for this operation other than that required auths are valid
    */
   struct custom_operation : public base_operation
   {
      flat_set< account_name_type > required_auths;
      uint16_t                      id = 0;
      vector< char >                data;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_auths ) a.insert(i); }
   };


   /** serves the same purpose as custom_operation but also supports required posting authorities. Unlike custom_operation,
    * this operation is designed to be human readable/developer friendly.
    **/
   struct custom_json_operation : public base_operation
   {
      flat_set< account_name_type > required_auths;
      flat_set< account_name_type > required_posting_auths;
      string                        id; ///< must be less than 32 characters long
      string                        json; ///< must be proper utf8 / JSON string.

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_auths ) a.insert(i); }
      void get_required_posting_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_posting_auths ) a.insert(i); }
   };


   struct custom_binary_operation : public base_operation
   {
      flat_set< account_name_type > required_owner_auths;
      flat_set< account_name_type > required_active_auths;
      flat_set< account_name_type > required_posting_auths;
      vector< authority >           required_auths;

      string                        id; ///< must be less than 32 characters long
      vector< char >                data;

      void validate()const;
      void get_required_owner_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_owner_auths ) a.insert(i); }
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_active_auths ) a.insert(i); }
      void get_required_posting_authorities( flat_set<account_name_type>& a )const{ for( const auto& i : required_posting_auths ) a.insert(i); }
      void get_required_authorities( vector< authority >& a )const{ for( const auto& i : required_auths ) a.push_back( i ); }
   };



   struct pow
   {
      public_key_type worker;
      digest_type     input;
      signature_type  signature;
      digest_type     work;

      void create( const fc::ecc::private_key& w, const digest_type& i );
      void validate()const;
   };


   struct pow_operation : public base_operation
   {
      account_name_type worker_account;
      block_id_type     block_id;
      uint64_t          nonce = 0;
      pow               work;
      chain_properties  props;

      void validate()const;
      fc::sha256 work_input()const;

      const account_name_type& get_worker_account()const { return worker_account; }

      /** there is no need to verify authority, the proof of work is sufficient */
      void get_required_active_authorities( flat_set<account_name_type>& a )const{  }
   };


   struct pow2_input
   {
      account_name_type worker_account;
      block_id_type     prev_block;
      uint64_t          nonce = 0;
   };


   struct pow2
   {
      pow2_input        input;
      uint32_t          pow_summary = 0;

      void create( const block_id_type& prev_block, const account_name_type& account_name, uint64_t nonce );
      void validate()const;
   };

   struct equihash_pow
   {
      pow2_input           input;
      fc::equihash::proof  proof;
      block_id_type        prev_block;
      uint32_t             pow_summary = 0;

      void create( const block_id_type& recent_block, const account_name_type& account_name, uint32_t nonce );
      void validate() const;
   };

   typedef fc::static_variant< pow2, equihash_pow > pow2_work;

//   struct pow2_operation : public base_operation
//   {
//      pow2_work                     work;
//      optional< public_key_type >   new_owner_key;
//      chain_properties              props;
//
//      void validate()const;
//
//      void get_required_active_authorities( flat_set<account_name_type>& a )const;
//
//      void get_required_authorities( vector< authority >& a )const
//      {
//         if( new_owner_key )
//         {
//            a.push_back( authority( 1, *new_owner_key, 1 ) );
//         }
//      }
//   };


   /**
    * This operation is used to report a miner who signs two blocks
    * at the same time. To be valid, the violation must be reported within
    * CONTENTO_MAX_WITNESSES blocks of the head block (1 round) and the
    * producer must be in the ACTIVE witness set.
    *
    * Users not in the ACTIVE witness set should not have to worry about their
    * key getting compromised and being used to produced multiple blocks so
    * the attacker can report it and steel their vesting steem.
    *
    * The result of the operation is to transfer the full VESTING STEEM balance
    * of the block producer to the reporter.
    */
   struct report_over_production_operation : public base_operation
   {
      account_name_type    reporter;
      signed_block_header  first_block;
      signed_block_header  second_block;

      void validate()const;
   };


   /**
    * All account recovery requests come from a listed recovery account. This
    * is secure based on the assumption that only a trusted account should be
    * a recovery account. It is the responsibility of the recovery account to
    * verify the identity of the account holder of the account to recover by
    * whichever means they have agreed upon. The blockchain assumes identity
    * has been verified when this operation is broadcast.
    *
    * This operation creates an account recovery request which the account to
    * recover has 24 hours to respond to before the request expires and is
    * invalidated.
    *
    * There can only be one active recovery request per account at any one time.
    * Pushing this operation for an account to recover when it already has
    * an active request will either update the request to a new new owner authority
    * and extend the request expiration to 24 hours from the current head block
    * time or it will delete the request. To cancel a request, simply set the
    * weight threshold of the new owner authority to 0, making it an open authority.
    *
    * Additionally, the new owner authority must be satisfiable. In other words,
    * the sum of the key weights must be greater than or equal to the weight
    * threshold.
    *
    * This operation only needs to be signed by the the recovery account.
    * The account to recover confirms its identity to the blockchain in
    * the recover account operation.
    */
   struct request_account_recovery_operation : public base_operation
   {
      account_name_type recovery_account;       ///< The recovery account is listed as the recovery account on the account to recover.

      account_name_type account_to_recover;     ///< The account to recover. This is likely due to a compromised owner authority.

      authority         new_owner_authority;    ///< The new owner authority the account to recover wishes to have. This is secret
                                                ///< known by the account to recover and will be confirmed in a recover_account_operation

      extensions_type   extensions;             ///< Extensions. Not currently used.

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert( recovery_account ); }

      void validate() const;
   };


   /**
    * Recover an account to a new authority using a previous authority and verification
    * of the recovery account as proof of identity. This operation can only succeed
    * if there was a recovery request sent by the account's recover account.
    *
    * In order to recover the account, the account holder must provide proof
    * of past ownership and proof of identity to the recovery account. Being able
    * to satisfy an owner authority that was used in the past 30 days is sufficient
    * to prove past ownership. The get_owner_history function in the database API
    * returns past owner authorities that are valid for account recovery.
    *
    * Proving identity is an off chain contract between the account holder and
    * the recovery account. The recovery request contains a new authority which
    * must be satisfied by the account holder to regain control. The actual process
    * of verifying authority may become complicated, but that is an application
    * level concern, not a blockchain concern.
    *
    * This operation requires both the past and future owner authorities in the
    * operation because neither of them can be derived from the current chain state.
    * The operation must be signed by keys that satisfy both the new owner authority
    * and the recent owner authority. Failing either fails the operation entirely.
    *
    * If a recovery request was made inadvertantly, the account holder should
    * contact the recovery account to have the request deleted.
    *
    * The two setp combination of the account recovery request and recover is
    * safe because the recovery account never has access to secrets of the account
    * to recover. They simply act as an on chain endorsement of off chain identity.
    * In other systems, a fork would be required to enforce such off chain state.
    * Additionally, an account cannot be permanently recovered to the wrong account.
    * While any owner authority from the past 30 days can be used, including a compromised
    * authority, the account can be continually recovered until the recovery account
    * is confident a combination of uncompromised authorities were used to
    * recover the account. The actual process of verifying authority may become
    * complicated, but that is an application level concern, not the blockchain's
    * concern.
    */
   struct recover_account_operation : public base_operation
   {
      account_name_type account_to_recover;        ///< The account to be recovered

      authority         new_owner_authority;       ///< The new owner authority as specified in the request account recovery operation.

      authority         recent_owner_authority;    ///< A previous owner authority that the account holder will use to prove past ownership of the account to be recovered.

      extensions_type   extensions;                ///< Extensions. Not currently used.

      void get_required_authorities( vector< authority >& a )const
      {
         a.push_back( new_owner_authority );
         a.push_back( recent_owner_authority );
      }

      void validate() const;
   };


   /**
    *  This operation allows recovery_accoutn to change account_to_reset's owner authority to
    *  new_owner_authority after 60 days of inactivity.
    */
   struct reset_account_operation : public base_operation {
      account_name_type reset_account;
      account_name_type account_to_reset;
      authority         new_owner_authority;

      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( reset_account ); }
      void validate()const;
   };

   /**
    * This operation allows 'account' owner to control which account has the power
    * to execute the 'reset_account_operation' after 60 days.
    */
   struct set_reset_account_operation : public base_operation {
      account_name_type account;
      account_name_type current_reset_account;
      account_name_type reset_account;
      void validate()const;
      void get_required_owner_authorities( flat_set<account_name_type>& a )const
      {
         if( current_reset_account.size() )
            a.insert( account );
      }

      void get_required_posting_authorities( flat_set<account_name_type>& a )const
      {
         if( !current_reset_account.size() )
            a.insert( account );
      }
   };


   /**
    * Each account lists another account as their recovery account.
    * The recovery account has the ability to create account_recovery_requests
    * for the account to recover. An account can change their recovery account
    * at any time with a 30 day delay. This delay is to prevent
    * an attacker from changing the recovery account to a malicious account
    * during an attack. These 30 days match the 30 days that an
    * owner authority is valid for recovery purposes.
    *
    * On account creation the recovery account is set either to the creator of
    * the account (The account that pays the creation fee and is a signer on the transaction)
    * or to the empty string if the account was mined. An account with no recovery
    * has the top voted witness as a recovery account, at the time the recover
    * request is created. Note: This does mean the effective recovery account
    * of an account with no listed recovery account can change at any time as
    * witness vote weights. The top voted witness is explicitly the most trusted
    * witness according to stake.
    */
   struct change_recovery_account_operation : public base_operation
   {
      account_name_type account_to_recover;     ///< The account that would be recovered in case of compromise
      account_name_type new_recovery_account;   ///< The account that creates the recover request
      extensions_type   extensions;             ///< Extensions. Not currently used.

      void get_required_owner_authorities( flat_set<account_name_type>& a )const{ a.insert( account_to_recover ); }
      void validate() const;
   };


   struct transfer_to_savings_operation : public base_operation {
      account_name_type from;
      account_name_type to;
      asset             amount;
      string            memo;

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert( from ); }
      void validate() const;
   };


   struct transfer_from_savings_operation : public base_operation {
      account_name_type from;
      uint32_t          request_id = 0;
      account_name_type to;
      asset             amount;
      string            memo;

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert( from ); }
      void validate() const;
   };


   struct cancel_transfer_from_savings_operation : public base_operation {
      account_name_type from;
      uint32_t          request_id = 0;

      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert( from ); }
      void validate() const;
   };


   struct decline_voting_rights_operation : public base_operation
   {
      account_name_type account;
      bool              decline = true;

      void get_required_owner_authorities( flat_set<account_name_type>& a )const{ a.insert( account ); }
      void validate() const;
   };

   struct claim_reward_balance_operation : public base_operation
   {
      account_name_type account;
      asset             reward_steem;
      asset             reward_sbd;
      asset             reward_vests;

      void get_required_posting_authorities( flat_set< account_name_type >& a )const{ a.insert( account ); }
      void validate() const;
   };

   /**
    * Delegate vesting shares from one account to the other. The vesting shares are still owned
    * by the original account, but content voting rights and bandwidth allocation are transferred
    * to the receiving account. This sets the delegation to `vesting_shares`, increasing it or
    * decreasing it as needed. (i.e. a delegation of 0 removes the delegation)
    *
    * When a delegation is removed the shares are placed in limbo for a week to prevent a satoshi
    * of VESTS from voting on the same content twice.
    */
   struct delegate_vesting_shares_operation : public base_operation
   {
      account_name_type delegator;        ///< The account delegating vesting shares
      account_name_type delegatee;        ///< The account receiving vesting shares
      asset             vesting_shares;   ///< The amount of vesting shares delegated

      void get_required_active_authorities( flat_set< account_name_type >& a ) const { a.insert( delegator ); }
      void validate() const;
   };

   struct vm_operation : public base_operation {
      account_name_type          caller;
      scope_name_type            contract_name;
      name                       action_name;
      bytes                      data;
      asset                      value;

      vm_operation() {}

      template<typename T, std::enable_if_t<std::is_base_of<bytes, T>::value>* = nullptr>
      vm_operation( account_name_type caller, const T& value )
      :caller(caller) {
         contract_name     = T::get_account();
         action_name        = T::get_name();
         data.assign(value.data(), value.data() + value.size());
      }

      template<typename T, std::enable_if_t<!std::is_base_of<bytes, T>::value>* = nullptr>
      vm_operation( account_name_type caller, const T& value )
      :caller(caller) {
         contract_name     = T::get_account();
         action_name        = T::get_name();
         data        = fc::raw::pack(value);
      }

      vm_operation( account_name_type caller, account_name_type account,
                    name name, const bytes& data )
            : caller(caller), contract_name(account), action_name(name), data(data) {}
      

      template<typename T>
      T as()const {
         FC_ASSERT( contract_name == T::get_account() );
         FC_ASSERT( action_name == T::get_name()  );
         return fc::raw::unpack<T>(data);
      }

      void get_required_active_authorities( flat_set< account_name_type >& a ) const { a.insert( caller ); }
      void validate() const;
   };
} } // contento::protocol


FC_REFLECT( contento::protocol::transfer_to_savings_operation, (from)(to)(amount)(memo) )
FC_REFLECT( contento::protocol::transfer_from_savings_operation, (from)(request_id)(to)(amount)(memo) )
FC_REFLECT( contento::protocol::cancel_transfer_from_savings_operation, (from)(request_id) )

FC_REFLECT( contento::protocol::reset_account_operation, (reset_account)(account_to_reset)(new_owner_authority) )
FC_REFLECT( contento::protocol::set_reset_account_operation, (account)(current_reset_account)(reset_account) )


FC_REFLECT( contento::protocol::report_over_production_operation, (reporter)(first_block)(second_block) )
FC_REFLECT( contento::protocol::pow, (worker)(input)(signature)(work) )
FC_REFLECT( contento::protocol::pow2, (input)(pow_summary) )
FC_REFLECT( contento::protocol::pow2_input, (worker_account)(prev_block)(nonce) )
FC_REFLECT( contento::protocol::equihash_pow, (input)(proof)(prev_block)(pow_summary) )
FC_REFLECT( contento::protocol::chain_properties, (account_creation_fee)(maximum_block_size)(sbd_interest_rate) );

FC_REFLECT_TYPENAME( contento::protocol::pow2_work )
FC_REFLECT( contento::protocol::pow_operation, (worker_account)(block_id)(nonce)(work)(props) )
//FC_REFLECT( contento::protocol::pow2_operation, (work)(new_owner_key)(props) )

FC_REFLECT( contento::protocol::admin_grant_operation, (creator)(nominee)(type)(is_grant))
FC_REFLECT( contento::protocol::comment_report_operation, (reporter)(author)(permlink)(credit)(tag)(is_ack)(approved))

FC_REFLECT( contento::protocol::account_create_operation,
            (fee)
            (creator)
            (new_account_name)
            (owner)
            (active)
            (posting)
            (memo_key)
            (json_metadata) )

FC_REFLECT( contento::protocol::account_create_with_delegation_operation,
            (fee)
            (delegation)
            (creator)
            (new_account_name)
            (owner)
            (active)
            (posting)
            (memo_key)
            (json_metadata)
            (extensions) )

FC_REFLECT( contento::protocol::account_update_operation,
            (account)
            (owner)
            (active)
            (posting)
            (memo_key)
            (json_metadata) )

FC_REFLECT( contento::protocol::transfer_operation, (from)(to)(amount)(memo) )
FC_REFLECT( contento::protocol::transfer_to_vesting_operation, (from)(to)(amount) )
FC_REFLECT( contento::protocol::convert_from_vesting_operation, (account)(vesting_shares))
FC_REFLECT( contento::protocol::set_withdraw_vesting_route_operation, (from_account)(to_account)(percent)(auto_vest) )
FC_REFLECT( contento::protocol::witness_update_operation, (owner)(url)(block_signing_key)(props)(fee) )
FC_REFLECT( contento::protocol::account_witness_vote_operation, (account)(witness)(approve) )
FC_REFLECT( contento::protocol::account_witness_proxy_operation, (account)(proxy) )
FC_REFLECT( contento::protocol::comment_operation, (parent_author)(parent_permlink)(category)(author)(permlink)(title)(body)(json_metadata) )
FC_REFLECT( contento::protocol::vote_operation, (voter)(author)(permlink)(weight) )
FC_REFLECT( contento::protocol::custom_operation, (required_auths)(id)(data) )
FC_REFLECT( contento::protocol::custom_json_operation, (required_auths)(required_posting_auths)(id)(json) )
FC_REFLECT( contento::protocol::custom_binary_operation, (required_owner_auths)(required_active_auths)(required_posting_auths)(required_auths)(id)(data) )

FC_REFLECT( contento::protocol::delete_comment_operation, (author)(permlink) )

FC_REFLECT( contento::protocol::beneficiary_route_type, (account)(weight) )
FC_REFLECT( contento::protocol::comment_payout_beneficiaries, (beneficiaries) )
FC_REFLECT_TYPENAME( contento::protocol::comment_options_extension )
FC_REFLECT( contento::protocol::comment_options_operation, (author)(permlink)(max_accepted_payout)(percent_steem_dollars)(allow_votes)(allow_curation_rewards)(extensions) )

//FC_REFLECT( contento::protocol::escrow_transfer_operation, (from)(to)(sbd_amount)(steem_amount)(escrow_id)(agent)(fee)(json_meta)(ratification_deadline)(escrow_expiration) );
//FC_REFLECT( contento::protocol::escrow_approve_operation, (from)(to)(agent)(who)(escrow_id)(approve) );
//FC_REFLECT( contento::protocol::escrow_dispute_operation, (from)(to)(agent)(who)(escrow_id) );
//FC_REFLECT( contento::protocol::escrow_release_operation, (from)(to)(agent)(who)(receiver)(escrow_id)(sbd_amount)(steem_amount) );
FC_REFLECT( contento::protocol::challenge_authority_operation, (challenger)(challenged)(require_owner) );
FC_REFLECT( contento::protocol::prove_authority_operation, (challenged)(require_owner) );
FC_REFLECT( contento::protocol::request_account_recovery_operation, (recovery_account)(account_to_recover)(new_owner_authority)(extensions) );
FC_REFLECT( contento::protocol::recover_account_operation, (account_to_recover)(new_owner_authority)(recent_owner_authority)(extensions) );
FC_REFLECT( contento::protocol::change_recovery_account_operation, (account_to_recover)(new_recovery_account)(extensions) );
FC_REFLECT( contento::protocol::decline_voting_rights_operation, (account)(decline) );
FC_REFLECT( contento::protocol::claim_reward_balance_operation, (account)(reward_steem)(reward_sbd)(reward_vests) )
FC_REFLECT( contento::protocol::delegate_vesting_shares_operation, (delegator)(delegatee)(vesting_shares) );
FC_REFLECT( contento::protocol::vm_operation, (caller)(contract_name)(action_name)(data)(value) )
