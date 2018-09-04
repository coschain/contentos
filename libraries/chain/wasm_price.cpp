#include "wasm_price.hpp"

#define WASM_PRICE_FN_CONST_IMPL(PRICE)                 { return (uint64_t)(PRICE); }
#define WASM_PRICE_FN_CONST(NAME, SIG, PRICE)           WASM_PRICE_FN_DECL(NAME, SIG) WASM_PRICE_FN_CONST_IMPL(PRICE)

#define _WASM_PRICE_FN_INFO_NAME(NAME, SIG)             NAME
#define _WASM_PRICE_FN_INFO_SIG(NAME, SIG)              SIG
#define _WASM_PRICE_FN_CONST(R, PREFIX, INFO)           WASM_PRICE_FN_CONST(_WASM_PRICE_FN_INFO_NAME INFO, _WASM_PRICE_FN_INFO_SIG INFO, BOOST_PP_CAT(PREFIX, _WASM_PRICE_FN_INFO_NAME INFO))
#define WASM_PRICE_FN_CONSTS(SEQ)                       BOOST_PP_SEQ_FOR_EACH(_WASM_PRICE_FN_CONST, WASM_PRICE_FN_, WASM_PRICE_FN_WRAP_SEQ(SEQ))

//
// constant prices for intrinsic functions
//


// call_depth_api
#define WASM_PRICE_FN_call_depth_assert                                      WASM_PRICE_UNEXPECTED

// compiler_builtins
#define WASM_PRICE_FN___addtf3                                               40
#define WASM_PRICE_FN___ashlti3                                              34
#define WASM_PRICE_FN___ashrti3                                              29
#define WASM_PRICE_FN___cmptf2                                               18
#define WASM_PRICE_FN___divtf3                                               48
#define WASM_PRICE_FN___divti3                                               48
#define WASM_PRICE_FN___eqtf2                                                28
#define WASM_PRICE_FN___extenddftf2                                          27
#define WASM_PRICE_FN___extendsftf2                                          28
#define WASM_PRICE_FN___fixdfti                                              22
#define WASM_PRICE_FN___fixsfti                                              23
#define WASM_PRICE_FN___fixtfdi                                              25
#define WASM_PRICE_FN___fixtfsi                                              22
#define WASM_PRICE_FN___fixtfti                                              28
#define WASM_PRICE_FN___fixunsdfti                                           26
#define WASM_PRICE_FN___fixunssfti                                           28
#define WASM_PRICE_FN___fixunstfdi                                           26
#define WASM_PRICE_FN___fixunstfsi                                           22
#define WASM_PRICE_FN___fixunstfti                                           24
#define WASM_PRICE_FN___floatditf                                            26
#define WASM_PRICE_FN___floatsidf                                            17
#define WASM_PRICE_FN___floatsitf                                            23
#define WASM_PRICE_FN___floattidf                                            26
#define WASM_PRICE_FN___floatunditf                                          28
#define WASM_PRICE_FN___floatunsitf                                          30
#define WASM_PRICE_FN___floatuntidf                                          22
#define WASM_PRICE_FN___getf2                                                26
#define WASM_PRICE_FN___gttf2                                                20
#define WASM_PRICE_FN___letf2                                                18
#define WASM_PRICE_FN___lshlti3                                              27
#define WASM_PRICE_FN___lshrti3                                              29
#define WASM_PRICE_FN___lttf2                                                24
#define WASM_PRICE_FN___modti3                                               40
#define WASM_PRICE_FN___multf3                                               49
#define WASM_PRICE_FN___multi3                                               26
#define WASM_PRICE_FN___negtf2                                               23
#define WASM_PRICE_FN___netf2                                                24
#define WASM_PRICE_FN___subtf3                                               47
#define WASM_PRICE_FN___trunctfdf2                                           29
#define WASM_PRICE_FN___trunctfsf2                                           27
#define WASM_PRICE_FN___udivti3                                              36
#define WASM_PRICE_FN___umodti3                                              35
#define WASM_PRICE_FN___unordtf2                                             21

