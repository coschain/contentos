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
#define WASM_PRICE_FN_call_depth_assert                                      0

// compiler_builtins
#define WASM_PRICE_FN___ashlti3                                              0
#define WASM_PRICE_FN___ashrti3                                              0
#define WASM_PRICE_FN___lshlti3                                              0
#define WASM_PRICE_FN___lshrti3                                              0
#define WASM_PRICE_FN___divti3                                               0
#define WASM_PRICE_FN___udivti3                                              0
#define WASM_PRICE_FN___modti3                                               0
#define WASM_PRICE_FN___umodti3                                              0
#define WASM_PRICE_FN___multi3                                               0
#define WASM_PRICE_FN___addtf3                                               0
#define WASM_PRICE_FN___subtf3                                               0
#define WASM_PRICE_FN___multf3                                               0
#define WASM_PRICE_FN___divtf3                                               0
#define WASM_PRICE_FN___eqtf2                                                0
#define WASM_PRICE_FN___netf2                                                0
#define WASM_PRICE_FN___getf2                                                0
#define WASM_PRICE_FN___gttf2                                                0
#define WASM_PRICE_FN___lttf2                                                0
#define WASM_PRICE_FN___letf2                                                0
#define WASM_PRICE_FN___cmptf2                                               0
#define WASM_PRICE_FN___unordtf2                                             0
#define WASM_PRICE_FN___negtf2                                               0
#define WASM_PRICE_FN___floatsitf                                            0
#define WASM_PRICE_FN___floatunsitf                                          0
#define WASM_PRICE_FN___floatditf                                            0
#define WASM_PRICE_FN___floatunditf                                          0
#define WASM_PRICE_FN___floattidf                                            0
#define WASM_PRICE_FN___floatuntidf                                          0
#define WASM_PRICE_FN___floatsidf                                            0
#define WASM_PRICE_FN___extendsftf2                                          0
#define WASM_PRICE_FN___extenddftf2                                          0
#define WASM_PRICE_FN___fixtfti                                              0
#define WASM_PRICE_FN___fixtfdi                                              0
#define WASM_PRICE_FN___fixtfsi                                              0
#define WASM_PRICE_FN___fixunstfti                                           0
#define WASM_PRICE_FN___fixunstfdi                                           0
#define WASM_PRICE_FN___fixunstfsi                                           0
#define WASM_PRICE_FN___fixsfti                                              0
#define WASM_PRICE_FN___fixdfti                                              0
#define WASM_PRICE_FN___fixunssfti                                           0
#define WASM_PRICE_FN___fixunsdfti                                           0
#define WASM_PRICE_FN___trunctfdf2                                           0
#define WASM_PRICE_FN___trunctfsf2                                           0

// privileged_api
#define WASM_PRICE_FN_is_feature_active                                      0
#define WASM_PRICE_FN_activate_feature                                       0
#define WASM_PRICE_FN_get_resource_limits                                    0
#define WASM_PRICE_FN_set_resource_limits                                    0
#define WASM_PRICE_FN_set_proposed_producers                                 0
#define WASM_PRICE_FN_get_blockchain_parameters_packed                       0
#define WASM_PRICE_FN_set_blockchain_parameters_packed                       0
#define WASM_PRICE_FN_is_privileged                                          0
#define WASM_PRICE_FN_set_privileged                                         0

// transaction_context
#define WASM_PRICE_FN_checktime                                              0

// producer_api
#define WASM_PRICE_FN_get_active_producers                                   0

// database_api
#define WASM_PRICE_FN_db_store_i64                                           0
#define WASM_PRICE_FN_db_update_i64                                          0
#define WASM_PRICE_FN_db_remove_i64                                          0
#define WASM_PRICE_FN_db_get_i64                                             0
#define WASM_PRICE_FN_db_next_i64                                            0
#define WASM_PRICE_FN_db_previous_i64                                        0
#define WASM_PRICE_FN_db_find_i64                                            0
#define WASM_PRICE_FN_db_lowerbound_i64                                      0
#define WASM_PRICE_FN_db_upperbound_i64                                      0
#define WASM_PRICE_FN_db_end_i64                                             0

