#pragma once
//#include <string>
#include <fc/reflect/reflect.hpp>
#include <iosfwd>
#include <fc/variant.hpp>
#include <boost/algorithm/string.hpp>
#include <fc/exception/exception.hpp>
#include <fc/uint128.hpp>

namespace contento { namespace protocol {
   
   static const uint64_t char_to_symbol( char c ) {
      if( c >= 'a' && c <= 'z' )
         return (c - 'a') + 6;
      if( c >= '1' && c <= '5' )
         return (c - '1') + 1;
      return 0;
   }
   
   // Each char of the string is encoded into 5-bit chunk and left-shifted
   // to its 5-bit slot starting with the highest slot for the first char.
   // The 13th char, if str is long enough, is encoded into 4-bit chunk
   // and placed in the lowest 4 bits. 64 = 12 * 5 + 4
   static const uint64_t string_to_name( const char* str )
   {
      uint64_t name = 0;
      int i = 0;
      for ( ; str[i] && i < 12; ++i) {
         // NOTE: char_to_symbol() returns char type, and without this explicit
         // expansion to uint64 type, the compilation fails at the point of usage
         // of string_to_name(), where the usage requires constant (compile time) expression.
         name |= (char_to_symbol(str[i]) & 0x1f) << (64 - 5 * (i + 1));
      }
      
      // The for-loop encoded up to 60 high bits into uint64 'name' variable,
      // if (strlen(str) > 12) then encode str[12] into the low (remaining)
      // 4 bits of 'name'
      if (i == 12)
         name |= char_to_symbol(str[12]) & 0x0F;
      return name;
   }
   
   static const fc::uint128_t string_to_namex( const char* str )
   {
      
      uint len = 0;
      while(str[len]) ++len;
      
      fc::uint128_t name = 0;
      
      if (len <= 8) {
         for( uint i = 0; i < len; ++i) {
            name.lo |= (uint64_t(str[i]) << (8 * i));
         }
      } else if ( len <= 16 ) {
         for( uint i = 0; i < 8; ++i) {
            name.lo |= (uint64_t(str[i]) << (8 * i));
         }
         for( uint i = 8; i < len; ++i) {
            name.hi |= (uint64_t(str[i]) << (8 * i));
         }
      }
      
      return name;
   }
   
#define N(X) contento::protocol::string_to_name(#X)
   
   struct name {
      name(){}
      name( const char* str )   { set(str);           }
      name( const std::string& str ) { set( str.c_str() ); }
      name( const name& n ) { value = n.value; }
      name( const uint64_t& v ):value(v) {}
      
      operator std::string()const;
      
      bool empty()const { return 0 == value; }
      bool good()const  { return !empty();   }
      
      uint32_t size() const {
         return value == 0 ? 0 : 13;
      }
      
      uint32_t length() const {
         return value == 0 ? 0 : 13;
      }
      
      void set( const char* str );
      
      name& operator=( uint64_t v ) {
         value = v;
         return *this;
      }
      
      name& operator=( const std::string& n ) {
         value = name(n).value;
         return *this;
      }
      name& operator=( const char* n ) {
         value = name(n).value;
         return *this;
      }
      
      name& operator=( const name& n ) {
         value = n.value;
         return *this;
      }
      
      friend std::string operator + ( const name& a, const std::string& b ) {
         return std::string(a) + b;
      }
      friend std::string operator + ( const std::string& a, const name& b ) {
         return a + std::string(b);
      }
      
      //   friend std::string operator + ( const name& a, const name& b ) {
      //     return std::string(a) + std::string(b);
      //   }
      
      friend std::ostream& operator << ( std::ostream& out, const name& n ) {
         return out << std::string(n);
      }
      
      friend bool operator < ( const name& a, const name& b ) { return a.value < b.value; }
      friend bool operator <= ( const name& a, const name& b ) { return a.value <= b.value; }
      friend bool operator > ( const name& a, const name& b ) { return a.value > b.value; }
      friend bool operator >=( const name& a, const name& b ) { return a.value >= b.value; }
      friend bool operator == ( const name& a, const name& b ) { return a.value == b.value; }
      
      friend bool operator == ( const name& a, uint64_t b ) { return a.value == b; }
      friend bool operator != ( const name& a, uint64_t b ) { return a.value != b; }
      
      friend bool operator != ( const name& a, const name& b ) { return a.value != b.value; }
      
      //   operator bool()const            { return value; }
      uint64_t to_uint64_t() const        { return value; }
      //   operator unsigned __int128()const       { return value; }
      
      uint64_t value = 0;
   };
   
   
   inline std::vector<name> sort_names( std::vector<name>&& names ) {
      fc::deduplicate(names);
      return names;
   }
   
#define N16(X) contento::protocol::string_to_namex(#X)
   
   struct namex {
      namex(){}
      namex( const char* str )   { set(str);           }
      namex( const std::string& str ) { set( str.c_str() ); }
      namex( const namex& n ) { value = n.value; }
      namex( const fc::uint128_t& v ):value(v) {}
      namex( const uint64_t& v ) { value.hi = 0; value.lo = v; }
      
