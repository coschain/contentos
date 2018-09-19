#include <contento/protocol/contento_operations.hpp>
#include <contento/chain/block_summary_object.hpp>
#include <contento/chain/compound.hpp>
#include <contento/chain/custom_operation_interpreter.hpp>
#include <contento/chain/database.hpp>
#include <contento/chain/database_exceptions.hpp>
#include <contento/chain/db_with.hpp>
#include <contento/chain/evaluator_registry.hpp>
#include <contento/chain/global_property_object.hpp>
#include <contento/chain/global_reward_property_object.hpp>
#include <contento/chain/history_object.hpp>
#include <contento/chain/index.hpp>
#include <contento/chain/contento_evaluator.hpp>
#include <contento/chain/contento_objects.hpp>
#include <contento/chain/transaction_object.hpp>
#include <contento/chain/operation_notification.hpp>
#include <contento/chain/witness_schedule.hpp>
#include <contento/chain/contract_balance_object.hpp>

#include <contento/chain/util/asset.hpp>
#include <contento/chain/util/reward.hpp>
#include <contento/chain/util/uint256.hpp>
#include <contento/chain/util/reward.hpp>

#include <contento/protocol/transaction.hpp>


#include <fc/smart_ref_impl.hpp>
#include <fc/uint128.hpp>

#include <fc/container/deque.hpp>

#include <fc/io/fstream.hpp>

#include <cstdint>
#include <deque>
#include <fstream>
#include <functional>

namespace contento { namespace chain {

//namespace db2 = graphene::db2;

struct object_schema_repr
{
   std::pair< uint16_t, uint16_t > space_type;
   std::string type;
};

struct operation_schema_repr
{
   std::string id;
   std::string type;
};

struct db_schema
{
   std::map< std::string, std::string > types;
   std::vector< object_schema_repr > object_types;
   std::string operation_type;
   std::vector< operation_schema_repr > custom_operation_types;
};

} }

FC_REFLECT( contento::chain::object_schema_repr, (space_type)(type) )
FC_REFLECT( contento::chain::operation_schema_repr, (id)(type) )
FC_REFLECT( contento::chain::db_schema, (types)(object_types)(operation_type)(custom_operation_types) )

namespace contento { namespace chain {

using boost::container::flat_set;

struct reward_fund_context
{
    uint128_t   recent_claims = 0;
    asset       reward_balance = asset( 0, COS_SYMBOL );
    share_type  cos_awarded = 0;
};

class database_impl
{
   public:
      database_impl( database& self );

      database&                              _self;
      evaluator_registry< operation >        _evaluator_registry;
};

database_impl::database_impl( database& self )
   : _self(self), _evaluator_registry(self) {}

    
    //
    // TPS stats by counting trx# of latest blocks.
    //
    class tps_stats {
    public:
        tps_stats( database& self );
        
        // neccessary information out of a signed block
        struct block_info {
            uint32_t block_num;
            fc::time_point_sec timestamp;
            size_t trx_count;
        };
        
        // update the stats.
        void update(bool reset_before_update = false);
        
        // clear all cached data.
        void reset();
        
        // get TPS.
        uint32_t tps();
        
        database& _self;
        std::map<uint32_t, block_info> _latest_blocks;
        std::list<uint32_t> _latest_block_nums;
        uint32_t trx_total = 0;
    };
    
    tps_stats::tps_stats( database& self ): _self(self) {
        
    }
    
    uint32_t tps_stats::tps() {
        uint32_t r = 0;
        
        // we need at least 2 blocks to calculate TPS.
        if (_latest_blocks.size() > 1) {
            block_info &info1 = _latest_blocks[_latest_block_nums.back()];
            block_info &info0 = _latest_blocks[_latest_block_nums.front()];
            uint32_t t1 = info1.timestamp.sec_since_epoch();
            uint32_t t0 = info0.timestamp.sec_since_epoch();
            if (t1 > t0) {
                r = (trx_total - info0.trx_count)/ (t1 - t0);
            }
        }
        return r;
    }
    
    void tps_stats::reset() {
        _latest_blocks.clear();
        _latest_block_nums.clear();
        trx_total = 0;
    }
    
