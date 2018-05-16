#pragma once
#include <contento/protocol/types.hpp>
#include <contento/chain/steem_object_types.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>

namespace contento { namespace chain {
   using contento::protocol::public_key_type;
   using contento::protocol::account_name_type;
   using contento::protocol::weight_type;

   namespace bip = boost::interprocess;

   // TODO: move
   struct report_info_type
   {
      report_info_type() {}
      report_info_type(const account_name_type& acc, const asset& credit, const string& tag)
            : reporter(acc), credit(credit), tag(tag) {}

      account_name_type     reporter;
      asset                 credit;
      string                tag;
   };

   struct shared_report_info
   {
   private:
      shared_report_info() = delete;

   public:
      template< typename Allocator >
      shared_report_info( const Allocator& alloc )
         : total_credit(0),
         account_reports( account_pair_allocator_type( alloc.get_segment_manager() ) ) 
      {}

      void add_report(const account_name_type& acc, const asset& credit, const string& tag)
      {
         asset delta(credit);

         auto itr = account_reports.find(acc);
         if( itr != account_reports.end() )
            delta = credit - itr->second.credit;

         account_reports[acc] = report_info_type(acc, credit, tag);
         total_credit += delta;
      }

      asset total_credit;

      typedef bip::allocator< 
            shared_report_info, 
            bip::managed_mapped_file::segment_manager 
      > allocator_type;

      typedef bip::allocator< 
            std::pair< account_name_type, report_info_type >, 
            bip::managed_mapped_file::segment_manager 
      > account_pair_allocator_type;

      typedef bip::flat_map< 
            account_name_type, 
            report_info_type, 
            std::less< account_name_type >, 
            account_pair_allocator_type 
      > account_report_map;
      
      account_report_map     account_reports;
   };

} } //contento::chain

FC_REFLECT_TYPENAME( contento::chain::shared_report_info::account_report_map)
FC_REFLECT( contento::chain::shared_report_info, (total_credit)(account_reports) )
