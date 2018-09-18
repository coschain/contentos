
#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <cosiolib/cosio.hpp>
#include <cosiolib/static_variant.hpp>
#include <cosiolib/content_util.hpp>


namespace cosio { 

using std::vector;
using std::string;
using std::map;


using comment_id_type	 = id_type;
using account_id_type	 = id_type;
using account_authority_map	 = map<namex,uint16>;
using key_authority_map	 = map<public_key_type,uint16>;
using scope_name_type	 = namex;
using witness_id_type	 = id_type;
using feed_history_id_type	 = id_type;
using reward_fund_id_type	 = id_type;
using reward_fund_name_type	 = string16;
using owner_authority_history_id_type	 = id_type;
using account_recovery_request_id_type	 = id_type;
using savings_withdraw_id_type	 = id_type;

struct follow_api_obj {
	string		follower;
	string		following;
	vector<int64>		what; 
 
	COSLIB_SERIALIZE( follow_api_obj, (follower)(following)(what) ) 
};

struct follow_count_api_obj {
	string		account;
	uint32		follower_count;
	uint32		following_count; 
 
	COSLIB_SERIALIZE( follow_count_api_obj, (account)(follower_count)(following_count) ) 
};

struct feed_entry {
	string		author;
	string		permlink;
	vector<namex>		reblog_by;
	time_point_sec		reblog_on;
	uint32		entry_id; 
 
	COSLIB_SERIALIZE( feed_entry, (author)(permlink)(reblog_by)(reblog_on)(entry_id) ) 
};

struct beneficiary_route_type {
	namex		account;
	uint16		weight; 
 
	COSLIB_SERIALIZE( beneficiary_route_type, (account)(weight) ) 
};

struct comment_api_obj {
	comment_id_type		id;
	namex		author;
	string		permlink;
	string		category;
	namex		parent_author;
	string		parent_permlink;
	string		title;
	string		body;
	string		json_metadata;
	time_point_sec		last_update;
	time_point_sec		created;
	time_point_sec		active;
	time_point_sec		last_payout;
	uint8		depth;
	uint32		children;
	int64		net_rshares;
	int64		abs_rshares;
	int64		vote_rshares;
	int64		children_abs_rshares;
	time_point_sec		cashout_time;
	time_point_sec		max_cashout_time;
	uint64		total_vote_weight;
	uint16		reward_weight;
	asset		total_payout_value;
	int64		author_rewards;
	int32		net_votes;
	comment_id_type		root_comment;
	bool		allow_replies;
	bool		allow_votes;
	bool		allow_curation_rewards;
	vector<beneficiary_route_type>		beneficiaries; 
 
	COSLIB_SERIALIZE( comment_api_obj, (id)(author)(permlink)(category)(parent_author)(parent_permlink)(title)(body)(json_metadata)(last_update)(created)(active)(last_payout)(depth)(children)(net_rshares)(abs_rshares)(vote_rshares)(children_abs_rshares)(cashout_time)(max_cashout_time)(total_vote_weight)(reward_weight)(total_payout_value)(author_rewards)(net_votes)(root_comment)(allow_replies)(allow_votes)(allow_curation_rewards)(beneficiaries) ) 
};

struct comment_feed_entry {
	comment_api_obj		comment;
	vector<namex>		reblog_by;
	time_point_sec		reblog_on;
	uint32		entry_id; 
 
	COSLIB_SERIALIZE( comment_feed_entry, (comment)(reblog_by)(reblog_on)(entry_id) ) 
};

struct blog_entry {
	string		author;
	string		permlink;
	string		blog;
	time_point_sec		reblog_on;
	uint32		entry_id; 
 
	COSLIB_SERIALIZE( blog_entry, (author)(permlink)(blog)(reblog_on)(entry_id) ) 
};

struct comment_blog_entry {
	comment_api_obj		comment;
	string		blog;
	time_point_sec		reblog_on;
	uint32		entry_id; 
 
	COSLIB_SERIALIZE( comment_blog_entry, (comment)(blog)(reblog_on)(entry_id) ) 
};

struct account_reputation {
	string		account;
	int64		reputation; 
 
	COSLIB_SERIALIZE( account_reputation, (account)(reputation) ) 
};

struct tag_api_obj {
	string		name;
	asset		total_payouts;
	int32		net_votes;
	uint32		top_posts;
	uint32		comments;
	uint128		trending; 
 
	COSLIB_SERIALIZE( tag_api_obj, (name)(total_payouts)(net_votes)(top_posts)(comments)(trending) ) 
};

struct dynamic_global_property_object {
	int64		id;
	uint32		head_block_number;
	checksum160		head_block_id;
	time_point_sec		time;
	namex		current_witness;
	uint64		total_pow;
	uint32		num_pow_witnesses;
	asset		current_supply;
	asset		total_coc;
	asset		total_vesting_shares;
	uint128		total_reward_shares2;
	uint32		maximum_block_size;
	uint64		current_aslot;
	uint128		recent_slots_filled;
	uint8		participation_count;
	uint32		last_irreversible_block_num;
	uint32		vote_power_reserve_rate;
	uint32		tps; 
 
	COSLIB_SERIALIZE( dynamic_global_property_object, (id)(head_block_number)(head_block_id)(time)(current_witness)(total_pow)(num_pow_witnesses)(current_supply)(total_coc)(total_vesting_shares)(total_reward_shares2)(maximum_block_size)(current_aslot)(recent_slots_filled)(participation_count)(last_irreversible_block_num)(vote_power_reserve_rate)(tps) ) 
};

struct dynamic_global_property_api_obj : public dynamic_global_property_object {
	uint32		current_reserve_ratio;
	uint64		average_block_size;
	uint128		max_virtual_bandwidth; 
 
	COSLIB_SERIALIZE_DERIVED( dynamic_global_property_api_obj, dynamic_global_property_object,(current_reserve_ratio)(average_block_size)(max_virtual_bandwidth) ) 
};

struct tag_index {
	vector<string>		trending; 
 
	COSLIB_SERIALIZE( tag_index, (trending) ) 
};

struct discussion_index {
	string		category;
	vector<string>		trending;
	vector<string>		payout;
	vector<string>		payout_comments;
	vector<string>		trending30;
	vector<string>		updated;
	vector<string>		created;
	vector<string>		responses;
	vector<string>		active;
	vector<string>		votes;
	vector<string>		maturing;
	vector<string>		best;
	vector<string>		hot;
	vector<string>		promoted;
	vector<string>		cashout; 
 
	COSLIB_SERIALIZE( discussion_index, (category)(trending)(payout)(payout_comments)(trending30)(updated)(created)(responses)(active)(votes)(maturing)(best)(hot)(promoted)(cashout) ) 
};

struct vote_state {
	string		voter;
	uint64		weight;
	int64		rshares;
	int16		percent;
	int64		reputation;
	time_point_sec		time; 
 
