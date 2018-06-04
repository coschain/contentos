/*
 * Copyright (c) 2016 Steemit, Inc., and contributors.
 */
#pragma once

#define CONTENTO_BLOCKCHAIN_VERSION              ( version(0, 19, 2) )
#define CONTENTO_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( CONTENTO_BLOCKCHAIN_VERSION ) )

#ifdef IS_TEST_NET
#define CONTENTO_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define CONTENTO_INIT_PUBLIC_KEY_STR             (std::string( contento::protocol::public_key_type(CONTENTO_INIT_PRIVATE_KEY.get_public_key()) ))
#define CONTENTO_CHAIN_ID                        (fc::sha256::hash("testnet"))

#define VESTS_SYMBOL  (uint64_t(4) | (uint64_t('C') << 8) | (uint64_t('O') << 16) | (uint64_t('V') << 24))
#define COC_SYMBOL (uint64_t(4) | (uint64_t('C') << 8) | (uint64_t('O') << 16) | (uint64_t('C') << 24))
#define SBD_SYMBOL    (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('B') << 16) | (uint64_t('D') << 24) ) ///< Test Backed Dollars with 3 digits of precision
#define STMD_SYMBOL   (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('S') << 16) | (uint64_t('T') << 24) | (uint64_t('D') << 32) ) ///< Test Dollars with 3 digits of precision

#define CONTENTO_SYMBOL                          "TEST"
#define CONTENTO_ADDRESS_PREFIX                  "TST"

#define CONTENTO_ASA

#define CONTENTO_GENESIS_TIME                    (fc::time_point_sec(1451606400))
#define CONTENTO_MINING_TIME                     (fc::time_point_sec(1451606400))
#define CONTENTO_CASHOUT_WINDOW_SECONDS          (60*60) /// 1 hr
#define CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF12 (CONTENTO_CASHOUT_WINDOW_SECONDS)
#define CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF17 (CONTENTO_CASHOUT_WINDOW_SECONDS)
#define CONTENTO_SECOND_CASHOUT_WINDOW           (60*60*24*3) /// 3 days
#define CONTENTO_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24) /// 1 day
#define CONTENTO_VOTE_CHANGE_LOCKOUT_PERIOD      (60*10) /// 10 minutes
#define CONTENTO_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define CONTENTO_UPVOTE_LOCKOUT_HF17             (fc::minutes(5))


#define CONTENTO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE 0
#define CONTENTO_MIN_ACCOUNT_CREATION_FEE          0

#define CONTENTO_OWNER_AUTH_RECOVERY_PERIOD                  fc::seconds(60)
#define CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::seconds(12)
#define CONTENTO_OWNER_UPDATE_LIMIT                          fc::seconds(0)
#define CONTENTO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1

#define CONTENTO_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(0)) // no limit for TEST_NET
#define CONTENTO_MIN_REPLY_INTERVAL              (fc::seconds(0)) // no limit for TEST_NET

#define CONTENTO_INIT_SUPPLY                     int64_t(1000000000)  // 1 billion

#else // IS LIVE STEEM NETWORK

//#define CONTENTO_INIT_PUBLIC_KEY_STR             "STM8GC13uCZbP44HzMLV6zPZGwVQ8Nt4Kji8PapsPiNq1BK153XTX"
#define CONTENTO_ONLINE_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("contento"))))
#define CONTENTO_INIT_PUBLIC_KEY_STR             (std::string( contento::protocol::public_key_type(CONTENTO_ONLINE_INIT_PRIVATE_KEY.get_public_key()) ))
#define CONTENTO_CHAIN_ID                        (contento::protocol::chain_id_type())
#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define COC_SYMBOL  (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('T') << 16) | (uint64_t('E') << 24) | (uint64_t('E') << 32) | (uint64_t('M') << 40)) ///< STEEM with 3 digits of precision
#define SBD_SYMBOL    (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('B') << 16) | (uint64_t('D') << 24) ) ///< STEEM Backed Dollars with 3 digits of precision
#define STMD_SYMBOL   (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('T') << 16) | (uint64_t('M') << 24) | (uint64_t('D') << 32) ) ///< STEEM Dollars with 3 digits of precision
#define CONTENTO_SYMBOL                          "STEEM"
#define CONTENTO_ADDRESS_PREFIX                  "STM"

