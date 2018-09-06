#ifndef __WASM_PRICE_HPP__
#define __WASM_PRICE_HPP__

#include <boost/preprocessor.hpp>
#include <contento/chain/apply_context.hpp>

namespace contento { namespace chain { namespace wasm_price {
    
    using apply_context = contento::chain::apply_context;
    
#define WASM_PRICE_FN_DECL(NAME, SIG,...)           uint64_t NAME BOOST_PP_TUPLE_PUSH_FRONT(SIG, apply_context*)
#define WASM_PRICE_FN_ADD_PAREN1(...)               ((__VA_ARGS__)) WASM_PRICE_FN_ADD_PAREN2
#define WASM_PRICE_FN_ADD_PAREN2(...)               ((__VA_ARGS__)) WASM_PRICE_FN_ADD_PAREN1
#define WASM_PRICE_FN_ADD_PAREN1_END
#define WASM_PRICE_FN_ADD_PAREN2_END
#define WASM_PRICE_FN_WRAP_SEQ(SEQ)                 BOOST_PP_CAT(WASM_PRICE_FN_ADD_PAREN1 SEQ, _END)
#define _WASM_PRICE_FN_DECLS(R, D, E)               WASM_PRICE_FN_DECL E;
#define WASM_PRICE_FN_DECLS(SEQ)                    BOOST_PP_SEQ_FOR_EACH(_WASM_PRICE_FN_DECLS, _, WASM_PRICE_FN_WRAP_SEQ(SEQ))
    
    // call_depth_api
    WASM_PRICE_FN_DECLS(
                        (call_depth_assert,  (void*)               )
                        );
    