    void tps_stats::update(bool reset_before_update) {
        if (reset_before_update) {
            reset();
        }
        
        const dynamic_global_property_object& dpo = _self.get_dynamic_global_properties();
        uint32_t end = dpo.head_block_number;
        if (end <= 0) {
            // no block yet
            return;
        }
        uint32_t cache_end = _latest_block_nums.size()? _latest_block_nums.back() : 0;
        if (end == cache_end) {
            // last block not changed
            return;
        }
        
        // when cache data seems wrong, clear it.
        if (cache_end > 0 && end != cache_end + 1) {
            reset();
            cache_end = 0;
        }
        
        // remove old cache items.
        const uint32_t window_size = 100;
        uint32_t exp_begin = end > window_size? end - window_size : 1;
        uint32_t cache_begin = _latest_block_nums.size()? _latest_block_nums.front() : 0;
        long remove_count = (long)exp_begin - (long)cache_begin;
        long i;
        if (cache_begin > 0 && remove_count > 0) {
            for (i = 0; i < remove_count && _latest_block_nums.size(); i++) {
                uint32_t block_num = _latest_block_nums.front();
                trx_total -= _latest_blocks[block_num].trx_count;
                _latest_blocks.erase(block_num);
                _latest_block_nums.pop_front();
            }
        }
        
        // put missing block info into cache.
        cache_end = _latest_block_nums.size()? _latest_block_nums.back() : 0;
        for (i = (exp_begin <= cache_end? cache_end + 1 : exp_begin); i <= end; i++) {
            if (_latest_blocks.find(i) == _latest_blocks.end()) {
                auto block = _self.fetch_block_by_number(i);
                block_info info;
                info.block_num = i;
                info.timestamp = block->timestamp;
                info.trx_count = block->transactions.size();
                _latest_blocks[i] = info;
                _latest_block_nums.push_back(i);
                trx_total += info.trx_count;
            }
        }
        
        // update db
        uint32_t current_tps = tps();
        if (current_tps != dpo.tps) {
            _self.modify( dpo, [current_tps]( dynamic_global_property_object& _dpo )
                         {
                             _dpo.tps = current_tps;
                         } );
        }
    }

    
database::database()
   : _my( new database_impl(*this) ),
     ctrl(*this),
    _tps_stats( new tps_stats(*this) ) {
        ctrl.set_op_excute_callback(this);
     }

database::~database()
{
   clear_pending();
}

void database::open( const fc::path& data_dir, const fc::path& shared_mem_dir, uint64_t initial_supply, uint64_t shared_file_size, uint32_t chainbase_flags )
{
   try
   {
      init_schema();
      chainbase::database::open( shared_mem_dir, chainbase_flags, shared_file_size );

      initialize_indexes();
      initialize_evaluators();

      ctrl.add_indices();

      if( chainbase_flags & chainbase::database::read_write )
      {
         if( !find< dynamic_global_property_object >() )
            with_write_lock( [&]()
            {
               init_genesis( initial_supply );
            });

         _block_log.open( data_dir / "block_log" );

         auto log_head = _block_log.head();

         // Rewind all undo state. This should return us to the state at the last irreversible block.
         with_write_lock( [&]()
         {
            undo_all();
            FC_ASSERT( revision() == head_block_num(), "Chainbase revision does not match head block num",
               ("rev", revision())("head_block", head_block_num()) );
            validate_invariants();
         });

         if( head_block_num() )
         {
            auto head_block = _block_log.read_block_by_num( head_block_num() );
            // This assertion should be caught and a reindex should occur
            FC_ASSERT( head_block.valid() && head_block->id() == head_block_id(), "Chain state does not match block log. Please reindex blockchain." );

            _fork_db.start_block( *head_block );
         }
      }

      with_read_lock( [&]()
      {
         init_hardforks(); // Writes to local state, but reads from db
      });
   }
   FC_CAPTURE_LOG_AND_RETHROW( (data_dir)(shared_mem_dir)(shared_file_size) )
}

void database::reindex( const fc::path& data_dir, const fc::path& shared_mem_dir, uint64_t shared_file_size )
{
   try
   {
      ilog( "Reindexing Blockchain" );
      wipe( data_dir, shared_mem_dir, false );
      open( data_dir, shared_mem_dir, 0, shared_file_size, chainbase::database::read_write );
      _fork_db.reset();    // override effect of _fork_db.start_block() call in open()

      auto start = fc::time_point::now();
      CONTENTO_ASSERT( _block_log.head(), block_log_exception, "No blocks in block log. Cannot reindex an empty chain." );

      ilog( "Replaying blocks..." );


      uint64_t skip_flags =
         skip_witness_signature |
         skip_transaction_signatures |
         skip_transaction_dupe_check |
         skip_tapos_check |
         skip_merkle_check |
         skip_witness_schedule_check |
         skip_authority_check |
         skip_validate | /// no need to validate operations
         skip_validate_invariants |
         skip_block_log;

      with_write_lock( [&]()
      {
         auto itr = _block_log.read_block( 0 );
         auto last_block_num = _block_log.head()->block_num();

         while( itr.first.block_num() != last_block_num )
         {
            auto cur_block_num = itr.first.block_num();
            if( cur_block_num % 100000 == 0 )
               std::cerr << "   " << double( cur_block_num * 100 ) / last_block_num << "%   " << cur_block_num << " of " << last_block_num <<
               "   (" << (get_free_memory() / (1024*1024)) << "M free)\n";
            apply_block( itr.first, skip_flags );
            itr = _block_log.read_block( itr.second );
         }

         apply_block( itr.first, skip_flags );
         set_revision( head_block_num() );
      });

      if( _block_log.head()->block_num() )
         _fork_db.start_block( *_block_log.head() );

      auto end = fc::time_point::now();
      ilog( "Done reindexing, elapsed time: ${t} sec", ("t",double((end-start).count())/1000000.0 ) );
   }
   FC_CAPTURE_AND_RETHROW( (data_dir)(shared_mem_dir) )

}

void database::wipe( const fc::path& data_dir, const fc::path& shared_mem_dir, bool include_blocks)
{
   close();
   chainbase::database::wipe( shared_mem_dir );
   if( include_blocks )
   {
      fc::remove_all( data_dir / "block_log" );
      fc::remove_all( data_dir / "block_log.index" );
   }
}

void database::close(bool rewind)
{
   try
   {
      // Since pop_block() will move tx's in the popped blocks into pending,
      // we have to clear_pending() after we're done popping to get a clean
      // DB state (issue #336).
      clear_pending();

      chainbase::database::flush();
      chainbase::database::close();

      _block_log.close();

      _fork_db.reset();
   }
   FC_CAPTURE_AND_RETHROW()
}

void database::check_admin(const vector<operation>& ops)
{ try {
   vector<std::pair<account_name_type, admin_type>> admins;
   for( const auto& op : ops )
      operation_get_required_admin( op, admins );

   for( const auto& admin_pair : admins )
   {
      const auto& admin = get_admin(admin_pair.first);
      uint128_t nomination;
      switch (admin_pair.second)
      {
         case admin_type::comment_delete:
            nomination = admin.comment_delete_nomination;
         default:
            nomination = admin.commercial_nomination;
      }
      FC_ASSERT( nomination.popcount() >= 3 || is_councillor(admin_pair.first), 
            "account does not have admin authority", ("acc_name", admin_pair.first) );
   }
} FC_CAPTURE_AND_RETHROW() }

bool database::is_known_block( const block_id_type& id )const
{ try {
   return fetch_block_by_id( id ).valid();
} FC_CAPTURE_AND_RETHROW() }

/**
 * Only return true *if* the transaction has not expired or been invalidated. If this
 * method is called with a VERY old transaction we will return false, they should
 * query things by blocks if they are that old.
 */
bool database::is_known_transaction( const transaction_id_type& id )const
{ try {
   const auto& trx_idx = get_index<transaction_index>().indices().get<by_trx_id>();
   return trx_idx.find( id ) != trx_idx.end();
} FC_CAPTURE_AND_RETHROW() }

block_id_type database::find_block_id_for_num( uint32_t block_num )const
{
   try
   {
      if( block_num == 0 )
         return block_id_type();

      // Reversible blocks are *usually* in the TAPOS buffer.  Since this
      // is the fastest check, we do it first.
      block_summary_id_type bsid = block_num & 0xFFFF;
      const block_summary_object* bs = find< block_summary_object, by_id >( bsid );
      if( bs != nullptr )
      {
         if( protocol::block_header::num_from_id(bs->block_id) == block_num )
            return bs->block_id;
      }

      // Next we query the block log.   Irreversible blocks are here.
      auto b = _block_log.read_block_by_num( block_num );
      if( b.valid() )
         return b->id();

      // Finally we query the fork DB.
      shared_ptr< fork_item > fitem = _fork_db.fetch_block_on_main_branch_by_number( block_num );
      if( fitem )
         return fitem->id;

      return block_id_type();
   }
   FC_CAPTURE_AND_RETHROW( (block_num) )
}

block_id_type database::get_block_id_for_num( uint32_t block_num )const
{
   block_id_type bid = find_block_id_for_num( block_num );
   FC_ASSERT( bid != block_id_type() );
   return bid;
}


optional<signed_block> database::fetch_block_by_id( const block_id_type& id )const
{ try {
   auto b = _fork_db.fetch_block( id );
   if( !b )
   {
      auto tmp = _block_log.read_block_by_num( protocol::block_header::num_from_id( id ) );

      if( tmp && tmp->id() == id )
         return tmp;
      tmp.reset();
      return tmp;
   }
   return b->data;
} FC_CAPTURE_AND_RETHROW() }

optional<signed_block> database::fetch_block_by_number( uint32_t block_num )const
{ try {
   optional< signed_block > b;

   auto results = _fork_db.fetch_block_by_number( block_num );
   if( results.size() == 1 )
      b = results[0]->data;
   else
      b = _block_log.read_block_by_num( block_num );

   return b;
} FC_LOG_AND_RETHROW() }

const signed_transaction database::get_recent_transaction( const transaction_id_type& trx_id ) const
{ try {
   auto& index = get_index<transaction_index>().indices().get<by_trx_id>();
   auto itr = index.find(trx_id);
   FC_ASSERT(itr != index.end());
   signed_transaction trx;
   fc::raw::unpack( itr->packed_trx, trx );
   return trx;;
} FC_CAPTURE_AND_RETHROW() }

std::vector< block_id_type > database::get_block_ids_on_fork( block_id_type head_of_fork ) const
{ try {
   pair<fork_database::branch_type, fork_database::branch_type> branches = _fork_db.fetch_branch_from(head_block_id(), head_of_fork);
   if( !((branches.first.back()->previous_id() == branches.second.back()->previous_id())) )
   {
      edump( (head_of_fork)
             (head_block_id())
             (branches.first.size())
             (branches.second.size()) );
      assert(branches.first.back()->previous_id() == branches.second.back()->previous_id());
   }
   std::vector< block_id_type > result;
   for( const item_ptr& fork_block : branches.second )
      result.emplace_back(fork_block->id);
   result.emplace_back(branches.first.back()->previous_id());
   return result;
} FC_CAPTURE_AND_RETHROW() }

chain_id_type database::get_chain_id() const
{
   return CONTENTO_CHAIN_ID;
}

const witness_object& database::get_witness( const account_name_type& name ) const
{ try {
   return get< witness_object, by_name >( name );
} FC_CAPTURE_AND_RETHROW( (name) ) }

const witness_object* database::find_witness( const account_name_type& name ) const
{
   return find< witness_object, by_name >( name );
}

const account_object& database::get_account( const account_name_type& name )const
{ try {
   return get< account_object, by_name >( name );
} FC_CAPTURE_AND_RETHROW( (name) ) }
    
const contract_balance_object& database::get_contract_account( const account_name_type& name )const
{ try {
    return get< contract_balance_object, by_name >( name );
} FC_CAPTURE_AND_RETHROW( (name) ) }

const account_object* database::find_account( const account_name_type& name )const
{
   return find< account_object, by_name >( name );
}

const admin_object& database::get_admin( const account_name_type& name ) const
{ try {
   return get< admin_object, by_name >( name );
} FC_CAPTURE_AND_RETHROW( (name) ) }

const admin_object* database::find_admin( const account_name_type& name )const
{
   return find< admin_object, by_name >( name );
}

const comment_object& database::get_comment( const account_name_type& author, const shared_string& permlink )const
{ try {
   return get< comment_object, by_permlink >( boost::make_tuple( author, permlink ) );
} FC_CAPTURE_AND_RETHROW( (author)(permlink) ) }

const comment_object* database::find_comment( const account_name_type& author, const shared_string& permlink )const
{
   return find< comment_object, by_permlink >( boost::make_tuple( author, permlink ) );
}

const comment_object& database::get_comment( const account_name_type& author, const string& permlink )const
{ try {
   return get< comment_object, by_permlink >( boost::make_tuple( author, permlink) );
} FC_CAPTURE_AND_RETHROW( (author)(permlink) ) }

const comment_object* database::find_comment( const account_name_type& author, const string& permlink )const
{
   return find< comment_object, by_permlink >( boost::make_tuple( author, permlink ) );
}


const savings_withdraw_object& database::get_savings_withdraw( const account_name_type& owner, uint32_t request_id )const
{ try {
   return get< savings_withdraw_object, by_from_rid >( boost::make_tuple( owner, request_id ) );
} FC_CAPTURE_AND_RETHROW( (owner)(request_id) ) }

const savings_withdraw_object* database::find_savings_withdraw( const account_name_type& owner, uint32_t request_id )const
{
   return find< savings_withdraw_object, by_from_rid >( boost::make_tuple( owner, request_id ) );
}

const dynamic_global_property_object&database::get_dynamic_global_properties() const
{ try {
   return get< dynamic_global_property_object >();
} FC_CAPTURE_AND_RETHROW() }
    
const dynamic_global_reward_property_object&database::get_dynamic_global_reward_properties() const
{
    try {
        return get< dynamic_global_reward_property_object >();
    } FC_CAPTURE_AND_RETHROW()
}


const node_property_object& database::get_node_properties() const
{
   return _node_property_object;
}

//const feed_history_object& database::get_feed_history()const
//{ try {
//   return get< feed_history_object >();
//} FC_CAPTURE_AND_RETHROW() }

const witness_schedule_object& database::get_witness_schedule_object()const
{ try {
   return get< witness_schedule_object >();
} FC_CAPTURE_AND_RETHROW() }

const hardfork_property_object& database::get_hardfork_property_object()const
{ try {
   return get< hardfork_property_object >();
} FC_CAPTURE_AND_RETHROW() }

const time_point_sec database::calculate_discussion_payout_time( const comment_object& comment )const
{
//    if( has_hardfork( CONTENTO_HARDFORK_0_17__769 ) || comment.parent_author == CONTENTO_ROOT_POST_PARENT )
      return comment.cashout_time;
//    else
//       return get< comment_object >( comment.root_comment ).cashout_time;
}

const reward_fund_object& database::get_reward_fund( const comment_object& c ) const
{
   return get< reward_fund_object, by_name >( CONTENTO_POST_REWARD_FUND_NAME );
}

void database::pay_fee( const account_object& account, asset fee )
{
   FC_ASSERT( fee.amount >= 0 ); /// NOTE if this fails then validate() on some operation is probably wrong
   if( fee.amount == 0 )
      return;

   FC_ASSERT( account.balance >= fee );
   adjust_balance( account, -fee );
   adjust_supply( -fee );
}

uint32_t database::witness_participation_rate()const
{
   const dynamic_global_property_object& dpo = get_dynamic_global_properties();
   return uint64_t(CONTENTO_100_PERCENT) * dpo.recent_slots_filled.popcount() / 128;
}

void database::add_checkpoints( const flat_map< uint32_t, block_id_type >& checkpts )
{
   for( const auto& i : checkpts )
      _checkpoints[i.first] = i.second;
}

bool database::before_last_checkpoint()const
{
   return (_checkpoints.size() > 0) && (_checkpoints.rbegin()->first >= head_block_num());
}

/**
 * Push block "may fail" in which case every partial change is unwound.  After
 * push block is successful the block is appended to the chain database on disk.
 *
 * @return true if we switched forks as a result of this push.
 */
bool database::push_block(const signed_block& new_block, uint32_t skip)
{
   //fc::time_point begin_time = fc::time_point::now();

   bool result;
   detail::with_skip_flags( *this, skip, [&]()
   {
      with_write_lock( [&]()
      {
         detail::without_pending_transactions( *this, std::move(_pending_tx), [&]()
         {
            try
            {
               result = _push_block(new_block);
            }
            FC_CAPTURE_AND_RETHROW( (new_block) )
         });
      });
   });

   contento::protocol::sig_to_key.clear(); //clear verify auth cache

   //fc::time_point end_time = fc::time_point::now();
   //fc::microseconds dt = end_time - begin_time;
   //if( ( new_block.block_num() % 10000 ) == 0 )
   //   ilog( "push_block ${b} took ${t} microseconds", ("b", new_block.block_num())("t", dt.count()) );
   return result;
}

void database::_maybe_warn_multiple_production( uint32_t height )const
{
   auto blocks = _fork_db.fetch_block_by_number( height );
   if( blocks.size() > 1 )
   {
      vector< std::pair< account_name_type, fc::time_point_sec > > witness_time_pairs;
      for( const auto& b : blocks )
      {
         witness_time_pairs.push_back( std::make_pair( b->data.witness, b->data.timestamp ) );
      }

      ilog( "Encountered block num collision at block ${n} due to a fork, witnesses are: ${w}", ("n", height)("w", witness_time_pairs) );
   }
   return;
}

bool database::_push_block(const signed_block& new_block)
{ try {
   uint32_t skip = get_node_properties().skip_flags;
   //uint32_t skip_undo_db = skip & skip_undo_block;

   if( !(skip&skip_fork_db) )
   {
      shared_ptr<fork_item> new_head = _fork_db.push_block(new_block);
      _maybe_warn_multiple_production( new_head->num );

      //If the head block from the longest chain does not build off of the current head, we need to switch forks.
      if( new_head->data.previous != head_block_id() )
      {
         //If the newly pushed block is the same height as head, we get head back in new_head
         //Only switch forks if new_head is actually higher than head
         if( new_head->data.block_num() > head_block_num() )
         {
            // wlog( "Switching to fork: ${id}", ("id",new_head->data.id()) );
            auto branches = _fork_db.fetch_branch_from(new_head->data.id(), head_block_id());

            // pop blocks until we hit the forked block
            while( head_block_id() != branches.second.back()->data.previous )
               pop_block();

            // push all blocks on the new fork
            for( auto ritr = branches.first.rbegin(); ritr != branches.first.rend(); ++ritr )
            {
                // ilog( "pushing blocks from fork ${n} ${id}", ("n",(*ritr)->data.block_num())("id",(*ritr)->data.id()) );
                optional<fc::exception> except;
                try
                {
                   auto session = start_undo_session( true );
                   apply_block( (*ritr)->data, skip );
                   session.push();
                }
                catch ( const fc::exception& e ) { except = e; }
                if( except )
                {
                   // wlog( "exception thrown while switching forks ${e}", ("e",except->to_detail_string() ) );
                   // remove the rest of branches.first from the fork_db, those blocks are invalid
                   while( ritr != branches.first.rend() )
                   {
                      _fork_db.remove( (*ritr)->data.id() );
                      ++ritr;
                   }
                   _fork_db.set_head( branches.second.front() );

                   // pop all blocks from the bad fork
                   while( head_block_id() != branches.second.back()->data.previous )
                      pop_block();

                   // restore all blocks from the good fork
                   for( auto ritr = branches.second.rbegin(); ritr != branches.second.rend(); ++ritr )
                   {
                      auto session = start_undo_session( true );
                      apply_block( (*ritr)->data, skip );
                      session.push();
                   }
                   throw *except;
                }
            }
            return true;
         }
         else
            return false;
      }
   }

   try
   {
       if( !( skip & skip_apply_transaction ) )
       {
            auto session = start_undo_session( true );
            apply_block(new_block, skip);
            session.push();
       } else {
            apply_block(new_block, skip);
       }
   }
   catch( const fc::exception& e )
   {
      elog("Failed to push new block:\n${e}", ("e", e.to_detail_string()));
      _fork_db.remove(new_block.id());
      throw;
   }

   return false;
} FC_CAPTURE_AND_RETHROW() }

/**
 * Attempts to push the transaction into the pending queue
 *
 * When called to push a locally generated transaction, set the skip_block_size_check bit on the skip argument. This
 * will allow the transaction to be pushed even if it causes the pending block size to exceed the maximum block size.
 * Although the transaction will probably not propagate further now, as the peers are likely to have their pending
 * queues full as well, it will be kept in the queue to be propagated later when a new block flushes out the pending
 * queues.
 */
transaction_invoice database::push_transaction( const signed_transaction& trx, uint32_t skip )
{
   transaction_invoice invoice;
   try
   {
      try
      {
         FC_ASSERT( fc::raw::pack_size(trx) <= (get_dynamic_global_properties().maximum_block_size - 256) );
         set_producing( true );
         detail::with_skip_flags( *this, skip,
            [&]()
            {
               with_write_lock( [&]()
               {
                  invoice = _push_transaction( trx );
               });
            });
         set_producing( false );
      }
      catch( ... )
      {
         set_producing( false );
         throw;
      }
      return invoice;
   }
   FC_CAPTURE_AND_RETHROW( (trx) )
}
    
transaction_wrapper database::test_push_transaction( const signed_transaction& trx, uint32_t skip )
{
    transaction_wrapper trx_wrapper;
    trx_wrapper.sig_trx = trx;
    
    try {
        try {
            FC_ASSERT( fc::raw::pack_size(trx) <= (get_dynamic_global_properties().maximum_block_size - 256) );
            set_producing( true );
            detail::with_skip_flags( *this, skip, [&]() {
                with_write_lock( [&]() {
                    auto session = start_undo_session( true );
                    
                    asset lots_of_money(1000000000);
                    for (const operation& op: trx.operations) {
                        if ( op.contains<vm_operation>() ) {
                            const auto& caller = get_account(op.get<vm_operation>().caller);
                            if (caller.balance < lots_of_money) {
                                adjust_balance( caller, lots_of_money - caller.balance );
                            }
                        }
                    }
                    
                    _apply_transaction( trx_wrapper );
                });
            });
            set_producing( false );
        }
        catch( ... )
        {
            set_producing( false );
            throw;
        }
        return trx_wrapper;
        
    } FC_CAPTURE_AND_RETHROW( (trx) )
}

transaction_invoice database::_push_transaction( const signed_transaction& trx )
{
   // If this is the first transaction pushed after applying a block, start a new undo session.
   // This allows us to quickly rewind to the clean state of the head block, in case a new block arrives.
   if( !_pending_tx_session.valid() )
      _pending_tx_session = start_undo_session( true );

    // wrap transaction with invoice
    transaction_wrapper trx_wrapper;
    trx_wrapper.sig_trx = trx;

   // Create a temporary undo session as a child of _pending_tx_session.
   // The temporary session will be discarded by the destructor if
   // _apply_transaction fails.  If we make it to merge(), we
   // apply the changes.

   auto temp_session = start_undo_session( true );
   _apply_transaction( trx_wrapper );
   _pending_tx.push_back( trx_wrapper );

   notify_changed_objects();
   // The transaction applied successfully. Merge its changes into the pending block session.
   temp_session.squash();

   // notify anyone listening to pending transactions
   notify_on_pending_transaction( trx );

   return trx_wrapper.invoice;
}

signed_block database::generate_block(
   fc::time_point_sec when,
   const account_name_type& witness_owner,
   const fc::ecc::private_key& block_signing_private_key,
   uint32_t skip /* = 0 */
   )
{
   signed_block result;
   detail::with_skip_flags( *this, skip, [&]()
   {
      try
      {
         result = _generate_block( when, witness_owner, block_signing_private_key );
      }
      FC_CAPTURE_AND_RETHROW( (witness_owner) )
   });
   return result;
}


signed_block database::_generate_block(
   fc::time_point_sec when,
   const account_name_type& witness_owner,
   const fc::ecc::private_key& block_signing_private_key
   )
{
   uint32_t skip = get_node_properties().skip_flags;
   uint32_t slot_num = get_slot_at_time( when );
   FC_ASSERT( slot_num > 0 );
   string scheduled_witness = get_scheduled_witness( slot_num );
   FC_ASSERT( scheduled_witness == witness_owner );

   const auto& witness_obj = get_witness( witness_owner );

   if( !(skip & skip_witness_signature) )
      FC_ASSERT( witness_obj.signing_key == block_signing_private_key.get_public_key() );

   static const size_t max_block_header_size = fc::raw::pack_size( signed_block_header() ) + 4;
   auto maximum_block_size = get_dynamic_global_properties().maximum_block_size; //CONTENTO_MAX_BLOCK_SIZE;
   size_t total_block_size = max_block_header_size;

   signed_block pending_block;
   _current_trx_in_block = 0;

   // i don't think _checkpoints should exists, so delete it
   //uint32_t skip_new;
   //pending_block.previous = head_block_id();
   //if ( _checkpoints.size() && _checkpoints.rbegin()->second != block_id_type() ) {
   //    skip_new = process_checkpoints( pending_block, skip );
   //}

   with_write_lock( [&]()
   {
      //
      // The following code throws away existing pending_tx_session and
      // rebuilds it by re-applying pending transactions.
      //
      // This rebuild is necessary because pending transactions' validity
      // and semantics may have changed since they were received, because
      // time-based semantics are evaluated based on the current block
      // time.  These changes can only be reflected in the database when
      // the value of the "when" variable is known, which means we need to
      // re-apply pending transactions in this method.
      //
      _pending_tx_session.reset();
      _pending_tx_session = start_undo_session( true );

      uint64_t postponed_tx_count = 0;
      // pop pending state (reset to head block state)
      for(  transaction_wrapper& trx_wrapper : _pending_tx )
      {
         // Only include transactions that have not expired yet for currently generating block,
         // this should clear problem transactions and allow block production to continue

         if( trx_wrapper.sig_trx.expiration < when )
            continue;

         uint64_t new_total_size = total_block_size + fc::raw::pack_size( trx_wrapper );

         // postpone transaction if it would make block too big
         if( new_total_size >= maximum_block_size )
         {
            postponed_tx_count++;
            continue;
         }

         try {
             //_apply_transaction( trx_wrapper );
            auto temp_session = start_undo_session( true );
            detail::with_skip_flags( *this, skip, [&]()
            {
                _apply_transaction( trx_wrapper );
            });
            
             temp_session.squash();

             total_block_size += fc::raw::pack_size( trx_wrapper );
             pending_block.transactions.push_back( trx_wrapper );
             ++_current_trx_in_block;
         }
         catch ( const fc::exception& e )
         {
            // Do nothing, transaction will not be re-applied
            //wlog( "Transaction was not processed while generating block due to ${e}", ("e", e) );
            //wlog( "The transaction was ${t}", ("t", tx) );
         }

         /*
         try
         {
            auto temp_session = start_undo_session( true );
            _apply_transaction( trx_wrapper );
            temp_session.squash();

            total_block_size += fc::raw::pack_size( trx_wrapper );
            pending_block.transactions.push_back( trx_wrapper );
         }
         catch ( const fc::exception& e )
         {
            // Do nothing, transaction will not be re-applied
            //wlog( "Transaction was not processed while generating block due to ${e}", ("e", e) );
            //wlog( "The transaction was ${t}", ("t", tx) );
         }
         */
      }
      if( postponed_tx_count > 0 )
      {
         wlog( "Postponed ${n} transactions due to block size limit", ("n", postponed_tx_count) );
      }

      //_pending_tx_session.reset();
       
// #ifdef IS_TEST_NET
//        if( BOOST_UNLIKELY( head_block_id() == block_id_type() && init_genesis_hardforks ) )
//        {
//            // For every existing before the head_block_time (genesis time), apply the hardfork
//            // This allows the test net to launch with past hardforks and apply the next harfork when running
//            auto now = when;
//            for( size_t i = 0;
//                i <= CONTENTO_NUM_HARDFORKS && _hardfork_times[i] <= now;
//                i++ )
//            {
//                set_hardfork( i, true );
//            }
//        }
// #endif

   });

   // We have temporarily broken the invariant that
   // _pending_tx_session is the result of applying _pending_tx, as
   // _pending_tx now consists of the set of postponed transactions.
   // However, the push_block() call below will re-create the
   // _pending_tx_session.

   pending_block.previous = head_block_id();
   pending_block.timestamp = when;
   pending_block.transaction_merkle_root = pending_block.calculate_merkle_root();
   pending_block.witness = witness_owner;
//    if( has_hardfork( CONTENTO_HARDFORK_0_5__54 ) )
//    {
      const auto& witness = get_witness( witness_owner );

      if( witness.running_version != CONTENTO_BLOCKCHAIN_VERSION )
         pending_block.extensions.insert( block_header_extensions( CONTENTO_BLOCKCHAIN_VERSION ) );

      const auto& hfp = get_hardfork_property_object();

      if( hfp.current_hardfork_version < CONTENTO_BLOCKCHAIN_HARDFORK_VERSION // Binary is newer hardfork than has been applied
         && ( witness.hardfork_version_vote != _hardfork_versions[ hfp.last_hardfork + 1 ] || witness.hardfork_time_vote != _hardfork_times[ hfp.last_hardfork + 1 ] ) ) // Witness vote does not match binary configuration
      {
         // Make vote match binary configuration
         pending_block.extensions.insert( block_header_extensions( hardfork_version_vote( _hardfork_versions[ hfp.last_hardfork + 1 ], _hardfork_times[ hfp.last_hardfork + 1 ] ) ) );
      }
      else if( hfp.current_hardfork_version == CONTENTO_BLOCKCHAIN_HARDFORK_VERSION // Binary does not know of a new hardfork
         && witness.hardfork_version_vote > CONTENTO_BLOCKCHAIN_HARDFORK_VERSION ) // Voting for hardfork in the future, that we do not know of...
      {
         // Make vote match binary configuration. This is vote to not apply the new hardfork.
         pending_block.extensions.insert( block_header_extensions( hardfork_version_vote( _hardfork_versions[ hfp.last_hardfork ], _hardfork_times[ hfp.last_hardfork ] ) ) );
      }
//    }

   if( !(skip & skip_witness_signature) )
      pending_block.sign( block_signing_private_key );

   // TODO:  Move this to _push_block() so session is restored.
   if( !(skip & skip_block_size_check) )
   {
      FC_ASSERT( fc::raw::pack_size(pending_block) <= CONTENTO_MAX_BLOCK_SIZE );
   }

   //_pending_tx_session.push();

    
    auto res = push_block( pending_block, skip | skip_apply_transaction );
    if ( res ) {
        std::cout << "in _generate_block function, BP node should never come here!" << std::endl;
    } else {
        if ( pending_block.block_num() == head_block_num() )
        {
            _pending_tx_session.push();
        }
    }

    return pending_block;
}

/**
 * Removes the most recent block from the database and
 * undoes any changes it made.
 */
void database::pop_block()
{
   try
   {
      _pending_tx_session.reset();
      auto head_id = head_block_id();

      /// save the head block so we can recover its transactions
      optional<signed_block> head_block = fetch_block_by_id( head_id );
      CONTENTO_ASSERT( head_block.valid(), pop_empty_chain, "there are no blocks to pop" );

      _fork_db.pop_block();
      undo();
       
       _tps_stats->reset();

      _popped_tx.insert( _popped_tx.begin(), head_block->transactions.begin(), head_block->transactions.end() );

   }
   FC_CAPTURE_AND_RETHROW()
}

void database::clear_pending()
{
   try
   {
      assert( (_pending_tx.size() == 0) || _pending_tx_session.valid() );
      _pending_tx.clear();
      uint32_t skip = get_node_properties().skip_flags;
      if( !( skip & skip_apply_transaction ) )
            _pending_tx_session.reset();
   }
   FC_CAPTURE_AND_RETHROW()
}

void database::notify_pre_apply_operation( operation_notification& note )
{
   note.trx_id       = _current_trx_id;
   note.block        = _current_block_num;
   note.trx_in_block = _current_trx_in_block;
   note.op_in_trx    = _current_op_in_trx;

   CONTENTO_TRY_NOTIFY( pre_apply_operation, note )
}

void database::notify_post_apply_operation( const operation_notification& note )
{
   CONTENTO_TRY_NOTIFY( post_apply_operation, note )
}

inline const void database::push_virtual_operation( const operation& op, bool force )
{
/*
   if( !force )
   {
      #if defined( IS_LOW_MEM ) && ! defined( IS_TEST_NET )
      return;
      #endif
   }
*/
   FC_ASSERT( is_virtual_operation( op ) );
   operation_notification note(op);
   notify_pre_apply_operation( note );
   notify_post_apply_operation( note );
}

void database::notify_applied_block( const signed_block& block )
{
   CONTENTO_TRY_NOTIFY( applied_block, block )
}

void database::notify_on_pending_transaction( const signed_transaction& tx )
{
   CONTENTO_TRY_NOTIFY( on_pending_transaction, tx )
}

void database::notify_on_pre_apply_transaction( const signed_transaction& tx )
{
   CONTENTO_TRY_NOTIFY( on_pre_apply_transaction, tx )
}

void database::notify_on_applied_transaction( const signed_transaction& tx )
{
   CONTENTO_TRY_NOTIFY( on_applied_transaction, tx )
}

account_name_type database::get_scheduled_witness( uint32_t slot_num )const
{
   const dynamic_global_property_object& dpo = get_dynamic_global_properties();
   const witness_schedule_object& wso = get_witness_schedule_object();
   uint64_t current_aslot = dpo.current_aslot + slot_num;
   return wso.current_shuffled_witnesses[ current_aslot % wso.num_scheduled_witnesses ];
}

fc::time_point_sec database::get_slot_time(uint32_t slot_num)const
{
   if( slot_num == 0 )
      return fc::time_point_sec();

   auto interval = CONTENTO_BLOCK_INTERVAL;
   const dynamic_global_property_object& dpo = get_dynamic_global_properties();

   if( head_block_num() == 0 )
   {
      // n.b. first block is at genesis_time plus one block interval
      fc::time_point_sec genesis_time = dpo.time;
      return genesis_time + slot_num * interval;
   }

   int64_t head_block_abs_slot = head_block_time().sec_since_epoch() / interval;
   fc::time_point_sec head_slot_time( head_block_abs_slot * interval );

   // "slot 0" is head_slot_time
   // "slot 1" is head_slot_time,
   //   plus maint interval if head block is a maint block
   //   plus block interval if head block is not a maint block
   return head_slot_time + (slot_num * interval);
}

uint32_t database::get_slot_at_time(fc::time_point_sec when)const
{
   fc::time_point_sec first_slot_time = get_slot_time( 1 );
   if( when < first_slot_time )
      return 0;
   return (when - first_slot_time).to_seconds() / CONTENTO_BLOCK_INTERVAL + 1;
}


/**
 * @param to_account - the account to receive the new vesting shares
 * @param STEEM - STEEM to be converted to vesting shares
 */
asset database::create_vesting( const account_object& to_account, asset cos)
{
    FC_ASSERT( cos.symbol == COS_SYMBOL, "invalid symbol" );
   try
   {
       const auto& cprops = get_dynamic_global_properties();

       asset new_vesting = cos * cprops.get_vesting_share_price();
       modify( to_account, [&]( account_object& to ){
           to.vesting_shares += new_vesting;
       });
       

       modify( cprops, [&]( dynamic_global_property_object& props ){
           props.total_vesting_shares += new_vesting;
       });

        return new_vesting;
   }
   FC_CAPTURE_AND_RETHROW( (to_account.name)(cos) )
}

void database::adjust_proxied_witness_votes( const account_object& a,
                                   const std::array< share_type, CONTENTO_MAX_PROXY_RECURSION_DEPTH+1 >& delta,
                                   int depth )
{
   if( a.proxy != CONTENTO_PROXY_TO_SELF_ACCOUNT )
   {
      /// nested proxies are not supported, vote will not propagate
      if( depth >= CONTENTO_MAX_PROXY_RECURSION_DEPTH )
         return;

      const auto& proxy = get_account( a.proxy );

      modify( proxy, [&]( account_object& a )
      {
         for( int i = CONTENTO_MAX_PROXY_RECURSION_DEPTH - depth - 1; i >= 0; --i )
         {
            a.proxied_vsf_votes[i+depth] += delta[i];
         }
      } );

      adjust_proxied_witness_votes( proxy, delta, depth + 1 );
   }
   else
   {
      share_type total_delta = 0;
      for( int i = CONTENTO_MAX_PROXY_RECURSION_DEPTH - depth; i >= 0; --i )
         total_delta += delta[i];
      adjust_witness_votes( a, total_delta );
   }
}

void database::adjust_proxied_witness_votes( const account_object& a, share_type delta, int depth )
{
   if( a.proxy != CONTENTO_PROXY_TO_SELF_ACCOUNT )
   {
      /// nested proxies are not supported, vote will not propagate
      if( depth >= CONTENTO_MAX_PROXY_RECURSION_DEPTH )
         return;

      const auto& proxy = get_account( a.proxy );

      modify( proxy, [&]( account_object& a )
      {
         a.proxied_vsf_votes[depth] += delta;
      } );

      adjust_proxied_witness_votes( proxy, delta, depth + 1 );
   }
   else
   {
     adjust_witness_votes( a, delta );
   }
}

void database::adjust_witness_votes( const account_object& a, share_type delta )
{
   const auto& vidx = get_index< witness_vote_index >().indices().get< by_account_witness >();
   auto itr = vidx.lower_bound( boost::make_tuple( a.id, witness_id_type() ) );
   while( itr != vidx.end() && itr->account == a.id )
   {
      adjust_witness_vote( get(itr->witness), delta );
      ++itr;
   }
}

void database::adjust_witness_vote( const witness_object& witness, share_type delta )
{
   const witness_schedule_object& wso = get_witness_schedule_object();
   modify( witness, [&]( witness_object& w )
   {
      auto delta_pos = w.votes.value * (wso.current_virtual_time - w.virtual_last_update);
      w.virtual_position += delta_pos;

      w.virtual_last_update = wso.current_virtual_time;
      w.votes += delta;
      FC_ASSERT( w.votes <= get_dynamic_global_properties().total_vesting_shares.amount, "", ("w.votes", w.votes)("props",get_dynamic_global_properties().total_vesting_shares) );

    //   if( has_hardfork( CONTENTO_HARDFORK_0_2 ) )
         w.virtual_scheduled_time = w.virtual_last_update + (VIRTUAL_SCHEDULE_LAP_LENGTH2 - w.virtual_position)/(w.votes.value+1);
    //   else
    //      w.virtual_scheduled_time = w.virtual_last_update + (VIRTUAL_SCHEDULE_LAP_LENGTH - w.virtual_position)/(w.votes.value+1);

      /** witnesses with a low number of votes could overflow the time field and end up with a scheduled time in the past */
    //   if( has_hardfork( CONTENTO_HARDFORK_0_4 ) )
    //   {
         if( w.virtual_scheduled_time < wso.current_virtual_time )
            w.virtual_scheduled_time = fc::uint128::max_value();
//       }
   } );
}

void database::clear_witness_votes( const account_object& a )
{
   const auto& vidx = get_index< witness_vote_index >().indices().get<by_account_witness>();
   auto itr = vidx.lower_bound( boost::make_tuple( a.id, witness_id_type() ) );
   while( itr != vidx.end() && itr->account == a.id )
   {
      const auto& current = *itr;
      ++itr;
      remove(current);
   }

//    if( has_hardfork( CONTENTO_HARDFORK_0_6__104 ) )
      modify( a, [&](account_object& acc )
      {
         acc.witnesses_voted_for = 0;
      });
}

void database::clear_null_account_balance()
{

   const auto& null_account = get_account( CONTENTO_NULL_ACCOUNT );
   asset total_steem( 0, COS_SYMBOL );

   if( null_account.balance.amount > 0 )
   {
      total_steem += null_account.balance;
      adjust_balance( null_account, -null_account.balance );
   }

   if( null_account.savings_balance.amount > 0 )
   {
      total_steem += null_account.savings_balance;
      adjust_savings_balance( null_account, -null_account.savings_balance );
   }


   if( null_account.vesting_shares.amount > 0 )
   {
      const auto& gpo = get_dynamic_global_properties();
      auto converted_steem = null_account.vesting_shares * gpo.get_vesting_share_price();

      modify( gpo, [&]( dynamic_global_property_object& g )
      {
         g.total_vesting_shares -= null_account.vesting_shares;
         g.total_cos -= converted_steem;
      });

      modify( null_account, [&]( account_object& a )
      {
         a.vesting_shares.amount = 0;
      });

      total_steem += converted_steem;
   }

   if( null_account.reward_steem_balance.amount > 0 )
   {
      total_steem += null_account.reward_steem_balance;
      adjust_reward_balance( null_account, -null_account.reward_steem_balance );
   }

//   if( null_account.reward_sbd_balance.amount > 0 )
//   {
//      total_sbd += null_account.reward_sbd_balance;
//      adjust_reward_balance( null_account, -null_account.reward_sbd_balance );
//   }

   if( null_account.reward_vesting_balance.amount > 0 )
   {
      //const auto& gpo = get_dynamic_global_properties();

      total_steem += null_account.reward_vesting_steem;

//      modify( gpo, [&]( dynamic_global_property_object& g )
//      {
//         g.pending_rewarded_vesting_shares -= null_account.reward_vesting_balance;
//         g.pending_rewarded_vesting_steem -= null_account.reward_vesting_steem;
//      });

      modify( null_account, [&]( account_object& a )
      {
         a.reward_vesting_steem.amount = 0;
         a.reward_vesting_balance.amount = 0;
      });
   }

   if( total_steem.amount > 0 )
      adjust_supply( -total_steem );

//   if( total_sbd.amount > 0 )
//      adjust_supply( -total_sbd );
}

/**
 * This method updates total_reward_shares2 on DGPO, and children_rshares2 on comments, when a comment's rshares2 changes
 * from old_rshares2 to new_rshares2.  Maintaining invariants that children_rshares2 is the sum of all descendants' rshares2,
 * and dgpo.total_reward_shares2 is the total number of rshares2 outstanding.
 */
void database::adjust_rshares2( const comment_object& c, fc::uint128_t old_rshares2, fc::uint128_t new_rshares2 )
{

   const auto& dgpo = get_dynamic_global_properties();
   modify( dgpo, [&]( dynamic_global_property_object& p )
   {
      p.total_reward_shares2 -= old_rshares2;
      p.total_reward_shares2 += new_rshares2;
   } );
}

void database::update_owner_authority( const account_object& account, const authority& owner_authority )
{
   if( head_block_num() >= CONTENTO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM )
   {
      create< owner_authority_history_object >( [&]( owner_authority_history_object& hist )
      {
         hist.account = account.name;
         hist.previous_owner_authority = get< account_authority_object, by_account >( account.name ).owner;
         hist.last_valid_time = head_block_time();
      });
   }

   modify( get< account_authority_object, by_account >( account.name ), [&]( account_authority_object& auth )
   {
      auth.owner = owner_authority;
      auth.last_owner_update = head_block_time();
   });
}

void database::process_vesting_withdrawals()
{
    const auto& widx = get_index< account_index >().indices().get< by_next_vesting_withdrawal >();
   const auto& didx = get_index< withdraw_vesting_index>().indices().get<by_account>();
   auto current = widx.begin();

   const auto& cprops = get_dynamic_global_properties();
    

   while( current != widx.end() && current->next_vesting_withdrawal <= head_block_time() )
   {
      const auto& account = *current; ++current;

      share_type withdraw_quota;
       

      if ( account.to_withdraw - account.withdrawn < account.vesting_withdraw_rate.amount )
         withdraw_quota = std::min( account.vesting_shares.amount, account.to_withdraw % account.vesting_withdraw_rate.amount ).value;
      else
         withdraw_quota = std::min( account.vesting_shares.amount, account.vesting_withdraw_rate.amount ).value;
       
      share_type vests_converted_as_cos = 0;
      asset total_cos_converted = asset( 0, COS_SYMBOL );
       
       
       for (auto itr = didx.lower_bound(account.id); itr != didx.end() && itr -> account == account.id; ++itr )
       {
           if (withdraw_quota > 0) {
               share_type to_convert = withdraw_quota < itr -> vesting_shares.amount? withdraw_quota: itr -> vesting_shares.amount;
               withdraw_quota -= to_convert;
               vests_converted_as_cos += to_convert;
               auto converted_cos = asset( to_convert, VESTS_SYMBOL ) * cprops.get_vesting_share_price();
               total_cos_converted += converted_cos;
           }
       }
       



      modify( account, [&]( account_object& a )
      {
         a.vesting_shares.amount -= vests_converted_as_cos;
         a.balance += total_cos_converted;
         a.withdrawn += total_cos_converted.amount;

         if( a.withdrawn >= a.to_withdraw || a.vesting_shares.amount == 0 )
         {
            a.vesting_withdraw_rate.amount = 0;
            a.next_vesting_withdrawal = fc::time_point_sec::maximum();
         }
         else
         {
            a.next_vesting_withdrawal += fc::seconds( CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS );
         }
      });
       
       if( account.withdrawn >= account.to_withdraw || account.vesting_shares.amount == 0 ) {
           for (auto itr = didx.lower_bound(account.id); itr != didx.end() && itr -> account == account.id; ++itr )
           {
               remove(*itr);
           }
       }

      modify( cprops, [&]( dynamic_global_property_object& o )
      {
         o.total_cos += total_cos_converted;
         o.total_vesting_shares.amount -= vests_converted_as_cos;
      });

      push_virtual_operation( fill_vesting_withdraw_operation( account.name, account.name, asset( vests_converted_as_cos, VESTS_SYMBOL ), total_cos_converted ) );
   }
}


/**
 *  This method will iterate through all comment_vote_objects and give them
 *  (max_rewards * weight) / c.total_vote_weight.
 *
 *  @returns unclaimed rewards.
 */
share_type database::pay_curators( const comment_object& c, share_type& max_rewards )
{
   try
   {
      uint128_t total_weight( c.total_vote_weight );
      //edump( (total_weight)(max_rewards) );
      share_type unclaimed_rewards = max_rewards;

      if( !c.allow_curation_rewards )
      {
         unclaimed_rewards = 0;
         max_rewards = 0;
      }
      else if( c.total_vote_weight > 0 )
      {
         const auto& cvidx = get_index<comment_vote_index>().indices().get<by_comment_weight_voter>();
         auto itr = cvidx.lower_bound( c.id );
         while( itr != cvidx.end() && itr->comment == c.id )
         {
            uint128_t weight( itr->weight );
            auto claim = ( ( max_rewards.value * weight ) / total_weight ).to_uint64();
            if( claim > 0 ) // min_amt is non-zero satoshis
            {
               unclaimed_rewards -= claim;
               const auto& voter = get(itr->voter);
//               auto reward = create_vesting( voter, asset( claim, COS_SYMBOL ), has_hardfork( CONTENTO_HARDFORK_0_17__659 ) );
              auto reward = create_vesting( voter, asset( claim, COS_SYMBOL ));

               push_virtual_operation( curation_reward_operation( voter.name, reward, c.author, to_string( c.permlink ) ) );

               #ifndef IS_LOW_MEM
                  modify( voter, [&]( account_object& a )
                  {
                     a.curation_rewards += claim;
                  });
               #endif
            }
            ++itr;
         }
      }
      max_rewards -= unclaimed_rewards;

      return unclaimed_rewards;
   } FC_CAPTURE_AND_RETHROW()
}


share_type database::cashout_comment_helper( util::comment_reward_context& ctx, const comment_object& comment, bool is_subject )
{
    try
    {
        share_type claimed_reward = 0;
        if( comment.net_rshares > 0 )
        {
            ctx.rshares = comment.net_rshares;
            const share_type reward = util::get_rshare_reward( ctx );
            uint128_t reward_tokens = uint128_t( reward.value );
 
            if( reward_tokens > 0 )
            {
                share_type author_tokens = reward_tokens.to_uint64();
                claimed_reward = author_tokens;

                const auto& author = get_account( comment.author );
                auto cov_created = create_vesting(author, author_tokens);

                if(is_subject){
                    push_virtual_operation( subject_reward_operation( comment.author, to_string( comment.permlink ), cov_created));
                }
                else{
                    push_virtual_operation( comment_reward_operation( comment.author, to_string( comment.permlink ), cov_created));
                }
                modify( comment, [&]( comment_object& c )
                       {
                           c.author_rewards += author_tokens;
                       });
                modify( get_account( comment.author ), [&]( account_object& a )
                       {
                           a.posting_rewards += author_tokens;
                       });
            }
        }
        modify( comment, [&]( comment_object& c )
               {
                   /**
                    * A payout is only made for positive rshares, negative rshares hang around
                    * for the next time this post might get an upvote.
                    */
                   if( c.net_rshares > 0 )
                       c.net_rshares = 0;
                   c.children_abs_rshares = 0;
                   c.abs_rshares  = 0;
                   c.vote_rshares = 0;
                   c.total_vote_weight = 0;
                   c.max_cashout_time = fc::time_point_sec::maximum();
                   c.cashout_time = fc::time_point_sec::maximum();
                   c.last_payout = head_block_time();
               } );
        if(is_subject){
            push_virtual_operation( subject_payout_update_operation( comment.author, to_string( comment.permlink ) ) );
        }
        else {
            push_virtual_operation( comment_payout_update_operation( comment.author, to_string( comment.permlink ) ) );
        }
        return claimed_reward;
    } FC_CAPTURE_AND_RETHROW( (comment) )
}

void database::process_comment_cashout()
{
    const auto& grpo = get_dynamic_global_reward_properties();

    modify( grpo, [&]( dynamic_global_reward_property_object& dcpo )
    {
        fc::microseconds decay_rate;
        decay_rate = CONTENTO_RECENT_RSHARES_DECAY_RATE_HF17;
        dcpo.comment_recent_claims -= ( dcpo.comment_recent_claims * ( head_block_time() - dcpo.comment_last_update ).to_seconds() ) / decay_rate.to_seconds();
        dcpo.comment_last_update = head_block_time();
        dcpo.subject_recent_claims -= ( dcpo.subject_recent_claims * ( head_block_time() - dcpo.subject_last_update ).to_seconds() ) / decay_rate.to_seconds();
        dcpo.subject_last_update = head_block_time();
    });
    reward_fund_context subject_rf_ctx, comment_rf_ctx;
    subject_rf_ctx.recent_claims = grpo.subject_recent_claims;
    subject_rf_ctx.reward_balance = grpo.subject_reward_balance;
    comment_rf_ctx.recent_claims = grpo.comment_recent_claims;
    comment_rf_ctx.reward_balance = grpo.comment_reward_balance;
    const auto& cidx        = get_index< comment_index >().indices().get< contento::chain::by_cashout_time >();
    auto current = cidx.begin();
    //  add all rshares about to be cashed out to the reward funds. This ensures equal satoshi per rshare payment

    while( current != cidx.end() && current->cashout_time <= head_block_time() )
    {
        // subject
        if (current -> parent_author == account_name_type()) {
            if( current->net_rshares > 0 )
            {
                subject_rf_ctx.recent_claims += util::evaluate_reward_curve( current->net_rshares.value, grpo.subject_reward_curve, grpo.subject_content_constant );
            }
        }
        else {
            if( current->net_rshares > 0 )
            {
                comment_rf_ctx.recent_claims += util::evaluate_reward_curve( current->net_rshares.value, grpo.comment_reward_curve, grpo.comment_content_constant );
            }
        }
        ++current;
    }
    current = cidx.begin();
    /*
     * Payout all comments
     *
     * Each payout follows a similar pattern, but for a different reason.
     * Cashout comment helper does not know about the reward fund it is paying from.
     * The helper only does token allocation based on curation rewards and the SBD
     * global %, etc.
     *
     * Each context is used by get_rshare_reward to determine what part of each budget
     * the comment is entitled to. Prior to hardfork 17, all payouts are done against
     * the global state updated each payout. After the hardfork, each payout is done
     * against a reward fund state that is snapshotted before all payouts in the block.
     */
    util::comment_reward_context s_ctx, c_ctx;
    while( current != cidx.end() && current->cashout_time <= head_block_time() )
    {
        if (current -> parent_author == CONTENTO_ROOT_POST_PARENT) {
            s_ctx.total_reward_shares2 = subject_rf_ctx.recent_claims;
            s_ctx.total_reward_fund_cos = subject_rf_ctx.reward_balance;
            s_ctx.reward_curve = grpo.subject_reward_curve;
            s_ctx.reward_weight = CONTENTO_100_PERCENT;
            subject_rf_ctx.cos_awarded += cashout_comment_helper( s_ctx, *current, true );
        }
        else {
            c_ctx.total_reward_shares2 = comment_rf_ctx.recent_claims;
            c_ctx.total_reward_fund_cos = comment_rf_ctx.reward_balance;
            c_ctx.reward_weight = CONTENTO_100_PERCENT;
            c_ctx.reward_curve = grpo.comment_reward_curve;
            comment_rf_ctx.cos_awarded += cashout_comment_helper( c_ctx, *current, false );
        }
        // current = cidx.begin();
        modify( grpo, [&]( dynamic_global_reward_property_object& dcpo )
       {
           dcpo.subject_recent_claims = subject_rf_ctx.recent_claims;
           dcpo.subject_reward_balance -= subject_rf_ctx.cos_awarded;
           dcpo.comment_recent_claims = comment_rf_ctx.recent_claims;
           dcpo.comment_reward_balance -= comment_rf_ctx.cos_awarded;
       });
    }
}
/**
 *  Overall the network has an inflation rate of 102% of virtual steem per year
 *  90% of inflation is directed to vesting shares
 *  10% of inflation is directed to subjective proof of work voting

 *
 *  This method pays out vesting and reward shares every block, and liquidity shares once per day.
 *  This method does not pay out witnesses.
 */
void database::process_funds()
{
    const auto& props = get_dynamic_global_properties();
    const auto& grprops = get_dynamic_global_reward_properties();
    const auto& wso = get_witness_schedule_object();
    
    share_type new_cos = PER_BLOCK_PRODUCT_COS;
    auto creator_reward = ( new_cos * CONTENTO_CREATOR_REWARD_PERCENT) / CONTENTO_100_PERCENT;
    auto commenter_reward = ( new_cos * CONTENTO_COMMENTER_REWARD_PERCENT ) / CONTENTO_100_PERCENT; /// 15% to commenter
    auto other_reward = (new_cos * CONTENTO_OTHER_REWARD_PERCENT ) / CONTENTO_100_PERCENT; // 5% 预留
    auto witness_reward = new_cos - creator_reward - commenter_reward - other_reward;
    const auto& cwit = get_witness( props.current_witness );
    witness_reward *= CONTENTO_MAX_WITNESSES;
    if( cwit.schedule == witness_object::timeshare )
        witness_reward *= wso.timeshare_weight;
    else if( cwit.schedule == witness_object::miner )
        witness_reward *= wso.miner_weight;
    else if( cwit.schedule == witness_object::top19 )
        witness_reward *= wso.top19_weight;
    else
        wlog( "Encountered unknown witness type for witness: ${w}", ("w", cwit.owner) );
    witness_reward /= wso.witness_pay_normalization_factor;
    new_cos = creator_reward + commenter_reward + other_reward + witness_reward;
    modify( props, [&]( dynamic_global_property_object& p )
   {
       p.current_supply           += asset( new_cos, COS_SYMBOL );
   });
    
    modify( grprops, [&]( dynamic_global_reward_property_object& r){
        r.subject_reward_balance += asset( creator_reward, COS_SYMBOL );
        r.comment_reward_balance += asset( commenter_reward, COS_SYMBOL);
        r.other_reward_balance += asset(other_reward, COS_SYMBOL);
    });
    const auto& producer_reward = create_vesting( get_account( cwit.owner ), asset( witness_reward, COS_SYMBOL ) );
    push_virtual_operation( producer_reward_operation( cwit.owner, producer_reward ) );
}
    
void database::process_other_cashout()
{
    const auto& rpo = get_dynamic_global_reward_properties();
    if(rpo.tick % OTHER_REWARD_CASHOUT_INTERVAL == 0){
        const auto& report_idx = get_index< comment_report_index >().indices().get< by_cashout_time >();
        auto current = report_idx.begin();
        
        auto reward_balance = rpo.other_reward_balance;
        std::vector<account_name_type> reporters;
        
        while (current != report_idx.end() && current->cashout_time <= head_block_time()){
            reward_balance += current -> total_credit();
            auto& itr = current -> reports.account_reports;
            for(auto c = itr.begin();c != itr.end();++c){
                reporters.push_back(c -> first);
            }
            remove( *current );
            ++current;
        }
        
        auto size = reporters.size();
        
        auto creator_reward = reward_balance.amount / 2;
        auto commenter_reward = reward_balance.amount - creator_reward;
        if(size > 0){

            auto amount = reward_balance.amount / size;
            auto total = amount * size;
            
            creator_reward = (reward_balance.amount - total) / 2;
            commenter_reward = reward_balance.amount - total - creator_reward;
            
            for(auto iter=reporters.begin(); iter != reporters.end();++iter){
                const auto& account = get_account(*iter);
                create_vesting(account, asset(amount, COS_SYMBOL));
            }
        }
        
        
        // accumulate new cos into reward balance
        modify( rpo, [&](dynamic_global_reward_property_object& r)
        {
            r.subject_reward_balance += asset(creator_reward, COS_SYMBOL);
            r.comment_reward_balance += asset(commenter_reward, COS_SYMBOL);
            r.other_reward_balance = asset(0, COS_SYMBOL);
            r.tick = 1;
        });
        
    }
    else{
        modify(rpo, [&](dynamic_global_reward_property_object &r){
            r.tick ++;
        });
    }
}


void database::process_savings_withdraws()
{
  const auto& idx = get_index< savings_withdraw_index >().indices().get< by_complete_from_rid >();
  auto itr = idx.begin();
  while( itr != idx.end() ) {
     if( itr->complete > head_block_time() )
        break;
     adjust_balance( get_account( itr->to ), itr->amount );

     modify( get_account( itr->from ), [&]( account_object& a )
     {
        a.savings_withdraw_requests--;
     });

     push_virtual_operation( fill_transfer_from_savings_operation( itr->from, itr->to, itr->amount, itr->request_id, to_string( itr->memo) ) );

     remove( *itr );
     itr = idx.begin();
  }
}


share_type database::pay_reward_funds( share_type reward )
{
   const auto& reward_idx = get_index< reward_fund_index, by_id >();
   share_type used_rewards = 0;

   for( auto itr = reward_idx.begin(); itr != reward_idx.end(); ++itr )
   {
      // reward is a per block reward and the percents are 16-bit. This should never overflow
      auto r = ( reward * itr->percent_content_rewards ) / CONTENTO_100_PERCENT;

      modify( *itr, [&]( reward_fund_object& rfo )
      {
         rfo.reward_balance += asset( r, COS_SYMBOL );
      });

      used_rewards += r;

      // Sanity check to ensure we aren't printing more STEEM than has been allocated through inflation
      FC_ASSERT( used_rewards <= reward );
   }

   return used_rewards;
}


void database::account_recovery_processing()
{
   // Clear expired recovery requests
   const auto& rec_req_idx = get_index< account_recovery_request_index >().indices().get< by_expiration >();
   auto rec_req = rec_req_idx.begin();

   while( rec_req != rec_req_idx.end() && rec_req->expires <= head_block_time() )
   {
      remove( *rec_req );
      rec_req = rec_req_idx.begin();
   }

   // Clear invalid historical authorities
   const auto& hist_idx = get_index< owner_authority_history_index >().indices(); //by id
   auto hist = hist_idx.begin();

   while( hist != hist_idx.end() && time_point_sec( hist->last_valid_time + CONTENTO_OWNER_AUTH_RECOVERY_PERIOD ) < head_block_time() )
   {
      remove( *hist );
      hist = hist_idx.begin();
   }

   // Apply effective recovery_account changes
   const auto& change_req_idx = get_index< change_recovery_account_request_index >().indices().get< by_effective_date >();
   auto change_req = change_req_idx.begin();

   while( change_req != change_req_idx.end() && change_req->effective_on <= head_block_time() )
   {
      modify( get_account( change_req->account_to_recover ), [&]( account_object& a )
      {
         a.recovery_account = change_req->recovery_account;
      });

      remove( *change_req );
      change_req = change_req_idx.begin();
   }
}

void database::process_decline_voting_rights()
{
   const auto& request_idx = get_index< decline_voting_rights_request_index >().indices().get< by_effective_date >();
   auto itr = request_idx.begin();

   while( itr != request_idx.end() && itr->effective_date <= head_block_time() )
   {
      const auto& account = get(itr->account);

      /// remove all current votes
      std::array<share_type, CONTENTO_MAX_PROXY_RECURSION_DEPTH+1> delta;
      delta[0] = -account.vesting_shares.amount;
      for( int i = 0; i < CONTENTO_MAX_PROXY_RECURSION_DEPTH; ++i )
         delta[i+1] = -account.proxied_vsf_votes[i];
      adjust_proxied_witness_votes( account, delta );

      clear_witness_votes( account );

      modify( get(itr->account), [&]( account_object& a )
      {
         a.can_vote = false;
         a.proxy = CONTENTO_PROXY_TO_SELF_ACCOUNT;
      });

      remove( *itr );
      itr = request_idx.begin();
   }
}

time_point_sec database::head_block_time()const
{
   return get_dynamic_global_properties().time;
}

uint32_t database::head_block_num()const
{
   return get_dynamic_global_properties().head_block_number;
}

block_id_type database::head_block_id()const
{
   return get_dynamic_global_properties().head_block_id;
}

node_property_object& database::node_properties()
{
   return _node_property_object;
}

uint32_t database::last_non_undoable_block_num() const
{
   return get_dynamic_global_properties().last_irreversible_block_num;
}

void database::initialize_evaluators()
{
   _my->_evaluator_registry.register_evaluator< vote_evaluator                           >();
   _my->_evaluator_registry.register_evaluator< comment_evaluator                        >();
   _my->_evaluator_registry.register_evaluator< comment_options_evaluator                >();
    _my->_evaluator_registry.register_evaluator< convert_from_vesting_evaluator          >();
   _my->_evaluator_registry.register_evaluator< delete_comment_evaluator                 >();
   _my->_evaluator_registry.register_evaluator< transfer_evaluator                       >();
   _my->_evaluator_registry.register_evaluator< transfer_to_vesting_evaluator            >();

   _my->_evaluator_registry.register_evaluator< account_create_evaluator                 >();
   _my->_evaluator_registry.register_evaluator< admin_grant_evaluator                    >();
   _my->_evaluator_registry.register_evaluator< comment_report_evaluator                 >();
   _my->_evaluator_registry.register_evaluator< account_update_evaluator                 >();
   _my->_evaluator_registry.register_evaluator< witness_update_evaluator                 >();
   _my->_evaluator_registry.register_evaluator< account_witness_vote_evaluator           >();
   _my->_evaluator_registry.register_evaluator< account_witness_proxy_evaluator          >();
   _my->_evaluator_registry.register_evaluator< custom_evaluator                         >();
   _my->_evaluator_registry.register_evaluator< custom_binary_evaluator                  >();
   _my->_evaluator_registry.register_evaluator< custom_json_evaluator                    >();

   _my->_evaluator_registry.register_evaluator< report_over_production_evaluator         >();

   _my->_evaluator_registry.register_evaluator< challenge_authority_evaluator            >();
   _my->_evaluator_registry.register_evaluator< prove_authority_evaluator                >();
   _my->_evaluator_registry.register_evaluator< request_account_recovery_evaluator       >();
   _my->_evaluator_registry.register_evaluator< recover_account_evaluator                >();
   _my->_evaluator_registry.register_evaluator< change_recovery_account_evaluator        >();

   _my->_evaluator_registry.register_evaluator< account_create_with_delegation_evaluator >();


   _my->_evaluator_registry.register_evaluator< vm_evaluator        >();
}

void database::set_custom_operation_interpreter( const std::string& id, std::shared_ptr< custom_operation_interpreter > registry )
{
   bool inserted = _custom_operation_interpreters.emplace( id, registry ).second;
   // This assert triggering means we're mis-configured (multiple registrations of custom JSON evaluator for same ID)
   FC_ASSERT( inserted );
}

std::shared_ptr< custom_operation_interpreter > database::get_custom_json_evaluator( const std::string& id )
{
   auto it = _custom_operation_interpreters.find( id );
   if( it != _custom_operation_interpreters.end() )
      return it->second;
   return std::shared_ptr< custom_operation_interpreter >();
}

void database::initialize_indexes()
{
   add_core_index< dynamic_global_property_index           >(*this);
   add_core_index< dynamic_global_reward_property_index    >(*this);
   add_core_index< account_index                           >(*this);
   add_core_index< admin_index                             >(*this);
   add_core_index< account_authority_index                 >(*this);
   add_core_index< witness_index                           >(*this);
   add_core_index< transaction_index                       >(*this);
   add_core_index< block_summary_index                     >(*this);
   add_core_index< witness_schedule_index                  >(*this);
   add_core_index< comment_index                           >(*this);
   add_core_index< comment_vote_index                      >(*this);
   add_core_index< comment_report_index                    >(*this);
   add_core_index< witness_vote_index                      >(*this);
   add_core_index< limit_order_index                       >(*this);
//    add_core_index< feed_history_index                      >(*this);
   add_core_index< convert_request_index                   >(*this);
   add_core_index< liquidity_reward_balance_index          >(*this);
   add_core_index< operation_index                         >(*this);
   add_core_index< account_history_index                   >(*this);
   add_core_index< hardfork_property_index                 >(*this);
   add_core_index< withdraw_vesting_route_index            >(*this);
   add_core_index< withdraw_vesting_index                  >(*this);
   add_core_index< owner_authority_history_index           >(*this);
   add_core_index< account_recovery_request_index          >(*this);
   add_core_index< change_recovery_account_request_index   >(*this);
   add_core_index< escrow_index                            >(*this);
   add_core_index< savings_withdraw_index                  >(*this);
   add_core_index< decline_voting_rights_request_index     >(*this);
   add_core_index< reward_fund_index                       >(*this);
   add_core_index< vesting_delegation_index                >(*this);
   add_core_index< vesting_delegation_expiration_index     >(*this);
   add_core_index< contract_balance_index     >(*this);

   _plugin_index_signal();
}

const std::string& database::get_json_schema()const
{
   return _json_schema;
}

void database::init_schema()
{
   /*done_adding_indexes();

   db_schema ds;

   std::vector< std::shared_ptr< abstract_schema > > schema_list;

   std::vector< object_schema > object_schemas;
   get_object_schemas( object_schemas );

   for( const object_schema& oschema : object_schemas )
   {
      ds.object_types.emplace_back();
      ds.object_types.back().space_type.first = oschema.space_id;
      ds.object_types.back().space_type.second = oschema.type_id;
      oschema.schema->get_name( ds.object_types.back().type );
      schema_list.push_back( oschema.schema );
   }

   std::shared_ptr< abstract_schema > operation_schema = get_schema_for_type< operation >();
   operation_schema->get_name( ds.operation_type );
   schema_list.push_back( operation_schema );

   for( const std::pair< std::string, std::shared_ptr< custom_operation_interpreter > >& p : _custom_operation_interpreters )
   {
      ds.custom_operation_types.emplace_back();
      ds.custom_operation_types.back().id = p.first;
      schema_list.push_back( p.second->get_operation_schema() );
      schema_list.back()->get_name( ds.custom_operation_types.back().type );
   }

   graphene::db::add_dependent_schemas( schema_list );
   std::sort( schema_list.begin(), schema_list.end(),
      []( const std::shared_ptr< abstract_schema >& a,
          const std::shared_ptr< abstract_schema >& b )
      {
         return a->id < b->id;
      } );
   auto new_end = std::unique( schema_list.begin(), schema_list.end(),
      []( const std::shared_ptr< abstract_schema >& a,
          const std::shared_ptr< abstract_schema >& b )
      {
         return a->id == b->id;
      } );
   schema_list.erase( new_end, schema_list.end() );

   for( std::shared_ptr< abstract_schema >& s : schema_list )
   {
      std::string tname;
      s->get_name( tname );
      FC_ASSERT( ds.types.find( tname ) == ds.types.end(), "types with different ID's found for name ${tname}", ("tname", tname) );
      std::string ss;
      s->get_str_schema( ss );
      ds.types.emplace( tname, ss );
   }

   _json_schema = fc::json::to_string( ds );
   return;*/
}

void database::init_genesis( uint64_t init_supply )
{
   try
   {
      struct auth_inhibitor
      {
         auth_inhibitor(database& db) : db(db), old_flags(db.node_properties().skip_flags)
         { db.node_properties().skip_flags |= skip_authority_check; }
         ~auth_inhibitor()
         { db.node_properties().skip_flags = old_flags; }
      private:
         database& db;
         uint32_t old_flags;
      } inhibitor(*this);

      // Create blockchain accounts
      public_key_type      init_public_key(CONTENTO_INIT_PUBLIC_KEY);

      create< account_object >( [&]( account_object& a )
      {
         a.name = CONTENTO_MINER_ACCOUNT;
      } );
      create< account_authority_object >( [&]( account_authority_object& auth )
      {
         auth.account = CONTENTO_MINER_ACCOUNT;
         auth.owner.weight_threshold = 1;
         auth.active.weight_threshold = 1;
      });

      create< account_object >( [&]( account_object& a )
      {
         a.name = CONTENTO_NULL_ACCOUNT;
      } );
      create< account_authority_object >( [&]( account_authority_object& auth )
      {
         auth.account = CONTENTO_NULL_ACCOUNT;
         auth.owner.weight_threshold = 1;
         auth.active.weight_threshold = 1;
      });

      create< account_object >( [&]( account_object& a )
      {
         a.name = CONTENTO_TEMP_ACCOUNT;
      } );
      create< account_authority_object >( [&]( account_authority_object& auth )
      {
         auth.account = CONTENTO_TEMP_ACCOUNT;
         auth.owner.weight_threshold = 0;
         auth.active.weight_threshold = 0;
      });

      for( int i = 0; i < CONTENTO_NUM_INIT_MINERS; ++i )
      {
         create< account_object >( [&]( account_object& a )
         {
            a.name = CONTENTO_INIT_MINER_NAME + ( i ? fc::to_string( i ) : std::string() );
            a.memo_key = init_public_key;
            a.balance  = asset( i ? 0 : init_supply, COS_SYMBOL );
         } );

         create< account_authority_object >( [&]( account_authority_object& auth )
         {
            auth.account = CONTENTO_INIT_MINER_NAME + ( i ? fc::to_string( i ) : std::string() );
            auth.owner.add_authority( init_public_key, 1 );
            auth.owner.weight_threshold = 1;
            auth.active  = auth.owner;
            auth.posting = auth.active;
         });

         create< witness_object >( [&]( witness_object& w )
         {
            w.owner        = CONTENTO_INIT_MINER_NAME + ( i ? fc::to_string(i) : std::string() );
            w.signing_key  = init_public_key;
            w.schedule = witness_object::miner;
         } );
      }

      create< dynamic_global_property_object >( [&]( dynamic_global_property_object& p )
      {
         p.current_witness = CONTENTO_INIT_MINER_NAME;
         p.time = CONTENTO_GENESIS_TIME;
         p.recent_slots_filled = fc::uint128::max_value();
         p.participation_count = 128;
         p.current_supply = asset( init_supply, COS_SYMBOL );
         p.total_cos = p.current_supply;
         p.maximum_block_size = CONTENTO_MAX_BLOCK_SIZE;
      } );
       
       create< dynamic_global_reward_property_object>( [&]( dynamic_global_reward_property_object& p)
      {
          p.subject_last_update = CONTENTO_GENESIS_TIME;
          p.comment_last_update = CONTENTO_GENESIS_TIME;
      });

      // Nothing to do
//      create< feed_history_object >( [&]( feed_history_object& o ) {});
      for( int i = 0; i < 0x10000; i++ )
         create< block_summary_object >( [&]( block_summary_object& ) {});
      create< hardfork_property_object >( [&](hardfork_property_object& hpo )
      {
         hpo.processed_hardforks.push_back( CONTENTO_GENESIS_TIME );
      } );

      // Create witness scheduler
      create< witness_schedule_object >( [&]( witness_schedule_object& wso )
      {
         wso.current_shuffled_witnesses[0] = CONTENTO_INIT_MINER_NAME;
      } );
   }
   FC_CAPTURE_AND_RETHROW()
}


void database::validate_transaction(  transaction_wrapper& trx_wrapper )
{
   database::with_write_lock( [&]()
   {
      auto session = start_undo_session( true );
      _apply_transaction( trx_wrapper );
      session.undo();
   });
}

void database::notify_changed_objects()
{
   try
   {
      /*vector< graphene::chainbase::generic_id > ids;
      get_changed_ids( ids );
      CONTENTO_TRY_NOTIFY( changed_objects, ids )*/
      /*
      if( _undo_db.enabled() )
      {
         const auto& head_undo = _undo_db.head();
         vector<object_id_type> changed_ids;  changed_ids.reserve(head_undo.old_values.size());
         for( const auto& item : head_undo.old_values ) changed_ids.push_back(item.first);
         for( const auto& item : head_undo.new_ids ) changed_ids.push_back(item);
         vector<const object*> removed;
         removed.reserve( head_undo.removed.size() );
         for( const auto& item : head_undo.removed )
         {
            changed_ids.push_back( item.first );
            removed.emplace_back( item.second.get() );
         }
         CONTENTO_TRY_NOTIFY( changed_objects, changed_ids )
      }
      */
   }
   FC_CAPTURE_AND_RETHROW()

}

void database::set_flush_interval( uint32_t flush_blocks )
{
   _flush_blocks = flush_blocks;
   _next_flush_block = 0;
}

//////////////////// private methods ////////////////////

void database::apply_block( const signed_block& next_block, uint32_t skip )
{ try {
   //fc::time_point begin_time = fc::time_point::now();

   auto block_num = next_block.block_num();
   /*
   if( _checkpoints.size() && _checkpoints.rbegin()->second != block_id_type() )
   {
      auto itr = _checkpoints.find( block_num );
      if( itr != _checkpoints.end() )
         FC_ASSERT( next_block.id() == itr->second, "Block did not match checkpoint", ("checkpoint",*itr)("block_id",next_block.id()) );

      if( _checkpoints.rbegin()->first >= block_num )
         skip = skip_witness_signature
              | skip_transaction_signatures
              | skip_transaction_dupe_check
              | skip_fork_db
              | skip_block_size_check
              | skip_tapos_check
              | skip_authority_check
              // | skip_merkle_check While blockchain is being downloaded, txs need to be validated against block headers 
              | skip_undo_history_check
              | skip_witness_schedule_check
              | skip_validate
              | skip_validate_invariants
              ;
   }
   */
   
    //if ( _checkpoints.size() && _checkpoints.rbegin()->second != block_id_type() ) {
    //   auto skip_tmp = process_checkpoints( next_block, skip );
    //   if( skip & skip_apply_transaction ) {
    //       skip = skip_tmp | skip_apply_transaction;
    //   } else {
    //       skip = skip_tmp;
    //   }
    //}

   detail::with_skip_flags( *this, skip, [&]()
   {
      _apply_block( next_block );
   } );
    
   _tps_stats->update();

   /*try
   {
   /// check invariants
   if( is_producing() || !( skip & skip_validate_invariants ) )
      validate_invariants();
   }
   FC_CAPTURE_AND_RETHROW( (next_block) );*/

   //fc::time_point end_time = fc::time_point::now();
   //fc::microseconds dt = end_time - begin_time;
   if( _flush_blocks != 0 )
   {
      if( _next_flush_block == 0 )
      {
         uint32_t lep = block_num + 1 + _flush_blocks * 9 / 10;
         uint32_t rep = block_num + 1 + _flush_blocks;

         // use time_point::now() as RNG source to pick block randomly between lep and rep
         uint32_t span = rep - lep;
         uint32_t x = lep;
         if( span > 0 )
         {
            uint64_t now = uint64_t( fc::time_point::now().time_since_epoch().count() );
            x += now % span;
         }
         _next_flush_block = x;
         ilog( "Next flush scheduled at block ${b}", ("b", x) );
      }

      if( _next_flush_block == block_num )
      {
         _next_flush_block = 0;
         ilog( "Flushing database shared memory at block ${b}", ("b", block_num) );
         chainbase::database::flush();
      }
   }

   show_free_memory( false );

} FC_CAPTURE_AND_RETHROW( (next_block) ) }

void database::show_free_memory( bool force )
{
   uint32_t free_gb = uint32_t( get_free_memory() / (1024*1024*1024) );
   if( force || (free_gb < _last_free_gb_printed) || (free_gb > _last_free_gb_printed+1) )
   {
      ilog( "Free memory is now ${n}G", ("n", free_gb) );
      _last_free_gb_printed = free_gb;
   }

   if( free_gb == 0 )
   {
      uint32_t free_mb = uint32_t( get_free_memory() / (1024*1024) );

      if( free_mb <= 100 && head_block_num() % 10 == 0 )
         elog( "Free memory is now ${n}M. Increase shared file size immediately!" , ("n", free_mb) );
   }
}

void database::_apply_block( const signed_block& next_block )
{ try {
   uint32_t next_block_num = next_block.block_num();
   //block_id_type next_block_id = next_block.id();
    
// #ifdef IS_TEST_NET
//     if( BOOST_UNLIKELY( next_block_num == 1 && init_genesis_hardforks ) )
//     {
//         // For every existing before the head_block_time (genesis time), apply the hardfork
//         // This allows the test net to launch with past hardforks and apply the next harfork when running
//         auto now = next_block.timestamp;
//         for( size_t i = 0;
//             i <= CONTENTO_NUM_HARDFORKS && _hardfork_times[i] <= now;
//             i++ )
//         {
//             set_hardfork( i, true );
//         }
//     }
// #endif

   uint32_t skip = get_node_properties().skip_flags;

   if( !( skip & skip_merkle_check ) )
   {
      auto merkle_root = next_block.calculate_merkle_root();
      FC_ASSERT( next_block.transaction_merkle_root == merkle_root, "Merkle check failed", ("next_block.transaction_merkle_root",next_block.transaction_merkle_root)("calc",merkle_root)("next_block",next_block)("id",next_block.id()) );
   }

   const witness_object& signing_witness = validate_block_header(skip, next_block);

   _current_block_num    = next_block_num;
   _current_trx_in_block = 0;

   const auto& gprops = get_dynamic_global_properties();
   auto block_size = fc::raw::pack_size( next_block );
   FC_ASSERT( block_size <= gprops.maximum_block_size, "Block Size is too Big", ("next_block_num",next_block_num)("block_size", block_size)("max",gprops.maximum_block_size) );

   if( block_size < CONTENTO_MIN_BLOCK_SIZE )
   {
      elog( "Block size is too small",
         ("next_block_num",next_block_num)("block_size", block_size)("min",CONTENTO_MIN_BLOCK_SIZE)
      );
   }

   /// modify current witness so transaction evaluators can know who included the transaction,
   /// this is mostly for POW operations which must pay the current_witness
   modify( gprops, [&]( dynamic_global_property_object& dgp ){
      dgp.current_witness = next_block.witness;
   });

   /// parse witness version reporting
   process_header_extensions( next_block );

   const auto& witness = get_witness( next_block.witness );
   const auto& hardfork_state = get_hardfork_property_object();
   FC_ASSERT( witness.running_version >= hardfork_state.current_hardfork_version,
      "Block produced by witness that is not running current hardfork",
      ("witness",witness)("next_block.witness",next_block.witness)("hardfork_state", hardfork_state)
   );

    transaction_wrapper tmp_wrapper;
    
    if( !( skip & skip_apply_transaction ) ){
        for(  auto& trx_wrapper : next_block.transactions )
        {
            /* We do not need to push the undo state for each transaction
            * because they either all apply and are valid or the
            * entire block fails to apply.  We only need an "undo" state
            * for transactions when validating broadcast transactions or
            * when building a block.
            */
            tmp_wrapper = trx_wrapper;
            tmp_wrapper.invoice.status = 200;
            tmp_wrapper.invoice.gas_usage = 0;
            tmp_wrapper.invoice.vm_error = false;
            tmp_wrapper.invoice.vm_error_code = 0;
            tmp_wrapper.invoice.vm_error_msg.clear();
            tmp_wrapper.invoice.vm_console.clear();
            apply_transaction( tmp_wrapper, skip );
            FC_ASSERT(tmp_wrapper.invoice.status == trx_wrapper.invoice.status
                      && tmp_wrapper.invoice.gas_usage == trx_wrapper.invoice.gas_usage
                      && tmp_wrapper.invoice.vm_error == trx_wrapper.invoice.vm_error
                      && tmp_wrapper.invoice.vm_error_code == trx_wrapper.invoice.vm_error_code
                      ,"mismatched invoice");
            ++_current_trx_in_block;
        }
    }

   update_global_dynamic_data(next_block);
   update_signing_witness(signing_witness, next_block);

   update_last_irreversible_block();

   create_block_summary(next_block);
//   clear_expired_transactions();
//   clear_expired_orders();
   clear_expired_delegations();
   update_witness_schedule(*this);

//   update_median_feed();
//   update_virtual_supply();

   clear_null_account_balance();
   process_funds();
   // process_conversions();
   process_comment_cashout();
   process_other_cashout();
   process_vesting_withdrawals();
   //process_savings_withdraws();
//   update_virtual_supply();

   account_recovery_processing();
   // expire_escrow_ratification();
   process_decline_voting_rights();

   process_hardforks();

   // notify observers that the block has been applied
   notify_applied_block( next_block );

   notify_changed_objects();

} //FC_CAPTURE_AND_RETHROW( (next_block.block_num()) )  }
FC_CAPTURE_LOG_AND_RETHROW( (next_block.block_num()) )
}

void database::process_header_extensions( const signed_block& next_block )
{
   auto itr = next_block.extensions.begin();

   while( itr != next_block.extensions.end() )
   {
      switch( itr->which() )
      {
         case 0: // void_t
            break;
         case 1: // version
         {
            auto reported_version = itr->get< version >();
            const auto& signing_witness = get_witness( next_block.witness );
            //idump( (next_block.witness)(signing_witness.running_version)(reported_version) );

            if( reported_version != signing_witness.running_version )
            {
               modify( signing_witness, [&]( witness_object& wo )
               {
                  wo.running_version = reported_version;
               });
            }
            break;
         }
         case 2: // hardfork_version vote
         {
            auto hfv = itr->get< hardfork_version_vote >();
            const auto& signing_witness = get_witness( next_block.witness );
            //idump( (next_block.witness)(signing_witness.running_version)(hfv) );

            if( hfv.hf_version != signing_witness.hardfork_version_vote || hfv.hf_time != signing_witness.hardfork_time_vote )
               modify( signing_witness, [&]( witness_object& wo )
               {
                  wo.hardfork_version_vote = hfv.hf_version;
                  wo.hardfork_time_vote = hfv.hf_time;
               });

            break;
         }
         default:
            FC_ASSERT( false, "Unknown extension in block header" );
      }

      ++itr;
   }
}



//void database::update_median_feed() {
//try {
//   if( (head_block_num() % CONTENTO_FEED_INTERVAL_BLOCKS) != 0 )
//      return;
//
//   auto now = head_block_time();
//   const witness_schedule_object& wso = get_witness_schedule_object();
//   vector<price> feeds; feeds.reserve( wso.num_scheduled_witnesses );
//   for( int i = 0; i < wso.num_scheduled_witnesses; i++ )
//   {
//      const auto& wit = get_witness( wso.current_shuffled_witnesses[i] );
//    //   if( has_hardfork( CONTENTO_HARDFORK_0_19__822 ) )
//    //   {
//         if( now < wit.last_sbd_exchange_update + CONTENTO_MAX_FEED_AGE_SECONDS
//            && !wit.sbd_exchange_rate.is_null() )
//         {
//            feeds.push_back( wit.sbd_exchange_rate );
//         }
//    //   }
//    //   else if( wit.last_sbd_exchange_update < now + CONTENTO_MAX_FEED_AGE_SECONDS &&
//    //       !wit.sbd_exchange_rate.is_null() )
//    //   {
//    //      feeds.push_back( wit.sbd_exchange_rate );
//    //   }
//   }
//
//   if( feeds.size() >= CONTENTO_MIN_FEEDS )
//   {
//      std::sort( feeds.begin(), feeds.end() );
//      auto median_feed = feeds[feeds.size()/2];
//
//      modify( get_feed_history(), [&]( feed_history_object& fho )
//      {
//         fho.price_history.push_back( median_feed );
//         size_t steemit_feed_history_window = CONTENTO_FEED_HISTORY_WINDOW_PRE_HF_16;
//        //  if( has_hardfork( CONTENTO_HARDFORK_0_16__551) )
//            steemit_feed_history_window = CONTENTO_FEED_HISTORY_WINDOW;
//
//         if( fho.price_history.size() > steemit_feed_history_window )
//            fho.price_history.pop_front();
//
//         if( fho.price_history.size() )
//         {
//            std::deque< price > copy;
//            for( auto i : fho.price_history )
//            {
//               copy.push_back( i );
//            }
//
//            std::sort( copy.begin(), copy.end() ); /// TODO: use nth_item
//            fho.current_median_history = copy[copy.size()/2];
//
//// #ifdef IS_TEST_NET
////             if( skip_price_feed_limit_check )
////                return;
//// #endif
//         }
//      });
//   }
//} FC_CAPTURE_AND_RETHROW() }

void database::apply_transaction( transaction_wrapper& trx_wrapper, uint32_t skip)
{
   detail::with_skip_flags( *this, skip, [&]() { _apply_transaction(trx_wrapper); });
   notify_on_applied_transaction( trx_wrapper.sig_trx );
}


std::shared_ptr<transaction_context> database::_apply_transaction( transaction_wrapper& trx_wrapper)
{ try {
   auto trx = trx_wrapper.sig_trx;

   _current_trx_id = trx.id();
   uint32_t skip = get_node_properties().skip_flags;

   if( !(skip&skip_validate) )   /* issue #505 explains why this skip_flag is disabled */
      trx.validate();

   auto& trx_idx = get_index<transaction_index>();
   const chain_id_type& chain_id = CONTENTO_CHAIN_ID;
   auto trx_id = trx.id();
   // idump((trx_id)(skip&skip_transaction_dupe_check));
   FC_ASSERT( (skip & skip_transaction_dupe_check) ||
              trx_idx.indices().get<by_trx_id>().find(trx_id) == trx_idx.indices().get<by_trx_id>().end(),
              "Duplicate transaction check failed", ("trx_ix", trx_id) );

   if( !(skip & (skip_transaction_signatures | skip_authority_check) ) )
   {
      auto get_active  = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).active ); };
      auto get_owner   = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).owner );  };
      auto get_posting = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).posting );  };

      trx.verify_authority( chain_id, get_active, get_owner, get_posting, CONTENTO_MAX_SIG_CHECK_DEPTH );
      check_admin(trx.extract_admin_ops());
   }

   //Skip all manner of expiration and TaPoS checking if we're on block 1; It's impossible that the transaction is
   //expired, and TaPoS makes no sense as no blocks exist.
   if( BOOST_LIKELY(head_block_num() > 0) )
   {
      if( !(skip & skip_tapos_check) )
      {
         const auto& tapos_block_summary = get< block_summary_object >( trx.ref_block_num );
         //Verify TaPoS block summary has correct ID prefix, and that this block's time is not past the expiration
         CONTENTO_ASSERT( trx.ref_block_prefix == tapos_block_summary.block_id._hash[1], transaction_tapos_exception,
                    "", ("trx.ref_block_prefix", trx.ref_block_prefix)
                    ("tapos_block_summary",tapos_block_summary.block_id._hash[1]));
      }

      fc::time_point_sec now = head_block_time();

      CONTENTO_ASSERT( trx.expiration <= now + fc::seconds(CONTENTO_MAX_TIME_UNTIL_EXPIRATION), transaction_expiration_exception,
                  "", ("trx.expiration",trx.expiration)("now",now)("max_til_exp",CONTENTO_MAX_TIME_UNTIL_EXPIRATION));
      // Simple solution to pending trx bug when now == trx.expiration
      CONTENTO_ASSERT( now < trx.expiration, transaction_expiration_exception, "", ("now",now)("trx.exp",trx.expiration) );
      CONTENTO_ASSERT( now <= trx.expiration, transaction_expiration_exception, "", ("now",now)("trx.exp",trx.expiration) );
   }

   //Insert transaction into unique transactions database.
   if( !(skip & skip_transaction_dupe_check) )
   {
      create<transaction_object>([&](transaction_object& transaction) {
         transaction.trx_id = trx_id;
         transaction.expiration = trx.expiration;
         fc::raw::pack( transaction.packed_trx, trx );
      });
   }
   notify_on_pre_apply_transaction( trx );

   //Finally process the operations
   auto trx_ctx = std::make_shared<transaction_context>(ctrl, trx, trx_id);
   _current_op_in_trx = 0;
    
    try {
    
       for( const auto& op : trx.operations )
       {
           try {
               apply_operation(op, trx_ctx);
               ++_current_op_in_trx;
           } FC_CAPTURE_AND_RETHROW( (op) );
       }
        
    } catch(...) {
        trx_wrapper.invoice.status = 500;
        trx_wrapper.invoice.gas_usage = trx_ctx->gas_paid();
        trx_wrapper.invoice.vm_error = true;
        trx_wrapper.invoice.vm_error_code = 0;
        throw;
    }

   _current_trx_id = transaction_id_type();
    
    trx_wrapper.invoice.status = 200;
    trx_wrapper.invoice.gas_usage = trx_ctx->gas_paid();
    trx_wrapper.invoice.vm_error = trx_ctx->has_vm_error();
    trx_wrapper.invoice.vm_error_code = trx_ctx->vm_error()? trx_ctx->vm_error()->code() : 0;
    trx_wrapper.invoice.vm_error_msg = trx_ctx->vm_error()? trx_ctx->vm_error()->to_detail_string() : "";
    trx_wrapper.invoice.vm_console = trx_ctx->get_vm_console();
    
   return trx_ctx;
} FC_CAPTURE_AND_RETHROW( (trx_wrapper) ) }

