#include <contento/app/api_context.hpp>
#include <contento/app/application.hpp>
#include <contento/vmapi/contento_vm_api.hpp>

#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>


#include <cctype>

#include <cfenv>
#include <iostream>


namespace contento { namespace vmi {

class contento_vm_api_impl;


class contento_vm_api_impl : public std::enable_shared_from_this<contento_vm_api_impl>
{
   public:
      contento_vm_api_impl( const contento::app::api_context& ctx  );
      ~contento_vm_api_impl();

      // Accounts
      vector< account_obj_vmi > get_accounts( vector< string > names )const;
      set<string> lookup_accounts(const string& lower_bound_name, uint32_t limit)const;
      uint64_t get_account_count()const;

      contento::chain::database&                _db;
};

//////////////////////////////////////////////////////////////////////
//                                                                  //
// Constructors                                                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////

contento_vm_api::contento_vm_api( const contento::app::api_context& ctx )
   : my( new contento_vm_api_impl( ctx ) ) {}

contento_vm_api::~contento_vm_api() {}

contento_vm_api_impl::contento_vm_api_impl( const contento::app::api_context& ctx )
   : _db( *ctx.app.chain_database() )
{
   wlog("creating database api ${x}", ("x",int64_t(this)) );
}

contento_vm_api_impl::~contento_vm_api_impl()
{
   elog("freeing database api ${x}", ("x",int64_t(this)) );
}

void contento_vm_api::on_api_startup() {}

//////////////////////////////////////////////////////////////////////
//                                                                  //
// Accounts                                                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////

vector< account_obj_vmi > contento_vm_api::get_accounts( vector< string > names )const
{
   return my->_db.with_read_lock( [&]()
   {
      return my->get_accounts( names );
   });
}

vector< account_obj_vmi > contento_vm_api_impl::get_accounts( vector< string > names )const
{
   const auto& idx  = _db.get_index< account_index >().indices().get< by_name >();
   vector< account_obj_vmi > results;

   for( auto name: names )
   {
      auto itr = idx.find( name );
      if ( itr != idx.end() )
      {
         results.push_back( account_obj_vmi( *itr ) );
      }
   }

   return results;
}

uint64_t contento_vm_api::get_account_count()const
{
   return my->_db.with_read_lock( [&]()
   {
      return my->get_account_count();
   });
}

uint64_t contento_vm_api_impl::get_account_count()const
{
   return _db.get_index<account_index>().indices().size();
}



} } 
