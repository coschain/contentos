/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <contento/abi_generator/abi_def.hpp>

namespace contento { namespace chain {

using std::map;
using std::string;
using std::function;
using std::pair;


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

    template<typename Vec>
   static bool is_empty_abi(const Vec& abi_vec)
   {
      return abi_vec.size() <= 4;
   }

   static constexpr size_t max_recursion_depth = 128; // arbitrary depth to prevent infinite recursion

private:

    bool _is_type(const type_name& type, size_t recursion_depth)const;
};

} } // contento::chain