#define WASM_PRICE_FN_db_idx64_store                                         0
#define WASM_PRICE_FN_db_idx64_remove                                        0
#define WASM_PRICE_FN_db_idx64_update                                        0
#define WASM_PRICE_FN_db_idx64_find_primary                                  0
#define WASM_PRICE_FN_db_idx64_find_secondary                                0
#define WASM_PRICE_FN_db_idx64_lowerbound                                    0
#define WASM_PRICE_FN_db_idx64_upperbound                                    0
#define WASM_PRICE_FN_db_idx64_end                                           0
#define WASM_PRICE_FN_db_idx64_next                                          0
#define WASM_PRICE_FN_db_idx64_previous                                      0

#define WASM_PRICE_FN_db_idx128_store                                        0
#define WASM_PRICE_FN_db_idx128_remove                                       0
#define WASM_PRICE_FN_db_idx128_update                                       0
#define WASM_PRICE_FN_db_idx128_find_primary                                 0
#define WASM_PRICE_FN_db_idx128_find_secondary                               0
#define WASM_PRICE_FN_db_idx128_lowerbound                                   0
#define WASM_PRICE_FN_db_idx128_upperbound                                   0
#define WASM_PRICE_FN_db_idx128_end                                          0
#define WASM_PRICE_FN_db_idx128_next                                         0
#define WASM_PRICE_FN_db_idx128_previous                                     0

#define WASM_PRICE_FN_db_idx256_store                                        0
#define WASM_PRICE_FN_db_idx256_remove                                       0
#define WASM_PRICE_FN_db_idx256_update                                       0
#define WASM_PRICE_FN_db_idx256_find_primary                                 0
#define WASM_PRICE_FN_db_idx256_find_secondary                               0
#define WASM_PRICE_FN_db_idx256_lowerbound                                   0
#define WASM_PRICE_FN_db_idx256_upperbound                                   0
#define WASM_PRICE_FN_db_idx256_end                                          0
#define WASM_PRICE_FN_db_idx256_next                                         0
#define WASM_PRICE_FN_db_idx256_previous                                     0

#define WASM_PRICE_FN_db_idx_double_store                                    0
#define WASM_PRICE_FN_db_idx_double_remove                                   0
#define WASM_PRICE_FN_db_idx_double_update                                   0
#define WASM_PRICE_FN_db_idx_double_find_primary                             0
#define WASM_PRICE_FN_db_idx_double_find_secondary                           0
#define WASM_PRICE_FN_db_idx_double_lowerbound                               0
#define WASM_PRICE_FN_db_idx_double_upperbound                               0
#define WASM_PRICE_FN_db_idx_double_end                                      0
#define WASM_PRICE_FN_db_idx_double_next                                     0
#define WASM_PRICE_FN_db_idx_double_previous                                 0

#define WASM_PRICE_FN_db_idx_long_double_store                               0
#define WASM_PRICE_FN_db_idx_long_double_remove                              0
#define WASM_PRICE_FN_db_idx_long_double_update                              0
#define WASM_PRICE_FN_db_idx_long_double_find_primary                        0
#define WASM_PRICE_FN_db_idx_long_double_find_secondary                      0
#define WASM_PRICE_FN_db_idx_long_double_lowerbound                          0
#define WASM_PRICE_FN_db_idx_long_double_upperbound                          0
#define WASM_PRICE_FN_db_idx_long_double_end                                 0
#define WASM_PRICE_FN_db_idx_long_double_next                                0
#define WASM_PRICE_FN_db_idx_long_double_previous                            0

// crypto_api
#define WASM_PRICE_FN_assert_recover_key                                     0
#define WASM_PRICE_FN_recover_key                                            0
#define WASM_PRICE_FN_assert_sha256                                          0
#define WASM_PRICE_FN_assert_sha1                                            0
#define WASM_PRICE_FN_assert_sha512                                          0
#define WASM_PRICE_FN_assert_ripemd160                                       0
#define WASM_PRICE_FN_sha1                                                   0
#define WASM_PRICE_FN_sha256                                                 0
#define WASM_PRICE_FN_sha512                                                 0
#define WASM_PRICE_FN_ripemd160                                              0

