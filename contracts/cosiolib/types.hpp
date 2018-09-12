/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once
#include <cosiolib/types.h>
#include <cosiolib/system.h>
#include <functional>
#include <tuple>
#include <string>
// #include <boost/algorithm/string.hpp>
// #include <fc/uint128.hpp>

namespace cosio {

   typedef std::vector<std::tuple<uint16_t,std::vector<char>>> extensions_type;

  class uint128_x
  {
      public:
      uint128_x():hi(0),lo(0){}
      uint128_x( uint32_t l ):hi(0),lo(uint64_t(l)){}
      uint128_x( int32_t l ):hi( -(l<0) ),lo(uint64_t(l)){}
      uint128_x( int64_t l ):hi( -(l<0) ),lo(uint64_t(l)){}
      uint128_x( uint64_t l ):hi(0),lo(uint64_t(l)){}
      uint128_x( const std::string& s );
      uint128_x( uint64_t _h, uint64_t _l )
      :hi(_h),lo(_l){}
      explicit uint128_x( unsigned __int128 i ):hi( i >> 64 ), lo(uint64_t(i)){ }

      operator std::string()const;

      explicit operator unsigned __int128()const {
         unsigned __int128 result(hi);
         result <<= 64;
         return result | lo;
      }

      bool     operator == ( const uint128_x& o )const{ return hi == o.hi && lo == o.lo;             }
      bool     operator != ( const uint128_x& o )const{ return hi != o.hi || lo != o.lo;             }
      bool     operator < ( const uint128_x& o )const { return (hi == o.hi) ? lo < o.lo : hi < o.hi; }
      bool     operator < ( const int64_t& o )const { return *this < uint128_x(o); }
      bool     operator !()const                    { return !(hi !=0 || lo != 0);                 }
      uint128_x  operator -()const                    { return ++uint128_x( ~hi, ~lo );                }
      uint128_x  operator ~()const                    { return uint128_x( ~hi, ~lo );                  }

      uint128_x& operator++()    {  hi += (++lo == 0); return *this; }
      uint128_x& operator--()    {  hi -= (lo-- == 0); return *this; }
      uint128_x  operator++(int) { auto tmp = *this; ++(*this); return tmp; }
      uint128_x  operator--(int) { auto tmp = *this; --(*this); return tmp; }

      uint128_x& operator |= ( const uint128_x& u ) { hi |= u.hi; lo |= u.lo; return *this; }
      uint128_x& operator &= ( const uint128_x& u ) { hi &= u.hi; lo &= u.lo; return *this; }
      uint128_x& operator ^= ( const uint128_x& u ) { hi ^= u.hi; lo ^= u.lo; return *this; }
      uint128_x& operator <<= ( const uint128_x& u );
      uint128_x& operator >>= ( const uint128_x& u );

      uint128_x& operator += ( const uint128_x& u ) { const uint64_t old = lo; lo += u.lo;  hi += u.hi + (lo < old); return *this; }
      uint128_x& operator -= ( const uint128_x& u ) { return *this += -u; }
      uint128_x& operator *= ( const uint128_x& u );
      uint128_x& operator /= ( const uint128_x& u );
      uint128_x& operator %= ( const uint128_x& u );