	COSLIB_SERIALIZE( vote_state, (voter)(weight)(rshares)(percent)(reputation)(time) ) 
};

struct discussion : public comment_api_obj {
	string		url;
	string		root_title;
	asset		pending_payout_value;
	asset		total_pending_payout_value;
	vector<vote_state>		active_votes;
	vector<string>		replies;
	int64		author_reputation;
	asset		promoted;
	uint32		body_length;
	vector<namex>		reblogged_by;
	vector<namex>		first_reblogged_by;
	vector<time_point_sec>		first_reblogged_on; 
 
	COSLIB_SERIALIZE_DERIVED( discussion, comment_api_obj,(url)(root_title)(pending_payout_value)(total_pending_payout_value)(active_votes)(replies)(author_reputation)(promoted)(body_length)(reblogged_by)(first_reblogged_by)(first_reblogged_on) ) 
};

struct authority {
	uint32		weight_threshold;
	account_authority_map		account_auths;
	key_authority_map		key_auths; 
 
	COSLIB_SERIALIZE( authority, (weight_threshold)(account_auths)(key_auths) ) 
};

struct account_api_obj {
	account_id_type		id;
	namex		name;
	authority		owner;
	authority		active;
	authority		posting;
	public_key_type		memo_key;
	string		json_metadata;
	namex		proxy;
	time_point_sec		last_owner_update;
	time_point_sec		last_account_update;
	time_point_sec		created;
	bool		mined;
	bool		owner_challenged;
	bool		active_challenged;
	time_point_sec		last_owner_proved;
	time_point_sec		last_active_proved;
	namex		recovery_account;
	time_point_sec		last_account_recovery;
	namex		reset_account;
	uint32		comment_count;
	uint32		lifetime_vote_count;
	uint32		post_count;
	bool		can_vote;
	uint16		voting_power;
	time_point_sec		last_vote_time;
	asset		balance;
	asset		savings_balance;
	uint8		savings_withdraw_requests;
	asset		reward_steem_balance;
	asset		reward_vesting_balance;
	asset		reward_vesting_steem;
	asset		vesting_shares;
	asset		delegated_vesting_shares;
	asset		received_vesting_shares;
	asset		vesting_withdraw_rate;
	time_point_sec		next_vesting_withdrawal;
	int64		withdrawn;
	int64		to_withdraw;
	uint16		withdraw_routes;
	int64		curation_rewards;
	int64		posting_rewards;
	vector<int64>		proxied_vsf_votes;
	uint16		witnesses_voted_for;
	int64		average_bandwidth;
	int64		lifetime_bandwidth;
	time_point_sec		last_bandwidth_update;
	int64		average_market_bandwidth;
	int64		lifetime_market_bandwidth;
	time_point_sec		last_market_bandwidth_update;
	time_point_sec		last_post;
	time_point_sec		last_root_post; 
 
	COSLIB_SERIALIZE( account_api_obj, (id)(name)(owner)(active)(posting)(memo_key)(json_metadata)(proxy)(last_owner_update)(last_account_update)(created)(mined)(owner_challenged)(active_challenged)(last_owner_proved)(last_active_proved)(recovery_account)(last_account_recovery)(reset_account)(comment_count)(lifetime_vote_count)(post_count)(can_vote)(voting_power)(last_vote_time)(balance)(savings_balance)(savings_withdraw_requests)(reward_steem_balance)(reward_vesting_balance)(reward_vesting_steem)(vesting_shares)(delegated_vesting_shares)(received_vesting_shares)(vesting_withdraw_rate)(next_vesting_withdrawal)(withdrawn)(to_withdraw)(withdraw_routes)(curation_rewards)(posting_rewards)(proxied_vsf_votes)(witnesses_voted_for)(average_bandwidth)(lifetime_bandwidth)(last_bandwidth_update)(average_market_bandwidth)(lifetime_market_bandwidth)(last_market_bandwidth_update)(last_post)(last_root_post) ) 
};

struct vote_operation {
	namex		voter;
	namex		author;
	string		permlink;
	int16		weight; 
 
	COSLIB_SERIALIZE( vote_operation, (voter)(author)(permlink)(weight) ) 
};

struct comment_operation {
	namex		parent_author;
	string		parent_permlink;
	string		category;
	namex		author;
	string		permlink;
	string		title;
	string		body;
	string		json_metadata; 
 
	COSLIB_SERIALIZE( comment_operation, (parent_author)(parent_permlink)(category)(author)(permlink)(title)(body)(json_metadata) ) 
};

struct transfer_operation {
	namex		from;
	namex		to;
	asset		amount;
	string		memo; 
 
	COSLIB_SERIALIZE( transfer_operation, (from)(to)(amount)(memo) ) 
};

struct transfer_to_vesting_operation {
	namex		from;
	namex		to;
	asset		amount; 
 
	COSLIB_SERIALIZE( transfer_to_vesting_operation, (from)(to)(amount) ) 
};

struct withdraw_vesting_operation {
	namex		account;
	asset		vesting_shares; 
 
	COSLIB_SERIALIZE( withdraw_vesting_operation, (account)(vesting_shares) ) 
};

struct convert_from_vesting_operation {
	namex		account;
	asset		vesting_shares; 
 
	COSLIB_SERIALIZE( convert_from_vesting_operation, (account)(vesting_shares) ) 
};

struct limit_order_create_operation {
	namex		owner;
	uint32		orderid;
	asset		amount_to_sell;
	asset		min_to_receive;
	bool		fill_or_kill;
	time_point_sec		expiration; 
 
	COSLIB_SERIALIZE( limit_order_create_operation, (owner)(orderid)(amount_to_sell)(min_to_receive)(fill_or_kill)(expiration) ) 
};

struct limit_order_cancel_operation {
	namex		owner;
	uint32		orderid; 
 
	COSLIB_SERIALIZE( limit_order_cancel_operation, (owner)(orderid) ) 
};

struct price {
	asset		base;
	asset		quote; 
 
	COSLIB_SERIALIZE( price, (base)(quote) ) 
};

struct feed_publish_operation {
	namex		publisher;
	price		exchange_rate; 
 
	COSLIB_SERIALIZE( feed_publish_operation, (publisher)(exchange_rate) ) 
};

struct convert_operation {
	namex		owner;
	uint32		requestid;
	asset		amount; 
 
	COSLIB_SERIALIZE( convert_operation, (owner)(requestid)(amount) ) 
};

struct account_create_operation {
	asset		fee;
	namex		creator;
	namex		new_account_name;
	authority		owner;
	authority		active;
	authority		posting;
	public_key_type		memo_key;
	string		json_metadata; 
 
