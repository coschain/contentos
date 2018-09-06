#pragma once
#include <fc/variant.hpp>
#include <contento/app/contento_api_objects.hpp>
#include <contento/chain/contract_table_objects.hpp>

namespace contento { namespace app {

namespace contract_storage_def {
 //support for --key_types [sha256,ripemd160] and --encoding [dec/hex]
 constexpr const char i64[]       = "i64";
 constexpr const char i128[]      = "i128";
 constexpr const char i256[]      = "i256";
 constexpr const char float64[]   = "float64";
 constexpr const char float128[]  = "float128";
 constexpr const char sha256[]    = "sha256";
 constexpr const char ripemd160[] = "ripemd160";
 constexpr const char dec[]       = "dec";
 constexpr const char hex[]       = "hex";
}
 const string KEYi64 = "i64";

 template<const char*key_type , const char *encoding=contract_storage_def::dec>
 struct keytype_converter ;

 template<>
 struct keytype_converter<contract_storage_def::sha256, contract_storage_def::hex> {
     using input_type = chain::checksum256_type;
     using index_type = chain::index256_index;
     static auto function() {
        return [](const input_type& v) {
            chain::key256_t k;
            k[0] = ((uint128_t *)&v._hash)[0]; //0-127
            k[1] = ((uint128_t *)&v._hash)[1]; //127-256
            return k;
        };
     }
 };

 //key160 support with padding zeros in the end of key256
 template<>
 struct keytype_converter<contract_storage_def::ripemd160, contract_storage_def::hex> {
     using input_type = chain::checksum160_type;
     using index_type = chain::index256_index;
     static auto function() {
        return [](const input_type& v) {
            chain::key256_t k;
            memset(k.data(), 0, sizeof(k));
            memcpy(k.data(), v._hash, sizeof(v._hash));
            return k;
        };
     }
 };

 template<>
 struct keytype_converter<contract_storage_def::i256> {
     using input_type = boost::multiprecision::uint256_t;
     using index_type = chain::index256_index;
     static auto function() {
        return [](const input_type v) {
            chain::key256_t k;
            k[0] = ((uint128_t *)&v)[0]; //0-127
            k[1] = ((uint128_t *)&v)[1]; //127-256
            return k;
        };
     }
 };

struct get_table_rows_params {
      name        code;
      string      scope;
      name        table;
      string      table_key;
      string      lower_bound;
      string      upper_bound;
      uint32_t    limit = 10;
      string      key_type;  // type of key specified by index_position
      string      index_position; // 1 - primary (first), 2 - secondary index (in order defined by multi_index), 3 - third index, etc
      string      encode_type{"dec"}; //dec, hex , default=dec

      get_table_rows_params(string code, string scope, string table,
                           string lower_bound, string upper_bound, int limit,
                           string key_type, string index_pos, string encode_type)
                           :code(code)
                           ,scope(scope)
                           ,table(table)
                           ,lower_bound(lower_bound)
                           ,upper_bound(upper_bound)
                           ,limit(limit)
                           ,key_type(key_type)
                           ,index_position(index_pos)
                           ,encode_type(encode_type) {}
                           
};

// see specialization for uint64_t in source file
template<typename Type>
Type convert_to_type(const string& str, const string& desc) {
   try {
      return fc::variant(str).as<Type>();
   } FC_RETHROW_EXCEPTIONS(warn, "Could not convert ${desc} string '${str}' to key type.", ("desc", desc)("str",str) )
}

template<>
uint64_t convert_to_type(const string& str, const string& desc);

static inline void copy_inline_row(const chain::key_value_object& obj, vector<char>& data) {
   data.resize( obj.value.size() );
   memcpy( data.data(), obj.value.data(), obj.value.size() );
}

class contract_storage {
public:
   contract_storage(contento::chain::database& db)
   : _db(db) {}

   static uint64_t get_table_index_name(const get_table_rows_params& p, bool& primary);
   table_rows_api_obj get_table_rows( const get_table_rows_params& p )const;

