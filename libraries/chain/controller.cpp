#include <contento/chain/controller.hpp>

#include <contento/chain/contract_table_objects.hpp>
#include <contento/chain/global_property_object.hpp>
#include <chainbase/chainbase.hpp>
#include <fc/io/json.hpp>
#include <contento/chain/exceptions.hpp>
#include <contento/chain/contento_contract.hpp>
#include <contento/chain/contract_balance_object.hpp>

namespace contento { namespace chain {


struct controller_impl {
   controller&                    self;
   chainbase::database&           db;

   wasm_interface                 wasmif;
   chain_id_type                  chain_id;

   typedef pair<scope_name,action_name>                   handler_key;
   map< account_name, map<handler_key, apply_handler> >   apply_handlers;

   /**
    *  Transactions that were undone by pop_block or abort_block, transactions
    *  are removed from this list if they are re-applied in other blocks. Producers
    *  can query this list when scheduling new transactions into blocks.
    */

   void set_apply_handler( account_name receiver, account_name contract, action_name action, apply_handler v ) {
      apply_handlers[receiver][make_pair(contract,action)] = v;
   }

   controller_impl( controller& s, chainbase::database &db )
   :self(s),
    db(db),
    wasmif( wasm_interface::vm_type::binaryen )
   {

#define SET_APP_HANDLER( receiver, contract, action) \
   set_apply_handler( #receiver, #contract, #action, &BOOST_PP_CAT(apply_, BOOST_PP_CAT(contract, BOOST_PP_CAT(_,action) ) ) )

   SET_APP_HANDLER( contento, contento, setcode );
   SET_APP_HANDLER( contento, contento, setabi );

   }

   ~controller_impl() {}

   void add_indices() {

      db.add_index<account_sequence_index>();

      db.add_index<table_id_multi_index>();
      db.add_index<key_value_index>();
      db.add_index<index64_index>();
      db.add_index<index128_index>();
      db.add_index<index256_index>();
      db.add_index<index_double_index>();
      db.add_index<index_long_double_index>();

   }

   bool failure_is_subjective( const fc::exception& e ) {
      auto code = e.code();
      return    (code == subjective_block_production_exception::code_value)
             || (code == block_net_usage_exceeded::code_value)
             || (code == block_cpu_usage_exceeded::code_value)
             || (code == deadline_exception::code_value)
             || (code == leeway_deadline_exception::code_value)
             || (code == actor_whitelist_exception::code_value)
             || (code == actor_blacklist_exception::code_value)
             || (code == contract_whitelist_exception::code_value)
             || (code == contract_blacklist_exception::code_value)
             || (code == action_blacklist_exception::code_value)
             || (code == key_blacklist_exception::code_value);
   }
};


controller::controller(chainbase::database &db)
:my( new controller_impl( *this, db ))
{
}

const dynamic_global_property_object& controller::get_global_properties() const
{
   return my->db.get< dynamic_global_property_object >();
}

const time_point_sec controller::head_block_time()const
{
   return get_global_properties().time;
}

void controller::add_indices() {
   my->add_indices();
}

bool controller::is_producing_block() const {
      // TODO:
      return false;
}

const account_object& controller::get_account( account_name name )const
{ try {
   return my->db.get<account_object, by_name>(name);
} FC_CAPTURE_AND_RETHROW( (name) ) }

const contract_balance_object& controller::get_contract_account( account_name name )const
{ try {
    return my->db.get<contract_balance_object, by_name >( name );
} FC_CAPTURE_AND_RETHROW( (name) ) }
    
void controller::adjust_balance( const account_object& a, const asset& delta )
{
    my->db.modify( a, [&]( account_object& acnt )
           {
               switch( delta.symbol )
               {
                   case COC_SYMBOL:
                       acnt.balance += delta;
                       break;
                   default:
                       FC_ASSERT( false, "invalid symbol" );
               }
           } );
}
    
void controller::adjust_contract_balance( const contract_balance_object& a, const asset& delta )
{
    my->db.modify( a, [&]( contract_balance_object& cbo )
           {
               switch( delta.symbol )
               {
                   case COC_SYMBOL:
                       cbo.coc_balance += delta;
                       break;
                   default:
                       FC_ASSERT( false, "invalid symbol" );
               }
           } );
}

controller::~controller() {
}

chainbase::database& controller::db()const { return my->db; }



const apply_handler* controller::find_apply_handler( account_name receiver, account_name scope, action_name act ) const
{
   auto native_handler_scope = my->apply_handlers.find( receiver );
   if( native_handler_scope != my->apply_handlers.end() ) {
      auto handler = native_handler_scope->second.find( make_pair( scope, act ) );
      if( handler != native_handler_scope->second.end() )
         return &handler->second;
   }
   return nullptr;
}
wasm_interface& controller::get_wasm_interface() {
   return my->wasmif;
}

} } /// contento::chain