#define CONTENTO_GENESIS_TIME                    (fc::time_point_sec(1458835200))
#define CONTENTO_MINING_TIME                     (fc::time_point_sec(1458838800))
#define CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF12 (60*60*24)    /// 1 day
#define CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF17 (60*60*12)    /// 12 hours
#define CONTENTO_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
#define CONTENTO_SECOND_CASHOUT_WINDOW           (60*60*24*30) /// 30 days
#define CONTENTO_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24*14) /// 2 weeks
#define CONTENTO_VOTE_CHANGE_LOCKOUT_PERIOD      (60*60*2)     /// 2 hours
#define CONTENTO_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define CONTENTO_UPVOTE_LOCKOUT_HF17             (fc::hours(12))

#define CONTENTO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE  100000
#define CONTENTO_MIN_ACCOUNT_CREATION_FEE           1

#define CONTENTO_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
#define CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
#define CONTENTO_OWNER_UPDATE_LIMIT                          fc::minutes(60)
#define CONTENTO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 3186477

#define CONTENTO_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(60*5)) // 5 minutes
#define CONTENTO_MIN_REPLY_INTERVAL              (fc::seconds(20)) // 20 seconds

#define CONTENTO_INIT_SUPPLY                     int64_t(0)

#endif

#define CONTENTO_BLOCK_INTERVAL                  3
#define CONTENTO_BLOCKS_PER_YEAR                 (365*24*60*60/CONTENTO_BLOCK_INTERVAL)
#define CONTENTO_BLOCKS_PER_DAY                  (24*60*60/CONTENTO_BLOCK_INTERVAL)
#define CONTENTO_START_VESTING_BLOCK             (CONTENTO_BLOCKS_PER_DAY * 7)
#define CONTENTO_START_MINER_VOTING_BLOCK        (CONTENTO_BLOCKS_PER_DAY * 30)

#define CONTENTO_INIT_MINER_NAME                 "initminer"
#define CONTENTO_NUM_INIT_MINERS                 1
#define CONTENTO_INIT_TIME                       (fc::time_point_sec());

#define CONTENTO_MAX_WITNESSES                   21

#define CONTENTO_MAX_VOTED_WITNESSES_HF0         19
#define CONTENTO_MAX_MINER_WITNESSES_HF0         1
#define CONTENTO_MAX_RUNNER_WITNESSES_HF0        1

#define CONTENTO_MAX_VOTED_WITNESSES_HF17        20
#define CONTENTO_MAX_MINER_WITNESSES_HF17        0
#define CONTENTO_MAX_RUNNER_WITNESSES_HF17       1

#define CONTENTO_HARDFORK_REQUIRED_WITNESSES     0 // 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.
#define CONTENTO_MAX_TIME_UNTIL_EXPIRATION       (60*60) // seconds,  aka: 1 hour
#define CONTENTO_MAX_MEMO_SIZE                   2048
#define CONTENTO_MAX_PROXY_RECURSION_DEPTH       4
#define CONTENTO_VESTING_WITHDRAW_INTERVALS_PRE_HF_16 104
#define CONTENTO_VESTING_WITHDRAW_INTERVALS      13
#define CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS (60*60*24*7) /// 1 week per interval
#define CONTENTO_MAX_WITHDRAW_ROUTES             10
#define CONTENTO_SAVINGS_WITHDRAW_TIME        	(fc::days(3))
#define CONTENTO_SAVINGS_WITHDRAW_REQUEST_LIMIT  100
#define CONTENTO_VOTE_REGENERATION_SECONDS       (5*60*60*24) // 5 day
#define CONTENTO_MAX_VOTE_CHANGES                5
#define CONTENTO_REVERSE_AUCTION_WINDOW_SECONDS  (60*30) /// 30 minutes
#define CONTENTO_MIN_VOTE_INTERVAL_SEC           3
#define CONTENTO_VOTE_DUST_THRESHOLD             (50000000)