	COSLIB_SERIALIZE( account_create_operation, (fee)(creator)(new_account_name)(owner)(active)(posting)(memo_key)(json_metadata) ) 
};

struct account_update_operation {
	namex		account;
	vector<authority>		owner;
	vector<authority>		active;
	vector<authority>		posting;
	public_key_type		memo_key;
	string		json_metadata; 
 
	COSLIB_SERIALIZE( account_update_operation, (account)(owner)(active)(posting)(memo_key)(json_metadata) ) 
};

struct chain_properties {
	asset		account_creation_fee;
	uint32		maximum_block_size;
	uint16		sbd_interest_rate; 
 
	COSLIB_SERIALIZE( chain_properties, (account_creation_fee)(maximum_block_size)(sbd_interest_rate) ) 
};

struct witness_update_operation {
	namex		owner;
	string		url;
	public_key_type		block_signing_key;
	chain_properties		props;
	asset		fee; 
 
	COSLIB_SERIALIZE( witness_update_operation, (owner)(url)(block_signing_key)(props)(fee) ) 
};

struct account_witness_vote_operation {
	namex		account;
	namex		witness;
	bool		approve; 
 
	COSLIB_SERIALIZE( account_witness_vote_operation, (account)(witness)(approve) ) 
};

struct account_witness_proxy_operation {
	namex		account;
	namex		proxy; 
 
	COSLIB_SERIALIZE( account_witness_proxy_operation, (account)(proxy) ) 
};

struct pow {
	public_key_type		worker;
	checksum256		input;
	signature_type		signature;
	checksum256		work; 
 
	COSLIB_SERIALIZE( pow, (worker)(input)(signature)(work) ) 
};

struct pow_operation {
	namex		worker_account;
	checksum160		block_id;
	uint64		nonce;
	pow		work;
	chain_properties		props; 
 
	COSLIB_SERIALIZE( pow_operation, (worker_account)(block_id)(nonce)(work)(props) ) 
};

struct custom_operation {
	vector<namex>		required_auths;
	uint16		id;
	vector<int8>		data; 
 
	COSLIB_SERIALIZE( custom_operation, (required_auths)(id)(data) ) 
};

struct void_t {
 
 
	COSLIB_SERIALIZE( void_t,  ) 
};

struct version {
	uint32		v_num; 
 
	COSLIB_SERIALIZE( version, (v_num) ) 
};

struct hardfork_version : public version {
 
 
	COSLIB_SERIALIZE_DERIVED( hardfork_version, version, ) 
};

struct hardfork_version_vote {
	hardfork_version		hf_version;
	time_point_sec		hf_time; 
 
	COSLIB_SERIALIZE( hardfork_version_vote, (hf_version)(hf_time) ) 
};

typedef static_variant<void_t,version,hardfork_version_vote>
	block_header_extensions;


using block_header_extensions_type	 = vector<block_header_extensions>;

struct block_header {
	checksum160		previous;
	time_point_sec		timestamp;
	string		witness;
	checksum160		transaction_merkle_root;
	block_header_extensions_type		extensions; 
 
	COSLIB_SERIALIZE( block_header, (previous)(timestamp)(witness)(transaction_merkle_root)(extensions) ) 
};

struct signed_block_header : public block_header {
	signature_type		witness_signature; 
 
	COSLIB_SERIALIZE_DERIVED( signed_block_header, block_header,(witness_signature) ) 
};

struct report_over_production_operation {
	namex		reporter;
	signed_block_header		first_block;
	signed_block_header		second_block; 
 
	COSLIB_SERIALIZE( report_over_production_operation, (reporter)(first_block)(second_block) ) 
};

struct delete_comment_operation {
	namex		author;
	string		permlink; 
 
	COSLIB_SERIALIZE( delete_comment_operation, (author)(permlink) ) 
};

struct custom_json_operation {
	vector<namex>		required_auths;
	vector<namex>		required_posting_auths;
	string		id;
	string		json; 
 
	COSLIB_SERIALIZE( custom_json_operation, (required_auths)(required_posting_auths)(id)(json) ) 
};

struct comment_payout_beneficiaries {
	vector<beneficiary_route_type>		beneficiaries; 
 
	COSLIB_SERIALIZE( comment_payout_beneficiaries, (beneficiaries) ) 
};

typedef static_variant<comment_payout_beneficiaries>
	comment_options_extension;


using comment_options_extensions_type	 = vector<comment_options_extension>;

struct comment_options_operation {
	namex		author;
	string		permlink;
	asset		max_accepted_payout;
	uint16		percent_steem_dollars;
	bool		allow_votes;
	bool		allow_curation_rewards;
	comment_options_extensions_type		extensions; 
 
	COSLIB_SERIALIZE( comment_options_operation, (author)(permlink)(max_accepted_payout)(percent_steem_dollars)(allow_votes)(allow_curation_rewards)(extensions) ) 
};

struct set_withdraw_vesting_route_operation {
	namex		from_account;
	namex		to_account;
	uint16		percent;
	bool		auto_vest; 
 
	COSLIB_SERIALIZE( set_withdraw_vesting_route_operation, (from_account)(to_account)(percent)(auto_vest) ) 
};

struct limit_order_create2_operation {
	namex		owner;
	uint32		orderid;
	asset		amount_to_sell;
	price		exchange_rate;
	bool		fill_or_kill;
	time_point_sec		expiration; 
 
	COSLIB_SERIALIZE( limit_order_create2_operation, (owner)(orderid)(amount_to_sell)(exchange_rate)(fill_or_kill)(expiration) ) 
};

struct challenge_authority_operation {
	namex		challenger;
	namex		challenged;
	bool		require_owner; 
 
	COSLIB_SERIALIZE( challenge_authority_operation, (challenger)(challenged)(require_owner) ) 
};

struct prove_authority_operation {
	namex		challenged;
	bool		require_owner; 
 
	COSLIB_SERIALIZE( prove_authority_operation, (challenged)(require_owner) ) 
};

struct request_account_recovery_operation {
	namex		recovery_account;
	namex		account_to_recover;
	authority		new_owner_authority;
	extensions_type		extensions; 
 
	COSLIB_SERIALIZE( request_account_recovery_operation, (recovery_account)(account_to_recover)(new_owner_authority)(extensions) ) 
};

struct recover_account_operation {
	namex		account_to_recover;
	authority		new_owner_authority;
	authority		recent_owner_authority;
	extensions_type		extensions; 
 
	COSLIB_SERIALIZE( recover_account_operation, (account_to_recover)(new_owner_authority)(recent_owner_authority)(extensions) ) 
};

struct change_recovery_account_operation {
	namex		account_to_recover;
	namex		new_recovery_account;
	extensions_type		extensions; 
 
