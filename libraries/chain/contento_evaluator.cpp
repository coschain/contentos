#include <contento/chain/config.hpp>
#include <contento/chain/contento_evaluator.hpp>
#include <contento/chain/database.hpp>
#include <contento/chain/custom_operation_interpreter.hpp>
#include <contento/chain/contento_objects.hpp>
#include <contento/chain/witness_objects.hpp>


#ifndef IS_LOW_MEM
#include <diff_match_patch.h>
#include <boost/locale/encoding_utf.hpp>

using boost::locale::conv::utf_to_utf;

std::wstring utf8_to_wstring(const std::string& str)
{
    return utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
}

std::string wstring_to_utf8(const std::wstring& str)
{
    return utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
}

#endif

#include <fc/uint128.hpp>
#include <fc/utf8.hpp>

namespace contento { namespace chain {
   using fc::uint128_t;

inline void validate_permlink_0_1( const string& permlink )
{
   FC_ASSERT( permlink.size() > CONTENTO_MIN_PERMLINK_LENGTH && permlink.size() < CONTENTO_MAX_PERMLINK_LENGTH, "Permlink is not a valid size." );

   for( auto c : permlink )
   {
      switch( c )
      {
         case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
         case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
         case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case '0':
         case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
         case '-':
            break;
         default:
            FC_ASSERT( false, "Invalid permlink character: ${s}", ("s", std::string() + c ) );
      }
   }
}

struct strcmp_equal
{
   bool operator()( const shared_string& a, const string& b )
   {
      return a.size() == b.size() || std::strcmp( a.c_str(), b.c_str() ) == 0;
   }
};

void witness_update_evaluator::do_apply( const witness_update_operation& o )
{
   _db.get_account( o.owner ); // verify owner exists

    FC_ASSERT( o.url.size() <= CONTENTO_MAX_WITNESS_URL_LENGTH, "URL is too long" );
    FC_ASSERT( o.props.account_creation_fee.symbol == COC_SYMBOL );

   const auto& by_witness_name_idx = _db.get_index< witness_index >().indices().get< by_name >();
   auto wit_itr = by_witness_name_idx.find( o.owner );
   if( wit_itr != by_witness_name_idx.end() )
   {
      _db.modify( *wit_itr, [&]( witness_object& w ) {
         from_string( w.url, o.url );
         w.signing_key        = o.block_signing_key;
         w.props              = o.props;
      });
   }
   else
   {
      _db.create< witness_object >( [&]( witness_object& w ) {
         w.owner              = o.owner;
         from_string( w.url, o.url );
         w.signing_key        = o.block_signing_key;
         w.created            = _db.head_block_time();
         w.props              = o.props;
      });
   }
}

void admin_grant_evaluator::do_apply( const admin_grant_operation& o ) 
{
    _db.get_account( o.creator );
    _db.get_account( o.nominee );
   
    std::string c_name(o.creator);
    int bitshift = (c_name.compare("councillor") == 0) ? 0 : (c_name.at(c_name.length()-1)-'0');
    const admin_object* nominee = _db.find_admin( o.nominee );
    if(nominee != nullptr)
    {
        _db.modify( *nominee, [&]( admin_object& c ){
            if( !o.is_grant )
            {
                switch (o.type)
                {
                    case 0:
                        c.comment_delete_nomination &= ~(uint128_t(1) << uint128_t(bitshift));
                    default:
                        c.commercial_nomination &= ~(uint128_t(1) << uint128_t(bitshift));
                }
                return;
            }
            switch (o.type)
            {
                case 0:
                    c.comment_delete_nomination |= uint128_t(1) << uint128_t(bitshift);
                default:
                    c.commercial_nomination |= uint128_t(1) << uint128_t(bitshift);
            }
        });
        return;
    }

    _db.create< admin_object >( [&]( admin_object& c ) {
        c.name = o.nominee;
        if( !o.is_grant )
        {
            switch (o.type)
            {
                case 0:
                    c.comment_delete_nomination &= ~(uint128_t(1) << uint128_t(bitshift));
                default:
                    c.commercial_nomination &= ~(uint128_t(1) << uint128_t(bitshift));
            }
            return;
        }
        switch (o.type)
        {
            case 0:
                c.comment_delete_nomination |= uint128_t(1) << uint128_t(bitshift);
            default:
                c.commercial_nomination |= uint128_t(1) << uint128_t(bitshift);
        }
    });
}

void delete_comment( const comment_object& co, database &db ) {
    const auto& auth = db.get_account( co.author );
    FC_ASSERT( !(auth.owner_challenged || auth.active_challenged ), "Operation cannot be processed because account is currently challenged." );

    // delete all child comments
//    const auto& by_permlink_idx = db.get_index< comment_index >().indices().get< by_parent >();
    const auto& by_permlink_idx = db.get_index< comment_index >().indices().get< by_parent >();
    auto itr = by_permlink_idx.find( boost::make_tuple( co.author, co.permlink ) );
//    while( itr != by_permlink_idx.end() && itr->parent_author == co.author && itr->parent_permlink == co.permlink )
//    {
//        const auto& cur_child_comment = *itr;
//        ++itr;
//        delete_comment( cur_child_comment, db );
//    }
    
    while( itr != by_permlink_idx.end() && itr->parent_author == co.author && itr->parent_permlink == co.permlink)
    {
        const auto& cur_child_comment = *itr;
        ++itr;
        delete_comment( cur_child_comment, db );
    }
    //FC_ASSERT( co.cashout_time != fc::time_point_sec::maximum() );
    //FC_ASSERT( co.net_rshares <= 0, "Cannot delete a comment with net positive votes." );

    // delete all votes for this comment
    const auto& vote_idx = db.get_index<comment_vote_index>().indices().get<by_comment_voter>();
    auto vote_itr = vote_idx.lower_bound( comment_id_type(co.id) );
    while( vote_itr != vote_idx.end() && vote_itr->comment == co.id ) {
        const auto& cur_vote = *vote_itr;
        ++vote_itr;
        db.remove(cur_vote);
    }

    /// this loop can be skiped for validate-only nodes as it is merely gathering stats for indicies
    if( co.parent_author != CONTENTO_ROOT_POST_PARENT )
    {
        auto parent = &db.get_comment( co.parent_author, co.parent_permlink );
        auto now = db.head_block_time();
        while( parent )
        {
            db.modify( *parent, [&]( comment_object& p ){
                p.children--;
                p.active = now;
            });
        #ifndef IS_LOW_MEM
            if( parent->parent_author != CONTENTO_ROOT_POST_PARENT )
                parent = &db.get_comment( parent->parent_author, parent->parent_permlink );
            else
        #endif
                parent = nullptr;
        }
    }

    db.remove( co );
}

void comment_report_evaluator::do_apply( const comment_report_operation& o ) 
{
   const auto& comment = _db.get_comment( o.author, o.permlink );
   FC_ASSERT( comment.allow_report, "cannot report this comment",
              ("author", o.author)("permlink", o.permlink));
   const auto& by_comment_idx = _db.get_index< comment_report_index >().indices().get< by_comment >();
   auto comment_report_itr = by_comment_idx.find( comment.id );
   if( o.is_ack )
   {
      FC_ASSERT( comment_report_itr != by_comment_idx.end(), "cannot ack a non-existed report", 
            ("comment_author", o.author)("comment_permlink", o.permlink));
      
      if( o.approved )
      {
         // report is approved. 1. delete corresponding comment_obj, comment_index.
         // 2. start report reward process
          _db.modify( *comment_report_itr, [&]( comment_report_object& c ) {
              c.cashout_time = _db.head_block_time();
          });
          delete_comment(comment, _db);
      }
      else
      {
         // all comment_reports of the comment is denied. start report punish process
           _db.remove( *comment_report_itr );
          _db.modify(comment, [&]( comment_object& c){
              c.allow_report = false;
          });
      }

   }
   else
   {
       const auto& reporter = _db.get_account(o.author);
       const auto& balance = reporter.balance;
       FC_ASSERT( balance > o.credit, "balance credit not enough",
                 ("balance", balance)("credit", o.credit));
       _db.adjust_balance(reporter, -o.credit);
      if( comment_report_itr != by_comment_idx.end() )
      {
         _db.modify( *comment_report_itr, [&]( comment_report_object& c ) {
            c.add_report(o.reporter, o.credit, o.tag);
            c.last_update = _db.head_block_time();
         });
         return;
      }
        
      _db.create< comment_report_object >( [&]( comment_report_object& c ) {
         c.comment = comment.id;
         c.add_report(o.reporter, o.credit, o.tag);
         c.last_update = _db.head_block_time();
          c.cashout_time = fc::time_point_sec::maximum();
      });
   }
}

void account_create_evaluator::do_apply( const account_create_operation& o )
{
   const auto& creator = _db.get_account( o.creator );

   const auto& props = _db.get_dynamic_global_properties();

   FC_ASSERT( creator.balance >= o.fee, "Insufficient balance to create account.", ( "creator.balance", creator.balance )( "required", o.fee ) );


      for( auto& a : o.owner.account_auths )
      {
         _db.get_account( a.first );
      }

      for( auto& a : o.active.account_auths )
      {
         _db.get_account( a.first );
      }

      for( auto& a : o.posting.account_auths )
      {
         _db.get_account( a.first );
      }

   _db.modify( creator, [&]( account_object& c ){
      c.balance -= o.fee;
   });
    
    _db.modify( _db.get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
   {
       gpo.total_coc -= o.fee;
       
   });

   const auto& new_account = _db.create< account_object >( [&]( account_object& acc )
   {
      acc.name = o.new_account_name;
      acc.memo_key = o.memo_key;
      acc.created = props.time;
      acc.last_vote_time = props.time;
      acc.mined = false;

    acc.recovery_account = o.creator;


      #ifndef IS_LOW_MEM
         from_string( acc.json_metadata, o.json_metadata );
      #endif
   });

   _db.create< account_authority_object >( [&]( account_authority_object& auth )
   {
      auth.account = o.new_account_name;
      auth.owner = o.owner;
      auth.active = o.active;
      auth.posting = o.posting;
      auth.last_owner_update = fc::time_point_sec::min();
   });

   if( o.fee.amount > 0 )
      _db.create_vesting( new_account, o.fee );
}

void account_create_with_delegation_evaluator::do_apply( const account_create_with_delegation_operation& o )
{
//    FC_ASSERT( _db.has_hardfork( CONTENTO_HARDFORK_0_17__818 ), "Account creation with delegation is not enabled until hardfork 17" );

   const auto& creator = _db.get_account( o.creator );
   const auto& props = _db.get_dynamic_global_properties();
   const witness_schedule_object& wso = _db.get_witness_schedule_object();

   FC_ASSERT( creator.balance >= o.fee, "Insufficient balance to create account.",
               ( "creator.balance", creator.balance )
               ( "required", o.fee ) );

   FC_ASSERT( creator.vesting_shares - creator.delegated_vesting_shares - asset( creator.to_withdraw - creator.withdrawn, VESTS_SYMBOL ) >= o.delegation, "Insufficient vesting shares to delegate to new account.",
               ( "creator.vesting_shares", creator.vesting_shares )
               ( "creator.delegated_vesting_shares", creator.delegated_vesting_shares )( "required", o.delegation ) );

   auto target_delegation = asset( wso.median_props.account_creation_fee.amount * CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER * CONTENTO_CREATE_ACCOUNT_DELEGATION_RATIO, COC_SYMBOL ) * props.get_vesting_share_price();

   auto current_delegation = asset( o.fee.amount * CONTENTO_CREATE_ACCOUNT_DELEGATION_RATIO, COC_SYMBOL ) * props.get_vesting_share_price() + o.delegation;

   FC_ASSERT( current_delegation >= target_delegation, "Inssufficient Delegation ${f} required, ${p} provided.",
               ("f", target_delegation )
               ( "p", current_delegation )
               ( "account_creation_fee", wso.median_props.account_creation_fee )
               ( "o.fee", o.fee )
               ( "o.delegation", o.delegation ) );

   FC_ASSERT( o.fee >= wso.median_props.account_creation_fee, "Insufficient Fee: ${f} required, ${p} provided.",
               ("f", wso.median_props.account_creation_fee)
               ("p", o.fee) );

   for( auto& a : o.owner.account_auths )
   {
      _db.get_account( a.first );
   }

   for( auto& a : o.active.account_auths )
   {
      _db.get_account( a.first );
   }

   for( auto& a : o.posting.account_auths )
   {
      _db.get_account( a.first );
   }

   _db.modify( creator, [&]( account_object& c )
   {
      c.balance -= o.fee;
      c.delegated_vesting_shares += o.delegation;
   });
    
    _db.modify(props, [&](dynamic_global_property_object& p){
        p.total_coc -= o.fee; 
    });

   const auto& new_account = _db.create< account_object >( [&]( account_object& acc )
   {
      acc.name = o.new_account_name;
      acc.memo_key = o.memo_key;
      acc.created = props.time;
      acc.last_vote_time = props.time;
      acc.mined = false;

      acc.recovery_account = o.creator;

      acc.received_vesting_shares = o.delegation;

      #ifndef IS_LOW_MEM
         from_string( acc.json_metadata, o.json_metadata );
      #endif
   });

   _db.create< account_authority_object >( [&]( account_authority_object& auth )
   {
      auth.account = o.new_account_name;
      auth.owner = o.owner;
      auth.active = o.active;
      auth.posting = o.posting;
      auth.last_owner_update = fc::time_point_sec::min();
   });

//   if( o.delegation.amount > 0 || !_db.has_hardfork( CONTENTO_HARDFORK_0_19__997 ) )
   if( o.delegation.amount > 0 )
   {
      _db.create< vesting_delegation_object >( [&]( vesting_delegation_object& vdo )
      {
         vdo.delegator = o.creator;
         vdo.delegatee = o.new_account_name;
         vdo.vesting_shares = o.delegation;
         vdo.min_delegation_time = _db.head_block_time() + CONTENTO_CREATE_ACCOUNT_DELEGATION_TIME;
      });
   }

   if( o.fee.amount > 0 )
      _db.create_vesting( new_account, o.fee );
}


void account_update_evaluator::do_apply( const account_update_operation& o )
{
    FC_ASSERT( o.account != CONTENTO_TEMP_ACCOUNT, "Cannot update temp account." );

   if( o.posting )
       o.posting->validate();

   const auto& account = _db.get_account( o.account );
   const auto& account_auth = _db.get< account_authority_object, by_account >( o.account );

   if( o.owner )
   {
#ifndef IS_TEST_NET
//      if( _db.has_hardfork( CONTENTO_HARDFORK_0_11 ) )
     FC_ASSERT( _db.head_block_time() - account_auth.last_owner_update > CONTENTO_OWNER_UPDATE_LIMIT, "Owner authority can only be updated once an hour." );
#endif

     for( auto a: o.owner->account_auths )
     {
        _db.get_account( a.first );
     }


      _db.update_owner_authority( account, *o.owner );
   }

   if( o.active )
   {
      for( auto a: o.active->account_auths )
      {
         _db.get_account( a.first );
      }
   }

   if( o.posting )
   {
      for( auto a: o.posting->account_auths )
      {
         _db.get_account( a.first );
      }
   }

   _db.modify( account, [&]( account_object& acc )
   {
      if( o.memo_key != public_key_type() )
            acc.memo_key = o.memo_key;

      if( ( o.active || o.owner ) && acc.active_challenged )
      {
         acc.active_challenged = false;
         acc.last_active_proved = _db.head_block_time();
      }

      acc.last_account_update = _db.head_block_time();

      #ifndef IS_LOW_MEM
        if ( o.json_metadata.size() > 0 )
            from_string( acc.json_metadata, o.json_metadata );
      #endif
   });

   if( o.active || o.posting )
   {
      _db.modify( account_auth, [&]( account_authority_object& auth)
      {
         if( o.active )  auth.active  = *o.active;
         if( o.posting ) auth.posting = *o.posting;
      });
   }

}


/**
 *  Because net_rshares is 0 there is no need to update any pending payout calculations or parent posts.
 */
void delete_comment_evaluator::do_apply( const delete_comment_operation& o )
{

    const auto& auth = _db.get_account( o.author );
    FC_ASSERT( !(auth.owner_challenged || auth.active_challenged ), "Operation cannot be processed because account is currently challenged." );

    const auto& comment = _db.get_comment( o.author, o.permlink );
    FC_ASSERT( comment.children == 0, "Cannot delete a comment with replies." );

    FC_ASSERT( comment.cashout_time != fc::time_point_sec::maximum() );

    const auto& vote_idx = _db.get_index<comment_vote_index>().indices().get<by_comment_voter>();

   auto vote_itr = vote_idx.lower_bound( comment_id_type(comment.id) );
   while( vote_itr != vote_idx.end() && vote_itr->comment == comment.id ) {
      const auto& cur_vote = *vote_itr;
      ++vote_itr;
      _db.remove(cur_vote);
   }

   /// this loop can be skiped for validate-only nodes as it is merely gathering stats for indicies
   if(comment.parent_author != CONTENTO_ROOT_POST_PARENT )
   {
      auto parent = &_db.get_comment( comment.parent_author, comment.parent_permlink );
      auto now = _db.head_block_time();
      while( parent )
      {
         _db.modify( *parent, [&]( comment_object& p ){
            p.children--;
            p.active = now;
         });
   #ifndef IS_LOW_MEM
         if( parent->parent_author != CONTENTO_ROOT_POST_PARENT )
            parent = &_db.get_comment( parent->parent_author, parent->parent_permlink );
         else
   #endif
            parent = nullptr;
      }
   }

   _db.remove( comment );
}

struct comment_options_extension_visitor
{
   comment_options_extension_visitor( const comment_object& c, database& db ) : _c( c ), _db( db ) {}

