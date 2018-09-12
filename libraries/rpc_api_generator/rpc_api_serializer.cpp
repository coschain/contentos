/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <contento/rpc_api_generator/rpc_api_serializer.hpp>
#include <fc/io/raw.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <fc/io/varint.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

using namespace boost;

namespace contento { namespace rpc_api {

   using boost::algorithm::ends_with;
   using std::string;

   rpc_api_serializer::rpc_api_serializer( const abi_def& abi ) {
      configure_built_in_types();
      set_abi(abi);
   }

   void rpc_api_serializer::configure_built_in_types() {

      built_in_types.emplace("bool",                      1);
      built_in_types.emplace("int8",                      1);
      built_in_types.emplace("uint8",                     1);
      built_in_types.emplace("int16",                     1);
      built_in_types.emplace("uint16",                    1);
      built_in_types.emplace("int32",                     1);
      built_in_types.emplace("uint32",                    1);
      built_in_types.emplace("int64",                     1);
      built_in_types.emplace("uint64",                    1);
      built_in_types.emplace("int128",                    1);
      built_in_types.emplace("uint128",                   1);
      built_in_types.emplace("varint32",                  1);
      built_in_types.emplace("varuint32",                 1);
      built_in_types.emplace("float32",                   1);
      built_in_types.emplace("float64",                   1);
      built_in_types.emplace("float128",                  1);
      built_in_types.emplace("time_point",                1);
      built_in_types.emplace("time_point_sec",            1);
      built_in_types.emplace("name",                      1);
      built_in_types.emplace("bytes",                     1);
      built_in_types.emplace("string",                    1);
      built_in_types.emplace("checksum160",               1);
      built_in_types.emplace("checksum256",               1);
      built_in_types.emplace("sha256",               1);
      built_in_types.emplace("checksum512",               1);
      built_in_types.emplace("public_key_type",           1);
      built_in_types.emplace("public_key",                1);
      built_in_types.emplace("signature",                 1);
      built_in_types.emplace("signature_type",            1);
      //built_in_types.emplace("block_header_extensions_type",                 1);
      //built_in_types.emplace("future_extensions",                 1);
      built_in_types.emplace("variant_object",                 1);
      built_in_types.emplace("id_type",                 1);
      built_in_types.emplace("string16",                 1);
      built_in_types.emplace("namex",                 1);
      built_in_types.emplace("shuffled_witness_array_type",  1);


      built_in_types.emplace("asset",                     1);
      built_in_types.emplace("extensions_type",                     1);

      //built_in_types.emplace("comment_options_extension",                     1);


   }

   void rpc_api_serializer::set_abi(const abi_def& abi) {
      typedefs.clear();
      structs.clear();
      classes.clear();
//      actions.clear();
//      tables.clear();
//      error_messages.clear();

      for( const auto& st : abi.structs )
         structs[st.name] = st;

      for( const auto& td : abi.types ) {
         FC_ASSERT(is_type(td.type), "invalid type", ("type",td.type));
         FC_ASSERT(!is_type(td.new_type_name), "type already exists", ("new_type_name",td.new_type_name));
         typedefs[td.new_type_name] = td.type;
      }

      for( const auto& a : abi.classes )
         classes[a.name] = a;

      FC_ASSERT( typedefs.size() == abi.types.size() );
      FC_ASSERT( structs.size() == abi.structs.size() );
      FC_ASSERT( classes.size() == abi.classes.size() );

      validate();
   }

   bool rpc_api_serializer::is_builtin_type(const type_name& type)const {
      return built_in_types.find(type) != built_in_types.end();
   }

   bool rpc_api_serializer::is_integer(const type_name& type) const {
      string stype = type;
      return boost::starts_with(stype, "uint") || boost::starts_with(stype, "int");
   }

   int rpc_api_serializer::get_integer_size(const type_name& type) const {
      string stype = type;
      FC_ASSERT( is_integer(type), "${stype} is not an integer type", ("stype",stype));
      if( boost::starts_with(stype, "uint") ) {
         return boost::lexical_cast<int>(stype.substr(4));
      } else {
         return boost::lexical_cast<int>(stype.substr(3));
      }
   }

   bool rpc_api_serializer::is_struct(const type_name& type)const {
      return structs.find(resolve_type(type)) != structs.end();
   }

   bool rpc_api_serializer::is_array(const type_name& type)const {
      return ends_with(string(type), "[]");
   }