// privileged_api
// only privileged accounts can access these functions. set prices to a minimal 1.
#define WASM_PRICE_FN_is_feature_active                                      1
#define WASM_PRICE_FN_activate_feature                                       1
// #define WASM_PRICE_FN_get_resource_limits                                    1
// #define WASM_PRICE_FN_set_resource_limits                                    1
// #define WASM_PRICE_FN_set_proposed_producers                                 1
#define WASM_PRICE_FN_get_blockchain_parameters_packed                       1
#define WASM_PRICE_FN_set_blockchain_parameters_packed                       1
#define WASM_PRICE_FN_is_privileged                                          1
#define WASM_PRICE_FN_set_privileged                                         1

// transaction_context
#define WASM_PRICE_FN_checktime                                              13

// producer_api
#define WASM_PRICE_FN_get_active_producers                                   40

//contract_bank_api
#define WASM_PRICE_FN_get_contract_balance                                   400
#define WASM_PRICE_FN_transfer                                               1000
#define WASM_PRICE_FN_get_value                                              100
#define WASM_PRICE_FN_pay_prohibited                                         150

// database_api
#define WASM_PRICE_FN_db_end_i64                                             61
#define WASM_PRICE_FN_db_find_i64                                            225
//#define WASM_PRICE_FN_db_get_i64                                             0      // varied
//#define WASM_PRICE_FN_db_store_i64                                           0      // varied
//#define WASM_PRICE_FN_db_update_i64                                          0      // varied
#define WASM_PRICE_FN_db_upperbound_i64                                      135
#define WASM_PRICE_FN_db_lowerbound_i64                                      72
#define WASM_PRICE_FN_db_next_i64                                            52
#define WASM_PRICE_FN_db_previous_i64                                        56
#define WASM_PRICE_FN_db_remove_i64                                          423

#define WASM_PRICE_FN_db_idx_double_end                                      205
#define WASM_PRICE_FN_db_idx_double_find_primary                             38
#define WASM_PRICE_FN_db_idx_double_find_secondary                           42
#define WASM_PRICE_FN_db_idx_double_lowerbound                               984
#define WASM_PRICE_FN_db_idx_double_next                                     52
#define WASM_PRICE_FN_db_idx_double_previous                                 76
#define WASM_PRICE_FN_db_idx_double_remove                                   247
#define WASM_PRICE_FN_db_idx_double_store                                    318
#define WASM_PRICE_FN_db_idx_double_update                                   146
#define WASM_PRICE_FN_db_idx_double_upperbound                               963

#define WASM_PRICE_FN_db_idx_long_double_end                                 93
#define WASM_PRICE_FN_db_idx_long_double_find_primary                        39
#define WASM_PRICE_FN_db_idx_long_double_find_secondary                      42
#define WASM_PRICE_FN_db_idx_long_double_lowerbound                          888
#define WASM_PRICE_FN_db_idx_long_double_next                                56
#define WASM_PRICE_FN_db_idx_long_double_previous                            56
#define WASM_PRICE_FN_db_idx_long_double_remove                              247
#define WASM_PRICE_FN_db_idx_long_double_store                               361
#define WASM_PRICE_FN_db_idx_long_double_update                              170
#define WASM_PRICE_FN_db_idx_long_double_upperbound                          1326

#define WASM_PRICE_FN_db_idx128_end                                          103
#define WASM_PRICE_FN_db_idx128_find_primary                                 71
#define WASM_PRICE_FN_db_idx128_find_secondary                               41
#define WASM_PRICE_FN_db_idx128_lowerbound                                   666
#define WASM_PRICE_FN_db_idx128_next                                         49
#define WASM_PRICE_FN_db_idx128_previous                                     51
#define WASM_PRICE_FN_db_idx128_remove                                       269
#define WASM_PRICE_FN_db_idx128_store                                        379
#define WASM_PRICE_FN_db_idx128_update                                       149
#define WASM_PRICE_FN_db_idx128_upperbound                                   878

