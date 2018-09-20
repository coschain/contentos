#pragma once
#include <contento/app/applied_operation.hpp>
#include <contento/app/contento_api_objects.hpp>

#include <contento/chain/global_property_object.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/contento_objects.hpp>

namespace contento { namespace app {
   using std::string;
   using std::vector;

   struct discussion_index
   {
      string           category;    /// category by which everything is filtered
      vector< string > trending;    /// trending posts over the last 24 hours
      vector< string > payout;      /// pending posts by payout
      vector< string > payout_comments; /// pending comments by payout
      vector< string > trending30;  /// pending lifetime payout
      vector< string > created;     /// creation date
      vector< string > responses;   /// creation date
      vector< string > updated;     /// creation date
      vector< string > active;      /// last update or reply
      vector< string > votes;       /// last update or reply
      vector< string > cashout;     /// last update or reply
      vector< string > maturing;    /// about to be paid out
      vector< string > best;        /// total lifetime payout
      vector< string > hot;         /// total lifetime payout
      vector< string > promoted;    /// pending lifetime payout
   };

   struct tag_index
   {
      vector< string > trending; /// pending payouts
   };

   struct vote_state
   {
      string         voter;
      uint64_t       weight = 0;
      int64_t        rshares = 0;
      int16_t        percent = 0;
      share_type     reputation = 0;
      time_point_sec time;
   };

   struct account_vote
   {
      string         authorperm;
      uint64_t       weight = 0;
      int64_t        rshares = 0;
      int16_t        percent = 0;
      time_point_sec time;
   };

   struct  discussion : public comment_api_obj {
      discussion( const comment_object& o ):comment_api_obj(o){}
      discussion(){}

      string                      url; /// /category/@rootauthor/root_permlink#author/permlink
      string                      root_title;
      asset                       pending_payout_value; ///< sbd
      asset                       total_pending_payout_value; ///< sbd including replies
      vector<vote_state>          active_votes;
      vector<string>              replies; ///< author/slug mapping
      share_type                  author_reputation = 0;
      // asset                       promoted = asset(0, SBD_SYMBOL);
      asset                       promoted = asset(0, VESTS_SYMBOL);
      uint32_t                    body_length = 0;
      vector<account_name_type>   reblogged_by;
      optional<account_name_type> first_reblogged_by;
      optional<time_point_sec>    first_reblogged_on;
   };

   /**
    *  Convert's vesting shares
    */
   struct extended_account : public account_api_obj
   {
      extended_account(){}
      extended_account( const account_object& a, const database& db ):account_api_obj( a, db ){}

      asset                                   vesting_balance; /// convert vesting_shares to vesting steem
      share_type                              reputation = 0;
      map<uint64_t,applied_operation>         transfer_history; /// transfer to/from vesting
      map<uint64_t,applied_operation>         post_history;
      map<uint64_t,applied_operation>         vote_history;
      map<uint64_t,applied_operation>         other_history;
      set<string>                             witness_votes;
      vector<pair<string,uint32_t>>            tags_usage;
      vector<pair<account_name_type,uint32_t>> guest_bloggers;

      optional<vector<string>>                comments; /// permlinks for this user
      optional<vector<string>>                blog; /// blog posts for this user
      optional<vector<string>>                recent_replies; /// blog posts for this user
      optional<vector<string>>                recommended; /// posts recommened for this user
   };

   /**
    *  This struct is designed
    */
   struct state {
        string                            current_route;

        dynamic_global_property_api_obj   props;

        app::tag_index                    tag_idx;

        /**
         * "" is the global discussion index
         */
        map<string, discussion_index>     discussion_idx;

        map< string, tag_api_obj >        tags;

        /**
         *  map from account/slug to full nested discussion
         */
        map< string, discussion >         content;
        map< string, extended_account >   accounts;
        vector< account_name_type >       pow_queue;
        map< string, witness_api_obj >    witnesses;
        witness_schedule_api_obj          witness_schedule;
        string                            error;
   };

} }

FC_REFLECT_DERIVED( contento::app::extended_account,
                   (contento::app::account_api_obj),
                   (vesting_balance)(reputation)
                   (transfer_history)(post_history)(vote_history)(other_history)(witness_votes)(tags_usage)(guest_bloggers)(comments)(blog)(recent_replies)(recommended) )


FC_REFLECT( contento::app::vote_state, (voter)(weight)(rshares)(percent)(reputation)(time) );
FC_REFLECT( contento::app::account_vote, (authorperm)(weight)(rshares)(percent)(time) );

FC_REFLECT( contento::app::discussion_index, (category)(trending)(payout)(payout_comments)(trending30)(updated)(created)(responses)(active)(votes)(maturing)(best)(hot)(promoted)(cashout) )
FC_REFLECT( contento::app::tag_index, (trending) )
FC_REFLECT_DERIVED( contento::app::discussion, (contento::app::comment_api_obj), (url)(root_title)(pending_payout_value)(total_pending_payout_value)(active_votes)(replies)(author_reputation)(promoted)(body_length)(reblogged_by)(first_reblogged_by)(first_reblogged_on) )

FC_REFLECT( contento::app::state, (current_route)(props)(tag_idx)(tags)(content)(accounts)(pow_queue)(witnesses)(discussion_idx)(witness_schedule)(error) )