	COSLIB_SERIALIZE( change_recovery_account_operation, (account_to_recover)(new_recovery_account)(extensions) ) 
};

struct transfer_to_savings_operation {
	namex		from;
	namex		to;
	asset		amount;
	string		memo; 
 
	COSLIB_SERIALIZE( transfer_to_savings_operation, (from)(to)(amount)(memo) ) 
};

struct transfer_from_savings_operation {
	namex		from;
	uint32		request_id;
	namex		to;
	asset		amount;
	string		memo; 
 
	COSLIB_SERIALIZE( transfer_from_savings_operation, (from)(request_id)(to)(amount)(memo) ) 
};

struct cancel_transfer_from_savings_operation {
	namex		from;
	uint32		request_id; 
 
	COSLIB_SERIALIZE( cancel_transfer_from_savings_operation, (from)(request_id) ) 
};

struct custom_binary_operation {
	vector<namex>		required_owner_auths;
	vector<namex>		required_active_auths;
	vector<namex>		required_posting_auths;
	vector<authority>		required_auths;
	string		id;
	vector<int8>		data; 
 
	COSLIB_SERIALIZE( custom_binary_operation, (required_owner_auths)(required_active_auths)(required_posting_auths)(required_auths)(id)(data) ) 
};

struct decline_voting_rights_operation {
	namex		account;
	bool		decline; 
 
	COSLIB_SERIALIZE( decline_voting_rights_operation, (account)(decline) ) 
};

struct reset_account_operation {
	namex		reset_account;
	namex		account_to_reset;
	authority		new_owner_authority; 
 
	COSLIB_SERIALIZE( reset_account_operation, (reset_account)(account_to_reset)(new_owner_authority) ) 
};

struct set_reset_account_operation {
	namex		account;
	namex		current_reset_account;
	namex		reset_account; 
 
	COSLIB_SERIALIZE( set_reset_account_operation, (account)(current_reset_account)(reset_account) ) 
};

struct claim_reward_balance_operation {
	namex		account;
	asset		reward_steem;
	asset		reward_sbd;
	asset		reward_vests; 
 
	COSLIB_SERIALIZE( claim_reward_balance_operation, (account)(reward_steem)(reward_sbd)(reward_vests) ) 
};

struct delegate_vesting_shares_operation {
	namex		delegator;
	namex		delegatee;
	asset		vesting_shares; 
 
	COSLIB_SERIALIZE( delegate_vesting_shares_operation, (delegator)(delegatee)(vesting_shares) ) 
};

struct account_create_with_delegation_operation {
	asset		fee;
	asset		delegation;
	namex		creator;
	namex		new_account_name;
	authority		owner;
	authority		active;
	authority		posting;
	public_key_type		memo_key;
	string		json_metadata;
	extensions_type		extensions; 
 
	COSLIB_SERIALIZE( account_create_with_delegation_operation, (fee)(delegation)(creator)(new_account_name)(owner)(active)(posting)(memo_key)(json_metadata)(extensions) ) 
};

struct admin_grant_operation {
	namex		creator;
	namex		nominee;
	int32		type;
	bool		is_grant; 
 
	COSLIB_SERIALIZE( admin_grant_operation, (creator)(nominee)(type)(is_grant) ) 
};

struct comment_report_operation {
	namex		reporter;
	namex		author;
	string		permlink;
	asset		credit;
	string		tag;
	bool		is_ack;
	bool		approved; 
 
	COSLIB_SERIALIZE( comment_report_operation, (reporter)(author)(permlink)(credit)(tag)(is_ack)(approved) ) 
};

struct fill_convert_request_operation {
	namex		owner;
	uint32		requestid;
	asset		amount_in;
	asset		amount_out; 
 
	COSLIB_SERIALIZE( fill_convert_request_operation, (owner)(requestid)(amount_in)(amount_out) ) 
};

struct author_reward_operation {
	namex		author;
	string		permlink;
	asset		sbd_payout;
	asset		steem_payout;
	asset		vesting_payout; 
 
	COSLIB_SERIALIZE( author_reward_operation, (author)(permlink)(sbd_payout)(steem_payout)(vesting_payout) ) 
};

struct curation_reward_operation {
	namex		curator;
	asset		reward;
	namex		comment_author;
	string		comment_permlink; 
 
	COSLIB_SERIALIZE( curation_reward_operation, (curator)(reward)(comment_author)(comment_permlink) ) 
};

struct comment_reward_operation {
	namex		author;
	string		permlink;
	asset		payout; 
 
	COSLIB_SERIALIZE( comment_reward_operation, (author)(permlink)(payout) ) 
};

struct subject_reward_operation {
	namex		author;
	string		permlink;
	asset		payout; 
 
	COSLIB_SERIALIZE( subject_reward_operation, (author)(permlink)(payout) ) 
};

struct liquidity_reward_operation {
	namex		owner;
	asset		payout; 
 
	COSLIB_SERIALIZE( liquidity_reward_operation, (owner)(payout) ) 
};

struct fill_vesting_withdraw_operation {
	namex		from_account;
	namex		to_account;
	asset		withdrawn;
	asset		deposited; 
 
	COSLIB_SERIALIZE( fill_vesting_withdraw_operation, (from_account)(to_account)(withdrawn)(deposited) ) 
};

struct fill_order_operation {
	namex		current_owner;
	uint32		current_orderid;
	asset		current_pays;
	namex		open_owner;
	uint32		open_orderid;
	asset		open_pays; 
 
	COSLIB_SERIALIZE( fill_order_operation, (current_owner)(current_orderid)(current_pays)(open_owner)(open_orderid)(open_pays) ) 
};

struct shutdown_witness_operation {
	namex		owner; 
 
	COSLIB_SERIALIZE( shutdown_witness_operation, (owner) ) 
};

struct fill_transfer_from_savings_operation {
	namex		from;
	namex		to;
	asset		amount;
	uint32		request_id;
	string		memo; 
 
	COSLIB_SERIALIZE( fill_transfer_from_savings_operation, (from)(to)(amount)(request_id)(memo) ) 
};

struct hardfork_operation {
	uint32		hardfork_id; 
 
	COSLIB_SERIALIZE( hardfork_operation, (hardfork_id) ) 
};

struct comment_payout_update_operation {
	namex		author;
	string		permlink; 
 
	COSLIB_SERIALIZE( comment_payout_update_operation, (author)(permlink) ) 
};

struct subject_payout_update_operation {
	namex		author;
	string		permlink; 
 
	COSLIB_SERIALIZE( subject_payout_update_operation, (author)(permlink) ) 
};

struct return_vesting_delegation_operation {
	namex		account;
	asset		vesting_shares; 
 