#define CONTENTO_POST_AVERAGE_WINDOW             (60*60*24u) // 1 day
#define CONTENTO_POST_MAX_BANDWIDTH              (4*CONTENTO_100_PERCENT) // 2 posts per 1 days, average 1 every 12 hours
#define CONTENTO_POST_WEIGHT_CONSTANT            (uint64_t(CONTENTO_POST_MAX_BANDWIDTH) * CONTENTO_POST_MAX_BANDWIDTH)

#define CONTENTO_MAX_ACCOUNT_WITNESS_VOTES       30

#define CONTENTO_100_PERCENT                     10000
#define CONTENTO_1_PERCENT                       (CONTENTO_100_PERCENT/100)
#define CONTENTO_1_TENTH_PERCENT                 (CONTENTO_100_PERCENT/1000)
#define CONTENTO_DEFAULT_SBD_INTEREST_RATE       (10*CONTENTO_1_PERCENT) ///< 10% APR

#define CONTENTO_CREATOR_REWARD_PERCENT          (70*CONTENTO_1_PERCENT)
#define CONTENTO_COMMENTER_REWARD_PERCENT        (15*CONTENTO_1_PERCENT)
#define CONTENTO_OTHER_REWARD_PERCENT            (5*CONTENTO_1_PERCENT)

#define CONTENTO_INFLATION_RATE_START_PERCENT    (978) // Fixes block 7,000,000 to 9.5%
#define CONTENTO_INFLATION_RATE_STOP_PERCENT     (95) // 0.95%
#define CONTENTO_INFLATION_NARROWING_PERIOD      (250000) // Narrow 0.01% every 250k blocks
#define CONTENTO_CONTENT_REWARD_PERCENT          (75*CONTENTO_1_PERCENT) //75% of inflation, 7.125% inflation
#define CONTENTO_VESTING_FUND_PERCENT            (15*CONTENTO_1_PERCENT) //15% of inflation, 1.425% inflation

#define CONTENTO_MINER_PAY_PERCENT               (CONTENTO_1_PERCENT) // 1%
#define CONTENTO_MIN_RATION                      100000
#define CONTENTO_MAX_RATION_DECAY_RATE           (1000000)
#define CONTENTO_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT 100

#define CONTENTO_BANDWIDTH_AVERAGE_WINDOW_SECONDS (60*60*24*7) ///< 1 week
#define CONTENTO_BANDWIDTH_PRECISION             (uint64_t(1000000)) ///< 1 million
#define CONTENTO_MAX_COMMENT_DEPTH_PRE_HF17      6
#define CONTENTO_MAX_COMMENT_DEPTH               0xffff // 64k
#define CONTENTO_SOFT_MAX_COMMENT_DEPTH          0xff // 255

#define CONTENTO_MAX_RESERVE_RATIO               (20000)

#define CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER 30
#define CONTENTO_CREATE_ACCOUNT_DELEGATION_RATIO    5
#define CONTENTO_CREATE_ACCOUNT_DELEGATION_TIME     fc::days(30)

#define CONTENTO_MINING_REWARD                   asset( 1000, COC_SYMBOL )
#define CONTENTO_EQUIHASH_N                      140
#define CONTENTO_EQUIHASH_K                      6

#define CONTENTO_LIQUIDITY_TIMEOUT_SEC           (fc::seconds(60*60*24*7)) // After one week volume is set to 0
#define CONTENTO_MIN_LIQUIDITY_REWARD_PERIOD_SEC (fc::seconds(60)) // 1 minute required on books to receive volume
#define CONTENTO_LIQUIDITY_REWARD_PERIOD_SEC     (60*60)
#define CONTENTO_LIQUIDITY_REWARD_BLOCKS         (CONTENTO_LIQUIDITY_REWARD_PERIOD_SEC/CONTENTO_BLOCK_INTERVAL)
#define CONTENTO_MIN_LIQUIDITY_REWARD            (asset( 1000*CONTENTO_LIQUIDITY_REWARD_BLOCKS, COC_SYMBOL )) // Minumum reward to be paid out to liquidity providers
#define CONTENTO_MIN_CONTENT_REWARD              CONTENTO_MINING_REWARD
#define CONTENTO_MIN_CURATE_REWARD               CONTENTO_MINING_REWARD
#define CONTENTO_MIN_PRODUCER_REWARD             CONTENTO_MINING_REWARD
#define CONTENTO_MIN_POW_REWARD                  CONTENTO_MINING_REWARD