bool database::execute_operation(const transaction_context& trx_context, const operation& op ){

   auto get_active  = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).active ); };
   auto get_owner   = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).owner );  };
   auto get_posting = [&]( const string& name ) { return authority( get< account_authority_object, by_account >( name ).posting );  };

   try
   {
      std::vector<operation> ops;
      ops.push_back(op);
      trx_context.trx.verify_ops_authority(ops, get_chain_id(), get_active, get_owner, get_posting, CONTENTO_MAX_SIG_CHECK_DEPTH );
      // TODO YYK admin op must verify
      //check_admin(trx.extract_admin_ops());
   }
   catch( protocol::tx_missing_active_auth& e )
   {
      throw e;
   }

   apply_operation(op, nullptr);
   return true;
}

void database::apply_operation(const operation& op, std::shared_ptr<transaction_context> ctx)
{
   operation_notification note(op);
   notify_pre_apply_operation( note );
   _my->_evaluator_registry.get_evaluator( op ).apply( op, ctx );
   notify_post_apply_operation( note );
}

const witness_object& database::validate_block_header( uint32_t skip, const signed_block& next_block )const
{ try {
   FC_ASSERT( head_block_id() == next_block.previous, "", ("head_block_id",head_block_id())("next.prev",next_block.previous) );
   FC_ASSERT( head_block_time() < next_block.timestamp, "", ("head_block_time",head_block_time())("next",next_block.timestamp)("blocknum",next_block.block_num()) );
   const witness_object& witness = get_witness( next_block.witness );

   if( !(skip&skip_witness_signature) )
      FC_ASSERT( next_block.validate_signee( witness.signing_key ) );

   if( !(skip&skip_witness_schedule_check) )
   {
      uint32_t slot_num = get_slot_at_time( next_block.timestamp );
      FC_ASSERT( slot_num > 0 );

      string scheduled_witness = get_scheduled_witness( slot_num );

      FC_ASSERT( witness.owner == scheduled_witness, "Witness produced block at wrong time",
                 ("block witness",next_block.witness)("scheduled",scheduled_witness)("slot_num",slot_num) );
   }

   return witness;
} FC_CAPTURE_AND_RETHROW() }

