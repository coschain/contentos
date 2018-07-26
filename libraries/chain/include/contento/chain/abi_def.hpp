/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <contento/chain/types.hpp>

namespace contento { namespace chain {

using type_name      = string;
using field_name     = string;
//using action_name    = string;
using action_name16    = string;

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
   return_def           ret;

   bool operator==(const struct_def& other) const {
      return std::tie(name, base, fields, ret) == std::tie(other.name, other.base, other.fields, ret);
   }
};

struct action_def {
   action_def() = default;
   action_def(const action_name16& name, const type_name& type, const string& ricardian_contract)
   :name(name), type(type), ricardian_contract(ricardian_contract)
   {}

   action_name16 name;
   type_name   type;
   string      ricardian_contract;
};

struct table_def {
   table_def() = default;
   table_def(const table_name& name, const type_name& index_type, const vector<field_name>& key_names, const vector<type_name>& key_types, const type_name& type)
   :name(name), index_type(index_type), key_names(key_names), key_types(key_types), type(type)
   {}

   table_name         name;        // the name of the table
   type_name          index_type;  // the kind of index, i64, i128i128, etc
   vector<field_name> key_names;   // names for the keys defined by key_types
   vector<type_name>  key_types;   // the type of key parameters
   type_name          type;        // type of binary data stored in this table
};

struct clause_pair {
   clause_pair() = default;
   clause_pair( const string& id, const string& body )
   : id(id), body(body)
   {}

   string id;
   string body;
};

struct error_message {
   error_message() = default;
   error_message( uint64_t error_code, const string& error_msg )
   : error_code(error_code), error_msg(error_msg)
   {}

   uint64_t error_code;
   string   error_msg;
};

struct abi_def {
   abi_def() = default;
   abi_def(const vector<type_def>& types, const vector<struct_def>& structs, const vector<action_def>& actions, const vector<table_def>& tables, const vector<clause_pair>& clauses, const vector<error_message>& error_msgs)
   :version("contento::abi/1.0")
   ,types(types)
   ,structs(structs)
   ,actions(actions)
   ,tables(tables)
   ,ricardian_clauses(clauses)
   ,error_messages(error_msgs)
   {}

   string                version = "contento::abi/1.0";
   vector<type_def>      types;
   vector<struct_def>    structs;
   vector<action_def>    actions;
   vector<table_def>     tables;
   vector<clause_pair>   ricardian_clauses;
   vector<error_message> error_messages;
   extensions_type       abi_extensions;
};

abi_def contento_contract_abi(const abi_def& contento_system_abi);
vector<type_def> common_type_defs();

} } /// namespace contento::chain

FC_REFLECT( contento::chain::type_def                         , (new_type_name)(type) )
FC_REFLECT( contento::chain::field_def                        , (name)(type) )
FC_REFLECT( contento::chain::return_def                       , (type) )
FC_REFLECT( contento::chain::struct_def                       , (name)(base)(fields)(ret) )
FC_REFLECT( contento::chain::action_def                       , (name)(type)(ricardian_contract) )
FC_REFLECT( contento::chain::table_def                        , (name)(index_type)(key_names)(key_types)(type) )
FC_REFLECT( contento::chain::clause_pair                      , (id)(body) )
FC_REFLECT( contento::chain::error_message                    , (error_code)(error_msg) )
FC_REFLECT( contento::chain::abi_def                          , (version)(types)(structs)(actions)(tables)
                                                             (ricardian_clauses)(error_messages)(abi_extensions) )
