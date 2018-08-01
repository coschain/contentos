/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

//#include <contento/chain/types.hpp>

#include <fc/io/raw.hpp>
#include <fc/variant.hpp>
#include <fc/reflect/variant.hpp>

typedef std::vector<char>                bytes;
typedef std::vector<std::pair<uint16_t,std::vector<char>>> extensions_type;

namespace contento { namespace rpc_api {

   using std::string;
   using std::map;
   using std::set;
   using std::vector;

using type_name      = string;
using field_name     = string;
using action_name    = string;
using action_name16    = string;
   using table_name = string;
   using name = string;
   using class_name = string;

   
struct type_def {
   type_def() = default;
   type_def(const type_name& new_type_name, const type_name& type)
   :new_type_name(new_type_name), type(type)
   {}

   type_name   new_type_name;
   type_name   type;
};

struct field_def {
   field_def() = default;
   field_def(const field_name& name, const type_name& type)
   :name(name), type(type)
   {}

   field_name name;
   type_name  type;

   bool operator==(const field_def& other) const {
      return std::tie(name, type) == std::tie(other.name, other.type);
   }
};

struct return_def {
   return_def() = default;
   return_def(const type_name& type)
   :type(type)
   {}

   type_name  type;

   bool operator==(const return_def& other) const {
      return type == other.type;
   }
};

struct struct_def {
   struct_def() = default;
   struct_def(const type_name& name, const type_name& base, const vector<field_def>& fields)
   :name(name), base(base), fields(fields)
   {}

   type_name            name;
   type_name            base;
   vector<field_def>    fields;

   bool operator==(const struct_def& other) const {
      return std::tie(name, base, fields) == std::tie(other.name, other.base, other.fields);
   }
};

struct function_def {
   function_def() = default;
   function_def(const type_name& name, const return_def& ret, const vector<field_def>& fields)
   :name(name), fields(fields), ret(ret)
   {}

   type_name            name;
   vector<field_def>    fields;
   return_def           ret;

   bool operator==(const function_def& other) const {
      return std::tie(name, fields, ret) == std::tie(other.name, other.fields, other.ret);
   }
};

struct class_def {
   class_def() = default;
   class_def(const class_name& name, const vector<function_def>& functions )
   :name(name), functions(functions)
   {}

   class_name              name;
   vector<function_def>    functions;

   bool operator==(const class_def& other) const {
      return std::tie(name, functions) == std::tie(other.name, other.functions );
   }
};

struct action_def {
   action_def() = default;
   action_def(const action_name16& name, const type_name& type )
   :name(name), type(type)
   {}

   action_name16 name;
   type_name   type;
};


struct abi_def {
   abi_def() = default;
   abi_def(const vector<type_def>& types, const vector<struct_def>& structs, const vector<class_def>& classes)
   :version("contento::abi/1.0")
   ,types(types)
   ,structs(structs)
   ,classes(classes)
   {}

   string                version = "contento::rpc-api/1.0";
   vector<type_def>      types;
   vector<struct_def>    structs;
   vector<class_def>     classes;
//   vector<action_def>    actions;
   //vector<table_def>     tables;
   //vector<clause_pair>   ricardian_clauses;
   //vector<error_message> error_messages;
   //extensions_type       abi_extensions;
};

abi_def contento_contract_abi(const abi_def& contento_system_abi);

} } /// namespace contento::chain

FC_REFLECT( contento::rpc_api::type_def                         , (new_type_name)(type) )
FC_REFLECT( contento::rpc_api::field_def                        , (name)(type) )
FC_REFLECT( contento::rpc_api::function_def                        , (name)(fields)(ret) )

FC_REFLECT( contento::rpc_api::return_def                       , (type) )
FC_REFLECT( contento::rpc_api::struct_def                       , (name)(base)(fields) )
FC_REFLECT( contento::rpc_api::class_def                       , (name)(functions) )
FC_REFLECT( contento::rpc_api::abi_def                          , (version)(types)(structs)(classes) )
