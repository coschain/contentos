#include <contento/protocol/name.hpp>
#include <fc/variant.hpp>
#include <boost/algorithm/string.hpp>
#include <fc/exception/exception.hpp>


namespace contento { namespace protocol { 

   void name::set( const char* str ) {
      const auto len = strnlen(str, 14);
      FC_ASSERT(len <= 13, "Name is longer than 13 characters (${name}) ", ("name", std::string(str)));
      value = string_to_name(str);
   }

   // keep in sync with name::to_string() in contract definition for name
   name::operator std::string()const {
     static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

      std::string str(13,'.');

      uint64_t tmp = value;
      for( uint32_t i = 0; i <= 12; ++i ) {
         char c = charmap[tmp & (i == 0 ? 0x0f : 0x1f)];
         str[12-i] = c;
         tmp >>= (i == 0 ? 4 : 5);
      }

      boost::algorithm::trim_right_if( str, []( char c ){ return c == '.'; } );
      return str;
   }

   void name16::set( const char* str ) {
      const auto len = strnlen(str, 17);
      FC_ASSERT(len <= 16, "Name is longer than 16 characters (${name}) ", ("name", std::string(str)));
      value = string_to_name16(str);
   }

   name16::operator std::string()const {
    //  static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

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

} } /// contento::protocol

namespace fc {
  void to_variant(const contento::protocol::name& c, fc::variant& v) { v = std::string(c); }
  void from_variant(const fc::variant& v, contento::protocol::name& check) { check = v.get_string(); }
  void to_variant(const contento::protocol::name16& c, fc::variant& v) { v = std::string(c); }
  void from_variant(const fc::variant& v, contento::protocol::name16& check) { check = v.get_string(); }
} // fc