#define WASM_PRICE_FN_db_idx256_end                                          182
#define WASM_PRICE_FN_db_idx256_find_primary                                 41
#define WASM_PRICE_FN_db_idx256_find_secondary                               45
#define WASM_PRICE_FN_db_idx256_lowerbound                                   780
#define WASM_PRICE_FN_db_idx256_next                                         48
#define WASM_PRICE_FN_db_idx256_previous                                     57
#define WASM_PRICE_FN_db_idx256_remove                                       261
#define WASM_PRICE_FN_db_idx256_store                                        341
#define WASM_PRICE_FN_db_idx256_update                                       133
#define WASM_PRICE_FN_db_idx256_upperbound                                   700

#define WASM_PRICE_FN_db_idx64_end                                           117
#define WASM_PRICE_FN_db_idx64_find_primary                                  36
#define WASM_PRICE_FN_db_idx64_find_secondary                                38
#define WASM_PRICE_FN_db_idx64_lowerbound                                    794
#define WASM_PRICE_FN_db_idx64_next                                          67
#define WASM_PRICE_FN_db_idx64_previous                                      60
#define WASM_PRICE_FN_db_idx64_remove                                        220
#define WASM_PRICE_FN_db_idx64_store                                         357
#define WASM_PRICE_FN_db_idx64_update                                        164
#define WASM_PRICE_FN_db_idx64_upperbound                                    1342

// crypto_api
#define WASM_PRICE_FN_assert_recover_key                                     31462
#define WASM_PRICE_FN_recover_key                                            31462
//#define WASM_PRICE_FN_assert_sha256                                          0      // varied
//#define WASM_PRICE_FN_assert_sha1                                            0      // varied
//#define WASM_PRICE_FN_assert_sha512                                          0      // varied
//#define WASM_PRICE_FN_assert_ripemd160                                       0      // varied
//#define WASM_PRICE_FN_sha1                                                   0      // varied
//#define WASM_PRICE_FN_sha256                                                 0      // varied
//#define WASM_PRICE_FN_sha512                                                 0      // varied
//#define WASM_PRICE_FN_ripemd160                                              0      // varied

// permission_api
//#define WASM_PRICE_FN_check_transaction_authorization                        0      // varied
#define WASM_PRICE_FN_check_permission_authorization                         200000
#define WASM_PRICE_FN_get_permission_last_used                               49
#define WASM_PRICE_FN_get_account_creation_time                              86

// system_api
#define WASM_PRICE_FN_current_time                                           9
#define WASM_PRICE_FN_publication_time                                       7

// context_free_system_api
#define WASM_PRICE_FN_abort                                                  WASM_PRICE_UNEXPECTED
#define WASM_PRICE_FN_contento_assert                                        15
#define WASM_PRICE_FN_contento_assert_message                                15
#define WASM_PRICE_FN_contento_assert_code                                   15
#define WASM_PRICE_FN_contento_exit                                          WASM_PRICE_UNEXPECTED

// action_api
//#define WASM_PRICE_FN_read_action_data                                       0      // varied
#define WASM_PRICE_FN_action_data_size                                       31
// #define WASM_PRICE_FN_current_receiver                                       13
#define WASM_PRICE_FN_current_caller                                         13
#define WASM_PRICE_FN_current_coder                                          13

// authorization_api
#define WASM_PRICE_FN_require_recipient                                      60
#define WASM_PRICE_FN_require_auth                                           125
#define WASM_PRICE_FN_require_auth2                                          150
#define WASM_PRICE_FN_has_auth                                               125
#define WASM_PRICE_FN_is_account                                             140

// console_api
#define WASM_PRICE_FN_prints                                                 68      // fixed price of printing 128 chars.
//#define WASM_PRICE_FN_prints_l                                               0      // varied
#define WASM_PRICE_FN_printi                                                 120
#define WASM_PRICE_FN_printui                                                100
#define WASM_PRICE_FN_printi128                                              120
#define WASM_PRICE_FN_printui128                                             100
#define WASM_PRICE_FN_printsf                                                160
#define WASM_PRICE_FN_printdf                                                160
#define WASM_PRICE_FN_printqf                                                160
#define WASM_PRICE_FN_printn                                                 54
//#define WASM_PRICE_FN_printhex                                               0      // varied