	COSLIB_SERIALIZE( return_vesting_delegation_operation, (account)(vesting_shares) ) 
};

struct comment_benefactor_reward_operation {
	namex		benefactor;
	namex		author;
	string		permlink;
	asset		reward; 
 
	COSLIB_SERIALIZE( comment_benefactor_reward_operation, (benefactor)(author)(permlink)(reward) ) 
};

struct producer_reward_operation {
	namex		producer;
	asset		vesting_shares; 
 
	COSLIB_SERIALIZE( producer_reward_operation, (producer)(vesting_shares) ) 
};

struct vm_operation {
	namex		caller;
	scope_name_type		contract_name;
	name		action_name;
	bytes		data;
	asset		value; 
 
	COSLIB_SERIALIZE( vm_operation, (caller)(contract_name)(action_name)(data)(value) ) 
};

typedef static_variant<vote_operation,comment_operation,transfer_operation,transfer_to_vesting_operation,withdraw_vesting_operation,convert_from_vesting_operation,limit_order_create_operation,limit_order_cancel_operation,feed_publish_operation,convert_operation,account_create_operation,account_update_operation,witness_update_operation,account_witness_vote_operation,account_witness_proxy_operation,pow_operation,custom_operation,report_over_production_operation,delete_comment_operation,custom_json_operation,comment_options_operation,set_withdraw_vesting_route_operation,limit_order_create2_operation,challenge_authority_operation,prove_authority_operation,request_account_recovery_operation,recover_account_operation,change_recovery_account_operation,transfer_to_savings_operation,transfer_from_savings_operation,cancel_transfer_from_savings_operation,custom_binary_operation,decline_voting_rights_operation,reset_account_operation,set_reset_account_operation,claim_reward_balance_operation,delegate_vesting_shares_operation,account_create_with_delegation_operation,admin_grant_operation,comment_report_operation,fill_convert_request_operation,author_reward_operation,curation_reward_operation,comment_reward_operation,subject_reward_operation,liquidity_reward_operation,fill_vesting_withdraw_operation,fill_order_operation,shutdown_witness_operation,fill_transfer_from_savings_operation,hardfork_operation,comment_payout_update_operation,subject_payout_update_operation,return_vesting_delegation_operation,comment_benefactor_reward_operation,producer_reward_operation,vm_operation>
	operation;


struct applied_operation {
	checksum160		trx_id;
	uint32		block;
	uint32		trx_in_block;
	uint16		op_in_trx;
	uint64		virtual_op;
	time_point_sec		timestamp;
	operation		op; 
 
	COSLIB_SERIALIZE( applied_operation, (trx_id)(block)(trx_in_block)(op_in_trx)(virtual_op)(timestamp)(op) ) 
};

struct limit_order_object {
	int64		id;
	time_point_sec		created;
	time_point_sec		expiration;
	namex		seller;
	uint32		orderid;
	int64		for_sale;
	price		sell_price; 
 
	COSLIB_SERIALIZE( limit_order_object, (id)(created)(expiration)(seller)(orderid)(for_sale)(sell_price) ) 
};

using limit_order_api_obj	 = limit_order_object;

struct extended_limit_order : public limit_order_api_obj {
	float64		real_price;
	bool		rewarded; 
 
	COSLIB_SERIALIZE_DERIVED( extended_limit_order, limit_order_api_obj,(real_price)(rewarded) ) 
};

struct extended_account : public account_api_obj {
	asset		vesting_balance;
	int64		reputation;
	map<uint64,applied_operation>		transfer_history;
	map<uint64,applied_operation>		market_history;
	map<uint64,applied_operation>		post_history;
	map<uint64,applied_operation>		vote_history;
	map<uint64,applied_operation>		other_history;
	vector<string>		witness_votes;
	vector<map<string,uint32>>		tags_usage;
	vector<map<namex,uint32>>		guest_bloggers;
	vector<map<uint32,extended_limit_order>>		open_orders;
	vector<vector<string>>		comments;
	vector<vector<string>>		feed;
	vector<vector<string>>		blog;
	vector<vector<string>>		recent_replies;
	vector<vector<string>>		recommended; 
 
	COSLIB_SERIALIZE_DERIVED( extended_account, account_api_obj,(vesting_balance)(reputation)(transfer_history)(market_history)(post_history)(vote_history)(other_history)(witness_votes)(tags_usage)(guest_bloggers)(open_orders)(comments)(feed)(blog)(recent_replies)(recommended) ) 
};

struct witness_api_obj {
	witness_id_type		id;
	namex		owner;
	time_point_sec		created;
	string		url;
	int64		votes;
	uint128		virtual_last_update;
	uint128		virtual_position;
	uint128		virtual_scheduled_time;
	uint32		total_missed;
	uint64		last_aslot;
	uint64		last_confirmed_block_num;
	uint64		pow_worker;
	public_key_type		signing_key;
	chain_properties		props;
	price		sbd_exchange_rate;
	time_point_sec		last_sbd_exchange_update;
	checksum256		last_work;
	version		running_version;
	hardfork_version		hardfork_version_vote;
	time_point_sec		hardfork_time_vote; 
 
	COSLIB_SERIALIZE( witness_api_obj, (id)(owner)(created)(url)(votes)(virtual_last_update)(virtual_position)(virtual_scheduled_time)(total_missed)(last_aslot)(last_confirmed_block_num)(pow_worker)(signing_key)(props)(sbd_exchange_rate)(last_sbd_exchange_update)(last_work)(running_version)(hardfork_version_vote)(hardfork_time_vote) ) 
};

struct witness_schedule_object {
	int64		id;
	uint128		current_virtual_time;
	uint32		next_shuffle_block_num;
	shuffled_witness_array_type		current_shuffled_witnesses;
	uint8		num_scheduled_witnesses;
	uint8		top19_weight;
	uint8		timeshare_weight;
	uint8		miner_weight;
	uint32		witness_pay_normalization_factor;
	chain_properties		median_props;
	version		majority_version;
	uint8		max_voted_witnesses;
	uint8		max_miner_witnesses;
	uint8		max_runner_witnesses;
	uint8		hardfork_required_witnesses; 
 
	COSLIB_SERIALIZE( witness_schedule_object, (id)(current_virtual_time)(next_shuffle_block_num)(current_shuffled_witnesses)(num_scheduled_witnesses)(top19_weight)(timeshare_weight)(miner_weight)(witness_pay_normalization_factor)(median_props)(majority_version)(max_voted_witnesses)(max_miner_witnesses)(max_runner_witnesses)(hardfork_required_witnesses) ) 
};

using witness_schedule_api_obj	 = witness_schedule_object;

struct order_history_item {
	time_point_sec		time;
	string		type;
	asset		sbd_quantity;
	asset		steem_quantity;
	float64		real_price; 
 