    // compiler_builtins
    WASM_PRICE_FN_DECLS(
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
    WASM_PRICE_FN_DECLS(
                        (is_feature_active,                (int, int64_t)                          )
                        (activate_feature,                 (void*, int64_t)                         )
                        // (get_resource_limits,              (void*, int64_t,int,int,int)             )
                        // (set_resource_limits,              (void*, int,int64_t,int64_t,int64_t) )
                        // (set_proposed_producers,           (int64_t, int,int)                      )
                        (get_blockchain_parameters_packed, (int, int, int)                         )
                        (set_blockchain_parameters_packed, (void*, int,int)                         )
                        (is_privileged,                    (int, int)                          )
                        (set_privileged,                   (void*, int, int)                    )
                        );
    
    // transaction_context
    WASM_PRICE_FN_DECLS(
                        (checktime,      (void*))
                        );
    
    // producer_api
    WASM_PRICE_FN_DECLS(
                        (get_active_producers,      (int, int, int) )
                        );

    WASM_PRICE_FN_DECLS(
                         (get_contract_balance_internal,      (void*, int) )
                         (transfer,                  (void*, int, int))
                         (get_value_internal,                 (int64_t))
                         (accept_pay,            (void*))
                         );
    
#define DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(IDX) \
    (db_##IDX##_store,          (int, int,int64_t,int,int64_t,int))\
    (db_##IDX##_remove,         (void*, int))\
    (db_##IDX##_update,         (void*, int,int,int))\
    (db_##IDX##_find_primary,   (int, int,int,int64_t,int,int64_t))\
    (db_##IDX##_find_secondary, (int, int,int,int64_t,int,int))\
    (db_##IDX##_lowerbound,     (int, int,int,int64_t,int,int))\
    (db_##IDX##_upperbound,     (int, int,int,int64_t,int,int))\
    (db_##IDX##_end,            (int, int,int,int64_t))\
    (db_##IDX##_next,           (int, int, int))\
    (db_##IDX##_previous,       (int, int, int))
    
#define DECL_DB_SECONDARY_INDEX_METHODS_ARRAY(IDX) \
    (db_##IDX##_store,          (int, int,int64_t,int,int64_t,int,int))\
    (db_##IDX##_remove,         (void*, int))\
    (db_##IDX##_update,         (void*, int,int,int,int))\
    (db_##IDX##_find_primary,   (int, int,int,int64_t,int,int,int64_t))\
    (db_##IDX##_find_secondary, (int, int,int,int64_t,int,int,int))\
    (db_##IDX##_lowerbound,     (int, int,int,int64_t,int,int,int))\
    (db_##IDX##_upperbound,     (int, int,int,int64_t,int,int,int))\
    (db_##IDX##_end,            (int, int,int,int64_t))\
    (db_##IDX##_next,           (int, int, int))\
    (db_##IDX##_previous,       (int, int, int))
    
    // database_api
    WASM_PRICE_FN_DECLS(
                        (db_store_i64,        (int, int,int64_t,int,int64_t,int,int))
                        (db_update_i64,       (void*, int,int,int,int))
                        (db_remove_i64,       (void*, int))
                        (db_get_i64,          (int, int, int, int))
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
    WASM_PRICE_FN_DECLS(
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
    WASM_PRICE_FN_DECLS(
                        (check_transaction_authorization, (int, int, int, int, int, int, int)                  )
                        (check_permission_authorization,  (int, int64_t, int64_t, int, int, int, int, int64_t) )
                        (get_permission_last_used,        (int64_t, int64_t, int64_t) )
                        (get_account_creation_time,       (int64_t, int64_t) )
                        );
    
    // system_api
    WASM_PRICE_FN_DECLS(
                        (current_time, (int64_t)       )
                        (publication_time,   (int64_t) )
                        );
    
    // context_free_system_api
    WASM_PRICE_FN_DECLS(
                        (abort,                (void*)              )
                        (contento_assert,         (void*, int, int)      )
                        (contento_assert_message, (void*, int, int, int) )
                        (contento_assert_code,    (void*, int, int64_t)  )
                        (contento_exit,           (void*, int)           )
                        );
    
    // action_api
    WASM_PRICE_FN_DECLS(
                        (read_action_data,       (int, int, int)  )
                        (action_data_size,       (int)            )
                        // (current_receiver,       (int)        )
                        (current_receiver,           (void*, int))
                        (current_contract_name,            (void*, int))
                        );
    
    // authorization_api
    WASM_PRICE_FN_DECLS(
                        (require_recipient,     (void*, int64_t)          )
                        (require_auth,          (void*)          )
                        (require_auth2,         (void*, int64_t, int64_t) )
                        (has_auth,              (int, int64_t)           )
                        (is_account,            (int, int64_t)           )
                        );
    
    // console_api
    WASM_PRICE_FN_DECLS(
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
    WASM_PRICE_FN_DECLS(
                        (read_transaction,       (int, int, int)            )
                        (transaction_size,       (int)                    )
                        (expiration,             (int)                    )
                        (tapos_block_prefix,     (int)                    )
                        (tapos_block_num,        (int)                    )
                        (get_action,             (int, int, int, int, int) )
                        );
    
    // transaction_api
    WASM_PRICE_FN_DECLS(
                        (send_inline,               (void*, int, int)               )
                        (send_context_free_inline,  (void*, int, int)               )
                        (send_deferred,             (void*, int, int, int, int, int32_t) )
                        (cancel_deferred,           (int, int)                     )
                        );
    
    // content_api
    WASM_PRICE_FN_DECLS(
                        (on_content_call,           (int,int, int, int, int)      )
                        (excute_operation,          (int,int, int)         )
                        );
    
    // context_free_api
    WASM_PRICE_FN_DECLS(
                        (get_context_free_data, (int, int, int, int) )
                        );
    
    // memory_api
    WASM_PRICE_FN_DECLS(
                        (memcpy,                 (int, int, int, int)  )
                        (memmove,                (int, int, int, int)  )
                        (memcmp,                 (int, int, int, int)  )
                        (memset,                 (int, int, int, int)  )
                        );
    
    // softfloat_api
    WASM_PRICE_FN_DECLS(
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

//
// price of unexpected behaviors such as Unreachable intrinsic and/or assertions.
// this price is useless coz prices are given after return of intrinsics,
// but unexpected behaviors raise exceptions.
//
#define WASM_PRICE_UNEXPECTED      100000

//
// prices of basic intrinsics
//
#define WASM_PRICE_BlockId         29
#define WASM_PRICE_IfId            6
#define WASM_PRICE_LoopId          23
#define WASM_PRICE_BreakId         4
#define WASM_PRICE_SwitchId        12
#define WASM_PRICE_CallId          104
#define WASM_PRICE_CallImportId    30
#define WASM_PRICE_CallIndirectId  430
#define WASM_PRICE_GetLocalId      1
#define WASM_PRICE_SetLocalId      4
#define WASM_PRICE_GetGlobalId     8
#define WASM_PRICE_SetGlobalId     8
#define WASM_PRICE_LoadId          7
#define WASM_PRICE_StoreId         10
#define WASM_PRICE_ConstId         1
#define WASM_PRICE_UnaryId         4
#define WASM_PRICE_BinaryId        8
#define WASM_PRICE_SelectId        10
#define WASM_PRICE_DropId          5
#define WASM_PRICE_ReturnId        4
#define WASM_PRICE_HostId          3
#define WASM_PRICE_NopId           1
#define WASM_PRICE_UnreachableId   WASM_PRICE_UNEXPECTED

}}} // contento::chain::wasm_price

#define _WASM_PRICE_FN_OF(N,...)     ::contento::chain::wasm_price::N
#define WITH_PRICE(...)             ((__VA_ARGS__), _WASM_PRICE_FN_OF(__VA_ARGS__))

#endif
