#include <algorithm>
#include <contento/chain/apply_context.hpp>
#include <contento/chain/transaction_context.hpp>
#include <contento/chain/exceptions.hpp>
#include <contento/chain/wasm_interface.hpp>
//#include <contento/chain/generated_transaction_object.hpp>
//#include <contento/chain/authorization_manager.hpp>
//#include <contento/chain/resource_limits.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/contract_balance_object.hpp>

//#include <contento/chain/global_property_object.hpp>

/*#include <contento/protocol/authority.hpp>
#include <contento/chain/account_object.hpp>
#include <eosio/chain/apply_context.hpp>
#include <eosio/chain/controller.hpp>
#include <eosio/chain/transaction_context.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/wasm_interface.hpp>
#include <eosio/chain/generated_transaction_object.hpp>
#include <eosio/chain/authorization_manager.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/account_object.hpp>
#include <eosio/chain/global_property_object.hpp>
*/
#include <boost/container/flat_set.hpp>

using boost::container::flat_set;

namespace contento { namespace chain {

static inline void print_debug(account_name receiver, const std::string& log, const vm_operation& op) {
   if (!log.empty()) {
      auto prefix = fc::format_string(
                                      "\n[(${a},${n})->${r}]",
                                      fc::mutable_variant_object()
                                      ("a", op.contract_name)
                                      ("n", op.action_name)
                                      ("r", receiver));
      dlog(prefix + ": CONSOLE OUTPUT BEGIN =====================\n"
           + log
           + prefix + ": CONSOLE OUTPUT END   =====================" );
   }
}

void apply_context::exec_one()
{
   //const auto& cfg = control.get_global_properties().configuration;
   try {
      const auto &a = control.get_account(receiver);
      privileged = a.privileged;
      auto native = control.find_apply_handler(receiver, op.contract_name, op.action_name);
       std::cout << "contract_name = " << std::string(op.contract_name) << " action name = " <<
        std::string(op.action_name) << std::endl;
      if( native ) {
         (*native)(*this);
         return;
      }

      if( a.code.size() > 0
          && !(op.contract_name == config::system_account_name && op.action_name == N(setcode) && receiver == config::system_account_name) )
      {
         try {
            control.get_wasm_interface().apply(a.code_version, a.code, *this);
         } catch ( const wasm_exit& ){}
      }

   } FC_CAPTURE_AND_RETHROW((_pending_console_output.str()));

   //std::cout << "***************\nVM EXCUTE:\n" << _pending_console_output.str() << "\n*************\n" << std::endl;
   print_debug(receiver, _pending_console_output.str(), op);
   reset_console();
}

void apply_context::exec()
{
   _notified.push_back(receiver);
    std::cout << std::string(receiver) << std::endl;
   exec_one();
   for( uint32_t i = 1; i < _notified.size(); ++i ) {
      receiver = _notified[i];
      exec_one();
   }

   if(_inline_ops.size() > 0 ) {
      EOS_ASSERT( recurse_depth < 10, /*TODOO: put this in config*/
                  transaction_exception, "inline vm_operation recursion depth reached" );
   }

   for( const auto& inline_op : _inline_ops ) {
      trx_context.apply( inline_op, inline_op.contract_name, false, recurse_depth + 1 );
   }

} /// exec()

bool apply_context::is_account( const account_name& account )const {
   return nullptr != db.find<account_object,by_name>( account );
}
/*
void apply_context::require_authorization( const account_name& account ) {
    //todo ... change impl to use steem's db to verify accout's sig
    contento::protocol::authority active = contento::protocol::authority(db.get< contento::chain::account_authority_object, contento::chain::by_account >( account ).active);
    contento::protocol::authority owner = contento::protocol::authority(db.get< contento::chain::account_authority_object, contento::chain::by_account >( account ).owner);
    contento::protocol::authority posting = contento::protocol::authority(db.get< contento::chain::account_authority_object, contento::chain::by_account >( account ).posting);

    const contento::protocol::chain_id_type& chain_id = CONTENTO_CHAIN_ID;
    flat_set<public_key_type> trx_pubs = trx_context.trx.get_signature_keys(chain_id);

    for( const auto& k : posting.key_auths ) {
        if( trx_pubs.find( k.first ) != trx_pubs.end() ) {
            return;
        }
    }
    for( const auto& k : active.key_auths ) {
        if( trx_pubs.find( k.first ) != trx_pubs.end() ) {
            return;
        }
    }
    for( const auto& k : owner.key_auths ) {
        if( trx_pubs.find( k.first ) != trx_pubs.end() ) {
            return;
        }
    }
    
    EOS_ASSERT( false, missing_auth_exception, "missing authority of ${account}", ("account",account));
    
   //for( uint32_t i=0; i < act.authorization.size(); i++ ) {
   //  if( act.authorization[i].actor == account ) {
   //     used_authorizations[i] = true;
   //     return;
   //  }
   //}
   //EOS_ASSERT( false, missing_auth_exception, "missing authority of ${account}", ("account",account));
}
*/

void apply_context::require_authorization( const account_name& account ) {
    auto get_active  = [&]( const string& name ) { return contento::protocol::authority( db.get< contento::chain::account_authority_object, contento::chain::by_account >( name ).active ); };
    auto get_owner   = [&]( const string& name ) { return contento::protocol::authority( db.get< contento::chain::account_authority_object, contento::chain::by_account >( name ).owner );  };
    auto get_posting = [&]( const string& name ) { return contento::protocol::authority( db.get< contento::chain::account_authority_object, contento::chain::by_account >( name ).posting );  };

    const contento::protocol::chain_id_type& chain_id = CONTENTO_CHAIN_ID;
    try {
        trx_context.trx.verify_authority( chain_id, get_active, get_owner, get_posting, 0 );
    }
    catch( protocol::tx_missing_active_auth& e )
    {
        throw e;
    }
}

bool apply_context::has_authorization( const account_name& account )const {
    /*
   for( const auto& auth : act.authorization )
     if( auth.actor == account )
        return true;*/
  return false;
}

bool apply_context::has_recipient( account_name code )const {
   for( auto a : _notified )
      if( a == code )
         return true;
   return false;
}

void apply_context::require_recipient( account_name recipient ) {
   if( !has_recipient(recipient) ) {
      _notified.push_back(recipient);
   }
}


/*
 *  This will execute an vm_operation after checking the authorization. Inline transactions are
 *  implicitly authorized by the current receiver (running code). This method has significant
 *  security considerations and several options have been considered:
 *
 *  1. priviledged accounts (those marked as such by block producers) can authorize any vm_operation
 *  2. all other actions are only authorized by 'receiver' which means the following:
 *         a. the user must set permissions on their account to allow the 'receiver' to act on their behalf
 *
 *  Discarded Implemenation:  at one point we allowed any account that authorized the current transaction
 *   to implicitly authorize an inline transaction. This approach would allow privelege escalation and
 *   make it unsafe for users to interact with certain contracts.  We opted instead to have applications
 *   ask the user for permission to take certain actions rather than making it implicit. This way users
 *   can better understand the security risk.
 */
void apply_context::execute_inline( vm_operation&& op ) {
   auto* code = control.db().find<account_object, by_name>(op.contract_name);
   EOS_ASSERT( code != nullptr, action_validate_exception,
               "inline vm_operation's code account ${account} does not exist", ("account", op.contract_name) );

    /*
   for( const auto& auth : a.authorization ) {
      auto* actor = control.db().find<account_object, by_name>(auth.actor);

      EOS_ASSERT( actor != nullptr, action_validate_exception,
                  "inline vm_operation's authorizing actor ${account} does not exist", ("account", auth.actor) );
   }*/

   // No need to check authorization if: replaying irreversible blocks; contract is privileged; or, contract is calling itself.
    /* TODO: check auth
     
   if( !control.skip_auth_check() && !privileged && a.account != receiver ) {
      control.get_authorization_manager()
             .check_authorization( {a},
                                   flat_set<public_key_type>(),
                                   {{receiver, config::contento_code_name}},
                                   control.pending_block_time() - trx_context.published,
                                   std::bind(&transaction_context::checktime, &this->trx_context),
                                   false
                                 );
     

      //QUESTION: Is it smart to allow a deferred transaction that has been delayed for some time to get away
      //          with sending an inline vm_operation that requires a delay even though the decision to send that inline
      //          vm_operation was made at the moment the deferred transaction was executed with potentially no forewarning?
   }*/

   _inline_ops.emplace_back( move(op) );
}

////Y
// void apply_context::execute_context_free_inline( vm_operation&& a ) {
//    auto* code = control.db().find<account_object, by_name>(a.account);
//    EOS_ASSERT( code != nullptr, action_validate_exception,
//                "inline vm_operation's code account ${account} does not exist", ("account", a.account) );

//    EOS_ASSERT( a.authorization.size() == 0, action_validate_exception,
//                "context-free actions cannot have authorizations" );

//    _cfa_inline_actions.emplace_back( move(a) );
// }

const table_id_object* apply_context::find_table( name code, name scope, name table ) {
   return db.find<table_id_object, by_code_scope_table>(boost::make_tuple(code, scope, table));
}

const table_id_object& apply_context::find_or_create_table( name code, name scope, name table, const account_name &payer ) {
   const auto* existing_tid =  db.find<table_id_object, by_code_scope_table>(boost::make_tuple(code, scope, table));
   if (existing_tid != nullptr) {
      return *existing_tid;
   }

   update_db_usage(payer, config::billable_size_v<table_id_object>);

   return db.create<table_id_object>([&](table_id_object &t_id){
      t_id.code = code;
      t_id.scope = scope;
      t_id.table = table;
      t_id.payer = payer;
   });
}

void apply_context::remove_table( const table_id_object& tid ) {
   update_db_usage(tid.payer, - config::billable_size_v<table_id_object>);
   db.remove(tid);
}

void apply_context::reset_console() {
   _pending_console_output = std::ostringstream();
   _pending_console_output.setf( std::ios::scientific, std::ios::floatfield );
}

bytes apply_context::get_packed_transaction() {
   auto r = fc::raw::pack( static_cast<const transaction&>(trx_context.trx) );
   return r;
}

void apply_context::update_db_usage( const account_name& payer, int64_t delta ) {
   /* TODOO: if( delta > 0 ) {
      if( !(privileged || payer == account_name(receiver)) ) {
         require_authorization( payer );
      }
   }
   trx_context.add_ram_usage(payer, delta);
    */
    
    //
    // caller pays for everything.
    //
    trx_context.add_ram_usage( op.caller, delta );
}

void apply_context::add_action_price(uint64_t price, int wasm_expr_id) {
    trx_context.add_wasm_price( op.caller, price );
}

int apply_context::get_action( uint32_t type, uint32_t index, char* buffer, size_t buffer_size )const
{
    /* TODOO:
   const auto& trx = trx_context.trx;
   const vm_operation* act_ptr = nullptr;

   if( type == 0 ) {
      ////Y
      // if( index >= trx.context_free_actions.size() )
      //    return -1;
      // act_ptr = &trx.context_free_actions[index];
      return -1;
   }
   else if( type == 1 ) {
      if( index >= trx.actions.size() )
         return -1;
      act_ptr = &trx.actions[index];
   }

   FC_ASSERT(act_ptr, "vm_operation is not found" );

   auto ps = fc::raw::pack_size( *act_ptr );
   if( ps <= buffer_size ) {
      fc::datastream<char*> ds(buffer, buffer_size);
      fc::raw::pack( ds, *act_ptr );
   }
   return ps;
     */
    return 0;
}