      friend uint128_x operator + ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)+=r;   }
      friend uint128_x operator - ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)-=r;   }
      friend uint128_x operator * ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)*=r;   }
      friend uint128_x operator / ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)/=r;   }
      friend uint128_x operator % ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)%=r;   }
      friend uint128_x operator | ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)=(r);  }
      friend uint128_x operator & ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)&=r;   }
      friend uint128_x operator ^ ( const uint128_x& l, const uint128_x& r )   { return uint128_x(l)^=r;   }
      friend uint128_x operator << ( const uint128_x& l, const uint128_x& r )  { return uint128_x(l)<<=r;  }
      friend uint128_x operator >> ( const uint128_x& l, const uint128_x& r )  { return uint128_x(l)>>=r;  }
      friend bool    operator >  ( const uint128_x& l, const uint128_x& r )  { return r < l;           }
      friend bool    operator >  ( const uint128_x& l, const int64_t& r )  { return uint128_x(r) < l;           }
      friend bool    operator >  ( const int64_t& l, const uint128_x& r )  { return r < uint128_x(l);           }

      friend bool    operator >=  ( const uint128_x& l, const uint128_x& r ) { return l == r || l > r; }
      friend bool    operator >=  ( const uint128_x& l, const int64_t& r ) { return l >= uint128_x(r); }
      friend bool    operator >=  ( const int64_t& l, const uint128_x& r ) { return uint128_x(l) >= r; }
      friend bool    operator <=  ( const uint128_x& l, const uint128_x& r ) { return l == r || l < r; }
      friend bool    operator <=  ( const uint128_x& l, const int64_t& r ) { return l <= uint128_x(r); }
      friend bool    operator <=  ( const int64_t& l, const uint128_x& r ) { return uint128_x(l) <= r; }

      // friend std::size_t hash_value( const uint128_x& v ) { return city_hash_size_t((const char*)&v, sizeof(v)); }

      uint32_t to_integer()const
      {
          contento_assert( hi == 0, "hi must be 0");
          uint32_t lo32 = (uint32_t) lo;
          contento_assert( lo == lo32, "lo not be 0");
          return lo32;
      }
      uint64_t to_uint64()const
      {
          contento_assert( hi == 0, "hi must be 0");
          return lo;
      }
      uint32_t low_32_bits()const { return (uint32_t) lo; }
      uint64_t low_bits()const  { return lo; }
      uint64_t high_bits()const { return hi; }

      operator account_name() const {
         //return convert_u128_name(*this);
         account_name name;
         memcpy(&name, this, sizeof(account_name));
         return name;
      }

      static uint128_x max_value() {
          const uint64_t max64 = std::numeric_limits<uint64_t>::max();
          return uint128_x( max64, max64 );
      }

      static void full_product( const uint128_x& a, const uint128_x& b, uint128_x& result_hi, uint128_x& result_lo );

      uint8_t popcount() const;

      // fields must be public for serialization
      uint64_t hi;
      uint64_t lo;
  };

   /**
    *  @brief Converts a base32 symbol into its binary representation, used by string_to_name()
    *
    *  @details Converts a base32 symbol into its binary representation, used by string_to_name()
    *  @ingroup types
    */
   static constexpr  char char_to_symbol( char c ) {
      if( c >= 'a' && c <= 'z' )
         return (c - 'a') + 6;
      if( c >= '1' && c <= '5' )
         return (c - '1') + 1;
      return 0;
   }


   /**
    *  @brief Converts a base32 string to a uint64_t.
    *
    *  @details Converts a base32 string to a uint64_t. This is a constexpr so that
    *  this method can be used in template arguments as well.
    *
    *  @ingroup types
    */
   static constexpr uint64_t string_to_name( const char* str ) {

      uint32_t len = 0;
      while( str[len] ) ++len;

      uint64_t value = 0;

      for( uint32_t i = 0; i <= 12; ++i ) {
         uint64_t c = 0;
         if( i < len && i <= 12 ) c = uint64_t(char_to_symbol( str[i] ));

         if( i < 12 ) {
            c &= 0x1f;
            c <<= 64-5*(i+1);
         }
         else {
            c &= 0x0f;
         }

         value |= c;
      }

      return value;
   }

   /**
    * @brief used to generate a compile time uint64_t from the base32 encoded string interpretation of X
    * @ingroup types
    */
   #define N(X) ::cosio::string_to_name(#X)


   static constexpr uint64_t name_suffix( uint64_t n ) {
      uint32_t remaining_bits_after_last_actual_dot = 0;
      uint32_t tmp = 0;
      for( int32_t remaining_bits = 59; remaining_bits >= 4; remaining_bits -= 5 ) { // Note: remaining_bits must remain signed integer
         // Get characters one-by-one in name in order from left to right (not including the 13th character)
         auto c = (n >> remaining_bits) & 0x1Full;
         if( !c ) { // if this character is a dot
            tmp = static_cast<uint32_t>(remaining_bits);
         } else { // if this character is not a dot
            remaining_bits_after_last_actual_dot = tmp;
         }
      }

      uint64_t thirteenth_character = n & 0x0Full;
      if( thirteenth_character ) { // if 13th character is not a dot
         remaining_bits_after_last_actual_dot = tmp;
      }

      if( remaining_bits_after_last_actual_dot == 0 ) // there is no actual dot in the name other than potentially leading dots
         return n;

      // At this point remaining_bits_after_last_actual_dot has to be within the range of 4 to 59 (and restricted to increments of 5).

      // Mask for remaining bits corresponding to characters after last actual dot, except for 4 least significant bits (corresponds to 13th character).
      uint64_t mask = (1ull << remaining_bits_after_last_actual_dot) - 16;
      uint32_t shift = 64 - remaining_bits_after_last_actual_dot;

      return ( ((n & mask) << shift) + (thirteenth_character << (shift-1)) );
   }

   /**
    *  @brief wraps a uint64_t to ensure it is only passed to methods that expect a Name
    *  @details wraps a uint64_t to ensure it is only passed to methods that expect a Name and
    *         that no mathematical operations occur.  It also enables specialization of print
    *         so that it is printed as a base32 string.
    *
    *  @ingroup types
    *  @{
    */
   
   struct name {
      operator uint64_t()const { return value; }

      name(){}
      name(uint64_t aname){ this->value = aname; }
      name(const char* str){
            this->value = ::cosio::string_to_name(str);
      }

      name& operator = ( const char* str){
            this->value = ::cosio::string_to_name(str);
            return *this;
      }

      // keep in sync with name::operator string() in eosio source code definition for name
      std::string to_string() const {
         static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

         std::string str(13,'.');

         uint64_t tmp = value;
         for( uint32_t i = 0; i <= 12; ++i ) {
            char c = charmap[tmp & (i == 0 ? 0x0f : 0x1f)];
            str[12-i] = c;
            tmp >>= (i == 0 ? 4 : 5);
         }

         trim_right_dots( str );
         return str;
      }

      friend bool operator==( const name& a, const name& b ) { return a.value == b.value; }
      uint64_t value = 0;

   private:
      static void trim_right_dots(std::string& str ) {
         const auto last = str.find_last_not_of('.');
         if (last != std::string::npos)
            str = str.substr(0, last + 1);
      }
   }; 
   /// @}

   static const uint128_x string_to_namex( const char* str )
   {
      
      int len = 0;
      while(str[len]) ++len;
      
      uint128_x name = uint128_x(0l);
      
      if (len <= 8) {
         for( int i = 0; i < len; ++i) {
            name.lo |= (uint64_t(str[i]) << (8 * i));
         }
      } else if ( len > 8 && len <= 16 ) {
         for( int i = 0; i < 8; ++i) {
            name.lo |= (uint64_t(str[i]) << (8 * i));
         }
         for( int i = 8; i < len; ++i) {
            name.hi |= (uint64_t(str[i]) << (8 * i));
         }
      }
      
      return name;
   }

   uint128_x convert_name_u128(namex_ const name) {
      uint128_x u128;
      memcpy(&u128, &name, sizeof(u128));
      return u128;
   }

   namex_ convert_u128_name(uint128_x const u128) {
      namex_ name;
      memcpy(&name, &u128, sizeof(namex_));
      return name;
   }

   #define N16(X) ::cosio::string_to_namex(#X)
   
   struct namex {
      namex(){}
      namex( const char* str )   { set(str);           }
      namex( const std::string& str ) { set( str.c_str() ); }
      namex( const namex& n ) { value = n.value; }
      namex( const uint128_x& v ):value(v) {}
      namex( const namex_& n) {
            value = convert_name_u128(n);
      }
      
      operator std::string()const{
            return to_string();
      }

      operator namex_()const{
            return convert_u128_name(value);
      }
      
      bool empty()const { return 0 == value.lo && 0 == value.hi; }
      bool good()const  { return !empty();   }
      
      const std::string to_string() const {
         std::string str("");
         uint128_x tmp = value;
         if(tmp.hi > 0 && tmp.lo > 0) {
            while(tmp.lo > 0) {
               char c = char(tmp.lo & 0xFF);
               str += c;
               tmp.lo >>= 8;
            }
            while(tmp.hi > 0) {
               char c = char(tmp.hi & 0xFF);
               str += c;
               tmp.hi >>= 8;
            }
         } else if(tmp.hi == 0 && tmp.lo > 0) {
            while(tmp.lo > 0) {
               char c = char(tmp.lo & 0xFF);
               str += c;
               tmp.lo >>= 8;
            }
         }
      //    boost::algorithm::trim_right_if( str, []( char c ){ return c == '.'; } );
         return str;
      }
      
      uint32_t size() const {
         return value == uint128_x(0l) ? 0 : 16;
      }
      
      uint32_t length() const {
         return value == uint128_x(0l) ? 0 : 16;
      }
      
      void set( const char* str ) {
            const auto len = strnlen(str, 17);
            contento_assert(len <= 16, "Name is longer than 16 characters (${name}) ");
            value = string_to_namex(str);
      }
      
      namex& operator=( uint128_x v ) {
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

      namex& operator=( const namex_& n ) {
            // value.hi = n.value[0];
            // value.lo = n.value[1];
            value = convert_name_u128(n);
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
      friend bool operator == ( const namex_& a, const namex& b ) {
         return convert_name_u128(a) == b.value;
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
      
      friend bool operator == ( const namex& a, uint128_x b ) { return a.value == b; }
      friend bool operator != ( const namex& a, uint128_x b ) { return a.value != b; }
      
      friend bool operator != ( const namex& a, const namex& b ) { return a.value != b.value; }
      
      //   operator bool()const            { return value; }
      uint128_x to_uint128_x_t() const        { return value; }
      //   operator unsigned __int128()const       { return value; }
      uint64_t get_hi() const {return value.hi;}
      uint64_t get_lo() const {return value.lo;}
      
      uint128_x value = uint128_x(0l);
   };

} // namespace cosio

namespace std {
   /**
    * @brief provide less for checksum256
    */
   template<>
   struct less<checksum256> : binary_function<checksum256, checksum256, bool> {
      bool operator()( const checksum256& lhs, const checksum256& rhs ) const {
         return memcmp(&lhs, &rhs, sizeof(lhs)) < 0;
      }
   };

} // namespace std

/**
 * Provide == for checksum256 in global namespace
 */
bool operator==(const checksum256& lhs, const checksum256& rhs) {
   return memcmp(&lhs, &rhs, sizeof(lhs)) == 0;
}
bool operator==(const checksum160& lhs, const checksum160& rhs) {
   return memcmp(&lhs, &rhs, sizeof(lhs)) == 0;
}
bool operator!=(const checksum160& lhs, const checksum160& rhs) {
   return memcmp(&lhs, &rhs, sizeof(lhs)) != 0;
}
bool operator==(const account_name& lhs, const account_name& rhs) {
   return memcmp(&lhs, &rhs, sizeof(lhs)) == 0;
}
bool operator!=(const account_name& lhs, const account_name& rhs) {
   return memcmp(&lhs, &rhs, sizeof(lhs)) != 0;
}