// context_free_transaction_api
//#define WASM_PRICE_FN_read_transaction                                       0      // varied
#define WASM_PRICE_FN_transaction_size                                       66
#define WASM_PRICE_FN_expiration                                             14
#define WASM_PRICE_FN_tapos_block_prefix                                     13
#define WASM_PRICE_FN_tapos_block_num                                        15
//#define WASM_PRICE_FN_get_action                                             0      // varied

// transaction_api
#define WASM_PRICE_FN_send_inline                                            1984
#define WASM_PRICE_FN_send_context_free_inline                               1      // feature removed
#define WASM_PRICE_FN_send_deferred                                          1      // feature removed
#define WASM_PRICE_FN_cancel_deferred                                        1      // feature removed

// content_api
#define WASM_PRICE_FN_on_content_call                                        1      // todo: not implemented yet
#define WASM_PRICE_FN_excute_operation                                        1      // todo: not implemented yet

// context_free_api
//#define WASM_PRICE_FN_get_context_free_data                                  0      // varied

// memory_api
//#define WASM_PRICE_FN_memcpy                                                 0      // varied
//#define WASM_PRICE_FN_memmove                                                0      // varied
//#define WASM_PRICE_FN_memcmp                                                 0      // varied
//#define WASM_PRICE_FN_memset                                                 0      // varied

// softfloat_api
// all softfloat prices are from 9 to 13. quite fast and close.
// set them all to 12 for simplification.
#define WASM_PRICE_SOFTFLOAT                                                 12
#define WASM_PRICE_FN__contento_f32_add                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_sub                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_mul                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_div                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_min                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_max                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_copysign                                 WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_abs                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_neg                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_sqrt                                     WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_ceil                                     WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_floor                                    WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_trunc                                    WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_nearest                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_eq                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_ne                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_lt                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_le                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_gt                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_ge                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_add                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_sub                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_mul                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_div                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_min                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_max                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_copysign                                 WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_abs                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_neg                                      WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_sqrt                                     WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_ceil                                     WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_floor                                    WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_trunc                                    WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_nearest                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_eq                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_ne                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_lt                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_le                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_gt                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_ge                                       WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_promote                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_demote                                   WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_trunc_i32s                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_trunc_i32s                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_trunc_i32u                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_trunc_i32u                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_trunc_i64s                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_trunc_i64s                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f32_trunc_i64u                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_f64_trunc_i64u                               WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_i32_to_f32                                   WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_i64_to_f32                                   WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_ui32_to_f32                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_ui64_to_f32                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_i32_to_f64                                   WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_i64_to_f64                                   WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_ui32_to_f64                                  WASM_PRICE_SOFTFLOAT
#define WASM_PRICE_FN__contento_ui64_to_f64                                  WASM_PRICE_SOFTFLOAT

namespace contento { namespace chain { namespace wasm_price {
    
    /*
     A price function returns uint64_t price value based on given intrinsic operands and result.
     
     For example, __eqtf2 has a wasm signature of int(int64_t, int64_t, int64_t, int64_t).
     So that the intrinsic takes 4 int64_t operands and returns an int.
     Its price function will be `uint64_t contento::chain::wasm_price::__eqtf2(apply_context*, int, int64_t, int64_t, int64_t, int64_t)`,
     which returns uint64_t price based on __eqtf2's result (2nd arg) and operands (3rd, 4th, 5th and 6th arg).
     
     An apply_context* is given as the 1st arg of price functions for even more complex price logics.
     
     For intrincs that return nothing (i.e. void), the 2nd arg of their price functions will be a (void*)nullptr.
     */
    
    ///////////////////////////////////
    //
    // complex price functions
    //
    ///////////////////////////////////
    
    // database_api
    uint64_t db_get_i64(apply_context*, int, int, int, int len) {
        // larger the value, higher the price.
        return 24 + (len >> 8);
    }
    uint64_t db_update_i64(apply_context*, void*, int, int, int, int len) {
        // larger the value, higher the price.
        return 128 + (len >> 5);
    }
    uint64_t db_store_i64(apply_context*, int, int, int64_t, int, int64_t, int, int len) {
        // larger the value, higher the price.
        return 1280 + len / 3;
    }
    