      operator std::string()const;
      
      bool empty()const { return 0 == value.lo && 0 == value.hi; }
      bool good()const  { return !empty();   }
      
      const std::string to_string() const {
         std::string str("");
         fc::uint128_t tmp = value;
         if(tmp.hi > 0 && tmp.lo > 0) {
            while(tmp.lo > 0) {
               char c = tmp.lo & 0xFF;
               str += c;
               tmp.lo >>= 8;
            }
            while(tmp.hi > 0) {
               char c = tmp.hi & 0xFF;
               str += c;
               tmp.hi >>= 8;
            }
         } else if(tmp.hi == 0 && tmp.lo > 0) {
            while(tmp.lo > 0) {
               char c = tmp.lo & 0xFF;
               str += c;
               tmp.lo >>= 8;
            }
         }
         boost::algorithm::trim_right_if( str, []( char c ){ return c == '.'; } );
         return str;
      }
      
      uint32_t size() const {
         return value == 0 ? 0 : 16;
      }
      
      uint32_t length() const {
         return value == 0 ? 0 : 16;
      }
      
      void set( const char* str );
      
      namex& operator=( fc::uint128_t v ) {
         value = v;
         return *this;
      }
      
      namex& operator=( const std::string& n ) {
         value = namex(n).value;
         return *this;
      }
      namex& operator=( const char* n ) {
         value = namex(n).value;
         return *this;
      }
      
      namex& operator=( const namex& n ) {
         value = n.value;
         return *this;
      }
      
      friend std::string operator + ( const namex& a, const std::string& b ) {
         return std::string(a) + b;
      }
      friend std::string operator + ( const std::string& a, const namex& b ) {
         return a + std::string(b);
      }
      
      friend bool operator == ( const namex& a, const std::string& b ) {
         return std::string(a) == b;
      }
      friend bool operator == ( const std::string& a, const namex& b ) {
         return a == std::string(b);
      }
      
      friend bool operator != ( const namex& a, const std::string& b ) {
         return std::string(a) != b;
      }
      friend bool operator != ( const std::string& a, const namex& b ) {
         return a != std::string(b);
      }
      
      friend bool operator != ( const namex& a, const char* b ) {
         return std::string(a) != std::string(b);
      }
      friend bool operator != ( const char* a, const namex& b ) {
         return std::string(a) != std::string(b);
      }
      
      //   friend std::string operator + ( const name& a, const name& b ) {
      //     return std::string(a) + std::string(b);
      //   }
      
      friend std::ostream& operator << ( std::ostream& out, const namex& n ) {
         return out << std::string(n);
      }
      
      friend bool operator < ( const namex& a, const namex& b ) { return a.value < b.value; }
      friend bool operator <= ( const namex& a, const namex& b ) { return a.value <= b.value; }
      friend bool operator > ( const namex& a, const namex& b ) { return a.value > b.value; }
      friend bool operator >=( const namex& a, const namex& b ) { return a.value >= b.value; }
      friend bool operator == ( const namex& a, const namex& b ) { return a.value == b.value; }
      
      friend bool operator == ( const namex& a, fc::uint128_t b ) { return a.value == b; }
      friend bool operator != ( const namex& a, fc::uint128_t b ) { return a.value != b; }
      
      friend bool operator != ( const namex& a, const namex& b ) { return a.value != b.value; }
      
      //   operator bool()const            { return value; }
      fc::uint128_t to_uint128_t() const        { return value; }
      uint64_t to_uint64_t() const { return value.lo; }
      //   operator unsigned __int128()const       { return value; }
      uint64_t get_hi() const {return value.hi;}
      uint64_t get_lo() const {return value.lo;}
      
      fc::uint128_t value = 0;
   };

//   static bool operator() ( const namex& a, const namex& b ) { return a.value < b.value; }
   
   inline std::vector<namex> sort_names( std::vector<namex>&& names ) {
      fc::deduplicate(names);
      return names;
   }
   
} } // contento::protocol

namespace std {
   //  template<> struct hash<contento::protocol::name> : private hash<uint64_t> {
   //     typedef contento::protocol::name argument_type;
   //     typedef typename hash<uint64_t>::result_type result_type;
   //     result_type operator()(const argument_type& name) const noexcept
   //     {
   //        return hash<uint64_t>::operator()(name.value);
   //     }
   //  };
};

namespace fc {
   class variant;
   void to_variant(const contento::protocol::name& c, fc::variant& v);
   void from_variant(const fc::variant& v, contento::protocol::name& check);
   void to_variant(const contento::protocol::namex& c, fc::variant& v);
   void from_variant(const fc::variant& v, contento::protocol::namex& check);
} // fc


FC_REFLECT( contento::protocol::name, (value) )
FC_REFLECT( contento::protocol::namex, (value) )
