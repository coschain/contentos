/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <contento/abi_generator/abi_serializer.hpp>
//#include <fc/io/raw.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

//#include <fc/io/varint.hpp>
//#include <contento/protocol/asset.hpp>

using namespace boost;

namespace contento { namespace chain {

   using boost::algorithm::ends_with;
   using std::string;

   abi_serializer::abi_serializer( const abi_def& abi ) {
      configure_built_in_types();
      set_abi(abi);
   }
   
   void abi_serializer::configure_built_in_types() {

      built_in_types.emplace("bool",                      true);
      built_in_types.emplace("int8",                      true);
      built_in_types.emplace("uint8",                     true);
      built_in_types.emplace("int16",                     true);
      built_in_types.emplace("uint16",                    true);
      built_in_types.emplace("int32",                     true);
      built_in_types.emplace("uint32",                    true);
      built_in_types.emplace("int64",                     true);
      built_in_types.emplace("uint64",                    true);
      built_in_types.emplace("int128",                    true);
      built_in_types.emplace("uint128",                   true);
      built_in_types.emplace("varint32",                  true);
      built_in_types.emplace("varuint32",                 true);

      // TODO: Add proper support for floating point types. For now this is good enough.
      built_in_types.emplace("float32",                   true);
      built_in_types.emplace("float64",                   true);
      built_in_types.emplace("float128",                  true);

      built_in_types.emplace("time_point",                true);
      built_in_types.emplace("time_point_sec",            true);
      //built_in_types.emplace("block_timestamp_type",      pack_unpack<block_timestamp_type>());

      built_in_types.emplace("name",                      true);
      built_in_types.emplace("namex",                     true);
      built_in_types.emplace("namex_",                    true);
      built_in_types.emplace("bytes",                     true);
      built_in_types.emplace("string",                    true);

      built_in_types.emplace("checksum160",               true);
      built_in_types.emplace("checksum256",               true);
      built_in_types.emplace("checksum512",               true);

      built_in_types.emplace("public_key",                true);
      built_in_types.emplace("signature",                 true);
   }

   void abi_serializer::set_abi(const abi_def& abi) {
      typedefs.clear();
      structs.clear();
      actions.clear();
      tables.clear();
      error_messages.clear();

      for( const auto& st : abi.structs )
         structs[st.name] = st;

      for( const auto& td : abi.types ) {
         FC_ASSERT(is_type(td.type), "invalid type", ("type",td.type));
         FC_ASSERT(!is_type(td.new_type_name), "type already exists", ("new_type_name",td.new_type_name));
         typedefs[td.new_type_name] = td.type;
      }

      for( const auto& a : abi.actions )
         actions[a.name] = a.type;

      for( const auto& t : abi.tables )
         tables[t.name] = t.type;

      for( const auto& e : abi.error_messages )
         error_messages[e.error_code] = e.error_msg;

      /**
       *  The ABI vector may contain duplicates which would make it
       *  an invalid ABI
       */
      FC_ASSERT( typedefs.size() == abi.types.size() );
      FC_ASSERT( structs.size() == abi.structs.size() );
      FC_ASSERT( actions.size() == abi.actions.size() );
      FC_ASSERT( tables.size() == abi.tables.size() );
      FC_ASSERT( error_messages.size() == abi.error_messages.size() );

      validate();
   }

   bool abi_serializer::is_builtin_type(const type_name& type)const {
      return built_in_types.find(type) != built_in_types.end();
   }

   bool abi_serializer::is_integer(const type_name& type) const {
      string stype = type;
      return boost::starts_with(stype, "uint") || boost::starts_with(stype, "int");
   }

   int abi_serializer::get_integer_size(const type_name& type) const {
      string stype = type;
      FC_ASSERT( is_integer(type), "${stype} is not an integer type", ("stype",stype));
      if( boost::starts_with(stype, "uint") ) {
         return boost::lexical_cast<int>(stype.substr(4));
      } else {
         return boost::lexical_cast<int>(stype.substr(3));
      }
   }

   bool abi_serializer::is_struct(const type_name& type)const {
      return structs.find(resolve_type(type)) != structs.end();
   }

   bool abi_serializer::is_array(const type_name& type)const {
      return ends_with(string(type), "[]");
   }

   bool abi_serializer::is_optional(const type_name& type)const {
      return ends_with(string(type), "?");
   }

   type_name abi_serializer::fundamental_type(const type_name& type)const {
      if( is_array(type) ) {
         return type_name(string(type).substr(0, type.size()-2));
      } else if ( is_optional(type) ) {
         return type_name(string(type).substr(0, type.size()-1));
      } else {
       return type;
      }
   }

   bool abi_serializer::_is_type(const type_name& rtype, size_t recursion_depth)const {
      if( ++recursion_depth > max_recursion_depth) return false;
      auto type = fundamental_type(rtype);
      if( built_in_types.find(type) != built_in_types.end() ) return true;
      if( typedefs.find(type) != typedefs.end() ) return _is_type(typedefs.find(type)->second, recursion_depth);
      if( structs.find(type) != structs.end() ) return true;
      return false;
   }

   const struct_def& abi_serializer::get_struct(const type_name& type)const {
      auto itr = structs.find(resolve_type(type) );
      FC_ASSERT( itr != structs.end(), "Unknown struct ${type}", ("type",type) );
      return itr->second;
   }

   void abi_serializer::validate()const {
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
      for( const auto& a : actions ) { try {
        FC_ASSERT(is_type(a.second), "", ("type",a.second) );
      } FC_CAPTURE_AND_RETHROW( (a)  ) }

      for( const auto& t : tables ) { try {
        FC_ASSERT(is_type(t.second), "", ("type",t.second) );
      } FC_CAPTURE_AND_RETHROW( (t)  ) }
   }

   type_name abi_serializer::resolve_type(const type_name& type)const {
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


   type_name abi_serializer::get_action_type(name action)const {
      auto itr = actions.find(action);
      if( itr != actions.end() ) return itr->second;
      return type_name();
   }
   type_name abi_serializer::get_table_type(name action)const {
      auto itr = tables.find(action);
      if( itr != tables.end() ) return itr->second;
      return type_name();
   }

   string abi_serializer::get_error_message( uint64_t error_code )const {
      auto itr = error_messages.find( error_code );
      if( itr == error_messages.end() )
         return string("");

      return itr->second;
   }

} }