    // crypto_api
    uint64_t sha1(apply_context*, void*, int, int len, int) {
        // larger the plain-text, higher the price.
        return 72 + len / 5;
    }
    uint64_t sha256(apply_context*, void*, int, int len, int) {
        // larger the plain-text, higher the price.
        return 72 + (len >> 1);
    }
    uint64_t sha512(apply_context*, void*, int, int len, int) {
        // larger the plain-text, higher the price.
        return 72 + (len >> 1);
    }
    uint64_t ripemd160(apply_context*, void*, int, int len, int) {
        // larger the plain-text, higher the price.
        return 72 + 3 * (len >> 2);
    }
    uint64_t assert_sha1(apply_context*, void*, int, int len, int) {
        // same as sha1.
        return 72 + len / 5;
    }
    uint64_t assert_sha256(apply_context*, void*, int, int len, int) {
        // same as sha256.
        return 72 + (len >> 1);
    }
    uint64_t assert_sha512(apply_context*, void*, int, int len, int) {
        // same as sha512.
        return 72 + (len >> 1);
    }
    uint64_t assert_ripemd160(apply_context*, void*, int, int len, int) {
        // same as ripemd160.
        return 72 + 3 * (len >> 2);
    }
    
    // permission_api
    uint64_t check_transaction_authorization(apply_context*, int, int, int trx_size, int, int, int, int) {
        
        // it's basically multiple calls to check_permission_authorization.
        // the exact #calls is too expensive to calculate here, but it's proportional to #actions in statistics.
        // we simply take #actions as #calls using a default action_size of 256 bytes.
        return ( 1 + (trx_size >> 8) ) * WASM_PRICE_FN_check_permission_authorization;
    }
    
    // action_api
    uint64_t read_action_data(apply_context*, int read_len, int, int) {
        // larger the data, higher the price.
        return 95 + (read_len >> 7);
    }
    
    // console_api
    uint64_t prints_l(apply_context*, void*, int, int len) {
        // larger the data, higher the price.
        return 62 + (len >> 4);
    }

    uint64_t printhex(apply_context*, void*, int, int len) {
        // larger the data, higher the price.
        return 62 + (len << 2);
    }
    
    // context_free_transaction_api
    uint64_t read_transaction(apply_context*, int read_len, int, int) {
        // larger the value, higher the price.
        return 66 + (read_len >> 7);
    }
    uint64_t get_action(apply_context*, int action_size, int, int, int, int) {
        // larger the value, higher the price.
        return 24 + (action_size >> 7);
    }
    
    // context_free_api
    uint64_t get_context_free_data(apply_context*, int read_len, int, int, int) {
        // larger the data, higher the price.
        return 95 + (read_len >> 7);
    }
    
    // memory_api
    uint64_t memcpy(apply_context*, int, int, int, int len) {
        // larger the data, higher the price.
        return 10 + (len >> 7);
    }
    uint64_t memmove(apply_context*, int, int, int, int len) {
        // larger the data, higher the price.
        return 10 + (len >> 7);
    }
    uint64_t memcmp(apply_context*, int, int, int, int len) {
        // contracts never call this.
        // when a contract calls memcmp, it's just a normal 'call' to another memcmp inside libc++, not a 'callImport' to this one.
        // anyway, we give the price for the worst condition of comparing identical blocks.
        return 30 + 3 * (len >> 7);
    }
    uint64_t memset(apply_context*, int, int, int, int len) {
        // larger the data, higher the price.
        return 20 + (len >> 6);
    }
    

    ///////////////////////////////////
    //
    // constant price functions
    //
    ///////////////////////////////////
    
    /*
     WASM_PRICE_FN_CONSTS macro defines price functions that simply return constant values.
     The constant price for intrinsic X will be WASM_PRICE_FN_##X.
     */
    
    
    // call_depth_api
    WASM_PRICE_FN_CONSTS(
                         (call_depth_assert,  (void*)               )
                         );
    
