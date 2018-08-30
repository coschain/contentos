#pragma once
#include <contento/app/contract_storage.hpp>
#include <contento/chain/abi_serializer.hpp>
#include <contento/chain/exceptions.hpp>
#include <contento/chain/symbol.hpp>

namespace contento { namespace app {

string get_table_type( const abi_def& abi, const name& table_name ) {
   for( const auto& t : abi.tables ) {
      if( t.name == table_name ){
         return t.index_type;
      }
   }
   CONTENTO_ASSERT( false, chain::contract_table_query_exception, "Table ${table} is not specified in the ABI", ("table",table_name) );
}

uint64_t contract_storage::get_table_index_name(const get_table_rows_params& p, bool& primary) {
   using boost::algorithm::starts_with;
   // see multi_index packing of index name
   const uint64_t table = p.table.value;
   uint64_t index = table & 0xFFFFFFFFFFFFFFF0ULL;
   CONTENTO_ASSERT( index == table, chain::contract_table_query_exception, "Unsupported table name: ${n}", ("n", p.table) );

   primary = false;
   uint64_t pos = 0;
   if (p.index_position.empty() || p.index_position == "first" || p.index_position == "primary" || p.index_position == "one") {
      primary = true;
   } else if (starts_with(p.index_position, "sec") || p.index_position == "two") { // second, secondary
   } else if (starts_with(p.index_position , "ter") || starts_with(p.index_position, "th")) { // tertiary, ternary, third, three
      pos = 1;
   } else if (starts_with(p.index_position, "fou")) { // four, fourth
      pos = 2;
   } else if (starts_with(p.index_position, "fi")) { // five, fifth
      pos = 3;
   } else if (starts_with(p.index_position, "six")) { // six, sixth
      pos = 4;
   } else if (starts_with(p.index_position, "sev")) { // seven, seventh
      pos = 5;
   } else if (starts_with(p.index_position, "eig")) { // eight, eighth
      pos = 6;
   } else if (starts_with(p.index_position, "nin")) { // nine, ninth
      pos = 7;
   } else if (starts_with(p.index_position, "ten")) { // ten, tenth
      pos = 8;
   } else {
      try {
         pos = fc::to_uint64( p.index_position );
      } catch(...) {
         CONTENTO_ASSERT( false, chain::contract_table_query_exception, "Invalid index_position: ${p}", ("p", p.index_position));
      }
      if (pos < 2) {
         primary = true;
         pos = 0;
      } else {
         pos -= 2;
      }
   }
   index |= (pos & 0x000000000000000FULL);
   return index;
}

table_rows_api_obj contract_storage::get_table_rows( const get_table_rows_params& p )const {
   const account_object *acc = _db.find<account_object, by_name>(p.code);
   CONTENTO_ASSERT(acc != nullptr, chain::contract_table_query_exception, "Failed to retrieve account for ${account}", ("account", p.code));
   abi_def abi;
   abi_serializer::to_abi(acc->abi, abi);

   bool primary = false;
   auto table_with_index = get_table_index_name( p, primary );
   if( primary ) {
      CONTENTO_ASSERT( p.table == table_with_index, chain::contract_table_query_exception, "Invalid table name ${t}", ( "t", p.table ));
      auto table_type = get_table_type( abi, p.table );
      if( table_type == KEYi64 || p.key_type == "i64" || p.key_type == "name" ) {
         return get_table_rows_ex<key_value_index>(p);
      }
      CONTENTO_ASSERT( false, chain::contract_table_query_exception, "Invalid table type ${type}", ("type",table_type)("abi",abi));
   } else {
      CONTENTO_ASSERT( !p.key_type.empty(), chain::contract_table_query_exception, "key type required for non-primary index" );

      if (p.key_type == contract_storage_def::i64 || p.key_type == "name") {
         return get_table_rows_by_seckey<index64_index, uint64_t>(p, [](uint64_t v)->uint64_t {
            return v;
         });
      }
      else if (p.key_type == contract_storage_def::i128) {
         return get_table_rows_by_seckey<index128_index, uint128_t>(p, [](uint128_t v)->uint128_t {
            return v;
         });
      }
      else if (p.key_type == contract_storage_def::i256) {
         if ( p.encode_type == contract_storage_def::hex) {
            using  conv = keytype_converter<contract_storage_def::sha256,contract_storage_def::hex>;
            return get_table_rows_by_seckey<conv::index_type, conv::input_type>(p, conv::function());
         }
         using  conv = keytype_converter<contract_storage_def::i256>;
         return get_table_rows_by_seckey<conv::index_type, conv::input_type>(p, conv::function());
      }
      else if (p.key_type == contract_storage_def::float64) {
         return get_table_rows_by_seckey<index_double_index, double>(p, [](double v)->float64_t {
            float64_t f = *(float64_t *)&v;
            return f;
         });
      }
      else if (p.key_type == contract_storage_def::float128) {
         return get_table_rows_by_seckey<index_long_double_index, double>(p, [](double v)->float128_t{
            float64_t f = *(float64_t *)&v;
            float128_t f128;
            f64_to_f128M(f, &f128);
            return f128;
         });
      }
      else if (p.key_type == contract_storage_def::sha256) {
         using  conv = keytype_converter<contract_storage_def::sha256,contract_storage_def::hex>;
         return get_table_rows_by_seckey<conv::index_type, conv::input_type>(p, conv::function());
      }
      else if(p.key_type == contract_storage_def::ripemd160) {
         using  conv = keytype_converter<contract_storage_def::ripemd160,contract_storage_def::hex>;
         return get_table_rows_by_seckey<conv::index_type, conv::input_type>(p, conv::function());
      }
      CONTENTO_ASSERT(false, chain::contract_table_query_exception, "Unsupported secondary index type: ${t}", ("t", p.key_type));
   }
}

template<>
uint64_t convert_to_type(const string& str, const string& desc) {
   uint64_t value = 0;
   try {
      value = boost::lexical_cast<uint64_t>(str.c_str(), str.size());
   } catch( ... ) {
      try {
         auto trimmed_str = str;
         boost::trim(trimmed_str);
         name s(trimmed_str);
         value = s.value;
      } catch( ... ) {
         try {
            auto symb = contento::chain::symbol::from_string(str);
            value = symb.value();
         } catch( ... ) {
            try {
               value = ( contento::chain::string_to_symbol( 0, str.c_str() ) >> 8 );
            } catch( ... ) {
               EOS_ASSERT( false, chain_type_exception, "Could not convert ${desc} string '${str}' to any of the following: "
                                 "uint64_t, valid name, or valid symbol (with or without the precision)",
                          ("desc", desc)("str", str));
            }
         }
      }
   }
   return value;
}

}}