void database::create_block_summary(const signed_block& next_block)
{ try {
   block_summary_id_type sid( next_block.block_num() & 0xffff );
   modify( get< block_summary_object >( sid ), [&](block_summary_object& p) {
         p.block_id = next_block.id();
   });
} FC_CAPTURE_AND_RETHROW() }

void database::update_global_dynamic_data( const signed_block& b )
{ try {
   const dynamic_global_property_object& _dgp =
      get_dynamic_global_properties();

   uint32_t missed_blocks = 0;
   if( head_block_time() != fc::time_point_sec() )
   {
      missed_blocks = get_slot_at_time( b.timestamp );
      assert( missed_blocks != 0 );
      missed_blocks--;
      for( uint32_t i = 0; i < missed_blocks; ++i )
      {
         const auto& witness_missed = get_witness( get_scheduled_witness( i + 1 ) );
         if(  witness_missed.owner != b.witness )
         {
            modify( witness_missed, [&]( witness_object& w )
            {
               w.total_missed++;
            //    if( has_hardfork( CONTENTO_HARDFORK_0_14__278 ) )
            //    {
                  if( head_block_num() - w.last_confirmed_block_num  > CONTENTO_BLOCKS_PER_DAY )
                  {
                     w.signing_key = public_key_type();
                     push_virtual_operation( shutdown_witness_operation( w.owner ) );
                  }
            //    }
//               }
            } );
         }
      }
   }

   // dynamic global properties updating
   modify( _dgp, [&]( dynamic_global_property_object& dgp )
   {
      // This is constant time assuming 100% participation. It is O(B) otherwise (B = Num blocks between update)
      for( uint32_t i = 0; i < missed_blocks + 1; i++ )
      {
         dgp.participation_count -= dgp.recent_slots_filled.hi & 0x8000000000000000ULL ? 1 : 0;
         dgp.recent_slots_filled = ( dgp.recent_slots_filled << 1 ) + ( i == 0 ? 1 : 0 );
         dgp.participation_count += ( i == 0 ? 1 : 0 );
      }

      dgp.head_block_number = b.block_num();
      dgp.head_block_id = b.id();
      dgp.time = b.timestamp;
      dgp.current_aslot += missed_blocks+1;
   } );

   if( !(get_node_properties().skip_flags & skip_undo_history_check) )
   {
      CONTENTO_ASSERT( _dgp.head_block_number - _dgp.last_irreversible_block_num  < CONTENTO_MAX_UNDO_HISTORY, undo_database_exception,
                 "The database does not have enough undo history to support a blockchain with so many missed blocks. "
                 "Please add a checkpoint if you would like to continue applying blocks beyond this point.",
                 ("last_irreversible_block_num",_dgp.last_irreversible_block_num)("head", _dgp.head_block_number)
                 ("max_undo",CONTENTO_MAX_UNDO_HISTORY) );
   }
} FC_CAPTURE_AND_RETHROW() }