#define CONTENTO_ACTIVE_CHALLENGE_FEE            asset( 2000, COC_SYMBOL )
#define CONTENTO_OWNER_CHALLENGE_FEE             asset( 30000, COC_SYMBOL )
#define CONTENTO_ACTIVE_CHALLENGE_COOLDOWN       fc::days(1)
#define CONTENTO_OWNER_CHALLENGE_COOLDOWN        fc::days(1)

#define CONTENTO_POST_REWARD_FUND_NAME           ("post")
#define CONTENTO_COMMENT_REWARD_FUND_NAME        ("comment")
#define CONTENTO_RECENT_RSHARES_DECAY_RATE_HF17  (fc::days(30))
#define CONTENTO_RECENT_RSHARES_DECAY_RATE_HF19  (fc::days(15))
#define CONTENTO_CONTENT_CONSTANT_HF0            (uint128_t(uint64_t(2000000000000ll)))
// note, if redefining these constants make sure calculate_claims doesn't overflow

// 5ccc e802 de5f
// int(expm1( log1p( 1 ) / BLOCKS_PER_YEAR ) * 2**CONTENTO_APR_PERCENT_SHIFT_PER_BLOCK / 100000 + 0.5)
// we use 100000 here instead of 10000 because we end up creating an additional 9x for vesting
#define CONTENTO_APR_PERCENT_MULTIPLY_PER_BLOCK          ( (uint64_t( 0x5ccc ) << 0x20) \
                                                        | (uint64_t( 0xe802 ) << 0x10) \
                                                        | (uint64_t( 0xde5f )        ) \
                                                        )
// chosen to be the maximal value such that CONTENTO_APR_PERCENT_MULTIPLY_PER_BLOCK * 2**64 * 100000 < 2**128
#define CONTENTO_APR_PERCENT_SHIFT_PER_BLOCK             87

#define CONTENTO_APR_PERCENT_MULTIPLY_PER_ROUND          ( (uint64_t( 0x79cc ) << 0x20 ) \
                                                        | (uint64_t( 0xf5c7 ) << 0x10 ) \
                                                        | (uint64_t( 0x3480 )         ) \
                                                        )

#define CONTENTO_APR_PERCENT_SHIFT_PER_ROUND             83

// We have different constants for hourly rewards
// i.e. hex(int(math.expm1( math.log1p( 1 ) / HOURS_PER_YEAR ) * 2**CONTENTO_APR_PERCENT_SHIFT_PER_HOUR / 100000 + 0.5))
#define CONTENTO_APR_PERCENT_MULTIPLY_PER_HOUR           ( (uint64_t( 0x6cc1 ) << 0x20) \
                                                        | (uint64_t( 0x39a1 ) << 0x10) \
                                                        | (uint64_t( 0x5cbd )        ) \
                                                        )

// chosen to be the maximal value such that CONTENTO_APR_PERCENT_MULTIPLY_PER_HOUR * 2**64 * 100000 < 2**128
#define CONTENTO_APR_PERCENT_SHIFT_PER_HOUR              77

// These constants add up to GRAPHENE_100_PERCENT.  Each GRAPHENE_1_PERCENT is equivalent to 1% per year APY
// *including the corresponding 9x vesting rewards*
#define CONTENTO_CURATE_APR_PERCENT              3875
#define CONTENTO_CONTENT_APR_PERCENT             3875
#define CONTENTO_LIQUIDITY_APR_PERCENT            750
#define CONTENTO_PRODUCER_APR_PERCENT             750
#define CONTENTO_POW_APR_PERCENT                  750