    // compiler_builtins
    WASM_PRICE_FN_CONSTS(
                         (__ashlti3,     (void*, int, int64_t, int64_t, int)               )
                         (__ashrti3,     (void*, int, int64_t, int64_t, int)               )
                         (__lshlti3,     (void*, int, int64_t, int64_t, int)               )
                         (__lshrti3,     (void*, int, int64_t, int64_t, int)               )
                         (__divti3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__udivti3,     (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__modti3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__umodti3,     (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__multi3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__addtf3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__subtf3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__multf3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__divtf3,      (void*, int, int64_t, int64_t, int64_t, int64_t)  )
                         (__eqtf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__netf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__getf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__gttf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__lttf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__letf2,       (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__cmptf2,      (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__unordtf2,    (int, int64_t, int64_t, int64_t, int64_t)        )
                         (__negtf2,      (void*, int, int64_t, int64_t)                   )
                         (__floatsitf,   (void*, int, int)                                )
                         (__floatunsitf, (void*, int, int)                                )
                         (__floatditf,   (void*, int, int64_t)                            )
                         (__floatunditf, (void*, int, int64_t)                            )
                         (__floattidf,   (double, int64_t, int64_t)                      )
                         (__floatuntidf, (double, int64_t, int64_t)                      )
                         (__floatsidf,   (double, int)                                    )
                         (__extendsftf2, (void*, int, float)                               )
                         (__extenddftf2, (void*, int, double)                              )
                         (__fixtfti,     (void*, int, int64_t, int64_t)                    )
                         (__fixtfdi,     (int64_t, int64_t, int64_t)                      )
                         (__fixtfsi,     (int, int64_t, int64_t)                          )
                         (__fixunstfti,  (void*, int, int64_t, int64_t)                    )
                         (__fixunstfdi,  (int64_t, int64_t, int64_t)                      )
                         (__fixunstfsi,  (int, int64_t, int64_t)                          )
                         (__fixsfti,     (void*, int, float)                               )
                         (__fixdfti,     (void*, int, double)                              )
                         (__fixunssfti,  (void*, int, float)                               )
                         (__fixunsdfti,  (void*, int, double)                              )
                         (__trunctfdf2,  (double, int64_t, int64_t)                       )
                         (__trunctfsf2,  (float, int64_t, int64_t)                        )
                         );
    
    // privileged_api
    WASM_PRICE_FN_CONSTS(
                         (is_feature_active,                (int, int64_t)                          )
                         (activate_feature,                 (void*, int64_t)                         )
                        //  (get_resource_limits,              (void*, int64_t,int,int,int)             )
                        //  (set_resource_limits,              (void*, int,int64_t,int64_t,int64_t) )
                        //  (set_proposed_producers,           (int64_t, int,int)                      )
                         (get_blockchain_parameters_packed, (int, int, int)                         )
                         (set_blockchain_parameters_packed, (void*, int,int)                         )
                         (is_privileged,                    (int, int)                          )
                         (set_privileged,                   (void*, int, int)                    )
                         );
    
    // transaction_context
    WASM_PRICE_FN_CONSTS(
                         (checktime,      (void*))
                         );
    
    // producer_api
    WASM_PRICE_FN_CONSTS(
                         (get_active_producers,      (int, int, int) )
                         );
    
    // contract_balance_api
    WASM_PRICE_FN_CONSTS(
                         (get_contract_balance,      (void*, int) )
                         (transfer,                  (void*,int64_t, int))
                         (get_value,                 (int64_t))
                         (pay_prohibited,            (void*))
                         );
    
    // database_api
    WASM_PRICE_FN_CONSTS(
//                         (db_store_i64,        (int, int64_t,int64_t,int64_t,int64_t,int,int))
//                         (db_update_i64,       (void*, int,int64_t,int,int))
                         (db_remove_i64,       (void*, int))
//                         (db_get_i64,          (int, int, int, int))
                         (db_next_i64,         (int, int, int))
                         (db_previous_i64,     (int, int, int))
                         (db_find_i64,         (int, int,int,int64_t,int64_t))
                         (db_lowerbound_i64,   (int, int,int,int64_t,int64_t))
                         (db_upperbound_i64,   (int, int,int,int64_t,int64_t))
                         (db_end_i64,          (int, int,int,int64_t))
                         
                         DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx64)
                         DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx128)
                         DECL_DB_SECONDARY_INDEX_METHODS_ARRAY(idx256)
                         DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx_double)
                         DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx_long_double)
                         );
    