void database::update_virtual_supply()
    {
//    try {
//   modify( get_dynamic_global_properties(), [&]( dynamic_global_property_object& dgp )
//   {
//      dgp.virtual_supply = dgp.current_supply
//         + ( get_feed_history().current_median_history.is_null() ? asset( 0, COS_SYMBOL ) : dgp.current_sbd_supply * get_feed_history().current_median_history );
//
//      auto median_price = get_feed_history().current_median_history;
//
//      if( !median_price.is_null() && has_hardfork( CONTENTO_HARDFORK_0_14__230 ) )
//      {
//         auto percent_sbd = uint16_t( ( ( fc::uint128_t( ( dgp.current_sbd_supply * get_feed_history().current_median_history ).amount.value ) * CONTENTO_100_PERCENT )
//            / dgp.virtual_supply.amount.value ).to_uint64() );
//
//         if( percent_sbd <= CONTENTO_SBD_START_PERCENT )
//            dgp.sbd_print_rate = CONTENTO_100_PERCENT;
//         else if( percent_sbd >= CONTENTO_SBD_STOP_PERCENT )
//            dgp.sbd_print_rate = 0;
//         else
//            dgp.sbd_print_rate = ( ( CONTENTO_SBD_STOP_PERCENT - percent_sbd ) * CONTENTO_100_PERCENT ) / ( CONTENTO_SBD_STOP_PERCENT - CONTENTO_SBD_START_PERCENT );
//      }
//   });
//} FC_CAPTURE_AND_RETHROW()
    
}