// permission_api
#define WASM_PRICE_FN_check_transaction_authorization                        0
#define WASM_PRICE_FN_check_permission_authorization                         0
#define WASM_PRICE_FN_get_permission_last_used                               0
#define WASM_PRICE_FN_get_account_creation_time                              0

// system_api
#define WASM_PRICE_FN_current_time                                           0
#define WASM_PRICE_FN_publication_time                                       0

// context_free_system_api
#define WASM_PRICE_FN_abort                                                  0
#define WASM_PRICE_FN_eosio_assert                                           0
#define WASM_PRICE_FN_eosio_assert_message                                   0
#define WASM_PRICE_FN_eosio_assert_code                                      0
#define WASM_PRICE_FN_eosio_exit                                             0

// action_api
#define WASM_PRICE_FN_read_action_data                                       0
#define WASM_PRICE_FN_action_data_size                                       0
#define WASM_PRICE_FN_current_receiver                                       0

// authorization_api
#define WASM_PRICE_FN_require_recipient                                      0
#define WASM_PRICE_FN_require_auth                                           0
#define WASM_PRICE_FN_require_auth2                                          0
#define WASM_PRICE_FN_has_auth                                               0
#define WASM_PRICE_FN_is_account                                             0

// console_api
#define WASM_PRICE_FN_prints                                                 0
#define WASM_PRICE_FN_prints_l                                               0
#define WASM_PRICE_FN_printi                                                 0
#define WASM_PRICE_FN_printui                                                0
#define WASM_PRICE_FN_printi128                                              0
#define WASM_PRICE_FN_printui128                                             0
#define WASM_PRICE_FN_printsf                                                0
#define WASM_PRICE_FN_printdf                                                0
#define WASM_PRICE_FN_printqf                                                0
#define WASM_PRICE_FN_printn                                                 0
#define WASM_PRICE_FN_printhex                                               0

// context_free_transaction_api
#define WASM_PRICE_FN_read_transaction                                       0
#define WASM_PRICE_FN_transaction_size                                       0
#define WASM_PRICE_FN_expiration                                             0
#define WASM_PRICE_FN_tapos_block_prefix                                     0
#define WASM_PRICE_FN_tapos_block_num                                        0
#define WASM_PRICE_FN_get_action                                             0

// transaction_api
#define WASM_PRICE_FN_send_inline                                            0
#define WASM_PRICE_FN_send_context_free_inline                               0
#define WASM_PRICE_FN_send_deferred                                          0
#define WASM_PRICE_FN_cancel_deferred                                        0

// context_free_api
#define WASM_PRICE_FN_get_context_free_data                                  0

// memory_api
#define WASM_PRICE_FN_memcpy                                                 0
#define WASM_PRICE_FN_memmove                                                0
#define WASM_PRICE_FN_memcmp                                                 0
#define WASM_PRICE_FN_memset                                                 0