   template <typename IndexType, typename SecKeyType, typename ConvFn>
   table_rows_api_obj get_table_rows_by_seckey( const get_table_rows_params& p, ConvFn conv )const {
      table_rows_api_obj result;

      uint64_t scope = convert_to_type<uint64_t>(p.scope, "scope");

      bool primary = false;
      const uint64_t table_with_index = get_table_index_name(p, primary);
      const auto* t_id = _db.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, p.table));
      const auto* index_t_id = _db.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, table_with_index));
      if (t_id != nullptr && index_t_id != nullptr) {
         const auto& secidx = _db.get_index<IndexType, chain::by_secondary>();
         decltype(index_t_id->id) low_tid(index_t_id->id._id);
         decltype(index_t_id->id) next_tid(index_t_id->id._id + 1);
         auto lower = secidx.lower_bound(boost::make_tuple(low_tid));
         auto upper = secidx.lower_bound(boost::make_tuple(next_tid));

         if (p.lower_bound.size()) {
            if (p.key_type == "name") {
               name s(p.lower_bound);
                SecKeyType lv = convert_to_type<SecKeyType>( std::string(s), "lower_bound name" ); // avoids compiler error
               lower = secidx.lower_bound( boost::make_tuple( low_tid, conv( lv )));
            } else {
               SecKeyType lv = convert_to_type<SecKeyType>( p.lower_bound, "lower_bound" );
               lower = secidx.lower_bound( boost::make_tuple( low_tid, conv( lv )));
            }
         }
         if (p.upper_bound.size()) {
            if (p.key_type == "name") {
               name s(p.upper_bound);
               SecKeyType uv = convert_to_type<SecKeyType>( std::string(s), "upper_bound name" );
               upper = secidx.lower_bound( boost::make_tuple( low_tid, conv( uv )));
            } else {
               SecKeyType uv = convert_to_type<SecKeyType>( p.upper_bound, "upper_bound" );
               upper = secidx.lower_bound( boost::make_tuple( low_tid, conv( uv )));
            }
         }

         vector<char> data;

         auto end = fc::time_point::now() + fc::microseconds(1000 * 10); /// 10ms max time

         unsigned int count = 0;
         auto itr = lower;
         for (; itr != upper; ++itr) {

            const auto* itr2 = _db.find<chain::key_value_object, chain::by_scope_primary>(boost::make_tuple(t_id->id, itr->primary_key));
            if (itr2 == nullptr) continue;
            copy_inline_row(*itr2, data);
            result.raw_data_rows.emplace_back(data);

            if (++count == p.limit || fc::time_point::now() > end) {
               break;
            }
         }
         if (itr != upper) {
            result.more = true;
         }
      }
      return result;
   }

   template <typename IndexType>
   table_rows_api_obj get_table_rows_ex( const get_table_rows_params& p )const {
      table_rows_api_obj result;

      uint64_t scope = convert_to_type<uint64_t>(p.scope, "scope");

      const auto* t_id = _db.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, p.table));
      if (t_id != nullptr) {
         const auto& idx = _db.get_index<IndexType, chain::by_scope_primary>();
         decltype(t_id->id) next_tid(t_id->id._id + 1);
         auto lower = idx.lower_bound(boost::make_tuple(t_id->id));
         auto upper = idx.lower_bound(boost::make_tuple(next_tid));

         if (p.lower_bound.size()) {
            if (p.key_type == "name") {
               name s(p.lower_bound);
               lower = idx.lower_bound( boost::make_tuple( t_id->id, s.value ));
            } else {
               auto lv = convert_to_type<typename IndexType::value_type::key_type>( p.lower_bound, "lower_bound" );
               lower = idx.lower_bound( boost::make_tuple( t_id->id, lv ));
            }
         }
         if (p.upper_bound.size()) {
            if (p.key_type == "name") {
               name s(p.upper_bound);
               upper = idx.lower_bound( boost::make_tuple( t_id->id, s.value ));
            } else {
               auto uv = convert_to_type<typename IndexType::value_type::key_type>( p.upper_bound, "upper_bound" );
               upper = idx.lower_bound( boost::make_tuple( t_id->id, uv ));
            }
         }

         vector<char> data;

         auto end = fc::time_point::now() + fc::microseconds(1000 * 10); /// 10ms max time

         unsigned int count = 0;
         auto itr = lower;
         for (; itr != upper; ++itr) {
            copy_inline_row(*itr, data);
            result.raw_data_rows.emplace_back(data);

            if (++count == p.limit || fc::time_point::now() > end) {
               ++itr;
               break;
            }
         }
         if (itr != upper) {
            result.more = true;
         }
      }
      return result;
   }

private:
   contento::chain::database&       _db;
};

}}