void database::update_signing_witness(const witness_object& signing_witness, const signed_block& new_block)
{ try {
   const dynamic_global_property_object& dpo = get_dynamic_global_properties();
   uint64_t new_block_aslot = dpo.current_aslot + get_slot_at_time( new_block.timestamp );

   modify( signing_witness, [&]( witness_object& _wit )
   {
      _wit.last_aslot = new_block_aslot;
      _wit.last_confirmed_block_num = new_block.block_num();
   } );
} FC_CAPTURE_AND_RETHROW() }

void database::update_last_irreversible_block()
{ try {
   const dynamic_global_property_object& dpo = get_dynamic_global_properties();
    
   /**
    * Prior to voting taking over, we must be more conservative...
    *
    */
   if( head_block_num() < CONTENTO_START_MINER_VOTING_BLOCK )
   {
      modify( dpo, [&]( dynamic_global_property_object& _dpo )
      {
         if ( head_block_num() > CONTENTO_MAX_WITNESSES )
            _dpo.last_irreversible_block_num = head_block_num() - CONTENTO_MAX_WITNESSES;
      } );
   }
   else
   {
      const witness_schedule_object& wso = get_witness_schedule_object();

      vector< const witness_object* > wit_objs;
      wit_objs.reserve( wso.num_scheduled_witnesses );
      for( int i = 0; i < wso.num_scheduled_witnesses; i++ )
         wit_objs.push_back( &get_witness( wso.current_shuffled_witnesses[i] ) );

      static_assert( CONTENTO_IRREVERSIBLE_THRESHOLD > 0, "irreversible threshold must be nonzero" );

      // 1 1 1 2 2 2 2 2 2 2 -> 2     .7*10 = 7
      // 1 1 1 1 1 1 1 2 2 2 -> 1
      // 3 3 3 3 3 3 3 3 3 3 -> 3

      size_t offset = ((CONTENTO_100_PERCENT - CONTENTO_IRREVERSIBLE_THRESHOLD) * wit_objs.size() / CONTENTO_100_PERCENT);

      std::nth_element( wit_objs.begin(), wit_objs.begin() + offset, wit_objs.end(),
         []( const witness_object* a, const witness_object* b )
         {
            return a->last_confirmed_block_num < b->last_confirmed_block_num;
         } );

      uint32_t new_last_irreversible_block_num = wit_objs[offset]->last_confirmed_block_num;

      if( new_last_irreversible_block_num > dpo.last_irreversible_block_num )
      {
         modify( dpo, [&]( dynamic_global_property_object& _dpo )
         {
            _dpo.last_irreversible_block_num = new_last_irreversible_block_num;
         } );
      }
   }

   commit( dpo.last_irreversible_block_num );

   if( !( get_node_properties().skip_flags & skip_block_log ) )
   {
      // output to block log based on new last irreverisible block num
      const auto& tmp_head = _block_log.head();
      uint64_t log_head_num = 0;

      if( tmp_head )
         log_head_num = tmp_head->block_num();

      if( log_head_num < dpo.last_irreversible_block_num )
      {
         while( log_head_num < dpo.last_irreversible_block_num )
         {
            shared_ptr< fork_item > block = _fork_db.fetch_block_on_main_branch_by_number( log_head_num+1 );
            FC_ASSERT( block, "Current fork in the fork database does not contain the last_irreversible_block" );
            _block_log.append( block->data );
            log_head_num++;
         }

         _block_log.flush();
      }
   }

   _fork_db.set_max_size( dpo.head_block_number - dpo.last_irreversible_block_num + 1 );

} FC_CAPTURE_AND_RETHROW() }