// softfloat_api
#define WASM_PRICE_FN__eosio_f32_add                                         0
#define WASM_PRICE_FN__eosio_f32_sub                                         0
#define WASM_PRICE_FN__eosio_f32_mul                                         0
#define WASM_PRICE_FN__eosio_f32_div                                         0
#define WASM_PRICE_FN__eosio_f32_min                                         0
#define WASM_PRICE_FN__eosio_f32_max                                         0
#define WASM_PRICE_FN__eosio_f32_copysign                                    0
#define WASM_PRICE_FN__eosio_f32_abs                                         0
#define WASM_PRICE_FN__eosio_f32_neg                                         0
#define WASM_PRICE_FN__eosio_f32_sqrt                                        0
#define WASM_PRICE_FN__eosio_f32_ceil                                        0
#define WASM_PRICE_FN__eosio_f32_floor                                       0
#define WASM_PRICE_FN__eosio_f32_trunc                                       0
#define WASM_PRICE_FN__eosio_f32_nearest                                     0
#define WASM_PRICE_FN__eosio_f32_eq                                          0
#define WASM_PRICE_FN__eosio_f32_ne                                          0
#define WASM_PRICE_FN__eosio_f32_lt                                          0
#define WASM_PRICE_FN__eosio_f32_le                                          0
#define WASM_PRICE_FN__eosio_f32_gt                                          0
#define WASM_PRICE_FN__eosio_f32_ge                                          0
#define WASM_PRICE_FN__eosio_f64_add                                         0
#define WASM_PRICE_FN__eosio_f64_sub                                         0
#define WASM_PRICE_FN__eosio_f64_mul                                         0
#define WASM_PRICE_FN__eosio_f64_div                                         0
#define WASM_PRICE_FN__eosio_f64_min                                         0
#define WASM_PRICE_FN__eosio_f64_max                                         0
#define WASM_PRICE_FN__eosio_f64_copysign                                    0
#define WASM_PRICE_FN__eosio_f64_abs                                         0
#define WASM_PRICE_FN__eosio_f64_neg                                         0
#define WASM_PRICE_FN__eosio_f64_sqrt                                        0
#define WASM_PRICE_FN__eosio_f64_ceil                                        0
#define WASM_PRICE_FN__eosio_f64_floor                                       0
#define WASM_PRICE_FN__eosio_f64_trunc                                       0
#define WASM_PRICE_FN__eosio_f64_nearest                                     0
#define WASM_PRICE_FN__eosio_f64_eq                                          0
#define WASM_PRICE_FN__eosio_f64_ne                                          0
#define WASM_PRICE_FN__eosio_f64_lt                                          0
#define WASM_PRICE_FN__eosio_f64_le                                          0
#define WASM_PRICE_FN__eosio_f64_gt                                          0
#define WASM_PRICE_FN__eosio_f64_ge                                          0
#define WASM_PRICE_FN__eosio_f32_promote                                     0
#define WASM_PRICE_FN__eosio_f64_demote                                      0
#define WASM_PRICE_FN__eosio_f32_trunc_i32s                                  0
#define WASM_PRICE_FN__eosio_f64_trunc_i32s                                  0
#define WASM_PRICE_FN__eosio_f32_trunc_i32u                                  0
#define WASM_PRICE_FN__eosio_f64_trunc_i32u                                  0
#define WASM_PRICE_FN__eosio_f32_trunc_i64s                                  0
#define WASM_PRICE_FN__eosio_f64_trunc_i64s                                  0
#define WASM_PRICE_FN__eosio_f32_trunc_i64u                                  0
#define WASM_PRICE_FN__eosio_f64_trunc_i64u                                  0
#define WASM_PRICE_FN__eosio_i32_to_f32                                      0
#define WASM_PRICE_FN__eosio_i64_to_f32                                      0
#define WASM_PRICE_FN__eosio_ui32_to_f32                                     0
#define WASM_PRICE_FN__eosio_ui64_to_f32                                     0
#define WASM_PRICE_FN__eosio_i32_to_f64                                      0
#define WASM_PRICE_FN__eosio_i64_to_f64                                      0
#define WASM_PRICE_FN__eosio_ui32_to_f64                                     0
#define WASM_PRICE_FN__eosio_ui64_to_f64                                     0

namespace eosio { namespace chain { namespace wasm_price {
    
    /*
     A price function returns uint64_t price value based on given intrinsic operands and result.
     
     For example, __eqtf2 has a wasm signature of int(int64_t, int64_t, int64_t, int64_t).
     So that the intrinsic takes 4 int64_t operands and returns an int.
     Its price function will be `uint64_t eosio::chain::wasm_price::__eqtf2(apply_context*, int, int64_t, int64_t, int64_t, int64_t)`,
     which returns uint64_t price based on __eqtf2's result (2nd arg) and operands (3rd, 4th, 5th and 6th arg).
     
     An apply_context* is given as the 1st arg of price functions for even more complex price logics.
     
     For intrincs that return nothing (i.e. void), the 2nd arg of their price functions will be a (void*)nullptr.
     */
    
    ///////////////////////////////////
    //
    // complex price functions
    //
    ///////////////////////////////////
    