	COSLIB_SERIALIZE( order_history_item, (time)(type)(sbd_quantity)(steem_quantity)(real_price) ) 
};

struct candle_stick {
	time_point_sec		open_time;
	uint32		period;
	float64		high;
	float64		low;
	float64		open;
	float64		close;
	float64		steem_volume;
	float64		dollar_volume; 
 
	COSLIB_SERIALIZE( candle_stick, (open_time)(period)(high)(low)(open)(close)(steem_volume)(dollar_volume) ) 
};

struct market {
	vector<extended_limit_order>		bids;
	vector<extended_limit_order>		asks;
	vector<order_history_item>		history;
	vector<candle_stick>		price_history;
	vector<int32>		available_candlesticks;
	vector<int32>		available_zoom;
	int32		current_candlestick;
	int32		current_zoom; 
 
	COSLIB_SERIALIZE( market, (bids)(asks)(history)(price_history)(available_candlesticks)(available_zoom)(current_candlestick)(current_zoom) ) 
};

struct state {
	string		current_route;
	dynamic_global_property_api_obj		props;
	tag_index		tag_idx;
	map<string,tag_api_obj>		tags;
	map<string,discussion>		content;
	map<string,extended_account>		accounts;
	vector<namex>		pow_queue;
	map<string,witness_api_obj>		witnesses;
	map<string,discussion_index>		discussion_idx;
	witness_schedule_api_obj		witness_schedule;
	price		feed_price;
	string		error;
	vector<market>		market_data; 
 
	COSLIB_SERIALIZE( state, (current_route)(props)(tag_idx)(tags)(content)(accounts)(pow_queue)(witnesses)(discussion_idx)(witness_schedule)(feed_price)(error)(market_data) ) 
};

struct transaction {
	uint16		ref_block_num;
	uint32		ref_block_prefix;
	time_point_sec		expiration;
	vector<operation>		operations;
	extensions_type		extensions; 
 
	COSLIB_SERIALIZE( transaction, (ref_block_num)(ref_block_prefix)(expiration)(operations)(extensions) ) 
};

struct signed_transaction : public transaction {
	vector<signature_type>		signatures; 
 
	COSLIB_SERIALIZE_DERIVED( signed_transaction, transaction,(signatures) ) 
};

struct transaction_invoice {
	uint32		status;
	bool		vm_error;
	uint32		vm_error_code;
	uint64		gas_usage; 
 
	COSLIB_SERIALIZE( transaction_invoice, (status)(vm_error)(vm_error_code)(gas_usage) ) 
};

struct transaction_wrapper {
	signed_transaction		sig_trx;
	transaction_invoice		invoice; 
 
	COSLIB_SERIALIZE( transaction_wrapper, (sig_trx)(invoice) ) 
};

struct signed_block : public signed_block_header {
	vector<transaction_wrapper>		transactions; 
 
	COSLIB_SERIALIZE_DERIVED( signed_block, signed_block_header,(transactions) ) 
};

struct signed_block_api_obj : public signed_block {
	checksum160		block_id;
	public_key_type		signing_key;
	vector<checksum160>		transaction_ids; 
 
	COSLIB_SERIALIZE_DERIVED( signed_block_api_obj, signed_block,(block_id)(signing_key)(transaction_ids) ) 
};

//struct feed_history_api_obj {
//    feed_history_id_type        id;
//    price        current_median_history;
//    vector<price>        price_history;
//
//    COSLIB_SERIALIZE( feed_history_api_obj, (id)(current_median_history)(price_history) )
//};

struct scheduled_hardfork {
	hardfork_version		hf_version;
	time_point_sec		live_time; 
 
	COSLIB_SERIALIZE( scheduled_hardfork, (hf_version)(live_time) ) 
};

struct reward_fund_object {
	reward_fund_id_type		id;
	reward_fund_name_type		name;
	asset		reward_balance;
	uint128		recent_claims;
	time_point_sec		last_update;
	uint128		content_constant;
	uint16		percent_curation_rewards;
	uint16		percent_content_rewards;
	int64		author_reward_curve;
	int64		curation_reward_curve; 
 
	COSLIB_SERIALIZE( reward_fund_object, (id)(name)(reward_balance)(recent_claims)(last_update)(content_constant)(percent_curation_rewards)(percent_content_rewards)(author_reward_curve)(curation_reward_curve) ) 
};

using reward_fund_api_obj	 = reward_fund_object;

struct account_code_api_obj {
	namex		name;
	vector<int8>		code;
	vector<int8>		abi; 
 
	COSLIB_SERIALIZE( account_code_api_obj, (name)(code)(abi) ) 
};

struct table_rows_api_obj {
	vector<vector<int8>>		raw_data_rows;
	bool		more; 
 
	COSLIB_SERIALIZE( table_rows_api_obj, (raw_data_rows)(more) ) 
};

struct owner_authority_history_api_obj {
	owner_authority_history_id_type		id;
	namex		account;
	authority		previous_owner_authority;
	time_point_sec		last_valid_time; 
 
	COSLIB_SERIALIZE( owner_authority_history_api_obj, (id)(account)(previous_owner_authority)(last_valid_time) ) 
};

struct account_recovery_request_api_obj {
	account_recovery_request_id_type		id;
	namex		account_to_recover;
	authority		new_owner_authority;
	time_point_sec		expires; 
 
	COSLIB_SERIALIZE( account_recovery_request_api_obj, (id)(account_to_recover)(new_owner_authority)(expires) ) 
};

struct withdraw_route {
	string		from_account;
	string		to_account;
	uint16		percent;
	bool		auto_vest; 
 
	COSLIB_SERIALIZE( withdraw_route, (from_account)(to_account)(percent)(auto_vest) ) 
};

struct account_bandwidth_object {
	int64		id;
	namex		account;
	int64		type;
	int64		average_bandwidth;
	int64		lifetime_bandwidth;
	time_point_sec		last_bandwidth_update; 
 
	COSLIB_SERIALIZE( account_bandwidth_object, (id)(account)(type)(average_bandwidth)(lifetime_bandwidth)(last_bandwidth_update) ) 
};

using account_bandwidth_api_obj	 = account_bandwidth_object;

struct savings_withdraw_api_obj {
	savings_withdraw_id_type		id;
	namex		from;
	namex		to;
	string		memo;
	uint32		request_id;
	asset		amount;
	time_point_sec		complete; 
 
	COSLIB_SERIALIZE( savings_withdraw_api_obj, (id)(from)(to)(memo)(request_id)(amount)(complete) ) 
};

struct vesting_delegation_object {
	int64		id;
	namex		delegator;
	namex		delegatee;
	asset		vesting_shares;
	time_point_sec		min_delegation_time; 
 
