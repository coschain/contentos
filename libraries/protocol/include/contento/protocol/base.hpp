#pragma once

#include <contento/protocol/types.hpp>
#include <contento/protocol/authority.hpp>
#include <contento/protocol/version.hpp>

#include <fc/time.hpp>
#include <vector>

namespace contento { namespace protocol {

   enum admin_type
   {
      comment_delete,
      commercial
   };

   struct base_operation
   {
      void get_required_authorities( vector<authority>& )const {}
      void get_required_active_authorities( flat_set<account_name_type>& )const {}
      void get_required_posting_authorities( flat_set<account_name_type>& )const {}
      void get_required_owner_authorities( flat_set<account_name_type>& )const {}
      void get_required_admin( std::vector< std::pair<account_name_type, admin_type> >& admins ) const {}

      bool is_virtual()const { return false; }
      void validate()const {}
   };

   struct virtual_operation : public base_operation
   {
      bool is_virtual()const { return true; }
      void validate()const { FC_ASSERT( false, "This is a virtual operation" ); }
   };

   typedef static_variant<
      void_t,
      version,              // Normal witness version reporting, for diagnostics and voting
      hardfork_version_vote // Voting for the next hardfork to trigger
      >                                block_header_extensions;

   typedef static_variant<
      void_t
      >                                future_extensions;

   typedef flat_set<block_header_extensions > block_header_extensions_type;
   typedef flat_set<future_extensions> extensions_type;


} } // contento::protocol

FC_REFLECT_ENUM( contento::protocol::admin_type, (comment_delete)(commercial) )
FC_REFLECT_TYPENAME( contento::protocol::block_header_extensions )
FC_REFLECT_TYPENAME( contento::protocol::future_extensions )