   bool rpc_api_serializer::is_map(const type_name& type)const {
      return ends_with(string(type), "}") && starts_with(string(type), "{");
   }

   bool rpc_api_serializer::is_optional(const type_name& type)const {
      return ends_with(string(type), "?");
   }

   type_name rpc_api_serializer::fundamental_type(const type_name& type)const {
      if( is_array(type) ) {
         return type_name(string(type).substr(0, type.size()-2));
      } else if ( is_optional(type) ) {
         return type_name(string(type).substr(0, type.size()-1));
      } else {
       return type;
      }
   }

   type_name rpc_api_serializer::fundamental_map_key_type(const type_name& type)const{
      string kv = string(type).substr(1, type.size()-2);
      std::vector<std::string> vecSegTag;
      boost::split(vecSegTag, kv,boost::is_any_of(","));
      return type_name(vecSegTag[0]);
   }
   type_name rpc_api_serializer::fundamental_map_value_type(const type_name& type)const{
      string kv = string(type).substr(1, type.size()-2);
      std::vector<std::string> vecSegTag;
      boost::split(vecSegTag, kv,boost::is_any_of(","));
      return type_name(vecSegTag[1]);
   }

   bool rpc_api_serializer::_is_type(const type_name& rtype, size_t recursion_depth)const {
      if( ++recursion_depth > max_recursion_depth) return false;

      if( is_array(rtype) ){
         type_name new_type(string(rtype).substr(0, rtype.size()-2));
         return _is_type(new_type,recursion_depth);
      }
      else if( is_optional(rtype) ){
         type_name new_type(string(rtype).substr(0, rtype.size()-1));
         return _is_type(new_type,recursion_depth);
      }
      else if ( is_map(rtype) ){
         type_name key_type = fundamental_map_key_type(rtype);
         if ( !_is_type(key_type, recursion_depth) ){
            return false;
         }
         type_name value_type = fundamental_map_value_type(rtype);
         if ( !_is_type(value_type, recursion_depth) ){
            return false;
         }
         return true;
      }
      auto type = rtype;
      if( built_in_types.find(type) != built_in_types.end() ) return true;
      if( typedefs.find(type) != typedefs.end() ) return _is_type(typedefs.find(type)->second, recursion_depth);
      if( structs.find(type) != structs.end() ) return true;
      return false;
   }

   const struct_def& rpc_api_serializer::get_struct(const type_name& type)const {
      auto itr = structs.find(resolve_type(type) );
      FC_ASSERT( itr != structs.end(), "Unknown struct ${type}", ("type",type) );
      return itr->second;
   }

   void rpc_api_serializer::validate()const {
      for( const auto& t : typedefs ) { try {
         vector<type_name> types_seen{t.first, t.second};
         auto itr = typedefs.find(t.second);
         while( itr != typedefs.end() ) {
            FC_ASSERT( find(types_seen.begin(), types_seen.end(), itr->second) == types_seen.end(), "Circular reference in type ${type}", ("type",t.first) );
            types_seen.emplace_back(itr->second);
            itr = typedefs.find(itr->second);
         }
      } FC_CAPTURE_AND_RETHROW( (t) ) }
      for( const auto& t : typedefs ) { try {
         FC_ASSERT(is_type(t.second), "", ("type",t.second) );
      } FC_CAPTURE_AND_RETHROW( (t) ) }
      for( const auto& s : structs ) { try {
         if( s.second.base != type_name() ) {
            struct_def current = s.second;
            vector<type_name> types_seen{current.name};
            while( current.base != type_name() ) {
               const auto& base = get_struct(current.base); //<-- force struct to inherit from another struct
               FC_ASSERT( find(types_seen.begin(), types_seen.end(), base.name) == types_seen.end(), "Circular reference in struct ${type}", ("type",s.second.name) );
               types_seen.emplace_back(base.name);
               current = base;
            }
         }
         for( const auto& field : s.second.fields ) { try {
            FC_ASSERT(is_type(field.type) );
         } FC_CAPTURE_AND_RETHROW( (field) ) }
      } FC_CAPTURE_AND_RETHROW( (s) ) }
   }

   type_name rpc_api_serializer::resolve_type(const type_name& type)const {
      auto itr = typedefs.find(type);
      if( itr != typedefs.end() ) {
         for( auto i = typedefs.size(); i > 0; --i ) { // avoid infinite recursion
            const type_name& t = itr->second;
            itr = typedefs.find( t );
            if( itr == typedefs.end() ) return t;
         }
      }
      return type;
   }


} }