    // none so far...
    
    

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
                         (get_resource_limits,              (void*, int64_t,int,int,int)             )
                         (set_resource_limits,              (void*, int64_t,int64_t,int64_t,int64_t) )
                         (set_proposed_producers,           (int64_t, int,int)                      )
                         (get_blockchain_parameters_packed, (int, int, int)                         )
                         (set_blockchain_parameters_packed, (void*, int,int)                         )
                         (is_privileged,                    (int, int64_t)                          )
                         (set_privileged,                   (void*, int64_t, int)                    )
                         );
    
    // transaction_context
    WASM_PRICE_FN_CONSTS(
                         (checktime,      (void*))
                         );
    
    // producer_api
    WASM_PRICE_FN_CONSTS(
                         (get_active_producers,      (int, int, int) )
                         );
    
    // database_api
    WASM_PRICE_FN_CONSTS(
                         (db_store_i64,        (int, int64_t,int64_t,int64_t,int64_t,int,int))
                         (db_update_i64,       (void*, int,int64_t,int,int))
                         (db_remove_i64,       (void*, int))
                         (db_get_i64,          (int, int, int, int))
                         (db_next_i64,         (int, int, int))
                         (db_previous_i64,     (int, int, int))
                         (db_find_i64,         (int, int64_t,int64_t,int64_t,int64_t))
                         (db_lowerbound_i64,   (int, int64_t,int64_t,int64_t,int64_t))
                         (db_upperbound_i64,   (int, int64_t,int64_t,int64_t,int64_t))
                         (db_end_i64,          (int, int64_t,int64_t,int64_t))
                         
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
                         (assert_sha256,          (void*, int, int, int)           )
                         (assert_sha1,            (void*, int, int, int)           )
                         (assert_sha512,          (void*, int, int, int)           )
                         (assert_ripemd160,       (void*, int, int, int)           )
                         (sha1,                   (void*, int, int, int)           )
                         (sha256,                 (void*, int, int, int)           )
                         (sha512,                 (void*, int, int, int)           )
                         (ripemd160,              (void*, int, int, int)           )
                         );
    
    // permission_api
    WASM_PRICE_FN_CONSTS(
                         (check_transaction_authorization, (int, int, int, int, int, int, int)                  )
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
                         (eosio_assert,         (void*, int, int)      )
                         (eosio_assert_message, (void*, int, int, int) )
                         (eosio_assert_code,    (void*, int, int64_t)  )
                         (eosio_exit,           (void*, int)           )
                         );
    
    // action_api
    WASM_PRICE_FN_CONSTS(
                         (read_action_data,       (int, int, int)  )
                         (action_data_size,       (int)          )
                         (current_receiver,   (int64_t)          )
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
                         (prints_l,              (void*, int, int) )
                         (printi,                (void*, int64_t)  )
                         (printui,               (void*, int64_t)  )
                         (printi128,             (void*, int)      )
                         (printui128,            (void*, int)      )
                         (printsf,               (void*, float)    )
                         (printdf,               (void*, double)   )
                         (printqf,               (void*, int)      )
                         (printn,                (void*, int64_t)  )
                         (printhex,              (void*, int, int) )
                         );
    
    // context_free_transaction_api
    WASM_PRICE_FN_CONSTS(
                         (read_transaction,       (int, int, int)            )
                         (transaction_size,       (int)                    )
                         (expiration,             (int)                    )
                         (tapos_block_prefix,     (int)                    )
                         (tapos_block_num,        (int)                    )
                         (get_action,             (int, int, int, int, int) )
                         );
    
    // transaction_api
    WASM_PRICE_FN_CONSTS(
                         (send_inline,               (void*, int, int)               )
                         (send_context_free_inline,  (void*, int, int)               )
                         (send_deferred,             (void*, int, int64_t, int, int, int32_t) )
                         (cancel_deferred,           (int, int)                     )
                         );
    
    // context_free_api
    WASM_PRICE_FN_CONSTS(
                         (get_context_free_data, (int, int, int, int) )
                         );
    