void database::clear_expired_delegations()
{
   auto now = head_block_time();
   const auto& delegations_by_exp = get_index< vesting_delegation_expiration_index, by_expiration >();
   auto itr = delegations_by_exp.begin();
   while( itr != delegations_by_exp.end() && itr->expiration < now )
   {
      modify( get_account( itr->delegator ), [&]( account_object& a )
      {
         a.delegated_vesting_shares -= itr->vesting_shares;
      });

      push_virtual_operation( return_vesting_delegation_operation( itr->delegator, itr->vesting_shares ) );

      remove( *itr );
      itr = delegations_by_exp.begin();
   }
}

void database::adjust_balance( const account_object& a, const asset& delta )
{
    FC_ASSERT( delta.symbol == COS_SYMBOL, "invalid symbol" );
    const auto& cprops = get_dynamic_global_properties();
    modify( a, [&]( account_object& acnt ){
        acnt.balance += delta;
    });
    modify(cprops, [&](dynamic_global_property_object& gpo){
        gpo.total_cos += delta;
    });
}

void database::adjust_contract_balance( const contract_balance_object& a, const asset& delta )
{
    modify( a, [&]( contract_balance_object& cbo )
           {
               switch( delta.symbol )
               {
                   case COS_SYMBOL:
                       cbo.cos_balance += delta;
                       break;
                   default:
                       FC_ASSERT( false, "invalid symbol" );
               }
           } );
}

void database::adjust_savings_balance( const account_object& a, const asset& delta )
{
   modify( a, [&]( account_object& acnt )
   {
      switch( delta.symbol )
      {
         case COS_SYMBOL:
            acnt.savings_balance += delta;
            break;
         default:
            FC_ASSERT( !"invalid symbol" );
      }
   } );
}


void database::adjust_reward_balance( const account_object& a, const asset& delta )
{
   modify( a, [&]( account_object& acnt )
   {
      switch( delta.symbol )
      {
         case COS_SYMBOL:
            acnt.reward_steem_balance += delta;
            break;
         default:
            FC_ASSERT( false, "invalid symbol" );
      }
   });
}


void database::adjust_supply( const asset& delta, bool adjust_vesting )
{

   const auto& props = get_dynamic_global_properties();
   if( props.head_block_number < CONTENTO_BLOCKS_PER_DAY*7 )
      adjust_vesting = false;

   modify( props, [&]( dynamic_global_property_object& props )
   {
      switch( delta.symbol )
      {
         case COS_SYMBOL:
         {
            asset new_cos( delta.amount, COS_SYMBOL );
            props.current_supply += delta + new_cos;
            props.total_cos += new_cos;
            assert( props.current_supply.amount.value >= 0 );
            break;
         }
         default:
            FC_ASSERT( false, "invalid symbol" );
      }
   } );
}


asset database::get_balance( const account_object& a, asset_symbol_type symbol )const
{
   switch( symbol )
   {
      case COS_SYMBOL:
         return a.balance;
      default:
         FC_ASSERT( false, "invalid symbol" );
   }
}

asset database::get_savings_balance( const account_object& a, asset_symbol_type symbol )const
{
   switch( symbol )
   {
      case COS_SYMBOL:
         return a.savings_balance;
      default:
         FC_ASSERT( !"invalid symbol" );
   }
}

void database::init_hardforks()
{
   _hardfork_times[ 0 ] = fc::time_point_sec( CONTENTO_GENESIS_TIME );
   _hardfork_versions[ 0 ] = hardfork_version( 0, 0 );
//    FC_ASSERT( CONTENTO_HARDFORK_0_1 == 1, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_1 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_1_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_1 ] = CONTENTO_HARDFORK_0_1_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_2 == 2, "Invlaid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_2 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_2_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_2 ] = CONTENTO_HARDFORK_0_2_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_3 == 3, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_3 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_3_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_3 ] = CONTENTO_HARDFORK_0_3_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_4 == 4, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_4 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_4_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_4 ] = CONTENTO_HARDFORK_0_4_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_5 == 5, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_5 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_5_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_5 ] = CONTENTO_HARDFORK_0_5_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_6 == 6, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_6 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_6_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_6 ] = CONTENTO_HARDFORK_0_6_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_7 == 7, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_7 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_7_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_7 ] = CONTENTO_HARDFORK_0_7_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_8 == 8, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_8 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_8_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_8 ] = CONTENTO_HARDFORK_0_8_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_9 == 9, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_9 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_9_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_9 ] = CONTENTO_HARDFORK_0_9_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_10 == 10, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_10 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_10_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_10 ] = CONTENTO_HARDFORK_0_10_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_11 == 11, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_11 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_11_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_11 ] = CONTENTO_HARDFORK_0_11_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_12 == 12, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_12 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_12_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_12 ] = CONTENTO_HARDFORK_0_12_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_13 == 13, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_13 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_13_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_13 ] = CONTENTO_HARDFORK_0_13_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_14 == 14, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_14 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_14_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_14 ] = CONTENTO_HARDFORK_0_14_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_15 == 15, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_15 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_15_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_15 ] = CONTENTO_HARDFORK_0_15_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_16 == 16, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_16 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_16_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_16 ] = CONTENTO_HARDFORK_0_16_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_17 == 17, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_17 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_17_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_17 ] = CONTENTO_HARDFORK_0_17_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_18 == 18, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_18 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_18_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_18 ] = CONTENTO_HARDFORK_0_18_VERSION;
//    FC_ASSERT( CONTENTO_HARDFORK_0_19 == 19, "Invalid hardfork configuration" );
//    _hardfork_times[ CONTENTO_HARDFORK_0_19 ] = fc::time_point_sec( CONTENTO_HARDFORK_0_19_TIME );
//    _hardfork_versions[ CONTENTO_HARDFORK_0_19 ] = CONTENTO_HARDFORK_0_19_VERSION;


   const auto& hardforks = get_hardfork_property_object();
   FC_ASSERT( hardforks.last_hardfork <= CONTENTO_NUM_HARDFORKS, "Chain knows of more hardforks than configuration", ("hardforks.last_hardfork",hardforks.last_hardfork)("CONTENTO_NUM_HARDFORKS",CONTENTO_NUM_HARDFORKS) );
   FC_ASSERT( _hardfork_versions[ hardforks.last_hardfork ] <= CONTENTO_BLOCKCHAIN_VERSION, "Blockchain version is older than last applied hardfork" );
   FC_ASSERT( CONTENTO_BLOCKCHAIN_HARDFORK_VERSION == _hardfork_versions[ CONTENTO_NUM_HARDFORKS ] );
}

void database::process_hardforks()
{
   try
   {
      // If there are upcoming hardforks and the next one is later, do nothing
      const auto& hardforks = get_hardfork_property_object();

    //   if( has_hardfork( CONTENTO_HARDFORK_0_5__54 ) )
    //   {
         while( _hardfork_versions[ hardforks.last_hardfork ] < hardforks.next_hardfork
            && hardforks.next_hardfork_time <= head_block_time() )
         {
            if( hardforks.last_hardfork < CONTENTO_NUM_HARDFORKS ) {
               apply_hardfork( hardforks.last_hardfork + 1 );
            }
            else
               throw unknown_hardfork_exception();
         }
    //   }
    //   else
    //   {
    //      while( hardforks.last_hardfork < CONTENTO_NUM_HARDFORKS
    //            && _hardfork_times[ hardforks.last_hardfork + 1 ] <= head_block_time()
    //            && hardforks.last_hardfork < CONTENTO_HARDFORK_0_5__54 )
    //      {
    //         apply_hardfork( hardforks.last_hardfork + 1 );
    //      }
    //   }
   }
   FC_CAPTURE_AND_RETHROW()
}

bool database::has_hardfork( uint32_t hardfork )const
{
   return get_hardfork_property_object().processed_hardforks.size() > hardfork;
}

void database::set_hardfork( uint32_t hardfork, bool apply_now )
{
   auto const& hardforks = get_hardfork_property_object();

   for( uint32_t i = hardforks.last_hardfork + 1; i <= hardfork && i <= CONTENTO_NUM_HARDFORKS; i++ )
   {
    //   if( i <= CONTENTO_HARDFORK_0_5__54 )
    //      _hardfork_times[i] = head_block_time();
    //   else
    //   {
    //      modify( hardforks, [&]( hardfork_property_object& hpo )
    //      {
    //         hpo.next_hardfork = _hardfork_versions[i];
    //         hpo.next_hardfork_time = head_block_time();
    //      } );
    //   }

    //   if( apply_now )
    //      apply_hardfork( i );
   }
}