    /*
int apply_context::get_context_free_data( uint32_t index, char* buffer, size_t buffer_size )const
{
   const auto& trx = trx_context.trx;

   if( index >= trx.context_free_data.size() ) return -1;

   auto s = trx.context_free_data[index].size();
   if( buffer_size == 0 ) return s;

   auto copy_size = std::min( buffer_size, s );
   memcpy( buffer, trx.context_free_data[index].data(), copy_size );

   return copy_size;
}
     */

int apply_context::db_store_i64( uint64_t scope, uint64_t table, const account_name& payer, uint64_t id, const char* buffer, size_t buffer_size ) {
   return db_store_i64( receiver.to_uint64_t(), scope, table, payer, id, buffer, buffer_size);
}

int apply_context::db_store_i64( uint64_t code, uint64_t scope, uint64_t table, const account_name& payer, uint64_t id, const char* buffer, size_t buffer_size ) {
//   require_write_lock( scope );
   const auto& tab = find_or_create_table( code, scope, table, payer );
   auto tableid = tab.id;

   FC_ASSERT( payer != account_name(), "must specify a valid account to pay for new record" );

   const auto& obj = db.create<key_value_object>( [&]( auto& o ) {
      o.t_id        = tableid;
      o.primary_key = id;
      o.value.resize( buffer_size );
      o.payer       = payer;
      memcpy( (void*)o.value.data(), buffer, buffer_size );
   });

   db.modify( tab, [&]( auto& t ) {
     ++t.count;
   });

   int64_t billable_size = (int64_t)(buffer_size + config::billable_size_v<key_value_object>);
   update_db_usage( payer, billable_size);

   keyval_cache.cache_table( tab );
   return keyval_cache.add( obj );
}

void apply_context::db_update_i64( int iterator, account_name payer, const char* buffer, size_t buffer_size ) {
   const key_value_object& obj = keyval_cache.get( iterator );

   const auto& table_obj = keyval_cache.get_table( obj.t_id );
   FC_ASSERT( table_obj.code == receiver, "db access violation" );

//   require_write_lock( table_obj.scope );

   const int64_t overhead = config::billable_size_v<key_value_object>;
   int64_t old_size = (int64_t)(obj.value.size() + overhead);
   int64_t new_size = (int64_t)(buffer_size + overhead);

   if( payer == account_name() ) payer = obj.payer;

   if( account_name(obj.payer) != payer ) {
      // refund the existing payer
      update_db_usage( obj.payer,  -(old_size) );
      // charge the new payer
      update_db_usage( payer,  (new_size));
   } else if(old_size != new_size) {
      // charge/refund the existing payer the difference
      update_db_usage( obj.payer, new_size - old_size);
   }

   db.modify( obj, [&]( auto& o ) {
     o.value.resize( buffer_size );
     memcpy( (void*)o.value.data(), buffer, buffer_size );
     o.payer = payer;
   });
}

void apply_context::db_remove_i64( int iterator ) {
   const key_value_object& obj = keyval_cache.get( iterator );

   const auto& table_obj = keyval_cache.get_table( obj.t_id );
   FC_ASSERT( table_obj.code == receiver, "db access violation" );

//   require_write_lock( table_obj.scope );

   update_db_usage( obj.payer,  -(obj.value.size() + config::billable_size_v<key_value_object>) );

   db.modify( table_obj, [&]( auto& t ) {
      --t.count;
   });
   db.remove( obj );

   if (table_obj.count == 0) {
      remove_table(table_obj);
   }

   keyval_cache.remove( iterator );
}

int apply_context::db_get_i64( int iterator, char* buffer, size_t buffer_size ) {
   const key_value_object& obj = keyval_cache.get( iterator );

   auto s = obj.value.size();
   if( buffer_size == 0 ) return s;

   auto copy_size = std::min( buffer_size, s );
   memcpy( buffer, obj.value.data(), copy_size );

   return copy_size;
}

int apply_context::db_next_i64( int iterator, uint64_t& primary ) {
   if( iterator < -1 ) return -1; // cannot increment past end iterator of table

   const auto& obj = keyval_cache.get( iterator ); // Check for iterator != -1 happens in this call
   const auto& idx = db.get_index<key_value_index, by_scope_primary>();

   auto itr = idx.iterator_to( obj );
   ++itr;

   if( itr == idx.end() || itr->t_id != obj.t_id ) return keyval_cache.get_end_iterator_by_table_id(obj.t_id);

   primary = itr->primary_key;
   return keyval_cache.add( *itr );
}

int apply_context::db_previous_i64( int iterator, uint64_t& primary ) {
   const auto& idx = db.get_index<key_value_index, by_scope_primary>();

   if( iterator < -1 ) // is end iterator
   {
      auto tab = keyval_cache.find_table_by_end_iterator(iterator);
      FC_ASSERT( tab, "not a valid end iterator" );

      auto itr = idx.upper_bound(tab->id);
      if( idx.begin() == idx.end() || itr == idx.begin() ) return -1; // Empty table

      --itr;

      if( itr->t_id != tab->id ) return -1; // Empty table

      primary = itr->primary_key;
      return keyval_cache.add(*itr);
   }

   const auto& obj = keyval_cache.get(iterator); // Check for iterator != -1 happens in this call

   auto itr = idx.iterator_to(obj);
   if( itr == idx.begin() ) return -1; // cannot decrement past beginning iterator of table

   --itr;

   if( itr->t_id != obj.t_id ) return -1; // cannot decrement past beginning iterator of table

   primary = itr->primary_key;
   return keyval_cache.add(*itr);
}

int apply_context::db_find_i64( uint64_t code, uint64_t scope, uint64_t table, uint64_t id ) {
   //require_read_lock( code, scope ); // redundant?

   const auto* tab = find_table( code, scope, table );
   if( !tab ) return -1;

   auto table_end_itr = keyval_cache.cache_table( *tab );

   const key_value_object* obj = db.find<key_value_object, by_scope_primary>( boost::make_tuple( tab->id, id ) );
   if( !obj ) return table_end_itr;

   return keyval_cache.add( *obj );
}

int apply_context::db_lowerbound_i64( uint64_t code, uint64_t scope, uint64_t table, uint64_t id ) {
   //require_read_lock( code, scope ); // redundant?

   const auto* tab = find_table( code, scope, table );
   if( !tab ) return -1;

   auto table_end_itr = keyval_cache.cache_table( *tab );

   const auto& idx = db.get_index<key_value_index, by_scope_primary>();
   auto itr = idx.lower_bound( boost::make_tuple( tab->id, id ) );
   if( itr == idx.end() ) return table_end_itr;
   if( itr->t_id != tab->id ) return table_end_itr;

   return keyval_cache.add( *itr );
}

int apply_context::db_upperbound_i64( uint64_t code, uint64_t scope, uint64_t table, uint64_t id ) {
   //require_read_lock( code, scope ); // redundant?

   const auto* tab = find_table( code, scope, table );
   if( !tab ) return -1;

   auto table_end_itr = keyval_cache.cache_table( *tab );

   const auto& idx = db.get_index<key_value_index, by_scope_primary>();
   auto itr = idx.upper_bound( boost::make_tuple( tab->id, id ) );
   if( itr == idx.end() ) return table_end_itr;
   if( itr->t_id != tab->id ) return table_end_itr;

   return keyval_cache.add( *itr );
}

int apply_context::db_end_i64( uint64_t code, uint64_t scope, uint64_t table ) {
   //require_read_lock( code, scope ); // redundant?

   const auto* tab = find_table( code, scope, table );
   if( !tab ) return -1;

   return keyval_cache.cache_table( *tab );
}

uint64_t apply_context::next_global_sequence() {
    /* TODO:
   const auto& p = control.get_dynamic_global_properties();
   db.modify( p, [&]( auto& dgp ) {
      ++dgp.global_action_sequence;
   });
   return p.global_action_sequence;
     */
    return 0;
}

uint64_t apply_context::next_recv_sequence( account_name receiver ) {
   const auto& rs = db.get<account_sequence_object,by_name>( receiver );
   db.modify( rs, [&]( auto& mrs ) {
      ++mrs.recv_sequence;
   });
   return rs.recv_sequence;
}

std::vector<char> apply_context::on_vm_request( const std::vector<char>& req_body ){
   return control.get_vm_interface()->on_vm_request(req_body);
}

bool apply_context::excute_operation( const std::vector<char>& op_buff ){

   fc::datastream<char*> ds( (char*)op_buff.data(), op_buff.size());
   contento::protocol::operation op;
   fc::raw::unpack(ds, op);

   EOS_ASSERT( !is_vm_operation(op), transaction_exception, "Cant\'t Excute vm_operation, use send_inline instead");
   EOS_ASSERT( !is_virtual_operation(op), transaction_exception, "virtual operation not permitted");
   return control.get_op_excutor()->execute_operation( trx_context, op);
}

asset apply_context::get_contract_balance()  {
    const auto& account = control.get_contract_account(receiver);
    return account.coc_balance;
}
    
void apply_context::transfer( account_name name, const asset& value)  {
    
    const auto& to_account = control.get_account(name);
    const auto& from_account = control.get_contract_account(receiver);
    
    FC_ASSERT( get_contract_balance() >= value, "Contract does not have sufficient funds for transfer." );
//    asset s(value,COC_SYMBOL);
    control.adjust_contract_balance( from_account, -value );
    control.adjust_balance( to_account, value );
}
    
int64_t apply_context::get_value() {
    return op.value.amount.value;
}
} } /// contento::chain
