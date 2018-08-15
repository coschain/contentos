/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#include <cosiolib/cosio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   contento_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   contento_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   contento_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   contento_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   contento_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   contento_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   contento_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   contento_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   contento_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   contento_assert( sizeof(time) ==  4, "time size !=  4");
   contento_assert( sizeof(cosio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   contento_assert( cosio::char_to_symbol('1') ==  1, "cosio::char_to_symbol('1') !=  1");
   contento_assert( cosio::char_to_symbol('2') ==  2, "cosio::char_to_symbol('2') !=  2");
   contento_assert( cosio::char_to_symbol('3') ==  3, "cosio::char_to_symbol('3') !=  3");
   contento_assert( cosio::char_to_symbol('4') ==  4, "cosio::char_to_symbol('4') !=  4");
   contento_assert( cosio::char_to_symbol('5') ==  5, "cosio::char_to_symbol('5') !=  5");
   contento_assert( cosio::char_to_symbol('a') ==  6, "cosio::char_to_symbol('a') !=  6");
   contento_assert( cosio::char_to_symbol('b') ==  7, "cosio::char_to_symbol('b') !=  7");
   contento_assert( cosio::char_to_symbol('c') ==  8, "cosio::char_to_symbol('c') !=  8");
   contento_assert( cosio::char_to_symbol('d') ==  9, "cosio::char_to_symbol('d') !=  9");
   contento_assert( cosio::char_to_symbol('e') == 10, "cosio::char_to_symbol('e') != 10");
   contento_assert( cosio::char_to_symbol('f') == 11, "cosio::char_to_symbol('f') != 11");
   contento_assert( cosio::char_to_symbol('g') == 12, "cosio::char_to_symbol('g') != 12");
   contento_assert( cosio::char_to_symbol('h') == 13, "cosio::char_to_symbol('h') != 13");
   contento_assert( cosio::char_to_symbol('i') == 14, "cosio::char_to_symbol('i') != 14");
   contento_assert( cosio::char_to_symbol('j') == 15, "cosio::char_to_symbol('j') != 15");
   contento_assert( cosio::char_to_symbol('k') == 16, "cosio::char_to_symbol('k') != 16");
   contento_assert( cosio::char_to_symbol('l') == 17, "cosio::char_to_symbol('l') != 17");
   contento_assert( cosio::char_to_symbol('m') == 18, "cosio::char_to_symbol('m') != 18");
   contento_assert( cosio::char_to_symbol('n') == 19, "cosio::char_to_symbol('n') != 19");
   contento_assert( cosio::char_to_symbol('o') == 20, "cosio::char_to_symbol('o') != 20");
   contento_assert( cosio::char_to_symbol('p') == 21, "cosio::char_to_symbol('p') != 21");
   contento_assert( cosio::char_to_symbol('q') == 22, "cosio::char_to_symbol('q') != 22");
   contento_assert( cosio::char_to_symbol('r') == 23, "cosio::char_to_symbol('r') != 23");
   contento_assert( cosio::char_to_symbol('s') == 24, "cosio::char_to_symbol('s') != 24");
   contento_assert( cosio::char_to_symbol('t') == 25, "cosio::char_to_symbol('t') != 25");
   contento_assert( cosio::char_to_symbol('u') == 26, "cosio::char_to_symbol('u') != 26");
   contento_assert( cosio::char_to_symbol('v') == 27, "cosio::char_to_symbol('v') != 27");
   contento_assert( cosio::char_to_symbol('w') == 28, "cosio::char_to_symbol('w') != 28");
   contento_assert( cosio::char_to_symbol('x') == 29, "cosio::char_to_symbol('x') != 29");
   contento_assert( cosio::char_to_symbol('y') == 30, "cosio::char_to_symbol('y') != 30");
   contento_assert( cosio::char_to_symbol('z') == 31, "cosio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      contento_assert( cosio::char_to_symbol((char)i) == 0, "cosio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   contento_assert( cosio::string_to_name("a") == N(a) , "cosio::string_to_name(a)" );
   contento_assert( cosio::string_to_name("ba") == N(ba) , "cosio::string_to_name(ba)" );
   contento_assert( cosio::string_to_name("cba") == N(cba) , "cosio::string_to_name(cba)" );
   contento_assert( cosio::string_to_name("dcba") == N(dcba) , "cosio::string_to_name(dcba)" );
   contento_assert( cosio::string_to_name("edcba") == N(edcba) , "cosio::string_to_name(edcba)" );
   contento_assert( cosio::string_to_name("fedcba") == N(fedcba) , "cosio::string_to_name(fedcba)" );
   contento_assert( cosio::string_to_name("gfedcba") == N(gfedcba) , "cosio::string_to_name(gfedcba)" );
   contento_assert( cosio::string_to_name("hgfedcba") == N(hgfedcba) , "cosio::string_to_name(hgfedcba)" );
   contento_assert( cosio::string_to_name("ihgfedcba") == N(ihgfedcba) , "cosio::string_to_name(ihgfedcba)" );
   contento_assert( cosio::string_to_name("jihgfedcba") == N(jihgfedcba) , "cosio::string_to_name(jihgfedcba)" );
   contento_assert( cosio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "cosio::string_to_name(kjihgfedcba)" );
   contento_assert( cosio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "cosio::string_to_name(lkjihgfedcba)" );
   contento_assert( cosio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "cosio::string_to_name(mlkjihgfedcba)" );
   contento_assert( cosio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "cosio::string_to_name(mlkjihgfedcba2)" );
   contento_assert( cosio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "cosio::string_to_name(mlkjihgfedcba14)" );

   contento_assert( cosio::string_to_name("azAA34") == N(azBB34) , "cosio::string_to_name N(azBB34)" );
   contento_assert( cosio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "cosio::string_to_name AZaz12Bc34" );
   contento_assert( cosio::string_to_name("AAAAAAAAAAAAAAA") == cosio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "cosio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   contento_assert( cosio::name{cosio::string_to_name("azAA34")}.value == N(azAA34), "cosio::name != N(azAA34)" );
   contento_assert( cosio::name{cosio::string_to_name("AABBCC")}.value == 0, "cosio::name != N(0)" );
   contento_assert( cosio::name{cosio::string_to_name("AA11")}.value == N(AA11), "cosio::name != N(AA11)" );
   contento_assert( cosio::name{cosio::string_to_name("11AA")}.value == N(11), "cosio::name != N(11)" );
   contento_assert( cosio::name{cosio::string_to_name("22BBCCXXAA")}.value == N(22), "cosio::name != N(22)" );
   contento_assert( cosio::name{cosio::string_to_name("AAAbbcccdd")} == cosio::name{cosio::string_to_name("AAAbbcccdd")}, "cosio::name == cosio::name" );

   uint64_t tmp = cosio::name{cosio::string_to_name("11bbcccdd")};
   contento_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
