/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <contento/abi_generator/abi_def.hpp>
//#include <fc/variant_object.hpp>

namespace contento { namespace chain {

using std::map;
using std::string;
using std::function;
using std::pair;
//using namespace fc;
//using namespace protocol;

//namespace impl {
//  struct abi_from_variant;
//  struct abi_to_variant;
//}

/**
 *  Describes the binary representation message and table contents so that it can
 *  be converted to and from JSON.
 */
struct abi_serializer {
   abi_serializer(){ configure_built_in_types(); }
   abi_serializer( const abi_def& abi );
   void set_abi(const abi_def& abi);

   map<type_name, type_name>  typedefs;
   map<type_name, struct_def> structs;
   map<name,type_name>        actions;
   map<name,type_name>        tables;
   map<uint64_t, string>      error_messages;

//   typedef std::function<fc::variant(fc::datastream<const char*>&, bool, bool)>  unpack_function;
//   typedef std::function<void(const fc::variant&, fc::datastream<char*>&, bool, bool)>  pack_function;

   map<type_name, bool> built_in_types;
   void configure_built_in_types();

   void validate()const;

   type_name resolve_type(const type_name& t)const;
   bool      is_array(const type_name& type)const;
   bool      is_optional(const type_name& type)const;
   bool      is_type(const type_name& type)const {
      return _is_type(type, 0);
   }
   bool      is_builtin_type(const type_name& type)const;
   bool      is_integer(const type_name& type) const;
   int       get_integer_size(const type_name& type) const;
   bool      is_struct(const type_name& type)const;
   type_name fundamental_type(const type_name& type)const;

   const struct_def& get_struct(const type_name& type)const;

   type_name get_action_type(name action)const;
   type_name get_table_type(name action)const;

   string  get_error_message( uint64_t error_code )const;

   /*
   fc::variant binary_to_variant(const type_name& type, const bytes& binary)const {
      return _binary_to_variant(type, binary, 0);
   }
   bytes       variant_to_binary(const type_name& type, const fc::variant& var)const {
      return _variant_to_binary(type, var, 0);
   }

   fc::variant binary_to_variant(const type_name& type, fc::datastream<const char*>& binary)const {
      return _binary_to_variant(type, binary, 0);
   }
   void        variant_to_binary(const type_name& type, const fc::variant& var, fc::datastream<char*>& ds)const {
      _variant_to_binary(type, var, ds, 0);
   }


   template<typename T, typename Resolver>
   static void to_variant( const T& o, fc::variant& vo, Resolver resolver );

   template<typename T, typename Resolver>
   static void from_variant( const fc::variant& v, T& o, Resolver resolver );
*/
   template<typename Vec>
   static bool is_empty_abi(const Vec& abi_vec)
   {
      return abi_vec.size() <= 4;
   }

//   template<typename Vec>
//   static bool to_abi(const Vec& abi_vec, abi_def& abi)
//   {
//      if( !is_empty_abi(abi_vec) ) { /// 4 == packsize of empty Abi
//         fc::datastream<const char*> ds( abi_vec.data(), abi_vec.size() );
//         fc::raw::unpack( ds, abi );
//         return true;
//      }
//      return false;
//   }

   static constexpr size_t max_recursion_depth = 128; // arbitrary depth to prevent infinite recursion

private:

   //fc::variant _binary_to_variant(const type_name& type, const bytes& binary, size_t recursion_depth)const;
   //bytes       _variant_to_binary(const type_name& type, const fc::variant& var, size_t recursion_depth)const;

   //fc::variant _binary_to_variant(const type_name& type, fc::datastream<const char*>& binary, size_t recursion_depth)const;
   //void        _variant_to_binary(const type_name& type, const fc::variant& var, fc::datastream<char*>& ds, size_t recursion_depth)const;

   //void _binary_to_variant(const type_name& type, fc::datastream<const char*>& stream, fc::mutable_variant_object& obj, size_t recursion_depth)const;

   bool _is_type(const type_name& type, size_t recursion_depth)const;

   //friend struct impl::abi_from_variant;
   //friend struct impl::abi_to_variant;
};

/*
template<typename T, typename Resolver>
void abi_serializer::to_variant( const T& o, variant& vo, Resolver resolver ) try {
   mutable_variant_object mvo;
   impl::abi_to_variant::add(mvo, "_", o, resolver, 0);
   vo = std::move(mvo["_"]);
} FC_RETHROW_EXCEPTIONS(error, "Failed to serialize type", ("object",o))

template<typename T, typename Resolver>
void abi_serializer::from_variant( const variant& v, T& o, Resolver resolver ) try {
   impl::abi_from_variant::extract(v, o, resolver, 0);
} FC_RETHROW_EXCEPTIONS(error, "Failed to deserialize variant", ("variant",v))
*/

} } // contento::chain