    // memory_api
    WASM_PRICE_FN_CONSTS(
                         (memcpy,                 (int, int, int, int)  )
                         (memmove,                (int, int, int, int)  )
                         (memcmp,                 (int, int, int, int)  )
                         (memset,                 (int, int, int, int)  )
                         );
    
    // softfloat_api
    WASM_PRICE_FN_CONSTS(
                         (_eosio_f32_add,       (float, float, float)    )
                         (_eosio_f32_sub,       (float, float, float)    )
                         (_eosio_f32_mul,       (float, float, float)    )
                         (_eosio_f32_div,       (float, float, float)    )
                         (_eosio_f32_min,       (float, float, float)    )
                         (_eosio_f32_max,       (float, float, float)    )
                         (_eosio_f32_copysign,  (float, float, float)    )
                         (_eosio_f32_abs,       (float, float)           )
                         (_eosio_f32_neg,       (float, float)           )
                         (_eosio_f32_sqrt,      (float, float)           )
                         (_eosio_f32_ceil,      (float, float)           )
                         (_eosio_f32_floor,     (float, float)           )
                         (_eosio_f32_trunc,     (float, float)           )
                         (_eosio_f32_nearest,   (float, float)           )
                         (_eosio_f32_eq,        (int, float, float)      )
                         (_eosio_f32_ne,        (int, float, float)      )
                         (_eosio_f32_lt,        (int, float, float)      )
                         (_eosio_f32_le,        (int, float, float)      )
                         (_eosio_f32_gt,        (int, float, float)      )
                         (_eosio_f32_ge,        (int, float, float)      )
                         (_eosio_f64_add,       (double, double, double) )
                         (_eosio_f64_sub,       (double, double, double) )
                         (_eosio_f64_mul,       (double, double, double) )
                         (_eosio_f64_div,       (double, double, double) )
                         (_eosio_f64_min,       (double, double, double) )
                         (_eosio_f64_max,       (double, double, double) )
                         (_eosio_f64_copysign,  (double, double, double) )
                         (_eosio_f64_abs,       (double, double)         )
                         (_eosio_f64_neg,       (double, double)         )
                         (_eosio_f64_sqrt,      (double, double)         )
                         (_eosio_f64_ceil,      (double, double)         )
                         (_eosio_f64_floor,     (double, double)         )
                         (_eosio_f64_trunc,     (double, double)         )
                         (_eosio_f64_nearest,   (double, double)         )
                         (_eosio_f64_eq,        (int, double, double)    )
                         (_eosio_f64_ne,        (int, double, double)    )
                         (_eosio_f64_lt,        (int, double, double)    )
                         (_eosio_f64_le,        (int, double, double)    )
                         (_eosio_f64_gt,        (int, double, double)    )
                         (_eosio_f64_ge,        (int, double, double)    )
                         (_eosio_f32_promote,    (double, float)         )
                         (_eosio_f64_demote,     (float, double)         )
                         (_eosio_f32_trunc_i32s, (int, float)            )
                         (_eosio_f64_trunc_i32s, (int, double)           )
                         (_eosio_f32_trunc_i32u, (int, float)            )
                         (_eosio_f64_trunc_i32u, (int, double)           )
                         (_eosio_f32_trunc_i64s, (int64_t, float)        )
                         (_eosio_f64_trunc_i64s, (int64_t, double)       )
                         (_eosio_f32_trunc_i64u, (int64_t, float)        )
                         (_eosio_f64_trunc_i64u, (int64_t, double)       )
                         (_eosio_i32_to_f32,     (float, int32_t)        )
                         (_eosio_i64_to_f32,     (float, int64_t)        )
                         (_eosio_ui32_to_f32,    (float, int32_t)        )
                         (_eosio_ui64_to_f32,    (float, int64_t)        )
                         (_eosio_i32_to_f64,     (double, int32_t)       )
                         (_eosio_i64_to_f64,     (double, int64_t)       )
                         (_eosio_ui32_to_f64,    (double, int32_t)       )
                         (_eosio_ui64_to_f64,    (double, int64_t)       )
                         );
    
    
}}} // eosio::chain::wasm_price