   typedef void result_type;

   const comment_object& _c;
   database& _db;

   void operator()( const comment_payout_beneficiaries& cpb ) const
   {
      FC_ASSERT( _c.beneficiaries.size() == 0, "Comment already has beneficiaries specified." );
      FC_ASSERT( _c.abs_rshares == 0, "Comment must not have been voted on before specifying beneficiaries." );

      _db.modify( _c, [&]( comment_object& c )
      {
         for( auto& b : cpb.beneficiaries )
         {
            auto acc = _db.find< account_object, by_name >( b.account );
            FC_ASSERT( acc != nullptr, "Beneficiary \"${a}\" must exist.", ("a", b.account) );
            c.beneficiaries.push_back( b );
         }
      });
   }
};

void comment_options_evaluator::do_apply( const comment_options_operation& o )
{

      const auto& auth = _db.get_account( o.author );
      FC_ASSERT( !(auth.owner_challenged || auth.active_challenged ), "Operation cannot be processed because account is currently challenged." );

   const auto& comment = _db.get_comment( o.author, o.permlink );
      if( !o.allow_curation_rewards || !o.allow_votes)
      FC_ASSERT( comment.abs_rshares == 0, "One of the included comment options requires the comment to have no rshares allocated to it." );

   FC_ASSERT( comment.allow_curation_rewards >= o.allow_curation_rewards, "Curation rewards cannot be re-enabled." );
   FC_ASSERT( comment.allow_votes >= o.allow_votes, "Voting cannot be re-enabled." );

   _db.modify( comment, [&]( comment_object& c ) {
       c.allow_votes           = o.allow_votes;
       c.allow_curation_rewards = o.allow_curation_rewards;
   });

   for( auto& e : o.extensions )
   {
      e.visit( comment_options_extension_visitor( comment, _db ) );
   }
}

void comment_evaluator::do_apply( const comment_operation& o )
{ try {
    FC_ASSERT( o.title.size() + o.body.size() + o.json_metadata.size(), "Cannot update comment because nothing appears to be changing." );
    const auto& by_permlink_idx = _db.get_index< comment_index >().indices().get< by_permlink >();
    auto itr = by_permlink_idx.find( boost::make_tuple( o.author, o.permlink ) );
    const auto& auth = _db.get_account( o.author ); /// prove it exists
    FC_ASSERT( !(auth.owner_challenged || auth.active_challenged ), "Operation cannot be processed because account is currently challenged." );
    comment_id_type id;
    const comment_object* parent = nullptr;
    if( o.parent_author != CONTENTO_ROOT_POST_PARENT )
    {
        parent = &_db.get_comment( o.parent_author, o.parent_permlink );
        FC_ASSERT( parent->depth < CONTENTO_MAX_COMMENT_DEPTH, "Comment is nested ${x} posts deep, maximum depth is ${y}.", ("x",parent->depth)("y",CONTENTO_MAX_COMMENT_DEPTH) );
    }
    if (o.json_metadata.size())
        FC_ASSERT( fc::is_utf8( o.json_metadata ), "JSON Metadata must be UTF-8" );
    auto now = _db.head_block_time();
    if ( itr == by_permlink_idx.end() )
    {
        if( o.parent_author != CONTENTO_ROOT_POST_PARENT )
        {
            FC_ASSERT( _db.get( parent->root_comment ).allow_replies, "The parent comment has disabled replies." );
        }
        
        if( o.parent_author == CONTENTO_ROOT_POST_PARENT )
            FC_ASSERT( ( now - auth.last_root_post ) >= CONTENTO_MIN_ROOT_COMMENT_INTERVAL, "You may only post once every 5 minutes.", ("now",now)("last_root_post", auth.last_root_post) );
        else
            FC_ASSERT( (now - auth.last_post) >= CONTENTO_MIN_REPLY_INTERVAL, "You may only comment once every 20 seconds.", ("now",now)("auth.last_post",auth.last_post) );
        uint16_t reward_weight = CONTENTO_100_PERCENT;

        _db.modify( auth, [&]( account_object& a ) {
            if( o.parent_author == CONTENTO_ROOT_POST_PARENT )
            {
                a.last_root_post = now;
                //            a.post_bandwidth = uint32_t( post_bandwidth );
            }
            a.last_post = now;
            a.post_count++;
        });
        const auto& new_comment = _db.create< comment_object >( [&]( comment_object& com )
        {
           if ( o.parent_author == CONTENTO_ROOT_POST_PARENT )
           {
               validate_permlink_0_1( o.permlink );
           }
           else {
                validate_permlink_0_1( o.parent_permlink );
                validate_permlink_0_1( o.permlink );
           }

           com.author = o.author;
           from_string( com.permlink, o.permlink );
           com.last_update = _db.head_block_time();
           com.created = com.last_update;
           com.active = com.last_update;
           com.last_payout = fc::time_point_sec::min();
           com.max_cashout_time = fc::time_point_sec::maximum();
           com.reward_weight = reward_weight;
           // subject
           if ( o.parent_author == CONTENTO_ROOT_POST_PARENT )
           {
               com.parent_author = "";
               from_string( com.parent_permlink, o.parent_permlink );
               from_string( com.category, o.category );
               com.root_comment = com.id;
               com.cashout_time = com.created + CONTENTO_CASHOUT_WINDOW_SECONDS;
           }
           else
           {
               com.parent_author = parent->author;
               com.parent_permlink = parent->permlink;
               com.depth = parent->depth + 1;
               com.category = parent->category;
               com.root_comment = parent->root_comment;
               if(parent->cashout_time == fc::time_point_sec::maximum())
                   com.cashout_time = fc::time_point_sec::maximum();
               else
                   com.cashout_time = com.created + CONTENTO_CASHOUT_WINDOW_SECONDS;
           }
           from_string( com.title, o.title );
           if( o.body.size() < 1024*1024*128 )
           {
               from_string( com.body, o.body );
           }
           if( fc::is_utf8( o.json_metadata ) )
               from_string( com.json_metadata, o.json_metadata );
           else
               wlog( "Comment ${a}/${p} contains invalid UTF-8 metadata", ("a", o.author)("p", o.permlink) );
       });
        id = new_comment.id;
        /// this loop can be skiped for validate-only nodes as it is merely gathering stats for indicies
        auto now = _db.head_block_time();
        while( parent ) {
            _db.modify( *parent, [&]( comment_object& p ){
                p.children++;
                p.active = now;
            });
            if( parent->parent_author != CONTENTO_ROOT_POST_PARENT )
                parent = &_db.get_comment( parent->parent_author, parent->parent_permlink );
            else
                parent = nullptr;
        }
    }
    else // start edit case
    {
        const auto& comment = *itr;
        _db.modify( comment, [&]( comment_object& com )
        {
            com.last_update   = _db.head_block_time();
            com.active        = com.last_update;
            strcmp_equal equal;
            if( !parent )
            {
                FC_ASSERT( com.parent_author == account_name_type(), "The parent of a comment cannot change." );
                FC_ASSERT( equal( com.parent_permlink, o.parent_permlink ), "The permlink of a comment cannot change." );
            }
            else
            {
                FC_ASSERT( com.parent_author == o.parent_author, "The parent of a comment cannot change." );
                FC_ASSERT( equal( com.parent_permlink, o.parent_permlink ), "The permlink of a comment cannot change." );
            }
            if( o.title.size() )         from_string( com.title, o.title );
            if( o.json_metadata.size() )
            {
                if( fc::is_utf8( o.json_metadata ) )
                    from_string( com.json_metadata, o.json_metadata );
                else
                    wlog( "Comment ${a}/${p} contains invalid UTF-8 metadata", ("a", o.author)("p", o.permlink) );
            }
            if( o.body.size() ) {
                try {
                    diff_match_patch<std::wstring> dmp;
                    auto patch = dmp.patch_fromText( utf8_to_wstring(o.body) );
                    if( patch.size() ) {
                        auto result = dmp.patch_apply( patch, utf8_to_wstring( to_string( com.body ) ) );
                        auto patched_body = wstring_to_utf8(result.first);
                        if( !fc::is_utf8( patched_body ) ) {
                            idump(("invalid utf8")(patched_body));
                            from_string( com.body, fc::prune_invalid_utf8(patched_body) );
                        } else { from_string( com.body, patched_body ); }
                    }
                    else { // replace
                        from_string( com.body, o.body );
                    }
                } catch ( ... ) {
                    from_string( com.body, o.body );
                }
            }
        });
    } // end EDIT case
} FC_CAPTURE_AND_RETHROW( (o) ) }


void transfer_evaluator::do_apply( const transfer_operation& o )
{
   const auto& from_account = _db.get_account(o.from);
   const auto& to_account = _db.get_account(o.to);

   if( from_account.active_challenged )
   {
      _db.modify( from_account, [&]( account_object& a )
      {
         a.active_challenged = false;
         a.last_active_proved = _db.head_block_time();
      });
   }

   FC_ASSERT( _db.get_balance( from_account, o.amount.symbol ) >= o.amount, "Account does not have sufficient funds for transfer." );
   _db.adjust_balance( from_account, -o.amount );
   _db.adjust_balance( to_account, o.amount );
}

void transfer_to_vesting_evaluator::do_apply( const transfer_to_vesting_operation& o )
{
   //CONTENTOS_OP_CLOSE_ASSERT();
   const auto& from_account = _db.get_account(o.from);
   const auto& to_account = o.to.size() ? _db.get_account(o.to) : from_account;

   FC_ASSERT( _db.get_balance( from_account, COC_SYMBOL) >= o.amount, "Account does not have sufficient STEEM for transfer." );
   _db.adjust_balance( from_account, -o.amount );
   _db.create_vesting( to_account, o.amount );
}
    
void convert_from_vesting_evaluator::do_apply(const convert_from_vesting_operation & o)
{
    const auto& account = _db.get_account(o.account);
    FC_ASSERT(o.vesting_shares >= asset(0, VESTS_SYMBOL), "Could not convert from negative");
    FC_ASSERT( account.vesting_shares >= asset( 0, VESTS_SYMBOL ), "Account does not have sufficient Steem Power for withdraw." );
    FC_ASSERT( account.vesting_shares - account.delegated_vesting_shares >= o.vesting_shares, "Account does not have sufficient Steem Power for withdraw." );
    
    // reset convert status
    if( o.vesting_shares.amount == 0 )
    {
        FC_ASSERT( account.vesting_withdraw_rate.amount  != 0, "This operation would not change the vesting withdraw rate." );
        
        _db.modify( account, [&]( account_object& a ) {
            a.vesting_withdraw_rate = asset( 0, VESTS_SYMBOL );
            a.next_vesting_withdrawal = time_point_sec::maximum();
            a.to_withdraw = 0;
            a.withdrawn = 0;
        });
        
        const auto& wd_idx = _db.get_index< withdraw_vesting_index >().indices().get< by_account >();
        
        auto itr = wd_idx.find( account.id );
        if( itr != wd_idx.end() ){
            _db.remove( *itr );
        }
        
    }
    else
    {
        int vesting_withdraw_intervals = CONTENTO_VESTING_WITHDRAW_INTERVALS; /// 13 weeks = 1 quarter of a year
        
        auto new_vesting_withdraw_rate = asset( o.vesting_shares.amount / vesting_withdraw_intervals, VESTS_SYMBOL );
        
        if (new_vesting_withdraw_rate.amount == 0)
            new_vesting_withdraw_rate.amount = 1;
        
        const auto& wd_idx = _db.get_index< withdraw_vesting_index >().indices().get< by_account >();

        _db.modify( account, [&]( account_object& a )
        {
           FC_ASSERT( account.vesting_withdraw_rate  != new_vesting_withdraw_rate, "This operation would not change the vesting withdraw rate." );
           
           a.vesting_withdraw_rate = new_vesting_withdraw_rate;
           a.next_vesting_withdrawal = _db.head_block_time() + fc::seconds(CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS);
           a.to_withdraw = o.vesting_shares.amount;
           a.withdrawn = 0;
        });
        
        auto itr = wd_idx.find( account.id );

        if( itr == wd_idx.end() )
        {
            _db.create< withdraw_vesting_object >( [&]( withdraw_vesting_object& wvo )
            {
                wvo.account = account.id;
                wvo.vesting_shares = new_vesting_withdraw_rate;
            });
            
        }
        else
        {
            _db.modify( *itr, [&]( withdraw_vesting_object& wvo )
           {
               wvo.account = account.id;
               wvo.vesting_shares = new_vesting_withdraw_rate;
           });
        }
    }
    
}



void account_witness_proxy_evaluator::do_apply( const account_witness_proxy_operation& o )
{
   const auto& account = _db.get_account( o.account );
   FC_ASSERT( account.proxy != o.proxy, "Proxy must change." );

   FC_ASSERT( account.can_vote, "Account has declined the ability to vote and cannot proxy votes." );

   /// remove all current votes
   std::array<share_type, CONTENTO_MAX_PROXY_RECURSION_DEPTH+1> delta;
   delta[0] = -account.vesting_shares.amount;
   for( int i = 0; i < CONTENTO_MAX_PROXY_RECURSION_DEPTH; ++i )
      delta[i+1] = -account.proxied_vsf_votes[i];
   _db.adjust_proxied_witness_votes( account, delta );

   if( o.proxy.size() ) {
      const auto& new_proxy = _db.get_account( o.proxy );
      flat_set<account_id_type> proxy_chain( { account.id, new_proxy.id } );
      proxy_chain.reserve( CONTENTO_MAX_PROXY_RECURSION_DEPTH + 1 );

      /// check for proxy loops and fail to update the proxy if it would create a loop
      auto cprox = &new_proxy;
      while( cprox->proxy.size() != 0 ) {
         const auto next_proxy = _db.get_account( cprox->proxy );
         FC_ASSERT( proxy_chain.insert( next_proxy.id ).second, "This proxy would create a proxy loop." );
         cprox = &next_proxy;
         FC_ASSERT( proxy_chain.size() <= CONTENTO_MAX_PROXY_RECURSION_DEPTH, "Proxy chain is too long." );
      }

      /// clear all individual vote records
      _db.clear_witness_votes( account );

      _db.modify( account, [&]( account_object& a ) {
         a.proxy = o.proxy;
      });

      /// add all new votes
      for( int i = 0; i <= CONTENTO_MAX_PROXY_RECURSION_DEPTH; ++i )
         delta[i] = -delta[i];
      _db.adjust_proxied_witness_votes( account, delta );
   } else { /// we are clearing the proxy which means we simply update the account
      _db.modify( account, [&]( account_object& a ) {
          a.proxy = o.proxy;
      });
   }
}


void account_witness_vote_evaluator::do_apply( const account_witness_vote_operation& o )
{
   const auto& voter = _db.get_account( o.account );
   FC_ASSERT( voter.proxy.size() == 0, "A proxy is currently set, please clear the proxy before voting for a witness." );

   if( o.approve )
      FC_ASSERT( voter.can_vote, "Account has declined its voting rights." );

   const auto& witness = _db.get_witness( o.witness );

   const auto& by_account_witness_idx = _db.get_index< witness_vote_index >().indices().get< by_account_witness >();
   auto itr = by_account_witness_idx.find( boost::make_tuple( voter.id, witness.id ) );

   if( itr == by_account_witness_idx.end() ) {
      FC_ASSERT( o.approve, "Vote doesn't exist, user must indicate a desire to approve witness." );

         FC_ASSERT( voter.witnesses_voted_for < CONTENTO_MAX_ACCOUNT_WITNESS_VOTES, "Account has voted for too many witnesses." ); // TODO: Remove after hardfork 2

         _db.create<witness_vote_object>( [&]( witness_vote_object& v ) {
             v.witness = witness.id;
             v.account = voter.id;
         });

      _db.adjust_witness_vote( witness, voter.witness_vote_weight() );

      _db.modify( voter, [&]( account_object& a ) {
         a.witnesses_voted_for++;
      });

   } else {
      FC_ASSERT( !o.approve, "Vote currently exists, user must indicate a desire to reject witness." );

      _db.modify( voter, [&]( account_object& a ) {
         a.witnesses_voted_for--;
      });
      _db.remove( *itr );
   }
}

void vote_evaluator::do_apply( const vote_operation& o )
{ try {
   const auto& comment = _db.get_comment( o.author, o.permlink );
   const auto& voter   = _db.get_account( o.voter );

   FC_ASSERT( !(voter.owner_challenged || voter.active_challenged ), "Operation cannot be processed because the account is currently challenged." );

   FC_ASSERT( voter.can_vote, "Voter has declined their voting rights." );

   if( o.weight > 0 ) FC_ASSERT( comment.allow_votes, "Votes are not allowed on the comment." );

   if( comment.cashout_time == fc::time_point_sec::maximum() )
   {
      const auto& comment_vote_idx = _db.get_index< comment_vote_index >().indices().get< by_comment_voter >();
      auto itr = comment_vote_idx.find( std::make_tuple( comment.id, voter.id ) );

      if( itr == comment_vote_idx.end() )
         _db.create< comment_vote_object >( [&]( comment_vote_object& cvo )
         {
            cvo.voter = voter.id;
            cvo.comment = comment.id;
//            cvo.vote_percent = o.weight;
            cvo.last_update = _db.head_block_time();
         });
      else
         _db.modify( *itr, [&]( comment_vote_object& cvo )
         {
//            cvo.vote_percent = o.weight;
            cvo.last_update = _db.head_block_time();
         });
      return;
   }

   const auto& comment_vote_idx = _db.get_index< comment_vote_index >().indices().get< by_comment_voter >();
   auto itr = comment_vote_idx.find( std::make_tuple( comment.id, voter.id ) );

   int64_t elapsed_seconds   = (_db.head_block_time() - voter.last_vote_time).to_seconds();

      FC_ASSERT( elapsed_seconds >= CONTENTO_MIN_VOTE_INTERVAL_SEC, "Can only vote once every 3 seconds." );

   int64_t regenerated_power = (CONTENTO_100_PERCENT * elapsed_seconds) / CONTENTO_VOTE_REGENERATION_SECONDS;
   int64_t current_power     = std::min( int64_t(voter.voting_power + regenerated_power), int64_t(CONTENTO_100_PERCENT) );
   FC_ASSERT( current_power > 0, "Account currently does not have voting power." );

   int64_t  abs_weight    = abs(o.weight);
   int64_t  used_power    = (current_power * abs_weight) / CONTENTO_100_PERCENT;

   const dynamic_global_property_object& dgpo = _db.get_dynamic_global_properties();


   int64_t max_vote_denom = dgpo.vote_power_reserve_rate * CONTENTO_VOTE_REGENERATION_SECONDS / (60*60*24);
   FC_ASSERT( max_vote_denom > 0 );

   used_power = (used_power + max_vote_denom - 1) / max_vote_denom;
   FC_ASSERT( used_power <= current_power, "Account does not have enough power to vote." );


    int64_t abs_rshares = (uint128_t(voter.vesting_shares.amount.value * used_power) / (CONTENTO_100_PERCENT)).to_uint64();

   if( itr == comment_vote_idx.end() )
   {
      FC_ASSERT( o.weight != 0, "Vote weight cannot be 0." );
      /// this is the rshares voting for or against the post
      int64_t rshares        = o.weight < 0 ? -abs_rshares : abs_rshares;

      if( rshares > 0 )
      {
        FC_ASSERT( _db.head_block_time() < comment.cashout_time - CONTENTO_UPVOTE_LOCKOUT_HF17, "Cannot increase payout within last twelve hours before payout." );
      }

      _db.modify( voter, [&]( account_object& a ){
         a.voting_power = current_power - used_power;
         a.last_vote_time = _db.head_block_time();
      });

      fc::uint128_t avg_cashout_sec;


      FC_ASSERT( abs_rshares > 0, "Cannot vote with 0 rshares." );

      auto old_vote_rshares = comment.vote_rshares;

      _db.modify( comment, [&]( comment_object& c ){
         c.net_rshares += rshares;
         c.abs_rshares += abs_rshares;
         if( rshares > 0 )
            c.vote_rshares += rshares;
         if( rshares > 0 )
            c.net_votes++;
         else
            c.net_votes--;
      });

      _db.create<comment_vote_object>( [&]( comment_vote_object& cv ){
         cv.voter   = voter.id;
         cv.comment = comment.id;
         cv.rshares = rshares;
         cv.last_update = _db.head_block_time();

        });

   }
   else
   {
      FC_ASSERT( itr->num_changes < CONTENTO_MAX_VOTE_CHANGES, "Voter has used the maximum number of vote changes on this comment." );


      /// this is the rshares voting for or against the post
      int64_t rshares        =   o.weight < 0 ? -abs_rshares : abs_rshares;

     if( itr->rshares < rshares )
     {
       FC_ASSERT( _db.head_block_time() < comment.cashout_time - CONTENTO_UPVOTE_LOCKOUT_HF17, "Cannot increase payout within last twelve hours before payout." );
     }

      _db.modify( voter, [&]( account_object& a ){
         a.voting_power = current_power - used_power;
         a.last_vote_time = _db.head_block_time();
      });

      _db.modify( comment, [&]( comment_object& c )
      {
         c.net_rshares -= itr->rshares;
         c.net_rshares += rshares;
         c.abs_rshares += abs_rshares;

         if( rshares > 0 && itr->rshares < 0 )
            c.net_votes += 2;
         else if( rshares > 0 && itr->rshares == 0 )
            c.net_votes += 1;
         else if( rshares == 0 && itr->rshares < 0 )
            c.net_votes += 1;
         else if( rshares == 0 && itr->rshares > 0 )
            c.net_votes -= 1;
         else if( rshares < 0 && itr->rshares == 0 )
            c.net_votes -= 1;
         else if( rshares < 0 && itr->rshares > 0 )
            c.net_votes -= 2;
      });


      _db.modify( *itr, [&]( comment_vote_object& cv )
      {
         cv.rshares = rshares;
         cv.vote_percent = o.weight;
         cv.last_update = _db.head_block_time();
         cv.weight = 0;
         cv.num_changes += 1;
      });
   }

} FC_CAPTURE_AND_RETHROW( (o)) }

void custom_evaluator::do_apply( const custom_operation& o ){}

void custom_json_evaluator::do_apply( const custom_json_operation& o )
{
   database& d = db();
   std::shared_ptr< custom_operation_interpreter > eval = d.get_custom_json_evaluator( o.id );
   if( !eval )
      return;

   try
   {
      eval->apply( o );
   }
   catch( const fc::exception& e )
   {
      if( d.is_producing() )
         throw e;
   }
   catch(...)
   {
      elog( "Unexpected exception applying custom json evaluator." );
   }
}


void custom_binary_evaluator::do_apply( const custom_binary_operation& o )
{
   database& d = db();

   std::shared_ptr< custom_operation_interpreter > eval = d.get_custom_json_evaluator( o.id );
   if( !eval )
      return;

   try
   {
      eval->apply( o );
   }
   catch( const fc::exception& e )
   {
      if( d.is_producing() )
         throw e;
   }
   catch(...)
   {
      elog( "Unexpected exception applying custom json evaluator." );
   }
}

void report_over_production_evaluator::do_apply( const report_over_production_operation& o )
{
   FC_ASSERT( false, "report_over_production_operation is disabled." );
}

void challenge_authority_evaluator::do_apply( const challenge_authority_operation& o )
{
   CONTENTOS_OP_CLOSE_ASSERT();
   if( false ) FC_ASSERT( false, "Challenge authority operation is currently disabled." );
   const auto& challenged = _db.get_account( o.challenged );
   const auto& challenger = _db.get_account( o.challenger );

   if( o.require_owner )
   {
      FC_ASSERT( challenged.reset_account == o.challenger, "Owner authority can only be challenged by its reset account." );
      FC_ASSERT( challenger.balance >= CONTENTO_OWNER_CHALLENGE_FEE );
      FC_ASSERT( !challenged.owner_challenged );
      FC_ASSERT( _db.head_block_time() - challenged.last_owner_proved > CONTENTO_OWNER_CHALLENGE_COOLDOWN );

      _db.adjust_balance( challenger, - CONTENTO_OWNER_CHALLENGE_FEE );
      _db.create_vesting( _db.get_account( o.challenged ), CONTENTO_OWNER_CHALLENGE_FEE );

      _db.modify( challenged, [&]( account_object& a )
      {
         a.owner_challenged = true;
      });
  }
  else
  {
      FC_ASSERT( challenger.balance >= CONTENTO_ACTIVE_CHALLENGE_FEE, "Account does not have sufficient funds to pay challenge fee." );
      FC_ASSERT( !( challenged.owner_challenged || challenged.active_challenged ), "Account is already challenged." );
      FC_ASSERT( _db.head_block_time() - challenged.last_active_proved > CONTENTO_ACTIVE_CHALLENGE_COOLDOWN, "Account cannot be challenged because it was recently challenged." );

      _db.adjust_balance( challenger, - CONTENTO_ACTIVE_CHALLENGE_FEE );
      _db.create_vesting( _db.get_account( o.challenged ), CONTENTO_ACTIVE_CHALLENGE_FEE );

      _db.modify( challenged, [&]( account_object& a )
      {
         a.active_challenged = true;
      });
  }
}

void prove_authority_evaluator::do_apply( const prove_authority_operation& o )
{
   CONTENTOS_OP_CLOSE_ASSERT();
   const auto& challenged = _db.get_account( o.challenged );
   FC_ASSERT( challenged.owner_challenged || challenged.active_challenged, "Account is not challeneged. No need to prove authority." );

   _db.modify( challenged, [&]( account_object& a )
   {
      a.active_challenged = false;
      a.last_active_proved = _db.head_block_time();
      if( o.require_owner )
      {
         a.owner_challenged = false;
         a.last_owner_proved = _db.head_block_time();
      }
   });
}

void request_account_recovery_evaluator::do_apply( const request_account_recovery_operation& o )
{
   CONTENTOS_OP_CLOSE_ASSERT();
   const auto& account_to_recover = _db.get_account( o.account_to_recover );

   if ( account_to_recover.recovery_account.length() )   // Make sure recovery matches expected recovery account
      FC_ASSERT( account_to_recover.recovery_account == o.recovery_account, "Cannot recover an account that does not have you as there recovery partner." );
   else                                                  // Empty string recovery account defaults to top witness
      FC_ASSERT( _db.get_index< witness_index >().indices().get< by_vote_name >().begin()->owner == o.recovery_account, "Top witness must recover an account with no recovery partner." );

   const auto& recovery_request_idx = _db.get_index< account_recovery_request_index >().indices().get< by_account >();
   auto request = recovery_request_idx.find( o.account_to_recover );

   if( request == recovery_request_idx.end() ) // New Request
   {
      FC_ASSERT( !o.new_owner_authority.is_impossible(), "Cannot recover using an impossible authority." );
      FC_ASSERT( o.new_owner_authority.weight_threshold, "Cannot recover using an open authority." );

         for( auto& a : o.new_owner_authority.account_auths )
         {
            _db.get_account( a.first );
         }

      _db.create< account_recovery_request_object >( [&]( account_recovery_request_object& req )
      {
         req.account_to_recover = o.account_to_recover;
         req.new_owner_authority = o.new_owner_authority;
         req.expires = _db.head_block_time() + CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
      });
   }
   else if( o.new_owner_authority.weight_threshold == 0 ) // Cancel Request if authority is open
   {
      _db.remove( *request );
   }
   else // Change Request
   {
      FC_ASSERT( !o.new_owner_authority.is_impossible(), "Cannot recover using an impossible authority." );


         for( auto& a : o.new_owner_authority.account_auths )
         {
            _db.get_account( a.first );
         }

      _db.modify( *request, [&]( account_recovery_request_object& req )
      {
         req.new_owner_authority = o.new_owner_authority;
         req.expires = _db.head_block_time() + CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
      });
   }
}

void recover_account_evaluator::do_apply( const recover_account_operation& o )
{
   CONTENTOS_OP_CLOSE_ASSERT();
   const auto& account = _db.get_account( o.account_to_recover );

//    if( _db.has_hardfork( CONTENTO_HARDFORK_0_12 ) )
      FC_ASSERT( _db.head_block_time() - account.last_account_recovery > CONTENTO_OWNER_UPDATE_LIMIT, "Owner authority can only be updated once an hour." );

   const auto& recovery_request_idx = _db.get_index< account_recovery_request_index >().indices().get< by_account >();
   auto request = recovery_request_idx.find( o.account_to_recover );

   FC_ASSERT( request != recovery_request_idx.end(), "There are no active recovery requests for this account." );
   FC_ASSERT( request->new_owner_authority == o.new_owner_authority, "New owner authority does not match recovery request." );

   const auto& recent_auth_idx = _db.get_index< owner_authority_history_index >().indices().get< by_account >();
   auto hist = recent_auth_idx.lower_bound( o.account_to_recover );
   bool found = false;

   while( hist != recent_auth_idx.end() && hist->account == o.account_to_recover && !found )
   {
      found = hist->previous_owner_authority == o.recent_owner_authority;
      if( found ) break;
      ++hist;
   }

   FC_ASSERT( found, "Recent authority not found in authority history." );

   _db.remove( *request ); // Remove first, update_owner_authority may invalidate iterator
   _db.update_owner_authority( account, o.new_owner_authority );
   _db.modify( account, [&]( account_object& a )
   {
      a.last_account_recovery = _db.head_block_time();
   });
}

void change_recovery_account_evaluator::do_apply( const change_recovery_account_operation& o )
{
   CONTENTOS_OP_CLOSE_ASSERT();
   _db.get_account( o.new_recovery_account ); // Simply validate account exists
   const auto& account_to_recover = _db.get_account( o.account_to_recover );

   const auto& change_recovery_idx = _db.get_index< change_recovery_account_request_index >().indices().get< by_account >();
   auto request = change_recovery_idx.find( o.account_to_recover );

   if( request == change_recovery_idx.end() ) // New request
   {
      _db.create< change_recovery_account_request_object >( [&]( change_recovery_account_request_object& req )
      {
         req.account_to_recover = o.account_to_recover;
         req.recovery_account = o.new_recovery_account;
         req.effective_on = _db.head_block_time() + CONTENTO_OWNER_AUTH_RECOVERY_PERIOD;
      });
   }
   else if( account_to_recover.recovery_account != o.new_recovery_account ) // Change existing request
   {
      _db.modify( *request, [&]( change_recovery_account_request_object& req )
      {
         req.recovery_account = o.new_recovery_account;
         req.effective_on = _db.head_block_time() + CONTENTO_OWNER_AUTH_RECOVERY_PERIOD;
      });
   }
   else // Request exists and changing back to current recovery account
   {
      _db.remove( *request );
   }
}




void vm_evaluator::do_apply( const vm_operation& o )  {
    
    uint64_t gas = 0;
    bool error = false;
    fc::exception_ptr exc_ptr;
    
    const auto& caller = _db.get_account(o.caller);

    auto session = _db.start_undo_session(true);
    try {
        
        if( caller.active_challenged )
        {
            _db.modify( caller, [&]( account_object& a )
                       {
                           a.active_challenged = false;
                           a.last_active_proved = _db.head_block_time();
                       });
        }
        
        // caller->contract trasfer
        if(o.value.amount > 0) {
            gas += config::gas_per_contract_trasfer;
            
            FC_ASSERT( _db.get_balance( caller, o.value.symbol ) >= o.value, "Account does not have sufficient funds for transfer." );
            _db.adjust_balance( caller, -o.value );
            _db.adjust_contract_balance( _db.get_contract_account(o.contract_name), o.value );
        }
        
        // apply vm action
        int64_t caller_coc = _db.get_balance( caller, COC_SYMBOL ).amount.value;
        FC_ASSERT( caller_coc >= gas / config::gas_per_coc, "Not enough balance to apply vm action." );
        
        const uint64_t max_tps = 3000;
        uint32_t tps = _db.tps();
        if (tps >= max_tps) tps = max_tps - 1;
        
        ctx->init_bill( (uint64_t)caller_coc * config::gas_per_coc - gas,
                       10,
                       1 * max_tps / (max_tps - tps)
                       );
        ctx->apply(o);
        
        // payable check, payable flag setted up in ctx->apply(o)
        if(!ctx->get_payable_flag()){
            FC_ASSERT(o.value.amount == 0, "api can not accept money.");
        }
    } catch (fc::exception& e) {
        error = true;
        exc_ptr = e.dynamic_copy_exception();
    } catch (...) {
        error = true;
        exc_ptr = std::make_shared<fc::exception>();
    }
    
    // prepare to pay the gas fee
    gas += ctx->gas();
    uint64_t coc_cost = gas / config::gas_per_coc;
    uint64_t caller_coc = _db.get_balance( caller, COC_SYMBOL ).amount.value;
    
    if (coc_cost > caller_coc) {
        // caller's balance is not enough for gas fee. we'll take all her money and mark an error.
        coc_cost = caller_coc;
        if (!error) {
            error = true;
            exc_ptr = std::make_shared<fc::exception>(unspecified_exception_code, 
                "exception", "Not enough balance for gas fee.");
        }
    }
    // before paying gas fee, rollback any changes if any error occurred.
    if (error) {
        session.undo();
    }
    
    // pay gas fee
    if (coc_cost > 0) {
        try {
            transfer_operation pay;
            pay.from = o.caller;
            pay.to = config::gas_fee_account_name;
            pay.amount = asset(coc_cost, COC_SYMBOL);
            pay.memo = "gas fee";
            
            transfer_evaluator(_db).do_apply(pay);
            ctx->add_paid_gas(coc_cost * config::gas_per_coc);
            
        } catch(fc::exception& e) {
            if (!error) {
                error = true;
                exc_ptr = e.dynamic_copy_exception();
            }
        } catch(...) {
            error = true;
            exc_ptr = std::make_shared<fc::exception>();
        }
    }
    
    if (error) {
        ctx->set_vm_error(exc_ptr);
    } else {
        // everything is ok, commit all changes.
        session.squash();
    }
}

} } // contento::chain