	COSLIB_SERIALIZE( vesting_delegation_object, (id)(delegator)(delegatee)(vesting_shares)(min_delegation_time) ) 
};

using vesting_delegation_api_obj	 = vesting_delegation_object;

struct vesting_delegation_expiration_object {
	int64		id;
	namex		delegator;
	asset		vesting_shares;
	time_point_sec		expiration; 
 
	COSLIB_SERIALIZE( vesting_delegation_expiration_object, (id)(delegator)(vesting_shares)(expiration) ) 
};

using vesting_delegation_expiration_api_obj	 = vesting_delegation_expiration_object;

struct convert_request_object {
	int64		id;
	namex		owner;
	uint32		requestid;
	asset		amount;
	time_point_sec		conversion_date; 
 
	COSLIB_SERIALIZE( convert_request_object, (id)(owner)(requestid)(amount)(conversion_date) ) 
};

using convert_request_api_obj	 = convert_request_object;

struct annotated_signed_transaction {
	signed_transaction		sig_trx;
	transaction_invoice		invoice;
	checksum160		transaction_id;
	uint32		block_num;
	uint32		transaction_num; 
 
	COSLIB_SERIALIZE( annotated_signed_transaction, (sig_trx)(invoice)(transaction_id)(block_num)(transaction_num) ) 
};

struct account_vote {
	string		authorperm;
	uint64		weight;
	int64		rshares;
	int16		percent;
	time_point_sec		time; 
 
	COSLIB_SERIALIZE( account_vote, (authorperm)(weight)(rshares)(percent)(time) ) 
};

struct discussion_query {
	string		tag;
	vector<string>		filter_tags;
	vector<string>		select_tags;
	vector<string>		select_authors;
	uint32		truncate_body;
	vector<string>		start_author;
	vector<string>		start_permlink;
	vector<string>		parent_author;
	vector<string>		parent_permlink;
	uint32		limit; 
 
	COSLIB_SERIALIZE( discussion_query, (tag)(filter_tags)(select_tags)(select_authors)(truncate_body)(start_author)(start_permlink)(parent_author)(parent_permlink)(limit) ) 
};


class follow_api {
public:

	std::string api_name()const{ return std::string("follow_api"); }

	vector<follow_api_obj> get_followers( const string& to, const string& start, const int64& type, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_followers), << to << start << type << limit);
	}

	vector<follow_api_obj> get_following( const string& from, const string& start, const int64& type, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_following), << from << start << type << limit);
	}

	follow_count_api_obj get_follow_count( const string& account) {
		STUB_API( RET_TYPE(follow_api::get_follow_count), << account);
	}

	vector<feed_entry> get_feed_entries( const string& account, const uint32& entry_id, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_feed_entries), << account << entry_id << limit);
	}

	vector<comment_feed_entry> get_feed( const string& account, const uint32& entry_id, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_feed), << account << entry_id << limit);
	}

	vector<blog_entry> get_blog_entries( const string& account, const uint32& entry_id, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_blog_entries), << account << entry_id << limit);
	}

	vector<comment_blog_entry> get_blog( const string& account, const uint32& entry_id, const uint16& limit) {
		STUB_API( RET_TYPE(follow_api::get_blog), << account << entry_id << limit);
	}

	vector<account_reputation> get_account_reputations( const string& lower_bound_name, const uint32& limit) {
		STUB_API( RET_TYPE(follow_api::get_account_reputations), << lower_bound_name << limit);
	}

	vector<namex> get_reblogged_by( const string& author, const string& permlink) {
		STUB_API( RET_TYPE(follow_api::get_reblogged_by), << author << permlink);
	}

	vector<map<namex,uint32>> get_blog_authors( const namex& blog_account) {
		STUB_API( RET_TYPE(follow_api::get_blog_authors), << blog_account);
	}

};

class database_api {
public:

	std::string api_name()const{ return std::string("database_api"); }

	vector<tag_api_obj> get_trending_tags( const string& after_tag, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_trending_tags), << after_tag << limit);
	}

	state get_state( const string& path) {
		STUB_API( RET_TYPE(database_api::get_state), << path);
	}

	vector<namex> get_active_witnesses() {
		STUB_API( RET_TYPE(database_api::get_active_witnesses),);
	}

	vector<namex> get_miner_queue() {
		STUB_API( RET_TYPE(database_api::get_miner_queue),);
	}

	vector<block_header> get_block_header( const uint32& block_num) {
		STUB_API( RET_TYPE(database_api::get_block_header), << block_num);
	}

	vector<signed_block_api_obj> get_block( const uint32& block_num) {
		STUB_API( RET_TYPE(database_api::get_block), << block_num);
	}

	vector<applied_operation> get_ops_in_block( const uint32& block_num, const bool& only_virtual) {
		STUB_API( RET_TYPE(database_api::get_ops_in_block), << block_num << only_virtual);
	}

	variant_object get_config() {
		STUB_API( RET_TYPE(database_api::get_config),);
	}

	dynamic_global_property_api_obj get_dynamic_global_properties() {
		STUB_API( RET_TYPE(database_api::get_dynamic_global_properties),);
	}

	chain_properties get_chain_properties() {
		STUB_API( RET_TYPE(database_api::get_chain_properties),);
	}

	price get_current_median_history_price() {
		STUB_API( RET_TYPE(database_api::get_current_median_history_price),);
	}

