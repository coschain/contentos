#pragma once 
#include <cosiolib/varint.hpp>
#include <cosiolib/serialize.hpp>

namespace cosio {
   struct public_key {
      unsigned_int        type;
      std::array<char,33> data;

      friend bool operator == ( const public_key& a, const public_key& b ) {
        return std::tie(a.type,a.data) == std::tie(b.type,b.data);
      }
      friend bool operator != ( const public_key& a, const public_key& b ) {
        return std::tie(a.type,a.data) != std::tie(b.type,b.data);
      }
      EOSLIB_SERIALIZE( public_key, (type)(data) )
   };

      struct public_key_2 {
      std::array<char,33> data;

      friend bool operator == ( const public_key_2& a, const public_key_2& b ) {
        return a.data == b.data;
      }
      friend bool operator != ( const public_key_2& a, const public_key_2& b ) {
        return a.data != b.data;
      }
      friend bool operator < ( const public_key_2& a, const public_key_2& b ) {
        return a.data < b.data;
      }
      EOSLIB_SERIALIZE( public_key_2, (data) )
   };
}