    // crypto_api
    WASM_PRICE_FN_CONSTS(
                         (assert_recover_key,     (void*, int, int, int, int, int) )
                         (recover_key,            (int, int, int, int, int, int)  )
//                         (assert_sha256,          (void*, int, int, int)           )
//                         (assert_sha1,            (void*, int, int, int)           )
//                         (assert_sha512,          (void*, int, int, int)           )
//                         (assert_ripemd160,       (void*, int, int, int)           )
//                         (sha1,                   (void*, int, int, int)           )
//                         (sha256,                 (void*, int, int, int)           )
//                         (sha512,                 (void*, int, int, int)           )
//                         (ripemd160,              (void*, int, int, int)           )
                         );
    
    // permission_api
    WASM_PRICE_FN_CONSTS(
//                         (check_transaction_authorization, (int, int, int, int, int, int, int)                  )
                         (check_permission_authorization,  (int, int64_t, int64_t, int, int, int, int, int64_t) )
                         (get_permission_last_used,        (int64_t, int64_t, int64_t) )
                         (get_account_creation_time,       (int64_t, int64_t) )
                         );
    
    // system_api
    WASM_PRICE_FN_CONSTS(
                         (current_time, (int64_t)       )
                         (publication_time,   (int64_t) )
                         );
    
    // context_free_system_api
    WASM_PRICE_FN_CONSTS(
                         (abort,                (void*)              )
                         (contento_assert,         (void*, int, int)      )
                         (contento_assert_message, (void*, int, int, int) )
                         (contento_assert_code,    (void*, int, int64_t)  )
                         (contento_exit,           (void*, int)           )
                         );
    
    // action_api
    WASM_PRICE_FN_CONSTS(
//                         (read_action_data,       (int, int, int)  )
                         (action_data_size,       (int)              )
                        //  (current_receiver,       (int)          )
                         (current_caller,           (void*, int)  )
                         (current_coder,            (void*, int)  )
                         );
    
    // authorization_api
    WASM_PRICE_FN_CONSTS(
                         (require_recipient,     (void*, int64_t)          )
                         (require_auth,          (void*, int64_t)          )
                         (require_auth2,         (void*, int64_t, int64_t) )
                         (has_auth,              (int, int64_t)           )
                         (is_account,            (int, int64_t)           )
                         );
    
    // console_api
    WASM_PRICE_FN_CONSTS(
                         (prints,                (void*, int)      )
//                         (prints_l,              (void*, int, int) )
                         (printi,                (void*, int64_t)  )
                         (printui,               (void*, int64_t)  )
                         (printi128,             (void*, int)      )
                         (printui128,            (void*, int)      )
                         (printsf,               (void*, float)    )
                         (printdf,               (void*, double)   )
                         (printqf,               (void*, int)      )
                         (printn,                (void*, int64_t)  )
//                         (printhex,              (void*, int, int) )
                         );
    
    // context_free_transaction_api
    WASM_PRICE_FN_CONSTS(
//                         (read_transaction,       (int, int, int)            )
                         (transaction_size,       (int)                    )
                         (expiration,             (int)                    )
                         (tapos_block_prefix,     (int)                    )
                         (tapos_block_num,        (int)                    )
//                         (get_action,             (int, int, int, int, int) )
                         );
    
    // transaction_api
    WASM_PRICE_FN_CONSTS(
                         (send_inline,               (void*, int, int)               )
                         (send_context_free_inline,  (void*, int, int)               )
                         (send_deferred,             (void*, int, int, int, int, int32_t) )
                         (cancel_deferred,           (int, int)                     )
                         );
    
    // content_api
    WASM_PRICE_FN_CONSTS(
                         (on_content_call,           (int, int, int, int, int)      )
                         (excute_operation,           (int, int, int)   )
                        );
    