#define CONTENTO_MIN_PAYOUT_SBD                  (asset(20,SBD_SYMBOL))

#define CONTENTO_SBD_STOP_PERCENT                (5*CONTENTO_1_PERCENT ) // Stop printing SBD at 5% Market Cap
#define CONTENTO_SBD_START_PERCENT               (2*CONTENTO_1_PERCENT) // Start reducing printing of SBD at 2% Market Cap

#define CONTENTO_MIN_ACCOUNT_NAME_LENGTH          3
#define CONTENTO_MAX_ACCOUNT_NAME_LENGTH         16

#define CONTENTO_MIN_PERMLINK_LENGTH             0
#define CONTENTO_MAX_PERMLINK_LENGTH             256
#define CONTENTO_MAX_WITNESS_URL_LENGTH          2048

#define CONTENTO_MAX_SHARE_SUPPLY                int64_t(1000000000000000ll)
#define CONTENTO_MAX_SIG_CHECK_DEPTH             2

#define CONTENTO_MIN_TRANSACTION_SIZE_LIMIT      1024
#define CONTENTO_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define CONTENTO_SBD_INTEREST_COMPOUND_INTERVAL_SEC  (60*60*24*30)
#define CONTENTO_MAX_TRANSACTION_SIZE            (1024*64)
#define CONTENTO_MIN_BLOCK_SIZE_LIMIT            (CONTENTO_MAX_TRANSACTION_SIZE)
#define CONTENTO_MAX_BLOCK_SIZE                  (CONTENTO_MAX_TRANSACTION_SIZE*CONTENTO_BLOCK_INTERVAL*2000)
#define CONTENTO_MIN_BLOCK_SIZE                  115
#define CONTENTO_BLOCKS_PER_HOUR                 (60*60/CONTENTO_BLOCK_INTERVAL)
#define CONTENTO_FEED_INTERVAL_BLOCKS            (CONTENTO_BLOCKS_PER_HOUR)
#define CONTENTO_FEED_HISTORY_WINDOW_PRE_HF_16   (24*7) /// 7 days * 24 hours per day
#define CONTENTO_FEED_HISTORY_WINDOW             (12*7) // 3.5 days
#define CONTENTO_MAX_FEED_AGE_SECONDS            (60*60*24*7) // 7 days
#define CONTENTO_MIN_FEEDS                       (CONTENTO_MAX_WITNESSES/3) /// protects the network from conversions before price has been established
#define CONTENTO_CONVERSION_DELAY_PRE_HF_16      (fc::days(7))
#define CONTENTO_CONVERSION_DELAY                (fc::hours(CONTENTO_FEED_HISTORY_WINDOW)) //3.5 day conversion

#define CONTENTO_MIN_UNDO_HISTORY                10
#define CONTENTO_MAX_UNDO_HISTORY                10000

#define CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT (CONTENTO_BLOCK_INTERVAL * 5) // 5 transactions per block
#define CONTENTO_BLOCKCHAIN_PRECISION            uint64_t( 1000 )

#define CONTENTO_BLOCKCHAIN_PRECISION_DIGITS     3
#define CONTENTO_MAX_INSTANCE_ID                 (uint64_t(-1)>>16)
/** NOTE: making this a power of 2 (say 2^15) would greatly accelerate fee calcs */
#define CONTENTO_MAX_AUTHORITY_MEMBERSHIP        10
#define CONTENTO_MAX_ASSET_WHITELIST_AUTHORITIES 10
#define CONTENTO_MAX_URL_LENGTH                  127

#define CONTENTO_IRREVERSIBLE_THRESHOLD          (75 * CONTENTO_1_PERCENT)

#define VIRTUAL_SCHEDULE_LAP_LENGTH  ( fc::uint128(uint64_t(-1)) )
#define VIRTUAL_SCHEDULE_LAP_LENGTH2 ( fc::uint128::max_value() )

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define CONTENTO_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define CONTENTO_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define CONTENTO_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define CONTENTO_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define CONTENTO_ROOT_POST_PARENT                (account_name_type())
///@}
