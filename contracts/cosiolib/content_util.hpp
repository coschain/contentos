/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once

#include <cosiolib/types.h>
#include <cosiolib/content.h>
#include <vector>
#include <string>
#include <cosiolib/time.hpp>
#include <cosiolib/asset.hpp>
#include <cosiolib/datastream.hpp>
#include <cosiolib/serialize.hpp>
#include <cosiolib/public_key.hpp>

namespace eosio {

    typedef std::array<unsigned char,65> compact_signature;

using std::vector;
using std::string;
using eosio::asset;
using share_type = int64_t;
using account_id_type = int64_t;
using account_name_type = std::string;
using public_key_type = eosio::public_key_2;
using string16 = std::string;
using string8 = eosio::name;

using shuffled_witness_array_type = std::array<eosio::name, 21>;

using uint32 = uint32_t;
using uint64 = uint64_t;
using int32 = int32_t;
using int64 = int64_t;
using id_type = int64_t;
using int16 = int16_t;
using uint16 = uint16_t;
using uint128 = uint128_t;
using int128 = int128_t;
using uint8 = uint8_t;
using int8 = int8_t;
using signature_type = compact_signature;
using float64 = double;
using variant_object = int64_t;
//using name = string;

#define DEFAULT_OUT_BUFFER_LENGTH 10*1024


template<typename T> struct cls_ret_type;
template<typename R, typename Cls, typename ... Args >
struct cls_ret_type<R (Cls::*)(Args...)>{
   typedef R RetType;
};

#define RET_TYPE(XXXX) cls_ret_type<decltype(&XXXX)>::RetType

#define STUB_API(RetType, params )  \
        datastream<size_t> dss; \
        dss << api_name() << string( __FUNCTION__ ) params;  \
        std::vector<char>  vec_in(dss.tellp()); \
        datastream<const char*> ds(vec_in.data(), vec_in.size()); \
        ds << api_name() << string( __FUNCTION__ ) params; \
        std::vector<char>  vec_out(DEFAULT_OUT_BUFFER_LENGTH);  \
        int ret_length = on_content_call( vec_in.data(), vec_in.size(), vec_out.data(), DEFAULT_OUT_BUFFER_LENGTH); \
        if ( ret_length > DEFAULT_OUT_BUFFER_LENGTH ){  \
            vec_out.resize(ret_length); \
            ret_length = on_content_call( vec_in.data(), vec_in.size(), vec_out.data(), ret_length);  \
        } \
        return unpack<RetType>(vec_out.data(), ret_length);  \

}