void database::apply_hardfork( uint32_t hardfork )
{
   if( _log_hardforks )
      elog( "HARDFORK ${hf} at block ${b}", ("hf", hardfork)("b", head_block_num()) );

   switch( hardfork )
   {
//       case CONTENTO_HARDFORK_0_1:
//          // perform_vesting_share_split( 1000000 );
// #ifdef IS_TEST_NET
//          {
//             custom_operation test_op;
//             string op_msg = "Testnet: Hardfork applied";
//             test_op.data = vector< char >( op_msg.begin(), op_msg.end() );
//             test_op.required_auths.insert( CONTENTO_INIT_MINER_NAME );
//             operation op = test_op;   // we need the operation object to live to the end of this scope
//             operation_notification note( op );
//             notify_pre_apply_operation( note );
//             notify_post_apply_operation( note );
//          }
//          break;
// #endif
//          break;
//       case CONTENTO_HARDFORK_0_2:
//          retally_witness_votes();
//          break;
//       case CONTENTO_HARDFORK_0_3:
//          retally_witness_votes();
//          break;
//       case CONTENTO_HARDFORK_0_4:
//          reset_virtual_schedule_time(*this);
//          break;
//       case CONTENTO_HARDFORK_0_5:
//          break;
//       case CONTENTO_HARDFORK_0_6:
//          retally_witness_vote_counts();
//          retally_comment_children();
//          break;
//       case CONTENTO_HARDFORK_0_7:
//          break;
//       case CONTENTO_HARDFORK_0_8:
//          retally_witness_vote_counts(true);
//          break;
//       case CONTENTO_HARDFORK_0_9:
// //         {
// //            for( const std::string& acc : hardfork9::get_compromised_accounts() )
// //            {
// //               const account_object* account = find_account( acc );
// //               if( account == nullptr )
// //                  continue;
// //
// //               update_owner_authority( *account, authority( 1, public_key_type( "STM7sw22HqsXbz7D2CmJfmMwt9rimtk518dRzsR1f8Cgw52dQR1pR" ), 1 ) );
// //
// //               modify( get< account_authority_object, by_account >( account->name ), [&]( account_authority_object& auth )
// //               {
// //                  auth.active  = authority( 1, public_key_type( "STM7sw22HqsXbz7D2CmJfmMwt9rimtk518dRzsR1f8Cgw52dQR1pR" ), 1 );
// //                  auth.posting = authority( 1, public_key_type( "STM7sw22HqsXbz7D2CmJfmMwt9rimtk518dRzsR1f8Cgw52dQR1pR" ), 1 );
// //               });
// //            }
// //         }
//          break;
//       case CONTENTO_HARDFORK_0_10:
//          retally_liquidity_weight();
//          break;
//       case CONTENTO_HARDFORK_0_11:
//          break;
//       case CONTENTO_HARDFORK_0_12:
// //         {
// //            const auto& comment_idx = get_index< comment_index >().indices();
// //
// //            for( auto itr = comment_idx.begin(); itr != comment_idx.end(); ++itr )
// //            {
// //               // At the hardfork time, all new posts with no votes get their cashout time set to +12 hrs from head block time.
// //               // All posts with a payout get their cashout time set to +30 days. This hardfork takes place within 30 days
// //               // initial payout so we don't have to handle the case of posts that should be frozen that aren't
// //               if( itr->parent_author == CONTENTO_ROOT_POST_PARENT )
// //               {
// //                  // Post has not been paid out and has no votes (cashout_time == 0 === net_rshares == 0, under current semmantics)
// //                  if( itr->last_payout == fc::time_point_sec::min() && itr->cashout_time == fc::time_point_sec::maximum() )
// //                  {
// //                     modify( *itr, [&]( comment_object & c )
// //                     {
// //                        c.cashout_time = head_block_time() + CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF17;
// //                     });
// //                  }
// //                  // Has been paid out, needs to be on second cashout window
// //                  else if( itr->last_payout > fc::time_point_sec() )
// //                  {
// //                     modify( *itr, [&]( comment_object& c )
// //                     {
// //                        c.cashout_time = c.last_payout + CONTENTO_SECOND_CASHOUT_WINDOW;
// //                     });
// //                  }
// //               }
// //            }
// //
// //            modify( get< account_authority_object, by_account >( CONTENTO_MINER_ACCOUNT ), [&]( account_authority_object& auth )
// //            {
// //               auth.posting = authority();
// //               auth.posting.weight_threshold = 1;
// //            });
// //
// //            modify( get< account_authority_object, by_account >( CONTENTO_NULL_ACCOUNT ), [&]( account_authority_object& auth )
// //            {
// //               auth.posting = authority();
// //               auth.posting.weight_threshold = 1;
// //            });
// //
// //            modify( get< account_authority_object, by_account >( CONTENTO_TEMP_ACCOUNT ), [&]( account_authority_object& auth )
// //            {
// //               auth.posting = authority();
// //               auth.posting.weight_threshold = 1;
// //            });
// //         }
//          break;
//       case CONTENTO_HARDFORK_0_13:
//          break;
//       case CONTENTO_HARDFORK_0_14:
//          break;
//       case CONTENTO_HARDFORK_0_15:
//          break;
//       case CONTENTO_HARDFORK_0_16:
// //         {
// //            modify( get_feed_history(), [&]( feed_history_object& fho )
// //            {
// //               while( fho.price_history.size() > CONTENTO_FEED_HISTORY_WINDOW )
// //                  fho.price_history.pop_front();
// //            });
// //         }
//          break;
//       case CONTENTO_HARDFORK_0_17:
// //         {
// //            static_assert(
// //               CONTENTO_MAX_VOTED_WITNESSES_HF0 + CONTENTO_MAX_MINER_WITNESSES_HF0 + CONTENTO_MAX_RUNNER_WITNESSES_HF0 == CONTENTO_MAX_WITNESSES,
// //               "HF0 witness counts must add up to CONTENTO_MAX_WITNESSES" );
// //            static_assert(
// //               CONTENTO_MAX_VOTED_WITNESSES_HF17 + CONTENTO_MAX_MINER_WITNESSES_HF17 + CONTENTO_MAX_RUNNER_WITNESSES_HF17 == CONTENTO_MAX_WITNESSES,
// //               "HF17 witness counts must add up to CONTENTO_MAX_WITNESSES" );
// //
// //            modify( get_witness_schedule_object(), [&]( witness_schedule_object& wso )
// //            {
// //               wso.max_voted_witnesses = CONTENTO_MAX_VOTED_WITNESSES_HF17;
// //               wso.max_miner_witnesses = CONTENTO_MAX_MINER_WITNESSES_HF17;
// //               wso.max_runner_witnesses = CONTENTO_MAX_RUNNER_WITNESSES_HF17;
// //            });
// //
// //            const auto& gpo = get_dynamic_global_properties();
// //
// //            auto post_rf = create< reward_fund_object >( [&]( reward_fund_object& rfo )
// //            {
// //               rfo.name = CONTENTO_POST_REWARD_FUND_NAME;
// //               rfo.last_update = head_block_time();
// //               rfo.content_constant = CONTENTO_CONTENT_CONSTANT_HF0;
// //               rfo.percent_curation_rewards = CONTENTO_1_PERCENT * 25;
// //               rfo.percent_content_rewards = CONTENTO_100_PERCENT;
// //               rfo.reward_balance = gpo.total_reward_fund_steem;
// //#ifndef IS_TEST_NET
// //               rfo.recent_claims = CONTENTO_HF_17_RECENT_CLAIMS;
// //#endif
// //               rfo.author_reward_curve = curve_id::quadratic;
// //               rfo.curation_reward_curve = curve_id::quadratic_curation;
// //            });
// //
// //            // As a shortcut in payout processing, we use the id as an array index.
// //            // The IDs must be assigned this way. The assertion is a dummy check to ensure this happens.
// //            FC_ASSERT( post_rf.id._id == 0 );
// //
// //            modify( gpo, [&]( dynamic_global_property_object& g )
// //            {
// //               g.total_reward_fund_steem = asset( 0, COS_SYMBOL );
// //               g.total_reward_shares2 = 0;
// //            });
// //
// //            /*
// //            * For all current comments we will either keep their current cashout time, or extend it to 1 week
// //            * after creation.
// //            *
// //            * We cannot do a simple iteration by cashout time because we are editting cashout time.
// //            * More specifically, we will be adding an explicit cashout time to all comments with parents.
// //            * To find all discussions that have not been paid out we fir iterate over posts by cashout time.
// //            * Before the hardfork these are all root posts. Iterate over all of their children, adding each
// //            * to a specific list. Next, update payout times for all discussions on the root post. This defines
// //            * the min cashout time for each child in the discussion. Then iterate over the children and set
// //            * their cashout time in a similar way, grabbing the root post as their inherent cashout time.
// //            */
// //            const auto& comment_idx = get_index< comment_index, by_cashout_time >();
// //            const auto& by_root_idx = get_index< comment_index, by_root >();
// //            vector< const comment_object* > root_posts;
// //            root_posts.reserve( CONTENTO_HF_17_NUM_POSTS );
// //            vector< const comment_object* > replies;
// //            replies.reserve( CONTENTO_HF_17_NUM_REPLIES );
// //
// //            for( auto itr = comment_idx.begin(); itr != comment_idx.end() && itr->cashout_time < fc::time_point_sec::maximum(); ++itr )
// //            {
// //               root_posts.push_back( &(*itr) );
// //
// //               for( auto reply_itr = by_root_idx.lower_bound( itr->id ); reply_itr != by_root_idx.end() && reply_itr->root_comment == itr->id; ++reply_itr )
// //               {
// //                  replies.push_back( &(*reply_itr) );
// //               }
// //            }
// //
// //            for( auto itr : root_posts )
// //            {
// //               modify( *itr, [&]( comment_object& c )
// //               {
// //                  c.cashout_time = std::max( c.created + CONTENTO_CASHOUT_WINDOW_SECONDS, c.cashout_time );
// //               });
// //            }
// //
// //            for( auto itr : replies )
// //            {
// //               modify( *itr, [&]( comment_object& c )
// //               {
// //                  c.cashout_time = std::max( calculate_discussion_payout_time( c ), c.created + CONTENTO_CASHOUT_WINDOW_SECONDS );
// //               });
// //            }
// //         }
//          break;
//       case CONTENTO_HARDFORK_0_18:
//          break;
//       case CONTENTO_HARDFORK_0_19:
// //         {
// //            modify( get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
// //            {
// //               gpo.vote_power_reserve_rate = 10;
// //            });
// //
// //            modify( get< reward_fund_object, by_name >( CONTENTO_POST_REWARD_FUND_NAME ), [&]( reward_fund_object &rfo )
// //            {
// //#ifndef IS_TEST_NET
// //               rfo.recent_claims = CONTENTO_HF_19_RECENT_CLAIMS;
// //#endif
// //               rfo.author_reward_curve = curve_id::linear;
// //               rfo.curation_reward_curve = curve_id::square_root;
// //            });
// //
// //            /* Remove all 0 delegation objects */
// //            vector< const vesting_delegation_object* > to_remove;
// //            const auto& delegation_idx = get_index< vesting_delegation_index, by_id >();
// //            auto delegation_itr = delegation_idx.begin();
// //
// //            while( delegation_itr != delegation_idx.end() )
// //            {
// //               if( delegation_itr->vesting_shares.amount == 0 )
// //                  to_remove.push_back( &(*delegation_itr) );
// //
// //               ++delegation_itr;
// //            }
// //
// //            for( const vesting_delegation_object* delegation_ptr: to_remove )
// //            {
// //               remove( *delegation_ptr );
// //            }
// //         }
//          break;
      default:
         break;
   }

   modify( get_hardfork_property_object(), [&]( hardfork_property_object& hfp )
   {
      FC_ASSERT( hardfork == hfp.last_hardfork + 1, "Hardfork being applied out of order", ("hardfork",hardfork)("hfp.last_hardfork",hfp.last_hardfork) );
      FC_ASSERT( hfp.processed_hardforks.size() == hardfork, "Hardfork being applied out of order" );
      hfp.processed_hardforks.push_back( _hardfork_times[ hardfork ] );
      hfp.last_hardfork = hardfork;
      hfp.current_hardfork_version = _hardfork_versions[ hardfork ];
      FC_ASSERT( hfp.processed_hardforks[ hfp.last_hardfork ] == _hardfork_times[ hfp.last_hardfork ], "Hardfork processing failed sanity check..." );
   } );

   push_virtual_operation( hardfork_operation( hardfork ), true );
}

void database::retally_liquidity_weight() {
   const auto& ridx = get_index< liquidity_reward_balance_index >().indices().get< by_owner >();
   for( const auto& i : ridx ) {
      modify( i, []( liquidity_reward_balance_object& o ){
         o.update_weight(true/*HAS HARDFORK10 if this method is called*/);
      });
   }
}

/**
 * Verifies all supply invariantes check out
 */
void database::validate_invariants()const
{
   try
   {
      const auto& account_idx = get_index<account_index>().indices().get<by_name>();
      asset total_cos = asset( 0, COS_SYMBOL );
      asset total_vesting = asset( 0, VESTS_SYMBOL );
      auto gpo = get_dynamic_global_properties();
      auto grpo = get_dynamic_global_reward_properties();

      /// verify no witness has too many votes
      const auto& witness_idx = get_index< witness_index >().indices();
      for( auto itr = witness_idx.begin(); itr != witness_idx.end(); ++itr )
         FC_ASSERT( itr->votes <= gpo.total_vesting_shares.amount, "", ("itr",*itr) );

      for( auto itr = account_idx.begin(); itr != account_idx.end(); ++itr )
      {
         total_cos += itr->balance;
         total_vesting += itr->vesting_shares;
      }


    auto  account_cos = total_cos;
    total_cos += grpo.subject_reward_balance + grpo.comment_reward_balance + grpo.other_reward_balance;
    FC_ASSERT(gpo.total_vesting_shares == total_vesting , "",
              ("gpo.total_vesting_shares", gpo.total_vesting_shares)
              ("total_vesting", total_vesting));
    FC_ASSERT(gpo.total_cos == account_cos , "",
             ("gpo.total_cos", gpo.total_cos)
             ("account_cos", account_cos));
    FC_ASSERT(gpo.current_supply == total_cos + total_vesting * gpo.get_vesting_share_price(), "",
              ("gpo.current_supply", gpo.current_supply)
              ("gpo.total_vesting_shares", gpo.total_vesting_shares)
              ("total_vesting", total_vesting)
              ("gpo.total_cos", gpo.total_cos)
              ("total_cos", total_cos ));
   }
   FC_CAPTURE_LOG_AND_RETHROW( (head_block_num()) );
}

void database::perform_vesting_share_split( uint32_t magnitude )
{
   try
   {
      modify( get_dynamic_global_properties(), [&]( dynamic_global_property_object& d )
      {
         d.total_vesting_shares.amount *= magnitude;
         d.total_reward_shares2 = 0;
      } );

      // Need to update all VESTS in accounts and the total VESTS in the dgpo
      for( const auto& account : get_index<account_index>().indices() )
      {
         modify( account, [&]( account_object& a )
         {
            a.vesting_shares.amount *= magnitude;
            a.withdrawn             *= magnitude;
            a.to_withdraw           *= magnitude;
            a.vesting_withdraw_rate  = asset( a.to_withdraw / CONTENTO_VESTING_WITHDRAW_INTERVALS_PRE_HF_16, VESTS_SYMBOL );
            if( a.vesting_withdraw_rate.amount == 0 )
               a.vesting_withdraw_rate.amount = 1;

            for( uint32_t i = 0; i < CONTENTO_MAX_PROXY_RECURSION_DEPTH; ++i )
               a.proxied_vsf_votes[i] *= magnitude;
         } );
      }

      const auto& comments = get_index< comment_index >().indices();
      for( const auto& comment : comments )
      {
         modify( comment, [&]( comment_object& c )
         {
            c.net_rshares       *= magnitude;
            c.abs_rshares       *= magnitude;
            c.vote_rshares      *= magnitude;
         } );
      }

      for( const auto& c : comments )
      {
         if( c.net_rshares.value > 0 )
            adjust_rshares2( c, 0, util::evaluate_reward_curve( c.net_rshares.value ) );
      }

   }
   FC_CAPTURE_AND_RETHROW()
}

void database::retally_comment_children()
{
   const auto& cidx = get_index< comment_index >().indices();

   // Clear children counts
   for( auto itr = cidx.begin(); itr != cidx.end(); ++itr )
   {
      modify( *itr, [&]( comment_object& c )
      {
         c.children = 0;
      });
   }

   for( auto itr = cidx.begin(); itr != cidx.end(); ++itr )
   {
      if( itr->parent_author != CONTENTO_ROOT_POST_PARENT )
      {
// Low memory nodes only need immediate child count, full nodes track total children
#ifdef IS_LOW_MEM
         modify( get_comment( itr->parent_author, itr->parent_permlink ), [&]( comment_object& c )
         {
            c.children++;
         });
#else
         const comment_object* parent = &get_comment( itr->parent_author, itr->parent_permlink );
         while( parent )
         {
            modify( *parent, [&]( comment_object& c )
            {
               c.children++;
            });

            if( parent->parent_author != CONTENTO_ROOT_POST_PARENT )
               parent = &get_comment( parent->parent_author, parent->parent_permlink );
            else
               parent = nullptr;
         }
#endif
      }
   }
}

void database::retally_witness_votes()
{
   const auto& witness_idx = get_index< witness_index >().indices();

   // Clear all witness votes
   for( auto itr = witness_idx.begin(); itr != witness_idx.end(); ++itr )
   {
      modify( *itr, [&]( witness_object& w )
      {
         w.votes = 0;
         w.virtual_position = 0;
      } );
   }

   const auto& account_idx = get_index< account_index >().indices();

   // Apply all existing votes by account
   for( auto itr = account_idx.begin(); itr != account_idx.end(); ++itr )
   {
      if( itr->proxy != CONTENTO_PROXY_TO_SELF_ACCOUNT ) continue;

      const auto& a = *itr;

      const auto& vidx = get_index<witness_vote_index>().indices().get<by_account_witness>();
      auto wit_itr = vidx.lower_bound( boost::make_tuple( a.id, witness_id_type() ) );
      while( wit_itr != vidx.end() && wit_itr->account == a.id )
      {
         adjust_witness_vote( get(wit_itr->witness), a.witness_vote_weight() );
         ++wit_itr;
      }
   }
}

void database::retally_witness_vote_counts( bool force )
{
   const auto& account_idx = get_index< account_index >().indices();

   // Check all existing votes by account
   for( auto itr = account_idx.begin(); itr != account_idx.end(); ++itr )
   {
      const auto& a = *itr;
      uint16_t witnesses_voted_for = 0;
      if( force || (a.proxy != CONTENTO_PROXY_TO_SELF_ACCOUNT  ) )
      {
        const auto& vidx = get_index< witness_vote_index >().indices().get< by_account_witness >();
        auto wit_itr = vidx.lower_bound( boost::make_tuple( a.id, witness_id_type() ) );
        while( wit_itr != vidx.end() && wit_itr->account == a.id )
        {
           ++witnesses_voted_for;
           ++wit_itr;
        }
      }
      if( a.witnesses_voted_for != witnesses_voted_for )
      {
         modify( a, [&]( account_object& account )
         {
            account.witnesses_voted_for = witnesses_voted_for;
         } );
      }
   }
}


uint32_t database::process_checkpoints( const signed_block& next_block, uint32_t skip_old ) {
      auto block_num = next_block.block_num();
      auto itr = _checkpoints.find( block_num );
      if( itr != _checkpoints.end() )
         FC_ASSERT( next_block.id() == itr->second, "Block did not match checkpoint", ("checkpoint",*itr)("block_id",next_block.id()) );
      uint32_t skip = skip_old;

      if( _checkpoints.rbegin()->first >= block_num )
         skip = skip_witness_signature
              | skip_transaction_signatures
              | skip_transaction_dupe_check
              | skip_fork_db
              | skip_block_size_check
              | skip_tapos_check
              | skip_authority_check
              /* | skip_merkle_check While blockchain is being downloaded, txs need to be validated against block headers */
              | skip_undo_history_check
              | skip_witness_schedule_check
              | skip_validate
              | skip_validate_invariants
              ;
       return skip;
}

// just for link error
/*
asset database::to_sbd( const asset& steem )const
{
    return asset(0);
}

// just for link error
asset database::to_steem( const asset& sbd )const
{
    return asset(0);
}
*/
    
    uint32_t database::tps() {
        return get_dynamic_global_properties().tps;
    }

} } //contento::chain