    // context_free_api
//    WASM_PRICE_FN_CONSTS(
//                         (get_context_free_data, (int, int, int, int) )
//                         );
    
    // memory_api
//    WASM_PRICE_FN_CONSTS(
//                         (memcpy,                 (int, int, int, int)  )
//                         (memmove,                (int, int, int, int)  )
//                         (memcmp,                 (int, int, int, int)  )
//                         (memset,                 (int, int, int, int)  )
//                         );
    
    // softfloat_api
    WASM_PRICE_FN_CONSTS(
                         (_contento_f32_add,       (float, float, float)    )
                         (_contento_f32_sub,       (float, float, float)    )
                         (_contento_f32_mul,       (float, float, float)    )
                         (_contento_f32_div,       (float, float, float)    )
                         (_contento_f32_min,       (float, float, float)    )
                         (_contento_f32_max,       (float, float, float)    )
                         (_contento_f32_copysign,  (float, float, float)    )
                         (_contento_f32_abs,       (float, float)           )
                         (_contento_f32_neg,       (float, float)           )
                         (_contento_f32_sqrt,      (float, float)           )
                         (_contento_f32_ceil,      (float, float)           )
                         (_contento_f32_floor,     (float, float)           )
                         (_contento_f32_trunc,     (float, float)           )
                         (_contento_f32_nearest,   (float, float)           )
                         (_contento_f32_eq,        (int, float, float)      )
                         (_contento_f32_ne,        (int, float, float)      )
                         (_contento_f32_lt,        (int, float, float)      )
                         (_contento_f32_le,        (int, float, float)      )
                         (_contento_f32_gt,        (int, float, float)      )
                         (_contento_f32_ge,        (int, float, float)      )
                         (_contento_f64_add,       (double, double, double) )
                         (_contento_f64_sub,       (double, double, double) )
                         (_contento_f64_mul,       (double, double, double) )
                         (_contento_f64_div,       (double, double, double) )
                         (_contento_f64_min,       (double, double, double) )
                         (_contento_f64_max,       (double, double, double) )
                         (_contento_f64_copysign,  (double, double, double) )
                         (_contento_f64_abs,       (double, double)         )
                         (_contento_f64_neg,       (double, double)         )
                         (_contento_f64_sqrt,      (double, double)         )
                         (_contento_f64_ceil,      (double, double)         )
                         (_contento_f64_floor,     (double, double)         )
                         (_contento_f64_trunc,     (double, double)         )
                         (_contento_f64_nearest,   (double, double)         )
                         (_contento_f64_eq,        (int, double, double)    )
                         (_contento_f64_ne,        (int, double, double)    )
                         (_contento_f64_lt,        (int, double, double)    )
                         (_contento_f64_le,        (int, double, double)    )
                         (_contento_f64_gt,        (int, double, double)    )
                         (_contento_f64_ge,        (int, double, double)    )
                         (_contento_f32_promote,    (double, float)         )
                         (_contento_f64_demote,     (float, double)         )
                         (_contento_f32_trunc_i32s, (int, float)            )
                         (_contento_f64_trunc_i32s, (int, double)           )
                         (_contento_f32_trunc_i32u, (int, float)            )
                         (_contento_f64_trunc_i32u, (int, double)           )
                         (_contento_f32_trunc_i64s, (int64_t, float)        )
                         (_contento_f64_trunc_i64s, (int64_t, double)       )
                         (_contento_f32_trunc_i64u, (int64_t, float)        )
                         (_contento_f64_trunc_i64u, (int64_t, double)       )
                         (_contento_i32_to_f32,     (float, int32_t)        )
                         (_contento_i64_to_f32,     (float, int64_t)        )
                         (_contento_ui32_to_f32,    (float, int32_t)        )
                         (_contento_ui64_to_f32,    (float, int64_t)        )
                         (_contento_i32_to_f64,     (double, int32_t)       )
                         (_contento_i64_to_f64,     (double, int64_t)       )
                         (_contento_ui32_to_f64,    (double, int32_t)       )
                         (_contento_ui64_to_f64,    (double, int64_t)       )
                         );
    
    
}}} // contento::chain::wasm_price