//    feed_history_api_obj get_feed_history() {
//        STUB_API( RET_TYPE(database_api::get_feed_history),);
//    }

	witness_schedule_api_obj get_witness_schedule() {
		STUB_API( RET_TYPE(database_api::get_witness_schedule),);
	}

	hardfork_version get_hardfork_version() {
		STUB_API( RET_TYPE(database_api::get_hardfork_version),);
	}

	scheduled_hardfork get_next_scheduled_hardfork() {
		STUB_API( RET_TYPE(database_api::get_next_scheduled_hardfork),);
	}

	reward_fund_api_obj get_reward_fund( const string& name) {
		STUB_API( RET_TYPE(database_api::get_reward_fund), << name);
	}

	vector<vector<string>> get_key_references( const vector<public_key_type>& key) {
		STUB_API( RET_TYPE(database_api::get_key_references), << key);
	}

	asset get_contract_balance( const string& name) {
		STUB_API( RET_TYPE(database_api::get_contract_balance), << name);
	}

	vector<extended_account> get_accounts( const vector<string>& names) {
		STUB_API( RET_TYPE(database_api::get_accounts), << names);
	}

	account_code_api_obj get_account_code( const string& name) {
		STUB_API( RET_TYPE(database_api::get_account_code), << name);
	}

	table_rows_api_obj get_table_rows( const string& code, const string& scope, const string& table, const string& lower_bound, const string& upper_bound, const int32& limit, const string& key_type, const string& index_pos, const string& encode_type) {
		STUB_API( RET_TYPE(database_api::get_table_rows), << code << scope << table << lower_bound << upper_bound << limit << key_type << index_pos << encode_type);
	}

	vector<account_id_type> get_account_references( const account_id_type& account_id) {
		STUB_API( RET_TYPE(database_api::get_account_references), << account_id);
	}

	vector<vector<account_api_obj>> lookup_account_names( const vector<string>& account_names) {
		STUB_API( RET_TYPE(database_api::lookup_account_names), << account_names);
	}

	vector<string> lookup_accounts( const string& lower_bound_name, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::lookup_accounts), << lower_bound_name << limit);
	}

	uint64 get_account_count() {
		STUB_API( RET_TYPE(database_api::get_account_count),);
	}

	vector<owner_authority_history_api_obj> get_owner_history( const string& account) {
		STUB_API( RET_TYPE(database_api::get_owner_history), << account);
	}

	vector<account_recovery_request_api_obj> get_recovery_request( const string& account) {
		STUB_API( RET_TYPE(database_api::get_recovery_request), << account);
	}

	vector<withdraw_route> get_withdraw_routes( const string& account, const int64& type) {
		STUB_API( RET_TYPE(database_api::get_withdraw_routes), << account << type);
	}

	vector<account_bandwidth_api_obj> get_account_bandwidth( const string& account, const int64& type) {
		STUB_API( RET_TYPE(database_api::get_account_bandwidth), << account << type);
	}

	vector<savings_withdraw_api_obj> get_savings_withdraw_from( const string& account) {
		STUB_API( RET_TYPE(database_api::get_savings_withdraw_from), << account);
	}

	vector<savings_withdraw_api_obj> get_savings_withdraw_to( const string& account) {
		STUB_API( RET_TYPE(database_api::get_savings_withdraw_to), << account);
	}

	vector<vesting_delegation_api_obj> get_vesting_delegations( const string& account, const string& from, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_vesting_delegations), << account << from << limit);
	}

	vector<vesting_delegation_expiration_api_obj> get_expiring_vesting_delegations( const string& account, const time_point_sec& from, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_expiring_vesting_delegations), << account << from << limit);
	}

	vector<vector<witness_api_obj>> get_witnesses( const vector<witness_id_type>& witness_ids) {
		STUB_API( RET_TYPE(database_api::get_witnesses), << witness_ids);
	}

	vector<convert_request_api_obj> get_conversion_requests( const string& account_name) {
		STUB_API( RET_TYPE(database_api::get_conversion_requests), << account_name);
	}

	vector<witness_api_obj> get_witness_by_account( const string& account_name) {
		STUB_API( RET_TYPE(database_api::get_witness_by_account), << account_name);
	}

	vector<witness_api_obj> get_witnesses_by_vote( const string& from, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_witnesses_by_vote), << from << limit);
	}

	vector<namex> lookup_witness_accounts( const string& lower_bound_name, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::lookup_witness_accounts), << lower_bound_name << limit);
	}

	uint64 get_witness_count() {
		STUB_API( RET_TYPE(database_api::get_witness_count),);
	}

	string get_transaction_hex( const signed_transaction& trx) {
		STUB_API( RET_TYPE(database_api::get_transaction_hex), << trx);
	}

	annotated_signed_transaction get_transaction( const checksum160& trx_id) {
		STUB_API( RET_TYPE(database_api::get_transaction), << trx_id);
	}

	vector<public_key_type> get_required_signatures( const signed_transaction& trx, const vector<public_key_type>& available_keys) {
		STUB_API( RET_TYPE(database_api::get_required_signatures), << trx << available_keys);
	}

	vector<public_key_type> get_potential_signatures( const signed_transaction& trx) {
		STUB_API( RET_TYPE(database_api::get_potential_signatures), << trx);
	}

	bool verify_authority( const signed_transaction& trx) {
		STUB_API( RET_TYPE(database_api::verify_authority), << trx);
	}

	bool verify_account_authority( const string& name_or_id, const vector<public_key_type>& signers) {
		STUB_API( RET_TYPE(database_api::verify_account_authority), << name_or_id << signers);
	}

	vector<vote_state> get_active_votes( const string& author, const string& permlink) {
		STUB_API( RET_TYPE(database_api::get_active_votes), << author << permlink);
	}

	vector<account_vote> get_account_votes( const string& voter) {
		STUB_API( RET_TYPE(database_api::get_account_votes), << voter);
	}

	discussion get_content( const string& author, const string& permlink) {
		STUB_API( RET_TYPE(database_api::get_content), << author << permlink);
	}

	vector<discussion> get_content_replies( const string& parent, const string& parent_permlink) {
		STUB_API( RET_TYPE(database_api::get_content_replies), << parent << parent_permlink);
	}

	vector<map<string,uint32>> get_tags_used_by_author( const string& author) {
		STUB_API( RET_TYPE(database_api::get_tags_used_by_author), << author);
	}

	vector<discussion> get_discussions_by_payout( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_payout), << query);
	}

	vector<discussion> get_post_discussions_by_payout( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_post_discussions_by_payout), << query);
	}

	vector<discussion> get_comment_discussions_by_payout( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_comment_discussions_by_payout), << query);
	}

	vector<discussion> get_discussions_by_trending( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_trending), << query);
	}

	vector<discussion> get_discussions_by_created( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_created), << query);
	}

	vector<discussion> get_discussions_by_active( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_active), << query);
	}

	vector<discussion> get_discussions_by_cashout( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_cashout), << query);
	}

	vector<discussion> get_discussions_by_votes( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_votes), << query);
	}

	vector<discussion> get_discussions_by_children( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_children), << query);
	}

	vector<discussion> get_discussions_by_hot( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_hot), << query);
	}

	vector<discussion> get_discussions_by_feed( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_feed), << query);
	}

	vector<discussion> get_discussions_by_blog( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_blog), << query);
	}

	vector<discussion> get_discussions_by_comments( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_comments), << query);
	}

	vector<discussion> get_discussions_by_promoted( const discussion_query& query) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_promoted), << query);
	}

	vector<discussion> get_replies_by_last_update( const namex& start_author, const string& start_permlink, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_replies_by_last_update), << start_author << start_permlink << limit);
	}

	vector<discussion> get_discussions_by_author_before_date( const string& author, const string& start_permlink, const time_point_sec& before_date, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_discussions_by_author_before_date), << author << start_permlink << before_date << limit);
	}

	map<uint32,applied_operation> get_account_history( const string& account, const uint64& from, const uint32& limit) {
		STUB_API( RET_TYPE(database_api::get_account_history), << account << from << limit);
	}

};


}

