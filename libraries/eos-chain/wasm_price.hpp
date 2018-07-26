#ifndef __WASM_PRICE_HPP__
#define __WASM_PRICE_HPP__

#include <type_traits>
#include <boost/preprocessor/seq/for_each.hpp>
#include <eosio/chain/apply_context.hpp>
#include <wasm/wasm.h>

namespace eosio { namespace chain { namespace wasm_price {

    template <typename T>
    struct arg_type {
        template <typename C> static C test( typename std::enable_if<!std::is_void<C>::value, C>::type* );
        template <typename> static void* test(...);
        
        using type = decltype(test<T>(0));
    };

#define WASM_PRICE_FN_DECL(NAME, RET_TYPE)              uint64_t NAME (apply_context *context, typename arg_type<RET_TYPE>::type r)
#define WASM_PRICE_FN_DECLS_(R, D, E)                   WASM_PRICE_FN_DECL E;
#define WASM_PRICE_FN_DECLS(S)                          BOOST_PP_SEQ_FOR_EACH(WASM_PRICE_FN_DECLS_, _, S)

#define DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(IDX) \
    ((db_##IDX##_store,          int))\
    ((db_##IDX##_remove,         void))\
    ((db_##IDX##_update,         void))\
    ((db_##IDX##_find_primary,   int))\
    ((db_##IDX##_find_secondary, int))\
    ((db_##IDX##_lowerbound,     int))\
    ((db_##IDX##_upperbound,     int))\
    ((db_##IDX##_end,            int))\
    ((db_##IDX##_next,           int))\
    ((db_##IDX##_previous,       int))
    
#define DECL_DB_SECONDARY_INDEX_METHODS_ARRAY(IDX) \
    ((db_##IDX##_store,          int))\
    ((db_##IDX##_remove,         void))\
    ((db_##IDX##_update,         void))\
    ((db_##IDX##_find_primary,   int))\
    ((db_##IDX##_find_secondary, int))\
    ((db_##IDX##_lowerbound,     int))\
    ((db_##IDX##_upperbound,     int))\
    ((db_##IDX##_end,            int))\
    ((db_##IDX##_next,           int))\
    ((db_##IDX##_previous,       int))

    // call_depth_api
    WASM_PRICE_FN_DECLS(
                        ((call_depth_assert,  void))
                        );
    
    // compiler_builtins
    WASM_PRICE_FN_DECLS(
                        ((__ashlti3,     void))
                        ((__ashrti3,     void))
                        ((__lshlti3,     void))
                        ((__lshrti3,     void))
                        ((__divti3,      void))
                        ((__udivti3,     void))
                        ((__modti3,      void))
                        ((__umodti3,     void))
                        ((__multi3,      void))
                        ((__addtf3,      void))
                        ((__subtf3,      void))
                        ((__multf3,      void))
                        ((__divtf3,      void))
                        ((__eqtf2,       int))
                        ((__netf2,       int))
                        ((__getf2,       int))
                        ((__gttf2,       int))
                        ((__lttf2,       int))
                        ((__letf2,       int))
                        ((__cmptf2,      int))
                        ((__unordtf2,    int))
                        ((__negtf2,      void))
                        ((__floatsitf,   void))
                        ((__floatunsitf, void))
                        ((__floatditf,   void))
                        ((__floatunditf, void))
                        ((__floattidf,   double))
                        ((__floatuntidf, double))
                        ((__floatsidf,   double))
                        ((__extendsftf2, void))
                        ((__extenddftf2, void))
                        ((__fixtfti,     void))
                        ((__fixtfdi,     int64_t))
                        ((__fixtfsi,     int))
                        ((__fixunstfti,  void))
                        ((__fixunstfdi,  int64_t))
                        ((__fixunstfsi,  int))
                        ((__fixsfti,     void))
                        ((__fixdfti,     void))
                        ((__fixunssfti,  void))
                        ((__fixunsdfti,  void))
                        ((__trunctfdf2,  double))
                        ((__trunctfsf2,  float))
                        );
    
    // privileged_api
    WASM_PRICE_FN_DECLS(
                        ((is_feature_active,                int))
                        ((activate_feature,                 void))
                        ((get_resource_limits,              void))
                        ((set_resource_limits,              void))
                        ((set_proposed_producers,           int64_t))
                        ((get_blockchain_parameters_packed, int))
                        ((set_blockchain_parameters_packed, void))
                        ((is_privileged,                    int))
                        ((set_privileged,                   void))
                        );
    
    // transaction_context
    WASM_PRICE_FN_DECLS(
                        ((checktime,      void))
                        );
    
    // producer_api
    WASM_PRICE_FN_DECLS(
                        ((get_active_producers,      int))
                        );
    
    // database_api
    WASM_PRICE_FN_DECLS(
                        ((db_store_i64,        int))
                        ((db_update_i64,       void))
                        ((db_remove_i64,       void))
                        ((db_get_i64,          int))
                        ((db_next_i64,         int))
                        ((db_previous_i64,     int))
                        ((db_find_i64,         int))
                        ((db_lowerbound_i64,   int))
                        ((db_upperbound_i64,   int))
                        ((db_end_i64,          int))
                        
                        DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx64)
                        DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx128)
                        DECL_DB_SECONDARY_INDEX_METHODS_ARRAY(idx256)
                        DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx_double)
                        DECL_DB_SECONDARY_INDEX_METHODS_SIMPLE(idx_long_double)
                        );
    
    // crypto_api
    WASM_PRICE_FN_DECLS(
                        ((assert_recover_key,     void))
                        ((recover_key,            int))
                        ((assert_sha256,          void))
                        ((assert_sha1,            void))
                        ((assert_sha512,          void))
                        ((assert_ripemd160,       void))
                        ((sha1,                   void))
                        ((sha256,                 void))
                        ((sha512,                 void))
                        ((ripemd160,              void))
                        );
    
    // permission_api
    WASM_PRICE_FN_DECLS(
                        ((check_transaction_authorization, int))
                        ((check_permission_authorization,  int))
                        ((get_permission_last_used,        int64_t))
                        ((get_account_creation_time,       int64_t))
                        );
    
    // system_api
    WASM_PRICE_FN_DECLS(
                        ((current_time, int64_t))
                        ((publication_time,   int64_t))
                        );
    
    // context_free_system_api
    WASM_PRICE_FN_DECLS(
                        ((abort,                void))
                        ((eosio_assert,         void))
                        ((eosio_assert_message, void))
                        ((eosio_assert_code,    void))
                        ((eosio_exit,           void))
                        );
    
    // action_api
    WASM_PRICE_FN_DECLS(
                        ((read_action_data,       int))
                        ((action_data_size,       int))
                        ((current_receiver,   int64_t))
                        );
    
    // authorization_api
    WASM_PRICE_FN_DECLS(
                        ((require_recipient,    void))
                        ((require_auth,         void))
                        ((require_auth2,        void))
                        ((has_auth,              int))
                        ((is_account,            int))
                        );
    
    // console_api
    WASM_PRICE_FN_DECLS(
                        ((prints,                void))
                        ((prints_l,              void))
                        ((printi,                void))
                        ((printui,               void))
                        ((printi128,             void))
                        ((printui128,            void))
                        ((printsf,               void))
                        ((printdf,               void))
                        ((printqf,               void))
                        ((printn,                void))
                        ((printhex,              void))
                        );
    
    // context_free_transaction_api
    WASM_PRICE_FN_DECLS(
                        ((read_transaction,       int))
                        ((transaction_size,       int))
                        ((expiration,             int))
                        ((tapos_block_prefix,     int))
                        ((tapos_block_num,        int))
                        ((get_action,             int))
                        );
    
    // transaction_api
    WASM_PRICE_FN_DECLS(
                        ((send_inline,               void))
                        ((send_context_free_inline,  void))
                        ((send_deferred,             void))
                        ((cancel_deferred,           int))
                        );
    
    // context_free_api
    WASM_PRICE_FN_DECLS(
                        ((get_context_free_data, int))
                        );
    
    // memory_api
    WASM_PRICE_FN_DECLS(
                        ((memcpy,                 int))
                        ((memmove,                int))
                        ((memcmp,                 int))
                        ((memset,                 int))
                        );
    
    // softfloat_api
    WASM_PRICE_FN_DECLS(
                        ((_eosio_f32_add,       float))
                        ((_eosio_f32_sub,       float))
                        ((_eosio_f32_mul,       float))
                        ((_eosio_f32_div,       float))
                        ((_eosio_f32_min,       float))
                        ((_eosio_f32_max,       float))
                        ((_eosio_f32_copysign,  float))
                        ((_eosio_f32_abs,       float))
                        ((_eosio_f32_neg,       float))
                        ((_eosio_f32_sqrt,      float))
                        ((_eosio_f32_ceil,      float))
                        ((_eosio_f32_floor,     float))
                        ((_eosio_f32_trunc,     float))
                        ((_eosio_f32_nearest,   float))
                        ((_eosio_f32_eq,        int))
                        ((_eosio_f32_ne,        int))
                        ((_eosio_f32_lt,        int))
                        ((_eosio_f32_le,        int))
                        ((_eosio_f32_gt,        int))
                        ((_eosio_f32_ge,        int))
                        ((_eosio_f64_add,       double))
                        ((_eosio_f64_sub,       double))
                        ((_eosio_f64_mul,       double))
                        ((_eosio_f64_div,       double))
                        ((_eosio_f64_min,       double))
                        ((_eosio_f64_max,       double))
                        ((_eosio_f64_copysign,  double))
                        ((_eosio_f64_abs,       double))
                        ((_eosio_f64_neg,       double))
                        ((_eosio_f64_sqrt,      double))
                        ((_eosio_f64_ceil,      double))
                        ((_eosio_f64_floor,     double))
                        ((_eosio_f64_trunc,     double))
                        ((_eosio_f64_nearest,   double))
                        ((_eosio_f64_eq,        int))
                        ((_eosio_f64_ne,        int))
                        ((_eosio_f64_lt,        int))
                        ((_eosio_f64_le,        int))
                        ((_eosio_f64_gt,        int))
                        ((_eosio_f64_ge,        int))
                        ((_eosio_f32_promote,    double))
                        ((_eosio_f64_demote,     float))
                        ((_eosio_f32_trunc_i32s, int))
                        ((_eosio_f64_trunc_i32s, int))
                        ((_eosio_f32_trunc_i32u, int))
                        ((_eosio_f64_trunc_i32u, int))
                        ((_eosio_f32_trunc_i64s, int64_t))
                        ((_eosio_f64_trunc_i64s, int64_t))
                        ((_eosio_f32_trunc_i64u, int64_t))
                        ((_eosio_f64_trunc_i64u, int64_t))
                        ((_eosio_i32_to_f32,     float))
                        ((_eosio_i64_to_f32,     float))
                        ((_eosio_ui32_to_f32,    float))
                        ((_eosio_ui64_to_f32,    float))
                        ((_eosio_i32_to_f64,     double))
                        ((_eosio_i64_to_f64,     double))
                        ((_eosio_ui32_to_f64,    double))
                        ((_eosio_ui64_to_f64,    double))
                        );


//
// prices of basic intrinsics
//
#define WASM_PRICE_BlockId         0
#define WASM_PRICE_IfId            0
#define WASM_PRICE_LoopId          0
#define WASM_PRICE_BreakId         0
#define WASM_PRICE_SwitchId        0
#define WASM_PRICE_CallId          0
#define WASM_PRICE_CallImportId    0
#define WASM_PRICE_CallIndirectId  0
#define WASM_PRICE_GetLocalId      0
#define WASM_PRICE_SetLocalId      0
#define WASM_PRICE_GetGlobalId     0
#define WASM_PRICE_SetGlobalId     0
#define WASM_PRICE_LoadId          0
#define WASM_PRICE_StoreId         0
#define WASM_PRICE_ConstId         0
#define WASM_PRICE_UnaryId         0
#define WASM_PRICE_BinaryId        0
#define WASM_PRICE_SelectId        0
#define WASM_PRICE_DropId          0
#define WASM_PRICE_ReturnId        0
#define WASM_PRICE_HostId          0
#define WASM_PRICE_NopId           0
#define WASM_PRICE_UnreachableId   0

}}} // eosio::chain::wasm_price

#define _WASM_PRICE_FN_OF(N,...)     ::eosio::chain::wasm_price::N
#define WITH_PRICE(...)             ((__VA_ARGS__), _WASM_PRICE_FN_OF(__VA_ARGS__))

#endif
