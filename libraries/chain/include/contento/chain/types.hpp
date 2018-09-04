/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <contento/chain/contento_object_types.hpp>
#include <contento/protocol/types.hpp>

#include <fc/container/flat_fwd.hpp>
#include <fc/io/varint.hpp>
#include <fc/io/enum_type.hpp>
#include <fc/crypto/sha224.hpp>
#include <fc/optional.hpp>
#include <fc/safe.hpp>
#include <fc/container/flat.hpp>
#include <fc/string.hpp>
#include <fc/reflect/variant.hpp>
#include <fc/io/raw.hpp>
#include <fc/static_variant.hpp>
#include <fc/smart_ref_fwd.hpp>
#include <fc/crypto/ripemd160.hpp>
//#include <fc/fixed_string.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/reflect/variant.hpp>

#include <memory>
#include <vector>
#include <deque>
#include <cstdint>

#define OBJECT_CTOR1(NAME) \
    NAME() = delete; \
    public: \
    template<typename Constructor, typename Allocator> \
    NAME(Constructor&& c, chainbase::allocator<Allocator>) \
    { c(*this); }
#define OBJECT_CTOR2_MACRO(x, y, field) ,field(a)
#define OBJECT_CTOR2(NAME, FIELDS) \
    NAME() = delete; \
    public: \
    template<typename Constructor, typename Allocator> \
    NAME(Constructor&& c, chainbase::allocator<Allocator> a) \
    : id(0) BOOST_PP_SEQ_FOR_EACH(OBJECT_CTOR2_MACRO, _, FIELDS) \
    { c(*this); }
#define OBJECT_CTOR(...) BOOST_PP_OVERLOAD(OBJECT_CTOR, __VA_ARGS__)(__VA_ARGS__)

#define _V(n, v)  fc::mutable_variant_object(n, v)

namespace contento { namespace chain {
   using                               std::map;
   using                               std::vector;
   using                               std::unordered_map;
   using                               std::string;
   using                               std::deque;
   using                               std::shared_ptr;
   using                               std::weak_ptr;
   using                               std::unique_ptr;
   using                               std::set;
   using                               std::pair;
   using                               std::make_pair;
   using                               std::enable_shared_from_this;
   using                               std::tie;
   using                               std::move;
   using                               std::forward;
   using                               std::to_string;
   using                               std::all_of;

   using                               fc::path;
   using                               fc::smart_ref;
   using                               fc::variant_object;
   using                               fc::variant;
   using                               fc::enum_type;
   using                               fc::optional;
   using                               fc::unsigned_int;
   using                               fc::signed_int;
   using                               fc::time_point_sec;
   using                               fc::time_point;
   using                               fc::safe;
   using                               fc::flat_map;
   using                               fc::flat_set;
   using                               fc::static_variant;
   using                               fc::ecc::range_proof_type;
   using                               fc::ecc::range_proof_info;
   using                               fc::ecc::commitment_type;

   //using public_key_type  = fc::ecc::public_key;
   //using private_key_type = fc::ecc::private_key;
   //using signature_type   = fc::ecc::compact_signature;

   struct void_t{};

   using chainbase::allocator;
   //using shared_string = boost::interprocess::basic_string<char, std::char_traits<char>, allocator<char>>;
   template<typename T>
   using shared_vector = boost::interprocess::vector<T, allocator<T>>;
   template<typename T>
   using shared_set = boost::interprocess::set<T, std::less<T>, allocator<T>>;
   using name             = protocol::name;
   using namex            = protocol::namex;
   using action_name      = protocol::name;
   using scope_name       = protocol::namex;
   using account_name     = protocol::namex;
   using table_name       = protocol::name;


   using block_id_type       = protocol::block_id_type;
   using checksum_type       = protocol::checksum_type;
   using checksum256_type    = fc::sha256;
   using checksum512_type    = fc::sha512;
   using checksum160_type    = fc::ripemd160;
   using transaction_id_type = protocol::transaction_id_type;
   using digest_type         = protocol::digest_type;
   using weight_type         = protocol::weight_type;
   using block_num_type      = uint32_t;
   //using share_type          = int64_t;
   using int128_t            = __int128;
   //using uint128_t           = unsigned __int128;
   using bytes               = protocol::bytes;


   /**
    *  Extentions are prefixed with type and are a buffer that can be
    *  interpreted by code that is aware and ignored by unaware code.
    */
   typedef vector<std::pair<uint16_t,vector<char>>> extensions_type;


} }  // contento::chain

FC_REFLECT( contento::chain::void_t, )
