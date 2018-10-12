#include <graphene/utilities/git_revision.hpp>
#include <graphene/utilities/key_conversion.hpp>
#include <graphene/utilities/words.hpp>

#include <contento/app/api.hpp>
//#include <contento/app/contract_storage.hpp>
#include <contento/chain/abi_serializer.hpp>
#include <contento/chain/config.hpp>
#include <contento/protocol/base.hpp>
#include <contento/protocol/types.hpp>
#include <contento/protocol/config.hpp>
#include <contento/follow/follow_operations.hpp>
#include <contento/private_message/private_message_operations.hpp>
#include <contento/wallet/wallet.hpp>
#include <contento/wallet/api_documentation.hpp>
#include <contento/wallet/reflect_util.hpp>

#include <contento/account_by_key/account_by_key_api.hpp>

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <list>
#include <regex>

#include <boost/version.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm/sort.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include <fc/container/deque.hpp>
#include <fc/git_revision.hpp>
#include <fc/io/fstream.hpp>
#include <fc/io/json.hpp>
#include <fc/io/stdio.hpp>
#include <fc/network/http/websocket.hpp>
#include <fc/rpc/cli.hpp>
#include <fc/rpc/websocket_api.hpp>
#include <fc/crypto/aes.hpp>
#include <fc/crypto/hex.hpp>
#include <fc/thread/mutex.hpp>
#include <fc/thread/scoped_lock.hpp>
#include <fc/smart_ref_impl.hpp>

#include <contento/chain/wast_to_wasm.hpp>
#include <contento/chain/contract_types.hpp>
#include <contento/chain/exceptions.hpp>

#include <contento/gas_estimate/contento_gas_estimate.hpp>

#include <fc/compress/zlib.hpp>

#ifndef WIN32
# include <sys/types.h>
# include <sys/stat.h>
#endif

#define BRAIN_KEY_WORD_COUNT 16

namespace contento { namespace wallet {

namespace detail {

template<class T>
optional<T> maybe_id( const string& name_or_id )
{
   if( std::isdigit( name_or_id.front() ) )
   {
      try
      {
         return fc::variant(name_or_id).as<T>();
      }
      catch (const fc::exception&)
      {
      }
   }
   return optional<T>();
}

string pubkey_to_shorthash( const public_key_type& key )
{
   uint32_t x = fc::sha256::hash(key)._hash[0];
   static const char hd[] = "0123456789abcdef";
   string result;

   result += hd[(x >> 0x1c) & 0x0f];
   result += hd[(x >> 0x18) & 0x0f];
   result += hd[(x >> 0x14) & 0x0f];
   result += hd[(x >> 0x10) & 0x0f];
   result += hd[(x >> 0x0c) & 0x0f];
   result += hd[(x >> 0x08) & 0x0f];
   result += hd[(x >> 0x04) & 0x0f];
   result += hd[(x        ) & 0x0f];

   return result;
}


fc::ecc::private_key derive_private_key( const std::string& prefix_string,
                                         int sequence_number )
{
   std::string sequence_string = std::to_string(sequence_number);
   fc::sha512 h = fc::sha512::hash(prefix_string + " " + sequence_string);
   fc::ecc::private_key derived_key = fc::ecc::private_key::regenerate(fc::sha256::hash(h));
   return derived_key;
}

string normalize_brain_key( string s )
{
   size_t i = 0, n = s.length();
   std::string result;
   char c;
   result.reserve( n );

   bool preceded_by_whitespace = false;
   bool non_empty = false;
   while( i < n )
   {
      c = s[i++];
      switch( c )
      {
      case ' ':  case '\t': case '\r': case '\n': case '\v': case '\f':
         preceded_by_whitespace = true;
         continue;

      case 'a': c = 'A'; break;
      case 'b': c = 'B'; break;
      case 'c': c = 'C'; break;
      case 'd': c = 'D'; break;
      case 'e': c = 'E'; break;
      case 'f': c = 'F'; break;
      case 'g': c = 'G'; break;
      case 'h': c = 'H'; break;
      case 'i': c = 'I'; break;
      case 'j': c = 'J'; break;
      case 'k': c = 'K'; break;
      case 'l': c = 'L'; break;
      case 'm': c = 'M'; break;
      case 'n': c = 'N'; break;
      case 'o': c = 'O'; break;
      case 'p': c = 'P'; break;
      case 'q': c = 'Q'; break;
      case 'r': c = 'R'; break;
      case 's': c = 'S'; break;
      case 't': c = 'T'; break;
      case 'u': c = 'U'; break;
      case 'v': c = 'V'; break;
      case 'w': c = 'W'; break;
      case 'x': c = 'X'; break;
      case 'y': c = 'Y'; break;
      case 'z': c = 'Z'; break;

      default:
         break;
      }
      if( preceded_by_whitespace && non_empty )
         result.push_back(' ');
      result.push_back(c);
      preceded_by_whitespace = false;
      non_empty = true;
   }
   return result;
}

struct op_prototype_visitor
{
   typedef void result_type;

   int t = 0;
   flat_map< std::string, operation >& name2op;

   op_prototype_visitor(
      int _t,
      flat_map< std::string, operation >& _prototype_ops
      ):t(_t), name2op(_prototype_ops) {}

   template<typename Type>
   result_type operator()( const Type& op )const
   {
      string name = fc::get_typename<Type>::name();
      size_t p = name.rfind(':');
      if( p != string::npos )
         name = name.substr( p+1 );
      name2op[ name ] = Type();
   }
};

class wallet_api_impl
{
   public:
      api_documentation method_documentation;
   private:
      void enable_umask_protection() {
#ifdef __unix__
         _old_umask = umask( S_IRWXG | S_IRWXO );
#endif
      }

      void disable_umask_protection() {
#ifdef __unix__
         umask( _old_umask );
#endif
      }

      void init_prototype_ops()
      {
         operation op;
         for( int t=0; t<op.count(); t++ )
         {
            op.set_which( t );
            op.visit( op_prototype_visitor(t, _prototype_ops) );
         }
         return;
      }

public:
   wallet_api& self;
   wallet_api_impl( wallet_api& s, const wallet_data& initial_data, fc::api<login_api> rapi )
      : self( s ),
        _remote_api( rapi ),
        _remote_db( rapi->get_api_by_name("database_api")->as< database_api >() ),
        _remote_net_broadcast( rapi->get_api_by_name("network_broadcast_api")->as< network_broadcast_api >() )
   {
      init_prototype_ops();

      _wallet.ws_server = initial_data.ws_server;
      _wallet.ws_user = initial_data.ws_user;
      _wallet.ws_password = initial_data.ws_password;
   }
   virtual ~wallet_api_impl()
   {}

   void encrypt_keys()
   {
      if( !is_locked() )
      {
         plain_keys data;
         data.keys = _keys;
         data.checksum = _checksum;
         auto plain_txt = fc::raw::pack(data);
         _wallet.cipher_keys = fc::aes_encrypt( data.checksum, plain_txt );
      }
   }

   bool copy_wallet_file( string destination_filename )
   {
      fc::path src_path = get_wallet_filename();
      if( !fc::exists( src_path ) )
         return false;
      fc::path dest_path = destination_filename + _wallet_filename_extension;
      int suffix = 0;
      while( fc::exists(dest_path) )
      {
         ++suffix;
         dest_path = destination_filename + "-" + std::to_string( suffix ) + _wallet_filename_extension;
      }
      wlog( "backing up wallet ${src} to ${dest}",
            ("src", src_path)
            ("dest", dest_path) );

      fc::path dest_parent = fc::absolute(dest_path).parent_path();
      try
      {
         enable_umask_protection();
         if( !fc::exists( dest_parent ) )
            fc::create_directories( dest_parent );
         fc::copy( src_path, dest_path );
         disable_umask_protection();
      }
      catch(...)
      {
         disable_umask_protection();
         throw;
      }
      return true;
   }

   bool is_locked()const
   {
      return _checksum == fc::sha512();
   }

   variant info() const
   {
      auto dynamic_props = _remote_db->get_dynamic_global_properties();
      fc::mutable_variant_object result(fc::variant(dynamic_props).get_object());
      result["witness_majority_version"] = fc::string( _remote_db->get_witness_schedule().majority_version );
      result["hardfork_version"] = fc::string( _remote_db->get_hardfork_version() );
      result["head_block_num"] = dynamic_props.head_block_number;
      result["head_block_id"] = dynamic_props.head_block_id;
      result["head_block_age"] = fc::get_approximate_relative_time_string(dynamic_props.time,
                                                                          time_point_sec(time_point::now()),
                                                                          " old");
      result["participation"] = (100*dynamic_props.recent_slots_filled.popcount()) / 128.0;
      result["account_creation_fee"] = _remote_db->get_chain_properties().account_creation_fee;
      result["post_reward_fund"] = fc::variant(_remote_db->get_reward_fund( CONTENTO_POST_REWARD_FUND_NAME )).get_object();
      return result;
   }

   variant_object about() const
   {
      string client_version( graphene::utilities::git_revision_description );
      const size_t pos = client_version.find( '/' );
      if( pos != string::npos && client_version.size() > pos )
         client_version = client_version.substr( pos + 1 );

      fc::mutable_variant_object result;
      result["blockchain_version"]       = CONTENTO_BLOCKCHAIN_VERSION;
      result["client_version"]           = client_version;
      result["steem_revision"]           = graphene::utilities::git_revision_sha;
      result["steem_revision_age"]       = fc::get_approximate_relative_time_string( fc::time_point_sec( graphene::utilities::git_revision_unix_timestamp ) );
      result["fc_revision"]              = fc::git_revision_sha;
      result["fc_revision_age"]          = fc::get_approximate_relative_time_string( fc::time_point_sec( fc::git_revision_unix_timestamp ) );
      result["compile_date"]             = "compiled on " __DATE__ " at " __TIME__;
      result["boost_version"]            = boost::replace_all_copy(std::string(BOOST_LIB_VERSION), "_", ".");
      result["openssl_version"]          = OPENSSL_VERSION_TEXT;

      std::string bitness = boost::lexical_cast<std::string>(8 * sizeof(int*)) + "-bit";
#if defined(__APPLE__)
      std::string os = "osx";
#elif defined(__linux__)
      std::string os = "linux";
#elif defined(_MSC_VER)
      std::string os = "win32";
#else
      std::string os = "other";
#endif
      result["build"] = os + " " + bitness;

      try
      {
         auto v = _remote_api->get_version();
         result["server_blockchain_version"] = v.blockchain_version;
         result["server_steem_revision"] = v.steem_revision;
         result["server_fc_revision"] = v.fc_revision;
      }
      catch( fc::exception& )
      {
         result["server"] = "could not retrieve server version information";
      }

      return result;
   }

   account_api_obj get_account( string account_name ) const
   {
      auto accounts = _remote_db->get_accounts( { account_name } );
      FC_ASSERT( !accounts.empty(), "Unknown account" );
      return accounts.front();
   }

   account_code_api_obj get_account_code( string account_name ) const
   {
      auto account = _remote_db->get_account_code( account_name );
      return account;
   }

   table_rows_api_obj get_table_rows(string code, string scope, string table,
                              string lower_bound, string upper_bound, int limit,
                              string key_type, string index_pos, string encode_type) const 
   {
      return _remote_db->get_table_rows(code, scope, table, lower_bound, upper_bound, 
                                        limit, key_type, index_pos, encode_type);
   }

   string get_wallet_filename() const { return _wallet_filename; }

   optional<fc::ecc::private_key>  try_get_private_key(const public_key_type& id)const
   {
      auto it = _keys.find(id);
      if( it != _keys.end() )
         return wif_to_key( it->second );
      return optional<fc::ecc::private_key>();
   }

   fc::ecc::private_key              get_private_key(const public_key_type& id)const
   {
      auto has_key = try_get_private_key( id );
      FC_ASSERT( has_key );
      return *has_key;
   }


   fc::ecc::private_key get_private_key_for_account(const account_api_obj& account)const
   {
      vector<public_key_type> active_keys = account.active.get_keys();
      if (active_keys.size() != 1)
         FC_THROW("Expecting a simple authority with one active key");
      return get_private_key(active_keys.front());
   }

   // imports the private key into the wallet, and associate it in some way (?) with the
   // given account name.
   // @returns true if the key matches a current active/owner/memo key for the named
   //          account, false otherwise (but it is stored either way)
   bool import_key(string wif_key)
   {
      fc::optional<fc::ecc::private_key> optional_private_key = wif_to_key(wif_key);
      if (!optional_private_key)
         FC_THROW("Invalid private key");
      contento::chain::public_key_type wif_pub_key = optional_private_key->get_public_key();

      _keys[wif_pub_key] = wif_key;
      return true;
   }

   bool load_wallet_file(string wallet_filename = "")
   {
      // TODO:  Merge imported wallet with existing wallet,
      //        instead of replacing it
      if( wallet_filename == "" )
         wallet_filename = _wallet_filename;

      if( ! fc::exists( wallet_filename ) )
         return false;

      _wallet = fc::json::from_file( wallet_filename ).as< wallet_data >();

      return true;
   }

   void save_wallet_file(string wallet_filename = "")
   {
      //
      // Serialize in memory, then save to disk
      //
      // This approach lessens the risk of a partially written wallet
      // if exceptions are thrown in serialization
      //

      encrypt_keys();

      if( wallet_filename == "" )
         wallet_filename = _wallet_filename;

      wlog( "saving wallet to file ${fn}", ("fn", wallet_filename) );

      string data = fc::json::to_pretty_string( _wallet );
      try
      {
         enable_umask_protection();
         //
         // Parentheses on the following declaration fails to compile,
         // due to the Most Vexing Parse.  Thanks, C++
         //
         // http://en.wikipedia.org/wiki/Most_vexing_parse
         //
         fc::ofstream outfile{ fc::path( wallet_filename ) };
         outfile.write( data.c_str(), data.length() );
         outfile.flush();
         outfile.close();
         disable_umask_protection();
      }
      catch(...)
      {
         disable_umask_protection();
         throw;
      }
   }

   // This function generates derived keys starting with index 0 and keeps incrementing
   // the index until it finds a key that isn't registered in the block chain.  To be
   // safer, it continues checking for a few more keys to make sure there wasn't a short gap
   // caused by a failed registration or the like.
   int find_first_unused_derived_key_index(const fc::ecc::private_key& parent_key)
   {
      int first_unused_index = 0;
      int number_of_consecutive_unused_keys = 0;
      for (int key_index = 0; ; ++key_index)
      {
         fc::ecc::private_key derived_private_key = derive_private_key(key_to_wif(parent_key), key_index);
         contento::chain::public_key_type derived_public_key = derived_private_key.get_public_key();
         if( _keys.find(derived_public_key) == _keys.end() )
         {
            if (number_of_consecutive_unused_keys)
            {
               ++number_of_consecutive_unused_keys;
               if (number_of_consecutive_unused_keys > 5)
                  return first_unused_index;
            }
            else
            {
               first_unused_index = key_index;
               number_of_consecutive_unused_keys = 1;
            }
         }
         else
         {
            // key_index is used
            first_unused_index = 0;
            number_of_consecutive_unused_keys = 0;
         }
      }
   }

   signed_transaction create_account_with_private_key(fc::ecc::private_key owner_privkey,
                                                      string account_name,
                                                      string creator_account_name,
                                                      bool broadcast = false,
                                                      bool save_wallet = true)
   { try {
         int active_key_index = find_first_unused_derived_key_index(owner_privkey);
         fc::ecc::private_key active_privkey = derive_private_key( key_to_wif(owner_privkey), active_key_index);

         int memo_key_index = find_first_unused_derived_key_index(active_privkey);
         fc::ecc::private_key memo_privkey = derive_private_key( key_to_wif(active_privkey), memo_key_index);

         contento::chain::public_key_type owner_pubkey = owner_privkey.get_public_key();
         contento::chain::public_key_type active_pubkey = active_privkey.get_public_key();
         contento::chain::public_key_type memo_pubkey = memo_privkey.get_public_key();

         account_create_operation account_create_op;

         account_create_op.creator = creator_account_name;
         account_create_op.new_account_name = account_name;
         account_create_op.fee = _remote_db->get_chain_properties().account_creation_fee;
         account_create_op.owner = authority(1, owner_pubkey, 1);
         account_create_op.active = authority(1, active_pubkey, 1);
         account_create_op.memo_key = memo_pubkey;

         signed_transaction tx;

         tx.operations.push_back( account_create_op );
         tx.validate();

         if( save_wallet )
            save_wallet_file();
         if( broadcast )
         {
            //_remote_net_broadcast->broadcast_transaction( tx );
            auto result = _remote_net_broadcast->broadcast_transaction_synchronous( tx );
         }
         return tx;
   } FC_CAPTURE_AND_RETHROW( (account_name)(creator_account_name)(broadcast) ) }


   optional< witness_api_obj > get_witness( string owner_account )
   {
      return _remote_db->get_witness_by_account( owner_account );
   }

   signed_transaction _sign_transaction(signed_transaction tx)
   {
      flat_set< account_name_type >   req_active_approvals;
      flat_set< account_name_type >   req_owner_approvals;
      flat_set< account_name_type >   req_posting_approvals;
      vector< authority >  other_auths;

      tx.get_required_authorities( req_active_approvals, req_owner_approvals, req_posting_approvals, other_auths );

      for( const auto& auth : other_auths )
         for( const auto& a : auth.account_auths )
            req_active_approvals.insert(a.first);

      // std::merge lets us de-duplicate account_id's that occur in both
      //   sets, and dump them into a vector (as required by remote_db api)
      //   at the same time
      vector< string > v_approving_account_names;
      std::merge(req_active_approvals.begin(), req_active_approvals.end(),
                 req_owner_approvals.begin() , req_owner_approvals.end(),
                 std::back_inserter( v_approving_account_names ) );

      for( const auto& a : req_posting_approvals )
         v_approving_account_names.push_back(a);

      /// TODO: fetch the accounts specified via other_auths as well.

      auto approving_account_objects = _remote_db->get_accounts( v_approving_account_names );

      /// TODO: recursively check one layer deeper in the authority tree for keys

      FC_ASSERT( approving_account_objects.size() == v_approving_account_names.size(), "", ("aco.size:", approving_account_objects.size())("acn",v_approving_account_names.size()) );

      flat_map< string, account_api_obj > approving_account_lut;
      size_t i = 0;
      for( const optional< account_api_obj >& approving_acct : approving_account_objects )
      {
         if( !approving_acct.valid() )
         {
            wlog( "operation_get_required_auths said approval of non-existing account ${name} was needed",
                  ("name", v_approving_account_names[i]) );
            i++;
            continue;
         }
         approving_account_lut[ approving_acct->name ] =  *approving_acct;
         i++;
      }
      auto get_account_from_lut = [&]( const std::string& name ) -> const account_api_obj&
      {
         auto it = approving_account_lut.find( name );
         FC_ASSERT( it != approving_account_lut.end() );
         return it->second;
      };

      flat_set<public_key_type> approving_key_set;
      for( account_name_type& acct_name : req_active_approvals )
      {
         const auto it = approving_account_lut.find( acct_name );
         if( it == approving_account_lut.end() )
            continue;
         const account_api_obj& acct = it->second;
         vector<public_key_type> v_approving_keys = acct.active.get_keys();
         wdump((v_approving_keys));
         for( const public_key_type& approving_key : v_approving_keys )
         {
            wdump((approving_key));
            approving_key_set.insert( approving_key );
         }
      }

      for( account_name_type& acct_name : req_posting_approvals )
      {
         const auto it = approving_account_lut.find( acct_name );
         if( it == approving_account_lut.end() )
            continue;
         const account_api_obj& acct = it->second;
         vector<public_key_type> v_approving_keys = acct.posting.get_keys();
         wdump((v_approving_keys));
         for( const public_key_type& approving_key : v_approving_keys )
         {
            wdump((approving_key));
            approving_key_set.insert( approving_key );
         }
      }

      for( const account_name_type& acct_name : req_owner_approvals )
      {
         const auto it = approving_account_lut.find( acct_name );
         if( it == approving_account_lut.end() )
            continue;
         const account_api_obj& acct = it->second;
         vector<public_key_type> v_approving_keys = acct.owner.get_keys();
         for( const public_key_type& approving_key : v_approving_keys )
         {
            wdump((approving_key));
            approving_key_set.insert( approving_key );
         }
      }
      for( const authority& a : other_auths )
      {
         for( const auto& k : a.key_auths )
         {
            wdump((k.first));
            approving_key_set.insert( k.first );
         }
      }

      auto dyn_props = _remote_db->get_dynamic_global_properties();
      tx.set_reference_block( dyn_props.head_block_id );
      tx.set_expiration( dyn_props.time + fc::seconds(_tx_expiration_seconds) );
      tx.signatures.clear();

      //idump((_keys));
      flat_set< public_key_type > available_keys;
      flat_map< public_key_type, fc::ecc::private_key > available_private_keys;
      for( const public_key_type& key : approving_key_set )
      {
         auto it = _keys.find(key);
         if( it != _keys.end() )
         {
            fc::optional<fc::ecc::private_key> privkey = wif_to_key( it->second );
            FC_ASSERT( privkey.valid(), "Malformed private key in _keys" );
            available_keys.insert(key);
            available_private_keys[key] = *privkey;
         }
      }

      auto minimal_signing_keys = tx.minimize_required_signatures(
         CONTENTO_CHAIN_ID,
         available_keys,
         [&]( const string& account_name ) -> const authority&
         { return (get_account_from_lut( account_name ).active); },
         [&]( const string& account_name ) -> const authority&
         { return (get_account_from_lut( account_name ).owner); },
         [&]( const string& account_name ) -> const authority&
         { return (get_account_from_lut( account_name ).posting); },
         CONTENTO_MAX_SIG_CHECK_DEPTH
         );

      for( const public_key_type& k : minimal_signing_keys )
      {
         auto it = available_private_keys.find(k);
         FC_ASSERT( it != available_private_keys.end() );
         tx.sign( it->second, CONTENTO_CHAIN_ID );
      }

      return tx;
   }
    
    annotated_signed_transaction sign_transaction(signed_transaction trx_to_sign, bool broadcast = false) {
        signed_transaction tx = _sign_transaction(trx_to_sign);
        if( broadcast ) {
            try {
                auto result = _remote_net_broadcast->broadcast_transaction_synchronous( tx );
                annotated_signed_transaction rtrx(tx);
                rtrx.transaction_id = tx.id();
                rtrx.block_num = result.get_object()["block_num"].as_uint64();
                rtrx.transaction_num = result.get_object()["trx_num"].as_uint64();
                rtrx.invoice.status = result.get_object()["status"].as_uint64();
                rtrx.invoice.gas_usage = result.get_object()["gas_usage"].as_uint64();
                rtrx.invoice.vm_error = result.get_object()["vm_error"].as_bool();
                rtrx.invoice.vm_error_code = result.get_object()["vm_error_code"].as_uint64();
                rtrx.invoice.vm_error_msg = result.get_object()["vm_error_msg"].as_string();
                rtrx.invoice.vm_console = result.get_object()["vm_console"].as_string();
                return rtrx;
            }
            catch (const fc::exception& e)
            {
                elog("Caught exception while broadcasting tx ${id}:  ${e}", ("id", tx.id().str())("e", e.to_detail_string()) );
                throw;
            }
        }
        return tx;
    }
    
    asset estimate_gas(signed_transaction tx) {
        try {
            
            return (*_remote_gas_estimate)->estimated_gas_fee( _sign_transaction(tx) );
            
        } catch (const fc::exception& e) {
            elog("Caught exception while estimating gas fee of tx ${id}:  ${e}", ("id", tx.id().str())("e", e.to_detail_string()) );
            throw;
        }
    }

   std::map<string,std::function<string(fc::variant,const fc::variants&)>> get_result_formatters() const
   {
      std::map<string,std::function<string(fc::variant,const fc::variants&)> > m;
      m["help"] = [](variant result, const fc::variants& a)
      {
         return result.get_string();
      };

      m["gethelp"] = [](variant result, const fc::variants& a)
      {
         return result.get_string();
      };

      m["list_my_accounts"] = [](variant result, const fc::variants& a ) {
         std::stringstream out;

         auto accounts = result.as<vector<account_api_obj>>();
         asset total_steem;
         asset total_vest(0, VESTS_SYMBOL );
         for( const auto& a : accounts ) {
            total_steem += a.balance;
            total_vest  += a.vesting_shares;
            out << std::left << std::setw( 17 ) << std::string(a.name)
                << std::right << std::setw(18) << fc::variant(a.balance).as_string() <<" "
             << std::right << std::setw(26) << fc::variant(a.vesting_shares).as_string() <<"\n";
         }
         out << "-------------------------------------------------------------------------\n";
            out << std::left << std::setw( 17 ) << "TOTAL"
                << std::right << std::setw(18) << fc::variant(total_steem).as_string() <<" "
          << std::right << std::setw(26) << fc::variant(total_vest).as_string() <<"\n";
         return out.str();
      };
      m["get_account_history"] = []( variant result, const fc::variants& a ) {
         std::stringstream ss;
         ss << std::left << std::setw( 5 )  << "#" << " ";
         ss << std::left << std::setw( 10 ) << "BLOCK #" << " ";
         ss << std::left << std::setw( 15 ) << "TRX ID" << " ";
         ss << std::left << std::setw( 20 ) << "OPERATION" << " ";
         ss << std::left << std::setw( 50 ) << "DETAILS" << "\n";
         ss << "-------------------------------------------------------------------------------\n";
         const auto& results = result.get_array();
         for( const auto& item : results ) {
            ss << std::left << std::setw(5) << item.get_array()[0].as_string() << " ";
            const auto& op = item.get_array()[1].get_object();
            ss << std::left << std::setw(10) << op["block"].as_string() << " ";
            ss << std::left << std::setw(15) << op["trx_id"].as_string() << " ";
            const auto& opop = op["op"].get_array();
            ss << std::left << std::setw(20) << opop[0].as_string() << " ";
            ss << std::left << std::setw(50) << fc::json::to_string(opop[1]) << "\n ";
         }
         return ss.str();
      };
      m["push_action"] = []( variant result, const fc::variants& a )
      {
         std::string json_str = fc::json::to_pretty_string( result );

         try {
            auto invoice = result.get_object()["invoice"].get_object();
            auto console = invoice["vm_console"].as_string();
            if ( console.size() ) {
               std::stringstream ss;
               ss << "\n==== VM Console Begin ====\n" << console << "\n==== VM Console End ====";
               dlog( ss.str() );
            }
            if ( invoice["vm_error"].as_bool() ) {
               std::stringstream ss;
               ss << "\n==== VM Error Begin ====\n" << invoice["vm_error_msg"].as_string() << "\n==== VM Error End ====";
               wlog( ss.str() );
            }
         } catch(...) {}
      
         return json_str;
      };

      return m;
   }

   void use_network_node_api()
   {
      if( _remote_net_node )
         return;
      try
      {
         _remote_net_node = _remote_api->get_api_by_name("network_node_api")->as< network_node_api >();
      }
      catch( const fc::exception& e )
      {
         elog( "Couldn't get network node API" );
         throw(e);
      }
   }

   void use_remote_message_api()
   {
      if( _remote_message_api.valid() )
         return;

      try { _remote_message_api = _remote_api->get_api_by_name("private_message_api")->as< private_message_api >(); }
      catch( const fc::exception& e ) { elog( "Couldn't get private message API" ); throw(e); }
   }

   void use_follow_api()
   {
      if( _remote_follow_api.valid() )
         return;

      try { _remote_follow_api = _remote_api->get_api_by_name("follow_api")->as< follow::follow_api >(); }
      catch( const fc::exception& e ) { elog( "Couldn't get follow API" ); throw(e); }
   }
    
    void use_gas_estimate_api()
    {
        if( _remote_gas_estimate.valid() )
            return;
        
        try { _remote_gas_estimate = _remote_api->get_api_by_name("contento_gas_estimate_api")->as< gas_estimate::contento_gas_estimate_api >(); }
        catch( const fc::exception& e ) { elog( "Couldn't get gas_estimate API" ); throw(e); }
    }

   void use_remote_account_by_key_api()
   {
      if( _remote_account_by_key_api.valid() )
         return;

      try{ _remote_account_by_key_api = _remote_api->get_api_by_name( "account_by_key_api" )->as< account_by_key::account_by_key_api >(); }
      catch( const fc::exception& e ) { elog( "Couldn't get account_by_key API" ); throw(e); }
   }

   void network_add_nodes( const vector<string>& nodes )
   {
      use_network_node_api();
      for( const string& node_address : nodes )
      {
         (*_remote_net_node)->add_node( fc::ip::endpoint::from_string( node_address ) );
      }
   }

   vector< variant > network_get_connected_peers()
   {
      use_network_node_api();
      const auto peers = (*_remote_net_node)->get_connected_peers();
      vector< variant > result;
      result.reserve( peers.size() );
      for( const auto& peer : peers )
      {
         variant v;
         fc::to_variant( peer, v );
         result.push_back( v );
      }
      return result;
   }


   string                                  _wallet_filename;
   wallet_data                             _wallet;

   map<public_key_type,string>             _keys;
   fc::sha512                              _checksum;
   fc::api<login_api>                      _remote_api;
   fc::api<database_api>                   _remote_db;
   fc::api<network_broadcast_api>          _remote_net_broadcast;
   optional< fc::api<network_node_api> >   _remote_net_node;
   optional< fc::api<account_by_key::account_by_key_api> > _remote_account_by_key_api;
   optional< fc::api<private_message_api> > _remote_message_api;
   optional< fc::api<follow::follow_api> >  _remote_follow_api;
   optional< fc::api<gas_estimate::contento_gas_estimate_api> > _remote_gas_estimate;
   
   uint32_t                                _tx_expiration_seconds = 30;

   flat_map<string, operation>             _prototype_ops;

   static_variant_map _operation_which_map = create_static_variant_map< operation >();

#ifdef __unix__
   mode_t                  _old_umask;
#endif
   const string _wallet_filename_extension = ".wallet";
};

} } } // contento::wallet::detail



namespace contento { namespace wallet {

wallet_api::wallet_api(const wallet_data& initial_data, fc::api<login_api> rapi)
   : my(new detail::wallet_api_impl(*this, initial_data, rapi))
{}

wallet_api::~wallet_api(){}

bool wallet_api::copy_wallet_file(string destination_filename)
{
   return my->copy_wallet_file(destination_filename);
}

optional<signed_block_api_obj> wallet_api::get_block(uint32_t num)
{
   return my->_remote_db->get_block(num);
}

vector<applied_operation> wallet_api::get_ops_in_block(uint32_t block_num, bool only_virtual)
{
   return my->_remote_db->get_ops_in_block(block_num, only_virtual);
}

vector<account_api_obj> wallet_api::list_my_accounts()
{
   FC_ASSERT( !is_locked(), "Wallet must be unlocked to list accounts" );
   vector<account_api_obj> result;

   try
   {
      my->use_remote_account_by_key_api();
   }
   catch( fc::exception& e )
   {
      elog( "Connected node needs to enable account_by_key_api" );
      return result;
   }

   vector<public_key_type> pub_keys;
   pub_keys.reserve( my->_keys.size() );

   for( const auto& item : my->_keys )
      pub_keys.push_back(item.first);

   auto refs = (*my->_remote_account_by_key_api)->get_key_references( pub_keys );
   set<string> names;
   for( const auto& item : refs )
      for( const auto& name : item )
         names.insert( name );


   result.reserve( names.size() );
   for( const auto& name : names )
      result.emplace_back( get_account( name ) );

   return result;
}

set<string> wallet_api::list_accounts(const string& lowerbound, uint32_t limit)
{
   return my->_remote_db->lookup_accounts(lowerbound, limit);
}

vector<account_name_type> wallet_api::get_miner_queue()const {
   return my->_remote_db->get_miner_queue();
}

std::vector< account_name_type > wallet_api::get_active_witnesses()const {
   return my->_remote_db->get_active_witnesses();
}

brain_key_info wallet_api::suggest_brain_key()const
{
   brain_key_info result;
   // create a private key for secure entropy
   fc::sha256 sha_entropy1 = fc::ecc::private_key::generate().get_secret();
   fc::sha256 sha_entropy2 = fc::ecc::private_key::generate().get_secret();
   fc::bigint entropy1( sha_entropy1.data(), sha_entropy1.data_size() );
   fc::bigint entropy2( sha_entropy2.data(), sha_entropy2.data_size() );
   fc::bigint entropy(entropy1);
   entropy <<= 8*sha_entropy1.data_size();
   entropy += entropy2;
   string brain_key = "";

   for( int i=0; i<BRAIN_KEY_WORD_COUNT; i++ )
   {
      fc::bigint choice = entropy % graphene::words::word_list_size;
      entropy /= graphene::words::word_list_size;
      if( i > 0 )
         brain_key += " ";
      brain_key += graphene::words::word_list[ choice.to_int64() ];
   }

   brain_key = normalize_brain_key(brain_key);
   fc::ecc::private_key priv_key = detail::derive_private_key( brain_key, 0 );
   result.brain_priv_key = brain_key;
   result.wif_priv_key = key_to_wif( priv_key );
   result.pub_key = priv_key.get_public_key();
   return result;
}

string wallet_api::serialize_transaction( signed_transaction tx )const
{
   return fc::to_hex(fc::raw::pack(tx));
}

string wallet_api::get_wallet_filename() const
{
   return my->get_wallet_filename();
}


account_api_obj wallet_api::get_account( string account_name ) const
{
   return my->get_account( account_name );
}

account_code_api_obj wallet_api::get_account_code( string account_name ) const
{
   return my->get_account_code( account_name );
}

wallet_table_rows wallet_api::get_table_rows(string code, string scope, string table,
                                  string lower_bound, string upper_bound, int limit,
                                  string key_type, string index_pos, string encode_type) const
{
   auto obj = my->get_table_rows(code, scope, table, lower_bound, upper_bound, 
                                        limit, key_type, index_pos, encode_type);

   auto contract = get_account_code(code);
   abi_def abi;
   abi_serializer::to_abi(contract.abi, abi);
   
   abi_serializer abis;
   abis.set_abi(abi);

   wallet_table_rows result;
   for(auto ele : obj.raw_data_rows) {
      result.rows.emplace_back(abis.binary_to_variant(abis.get_table_type(table), ele));
   }
   result.more = obj.more;
   //auto mvo_result = fc::mutable_variant_object("rows", fc::variant(result.rows))("more", result.more)
   //return fc::json::to_pretty_string(fc::variant(mvo_result));
   return result;
}

bool wallet_api::import_key(string wif_key)
{
   FC_ASSERT(!is_locked());
   // backup wallet
   fc::optional<fc::ecc::private_key> optional_private_key = wif_to_key(wif_key);
   if (!optional_private_key)
      FC_THROW("Invalid private key");
//   string shorthash = detail::pubkey_to_shorthash( optional_private_key->get_public_key() );
//   copy_wallet_file( "before-import-key-" + shorthash );

   if( my->import_key(wif_key) )
   {
      save_wallet_file();
 //     copy_wallet_file( "after-import-key-" + shorthash );
      return true;
   }
   return false;
}

string wallet_api::normalize_brain_key(string s) const
{
   return detail::normalize_brain_key( s );
}

variant wallet_api::info()
{
   return my->info();
}

variant_object wallet_api::about() const
{
    return my->about();
}

/*
fc::ecc::private_key wallet_api::derive_private_key(const std::string& prefix_string, int sequence_number) const
{
   return detail::derive_private_key( prefix_string, sequence_number );
}
*/

set<account_name_type> wallet_api::list_witnesses(const string& lowerbound, uint32_t limit)
{
   return my->_remote_db->lookup_witness_accounts(lowerbound, limit);
}

optional< witness_api_obj > wallet_api::get_witness(string owner_account)
{
   return my->get_witness(owner_account);
}


void wallet_api::set_wallet_filename(string wallet_filename) { my->_wallet_filename = wallet_filename; }

annotated_signed_transaction wallet_api::sign_transaction(signed_transaction tx, bool broadcast /* = false */)
{ try {
   return my->sign_transaction( tx, broadcast);
} FC_CAPTURE_AND_RETHROW( (tx) ) }

void wallet_api::network_add_nodes( const vector<string>& nodes ) {
   my->network_add_nodes( nodes );
}

vector< variant > wallet_api::network_get_connected_peers() {
   return my->network_get_connected_peers();
}

string wallet_api::help()const
{
   std::vector<std::string> method_names = my->method_documentation.get_method_names();
   std::stringstream ss;
   for (const std::string method_name : method_names)
   {
      try
      {
         ss << my->method_documentation.get_brief_description(method_name);
      }
      catch (const fc::key_not_found_exception&)
      {
         ss << method_name << " (no help available)\n";
      }
   }
   return ss.str();
}

string wallet_api::gethelp(const string& method)const
{
   fc::api<wallet_api> tmp;
   std::stringstream ss;
   ss << "\n";

   std::string doxygenHelpString = my->method_documentation.get_detailed_description(method);
   if (!doxygenHelpString.empty())
      ss << doxygenHelpString;
   else
      ss << "No help defined for method " << method << "\n";

   return ss.str();
}

bool wallet_api::load_wallet_file( string wallet_filename )
{
   return my->load_wallet_file( wallet_filename );
}

void wallet_api::save_wallet_file( string wallet_filename )
{
   my->save_wallet_file( wallet_filename );
}

std::map<string,std::function<string(fc::variant,const fc::variants&)> >
wallet_api::get_result_formatters() const
{
   return my->get_result_formatters();
}

bool wallet_api::is_locked()const
{
   return my->is_locked();
}
bool wallet_api::is_new()const
{
   return my->_wallet.cipher_keys.size() == 0;
}

void wallet_api::encrypt_keys()
{
   my->encrypt_keys();
}

void wallet_api::lock()
{ try {
   FC_ASSERT( !is_locked() );
   encrypt_keys();
   for( auto key : my->_keys )
      key.second = key_to_wif(fc::ecc::private_key());
   my->_keys.clear();
   my->_checksum = fc::sha512();
   my->self.lock_changed(true);
} FC_CAPTURE_AND_RETHROW() }

void wallet_api::unlock(string password)
{ try {
   FC_ASSERT(password.size() > 0);
   auto pw = fc::sha512::hash(password.c_str(), password.size());
   vector<char> decrypted = fc::aes_decrypt(pw, my->_wallet.cipher_keys);
   auto pk = fc::raw::unpack<plain_keys>(decrypted);
   FC_ASSERT(pk.checksum == pw);
   my->_keys = std::move(pk.keys);
   my->_checksum = pk.checksum;
   my->self.lock_changed(false);
} FC_CAPTURE_AND_RETHROW() }

void wallet_api::set_password( string password )
{
   if( !is_new() )
      FC_ASSERT( !is_locked(), "The wallet must be unlocked before the password can be set" );
   my->_checksum = fc::sha512::hash( password.c_str(), password.size() );
   lock();
}

map<public_key_type, string> wallet_api::list_keys()
{
   FC_ASSERT(!is_locked());
   return my->_keys;
}

string wallet_api::get_private_key( public_key_type pubkey )const
{
   return key_to_wif( my->get_private_key( pubkey ) );
}

pair<public_key_type,string> wallet_api::get_private_key_from_password( string account, string role, string password )const {
   auto seed = account + role + password;
   FC_ASSERT( seed.size() );
   auto secret = fc::sha256::hash( seed.c_str(), seed.size() );
   auto priv = fc::ecc::private_key::regenerate( secret );
   return std::make_pair( public_key_type( priv.get_public_key() ), key_to_wif( priv ) );
}

annotated_signed_transaction wallet_api::create_councillor ( bool broadcast ) {
try {
   FC_ASSERT( !is_locked() );
   signed_transaction tx;
   for (int i = 0; i < 5; i++) {
      auto owner = suggest_brain_key();
      auto active = suggest_brain_key();
      auto posting = suggest_brain_key();
      auto memo = suggest_brain_key();
      import_key( owner.wif_priv_key );
      import_key( active.wif_priv_key );
      import_key( posting.wif_priv_key );
      import_key( memo.wif_priv_key );
      
      account_create_operation op;
      op.creator = CONTENTO_INIT_MINER_NAME;
      op.new_account_name = "councillor" + (i == 0 ? "" : std::to_string(i));
      op.owner = authority( 1, owner.pub_key, 1 );
      op.active = authority( 1, active.pub_key, 1 );
      op.posting = authority( 1, posting.pub_key, 1 );
      op.memo_key = memo.pub_key;
      //op.json_metadata = json_meta;
      op.fee = my->_remote_db->get_chain_properties().account_creation_fee * 
            asset( CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER, COS_SYMBOL );
            
      tx.operations.push_back(op);
   }
   tx.validate();
   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (broadcast) ) }

annotated_signed_transaction wallet_api::grant_admin( string creator,
      vector<string> targets, int type, bool is_grant, bool broadcast ) {
try {
   FC_ASSERT( !is_locked() && targets.size() );
   signed_transaction tx;
   for (auto target : targets) {
      admin_grant_operation op;
      op.creator = creator;
      op.nominee = target;
      op.is_grant = is_grant;
      op.type = type;

      tx.operations.push_back(op);
   }
   tx.validate();
   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (creator)(broadcast) ) }

annotated_signed_transaction wallet_api::report_comment( string reporter,
      int credit, string author, string permlink, string tag, 
      bool is_ack, bool approved, bool broadcast) {
try {
   FC_ASSERT( !is_locked() );
   comment_report_operation op;
   op.reporter = reporter;
   op.author = author;
   op.permlink = permlink;
   op.credit = asset( credit, COS_SYMBOL );
   op.tag = tag;
   op.is_ack = is_ack;
   op.approved = approved;

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();
   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (reporter)(author)(permlink)(broadcast) ) }

/**
 * This method is used by faucets to create new accounts for other users which must
 * provide their desired keys. The resulting account may not be controllable by this
 * wallet.
 */
annotated_signed_transaction wallet_api::create_account_with_keys( string creator,
                                      string new_account_name,
                                      string json_meta,
                                      public_key_type owner,
                                      public_key_type active,
                                      public_key_type posting,
                                      public_key_type memo,
                                      bool broadcast )const
{ try {
   FC_ASSERT( !is_locked() );
   account_create_operation op;
   op.creator = creator;
   op.new_account_name = new_account_name;
   op.owner = authority( 1, owner, 1 );
   op.active = authority( 1, active, 1 );
   op.posting = authority( 1, posting, 1 );
   op.memo_key = memo;
   op.json_metadata = json_meta;
   op.fee = my->_remote_db->get_chain_properties().account_creation_fee * asset( CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER, COS_SYMBOL );

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (creator)(new_account_name)(json_meta)(owner)(active)(memo)(broadcast) ) }

/**
 * This method is used by faucets to create new accounts for other users which must
 * provide their desired keys. The resulting account may not be controllable by this
 * wallet.
 */
annotated_signed_transaction wallet_api::create_account_with_keys_delegated( string creator,
                                      asset steem_fee,
                                      asset delegated_vests,
                                      string new_account_name,
                                      string json_meta,
                                      public_key_type owner,
                                      public_key_type active,
                                      public_key_type posting,
                                      public_key_type memo,
                                      bool broadcast )const
{ try {
   FC_ASSERT( !is_locked() );
   account_create_with_delegation_operation op;
   op.creator = creator;
   op.new_account_name = new_account_name;
   op.owner = authority( 1, owner, 1 );
   op.active = authority( 1, active, 1 );
   op.posting = authority( 1, posting, 1 );
   op.memo_key = memo;
   op.json_metadata = json_meta;
   op.fee = steem_fee;
   op.delegation = delegated_vests;

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (creator)(new_account_name)(json_meta)(owner)(active)(memo)(broadcast) ) }


annotated_signed_transaction wallet_api::update_account(
                                      string account_name,
                                      string json_meta,
                                      public_key_type owner,
                                      public_key_type active,
                                      public_key_type posting,
                                      public_key_type memo,
                                      bool broadcast )const
{
   try
   {
      FC_ASSERT( !is_locked() );

      account_update_operation op;
      op.account = account_name;
      op.owner  = authority( 1, owner, 1 );
      op.active = authority( 1, active, 1);
      op.posting = authority( 1, posting, 1);
      op.memo_key = memo;
      op.json_metadata = json_meta;

      signed_transaction tx;
      tx.operations.push_back(op);
      tx.validate();

      return my->sign_transaction( tx, broadcast );
   }
   FC_CAPTURE_AND_RETHROW( (account_name)(json_meta)(owner)(active)(memo)(broadcast) )
}

annotated_signed_transaction wallet_api::update_account_auth_key( string account_name, authority_type type, public_key_type key, weight_type weight, bool broadcast )
{
   FC_ASSERT( !is_locked() );

   auto accounts = my->_remote_db->get_accounts( { account_name } );
   FC_ASSERT( accounts.size() == 1, "Account does not exist" );
   FC_ASSERT( account_name == accounts[0].name, "Account name doesn't match?" );

   account_update_operation op;
   op.account = account_name;
   op.memo_key = accounts[0].memo_key;
   op.json_metadata = accounts[0].json_metadata;

   authority new_auth;

   switch( type )
   {
      case( owner ):
         new_auth = accounts[0].owner;
         break;
      case( active ):
         new_auth = accounts[0].active;
         break;
      case( posting ):
         new_auth = accounts[0].posting;
         break;
   }

   if( weight == 0 ) // Remove the key
   {
      new_auth.key_auths.erase( key );
   }
   else
   {
      new_auth.add_authority( key, weight );
   }

   if( new_auth.is_impossible() )
   {
      if ( type == owner )
      {
         FC_ASSERT( false, "Owner authority change would render account irrecoverable." );
      }

      wlog( "Authority is now impossible." );
   }

   switch( type )
   {
      case( owner ):
         op.owner = new_auth;
         break;
      case( active ):
         op.active = new_auth;
         break;
      case( posting ):
         op.posting = new_auth;
         break;
   }

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::update_account_auth_account( string account_name, authority_type type, string auth_account, weight_type weight, bool broadcast )
{
   FC_ASSERT( !is_locked() );

   auto accounts = my->_remote_db->get_accounts( { account_name } );
   FC_ASSERT( accounts.size() == 1, "Account does not exist" );
   FC_ASSERT( account_name == accounts[0].name, "Account name doesn't match?" );

   account_update_operation op;
   op.account = account_name;
   op.memo_key = accounts[0].memo_key;
   op.json_metadata = accounts[0].json_metadata;

   authority new_auth;

   switch( type )
   {
      case( owner ):
         new_auth = accounts[0].owner;
         break;
      case( active ):
         new_auth = accounts[0].active;
         break;
      case( posting ):
         new_auth = accounts[0].posting;
         break;
   }

   if( weight == 0 ) // Remove the key
   {
      new_auth.account_auths.erase( auth_account );
   }
   else
   {
      new_auth.add_authority( auth_account, weight );
   }

   if( new_auth.is_impossible() )
   {
      if ( type == owner )
      {
         FC_ASSERT( false, "Owner authority change would render account irrecoverable." );
      }

      wlog( "Authority is now impossible." );
   }

   switch( type )
   {
      case( owner ):
         op.owner = new_auth;
         break;
      case( active ):
         op.active = new_auth;
         break;
      case( posting ):
         op.posting = new_auth;
         break;
   }

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::update_account_auth_threshold( string account_name, authority_type type, uint32_t threshold, bool broadcast )
{
   FC_ASSERT( !is_locked() );

   auto accounts = my->_remote_db->get_accounts( { account_name } );
   FC_ASSERT( accounts.size() == 1, "Account does not exist" );
   FC_ASSERT( account_name == accounts[0].name, "Account name doesn't match?" );
   FC_ASSERT( threshold != 0, "Authority is implicitly satisfied" );

   account_update_operation op;
   op.account = account_name;
   op.memo_key = accounts[0].memo_key;
   op.json_metadata = accounts[0].json_metadata;

   authority new_auth;

   switch( type )
   {
      case( owner ):
         new_auth = accounts[0].owner;
         break;
      case( active ):
         new_auth = accounts[0].active;
         break;
      case( posting ):
         new_auth = accounts[0].posting;
         break;
   }

   new_auth.weight_threshold = threshold;

   if( new_auth.is_impossible() )
   {
      if ( type == owner )
      {
         FC_ASSERT( false, "Owner authority change would render account irrecoverable." );
      }

      wlog( "Authority is now impossible." );
   }

   switch( type )
   {
      case( owner ):
         op.owner = new_auth;
         break;
      case( active ):
         op.active = new_auth;
         break;
      case( posting ):
         op.posting = new_auth;
         break;
   }

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::update_account_meta( string account_name, string json_meta, bool broadcast )
{
   FC_ASSERT( !is_locked() );

   auto accounts = my->_remote_db->get_accounts( { account_name } );
   FC_ASSERT( accounts.size() == 1, "Account does not exist" );
   FC_ASSERT( account_name == accounts[0].name, "Account name doesn't match?" );

   account_update_operation op;
   op.account = account_name;
   op.memo_key = accounts[0].memo_key;
   op.json_metadata = json_meta;

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::update_account_memo_key( string account_name, public_key_type key, bool broadcast )
{
   FC_ASSERT( !is_locked() );

   auto accounts = my->_remote_db->get_accounts( { account_name } );
   FC_ASSERT( accounts.size() == 1, "Account does not exist" );
   FC_ASSERT( account_name == accounts[0].name, "Account name doesn't match?" );

   account_update_operation op;
   op.account = account_name;
   op.memo_key = key;
   op.json_metadata = accounts[0].json_metadata;

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}


/**
 *  This method will genrate new owner, active, and memo keys for the new account which
 *  will be controlable by this wallet.
 */
annotated_signed_transaction wallet_api::create_account( string creator, string new_account_name, string json_meta, bool broadcast )
{ try {
   FC_ASSERT( !is_locked() );
   auto owner = suggest_brain_key();
   auto active = suggest_brain_key();
   auto posting = suggest_brain_key();
   auto memo = suggest_brain_key();
   import_key( owner.wif_priv_key );
   import_key( active.wif_priv_key );
   import_key( posting.wif_priv_key );
   import_key( memo.wif_priv_key );
   return create_account_with_keys( creator, new_account_name, json_meta, owner.pub_key, active.pub_key, posting.pub_key, memo.pub_key, broadcast );
} FC_CAPTURE_AND_RETHROW( (creator)(new_account_name)(json_meta) ) }

/**
 *  This method will genrate new owner, active, and memo keys for the new account which
 *  will be controlable by this wallet.
 */
annotated_signed_transaction wallet_api::create_account_delegated( string creator, asset steem_fee, asset delegated_vests, string new_account_name, string json_meta, bool broadcast )
{ try {
   FC_ASSERT( !is_locked() );
   auto owner = suggest_brain_key();
   auto active = suggest_brain_key();
   auto posting = suggest_brain_key();
   auto memo = suggest_brain_key();
   import_key( owner.wif_priv_key );
   import_key( active.wif_priv_key );
   import_key( posting.wif_priv_key );
   import_key( memo.wif_priv_key );
   return create_account_with_keys_delegated( creator, steem_fee, delegated_vests, new_account_name, json_meta,  owner.pub_key, active.pub_key, posting.pub_key, memo.pub_key, broadcast );
} FC_CAPTURE_AND_RETHROW( (creator)(new_account_name)(json_meta) ) }


annotated_signed_transaction wallet_api::update_witness( string witness_account_name,
                                               string url,
                                               public_key_type block_signing_key,
                                               const chain_properties& props,
                                               bool broadcast  )
{
   FC_ASSERT( !is_locked() );

   witness_update_operation op;

   fc::optional< witness_api_obj > wit = my->_remote_db->get_witness_by_account( witness_account_name );
   if( !wit.valid() )
   {
      op.url = url;
   }
   else
   {
      FC_ASSERT( wit->owner == witness_account_name );
      if( url != "" )
         op.url = url;
      else
         op.url = wit->url;
   }
   op.owner = witness_account_name;
   op.block_signing_key = block_signing_key;
   op.props = props;

   signed_transaction tx;
   tx.operations.push_back(op);
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

void wallet_api::check_memo( const string& memo, const account_api_obj& account )const
{
   vector< public_key_type > keys;
      
   try
   {
      // Check if memo is a private key
      keys.push_back( fc::ecc::extended_private_key::from_base58( memo ).get_public_key() );
   }
   catch( fc::parse_error_exception& ) {}
   catch( fc::assert_exception& ) {}

   // Get possible keys if memo was an account password
   string owner_seed = account.name + "owner" + memo;
   auto owner_secret = fc::sha256::hash( owner_seed.c_str(), owner_seed.size() );
   keys.push_back( fc::ecc::private_key::regenerate( owner_secret ).get_public_key() );

   string active_seed = account.name + "active" + memo;
   auto active_secret = fc::sha256::hash( active_seed.c_str(), active_seed.size() );
   keys.push_back( fc::ecc::private_key::regenerate( active_secret ).get_public_key() );

   string posting_seed = account.name + "posting" + memo;
   auto posting_secret = fc::sha256::hash( posting_seed.c_str(), posting_seed.size() );
   keys.push_back( fc::ecc::private_key::regenerate( posting_secret ).get_public_key() );

   // Check keys against public keys in authorites
   for( auto& key_weight_pair : account.owner.key_auths )
   {
      for( auto& key : keys )
         FC_ASSERT( key_weight_pair.first != key, "Detected private owner key in memo field. Cancelling transaction." );
   }

   for( auto& key_weight_pair : account.active.key_auths )
   {
      for( auto& key : keys )
         FC_ASSERT( key_weight_pair.first != key, "Detected private active key in memo field. Cancelling transaction." );
   }

   for( auto& key_weight_pair : account.posting.key_auths )
   {
      for( auto& key : keys )
         FC_ASSERT( key_weight_pair.first != key, "Detected private posting key in memo field. Cancelling transaction." );
   }

   const auto& memo_key = account.memo_key;
   for( auto& key : keys )
      FC_ASSERT( memo_key != key, "Detected private memo key in memo field. Cancelling transaction." );

   // Check against imported keys
   for( auto& key_pair : my->_keys )
   {
      for( auto& key : keys )
         FC_ASSERT( key != key_pair.first, "Detected imported private key in memo field. Cancelling trasanction." );
   }
}

string wallet_api::get_encrypted_memo( string from, string to, string memo ) {

    if( memo.size() > 0 && memo[0] == '#' ) {
       memo_data m;

       auto from_account = get_account( from );
       auto to_account   = get_account( to );

       m.from            = from_account.memo_key;
       m.to              = to_account.memo_key;
       m.nonce = fc::time_point::now().time_since_epoch().count();

       auto from_priv = my->get_private_key( m.from );
       auto shared_secret = from_priv.get_shared_secret( m.to );

       fc::sha512::encoder enc;
       fc::raw::pack( enc, m.nonce );
       fc::raw::pack( enc, shared_secret );
       auto encrypt_key = enc.result();

       m.encrypted = fc::aes_encrypt( encrypt_key, fc::raw::pack(memo.substr(1)) );
       m.check = fc::sha256::hash( encrypt_key )._hash[0];
       return m;
    } else {
       return memo;
    }
}

annotated_signed_transaction wallet_api::transfer(string from, string to, asset amount, string memo, bool broadcast )
{ try {
   FC_ASSERT( !is_locked() );
    check_memo( memo, get_account( from ) );
    transfer_operation op;
    op.from = from;
    op.to = to;
    op.amount = amount;

    op.memo = get_encrypted_memo( from, to, memo );

    signed_transaction tx;
    tx.operations.push_back( op );
    tx.validate();

   return my->sign_transaction( tx, broadcast );
} FC_CAPTURE_AND_RETHROW( (from)(to)(amount)(memo)(broadcast) ) }


annotated_signed_transaction wallet_api::transfer_to_vesting(string from, string to, asset amount, bool broadcast )
{
   FC_ASSERT( !is_locked() );
    transfer_to_vesting_operation op;
    op.from = from;
    op.to = (to == from ? "" : to);
    op.amount = amount;

    signed_transaction tx;
    tx.operations.push_back( op );
    tx.validate();

   return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::convert_from_vesting(string account, asset vesting_shares, bool broadcast)
{
    FC_ASSERT( !is_locked() );
    convert_from_vesting_operation op;
    op.account = account;
    op.vesting_shares = vesting_shares;
    
    signed_transaction tx;
    tx.operations.push_back( op );
    tx.validate();
    
    return my->sign_transaction( tx, broadcast );
}


string wallet_api::decrypt_memo( string encrypted_memo ) {
   if( is_locked() ) return encrypted_memo;

   if( encrypted_memo.size() && encrypted_memo[0] == '#' ) {
      auto m = memo_data::from_string( encrypted_memo );
      if( m ) {
         fc::sha512 shared_secret;
         auto from_key = my->try_get_private_key( m->from );
         if( !from_key ) {
            auto to_key   = my->try_get_private_key( m->to );
            if( !to_key ) return encrypted_memo;
            shared_secret = to_key->get_shared_secret( m->from );
         } else {
            shared_secret = from_key->get_shared_secret( m->to );
         }
         fc::sha512::encoder enc;
         fc::raw::pack( enc, m->nonce );
         fc::raw::pack( enc, shared_secret );
         auto encryption_key = enc.result();

         uint32_t check = fc::sha256::hash( encryption_key )._hash[0];
         if( check != m->check ) return encrypted_memo;

         try {
            vector<char> decrypted = fc::aes_decrypt( encryption_key, m->encrypted );
            return fc::raw::unpack<std::string>( decrypted );
         } catch ( ... ){}
      }
   }
   return encrypted_memo;
}

map<uint32_t,applied_operation> wallet_api::get_account_history( string account, uint32_t from, uint32_t limit ) {
   auto result = my->_remote_db->get_account_history(account,from,limit);
   if( !is_locked() ) {
      for( auto& item : result ) {
         if( item.second.op.which() == operation::tag<transfer_operation>::value ) {
            auto& top = item.second.op.get<transfer_operation>();
            top.memo = decrypt_memo( top.memo );
         }
      }
   }
   return result;
}

app::state wallet_api::get_state( string url ) {
   return my->_remote_db->get_state(url);
}

annotated_signed_transaction wallet_api::post_subject( string author, string permlink, string category, string title, string body, string json, bool broadcast)
{
    FC_ASSERT( !is_locked() );
    comment_operation op;
    op.parent_author = "";
    op.parent_permlink = "";
    op.author = author;
    op.permlink = permlink;
    op.category = category;
    op.title = title;
    op.body = body;
    op.json_metadata = json;
    signed_transaction tx;
    tx.operations.push_back( op );
    tx.validate();
    return my->sign_transaction( tx, broadcast );
}
    
annotated_signed_transaction wallet_api::post_comment( string author, string permlink, string parent_author, string parent_permlink, string body, string json, bool broadcast )
{
    FC_ASSERT( !is_locked() );
    comment_operation op;
    op.parent_author =  parent_author;
    op.parent_permlink = parent_permlink;
    op.author = author;
    op.permlink = permlink;
    op.title = "";
    op.category = "";
    op.body = body;
    op.json_metadata = json;
    signed_transaction tx;
    tx.operations.push_back( op );
    tx.validate();
    return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::vote( string voter, string author, string permlink, int16_t weight, bool broadcast )
{
   FC_ASSERT( !is_locked() );
   FC_ASSERT( abs(weight) <= 100, "Weight must be between -100 and 100 and not 0" );

   vote_operation op;
   op.voter = voter;
   op.author = author;
   op.permlink = permlink;
   op.weight = weight * CONTENTO_1_PERCENT;

   signed_transaction tx;
   tx.operations.push_back( op );
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}


annotated_signed_transaction wallet_api::get_transaction( transaction_id_type id )const {
   return my->_remote_db->get_transaction( id );
}

annotated_signed_transaction wallet_api::follow( string follower, string following, set<string> what, bool broadcast ) {
   auto follwer_account     = get_account( follower );
   FC_ASSERT( following.size() );
   if( following[0] != '@' || following[0] != '#' ) {
      following = '@' + following;
   }
   if( following[0] == '@' ) {
      get_account( following.substr(1) );
   }
   FC_ASSERT( following.size() > 1 );

   follow::follow_operation fop;
   fop.follower = follower;
   fop.following = following;
   fop.what = what;
   follow::follow_plugin_operation op = fop;

   custom_json_operation jop;
   jop.id = "follow";
   jop.json = fc::json::to_string(op);
   jop.required_posting_auths.insert(follower);

   signed_transaction trx;
   trx.operations.push_back( jop );
   trx.validate();

   return my->sign_transaction( trx, broadcast );
}

fc::variant json_from_file_or_string(const string& file_or_str, fc::json::parse_type ptype = fc::json::legacy_parser)
{
   regex r("^[ \t]*[\{\[]");
   if ( !regex_search(file_or_str, r) && fc::is_regular_file(file_or_str) ) {
      return fc::json::from_file(file_or_str, ptype);
   } else {
      return fc::json::from_string(file_or_str, ptype);
   }
}

bytes param_to_bin(const wallet_api &api, string contract_name, string action_name, string param) {
   fc::variant action_args_var;
   if( !param.empty() ) {
      try {
         action_args_var = json_from_file_or_string(param, fc::json::relaxed_parser);
      } catch (const fc::exception& e) {
         elog("Caught exception while parsing action data: ${param}:  ${e}", ("param", param)("e", e.to_detail_string()) );
         throw;
      }
   }

   const auto contract_acc = api.get_account_code(contract_name);
   abi_def abi;
   bytes result;
   if(abi_serializer::to_abi(contract_acc.abi, abi)) {
      abi_serializer abis(abi);
      auto action_type = abis.get_action_type(action_name);
      FC_ASSERT( !action_type.empty(), "unknown action ${action} in contract ${contract}", 
                                       ("action", action_name)("contract", contract_name) );
                                    
      try {
         result = abis.variant_to_binary(action_type, action_args_var);
      } catch (const fc::exception& e) {
         elog("Caught exception while serializing action data: ${param}:  ${e}", ("param", param)("e", e.to_detail_string()) );
         throw;
      }  
   } else {
      FC_ASSERT(false, "No ABI found for contract: ${contract}", ("contract", contract_name));
   }   
   return result;                        
}

annotated_signed_transaction wallet_api::push_action(string caller, string contract_name, string action_name, string action_param, bool broadcast) {
   bytes bin = param_to_bin(*this, contract_name, action_name, action_param);
   signed_transaction tx;
   tx.operations.push_back( vm_operation(caller, contract_name, action_name, bin) );
   tx.validate();

   return my->sign_transaction( tx, broadcast );
}

asset wallet_api::estimate_gas(string caller, string contract_name, string action_name, string action_data) {
    try
    {
        my->use_gas_estimate_api();
    }
    catch( fc::exception& e )
    {
        elog( "Connected node needs to enable contento_gas_estimate_api" );
        return asset(0);
    }
    bytes bin = param_to_bin(*this, contract_name, action_name, action_data);
    signed_transaction tx;
    tx.operations.push_back( vm_operation(caller, contract_name, action_name, bin) );
    tx.validate();
    
    return my->estimate_gas(tx);
}
    
    asset wallet_api::get_contract_balance(string name) {
        return my->_remote_db->get_contract_balance(name);
    }
    
annotated_signed_transaction wallet_api::set_contract(string accountname, string contract_dir, string contract_name, bool broadcast ) {
      signed_transaction tx;

      set_code_callback ( accountname, contract_dir, contract_name, tx );
      set_abi_callback ( accountname, contract_dir, contract_name, tx );
      std::cout << "Publishing contract..." << std::endl;
      tx.validate();
      
      return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::set_code(string accountname, string contract_dir, string contract_name, bool broadcast ) {
      signed_transaction tx;

      set_code_callback ( accountname, contract_dir, contract_name, tx );
      std::cout << "Publishing contract code..." << std::endl;
      tx.validate();
      
      return my->sign_transaction( tx, broadcast );
}

annotated_signed_transaction wallet_api::set_abi(string accountname, string contract_dir, string contract_name, bool broadcast ) {
      signed_transaction tx;

      set_abi_callback ( accountname, contract_dir, contract_name, tx );
      std::cout << "Publishing contract abi..." << std::endl;
      tx.validate();
      
      return my->sign_transaction( tx, broadcast );
}

message_body wallet_api::try_decrypt_message( const message_api_obj& mo ) {
   message_body result;

   fc::sha512 shared_secret;

   auto it = my->_keys.find(mo.from_memo_key);
   if( it == my->_keys.end() )
   {
      it = my->_keys.find(mo.to_memo_key);
      if( it == my->_keys.end() )
      {
         wlog( "unable to find keys" );
         return result;
      }
      auto priv_key = wif_to_key( it->second );
      if( !priv_key ) return result;
      shared_secret = priv_key->get_shared_secret( mo.from_memo_key );
   } else {
      auto priv_key = wif_to_key( it->second );
      if( !priv_key ) return result;
      shared_secret = priv_key->get_shared_secret( mo.to_memo_key );
   }


   fc::sha512::encoder enc;
   fc::raw::pack( enc, mo.sent_time );
   fc::raw::pack( enc, shared_secret );
   auto encrypt_key = enc.result();

   uint32_t check = fc::sha256::hash( encrypt_key )._hash[0];

   if( mo.checksum != check )
      return result;

   auto decrypt_data = fc::aes_decrypt( encrypt_key, mo.encrypted_message );
   try {
      return fc::raw::unpack<message_body>( decrypt_data );
   } catch ( ... ) {
      return result;
   }
}

void wallet_api::set_code_callback( string accountname, string contract_dir, string contract_name, signed_transaction& tx ) {
      std::string wast;
      fc::path cpath(contract_dir);

      if( cpath.filename().generic_string() == "." ) cpath = cpath.parent_path();

      auto wastPath = (cpath / (cpath.filename().generic_string()+".wasm")).generic_string();
      if (!fc::exists(wastPath))
            wastPath = (cpath / (cpath.filename().generic_string()+".wast")).generic_string();

      std::cout << "Reading WAST/WASM from " + wastPath + "..." << std::endl;
      fc::read_file_contents(wastPath, wast);
      FC_ASSERT( !wast.empty(), "no wast file found ${f}", ("f", wastPath) );
      vector<uint8_t> wasm;
      const string binary_wasm_header("\x00\x61\x73\x6d", 4);
      
      if(wast.compare(0, 4, binary_wasm_header) == 0) {
            std::cout << "Using already assembled WASM..." << std::endl;
            wasm = vector<uint8_t>(wast.begin(), wast.end());
      }
      else {
            std::cout << "Assembling WASM..." << std::endl;
            wasm = wast_to_wasm(wast);
      }

      bytes bytes_wasm;
      uint8_t compression = 0;

      if(wasm.size() > MAX_UNCOMPRESSION_SIZE){
        std::string uncompressed(wasm.begin(), wasm.end());
        std::string compressed = fc::zlib_compress(uncompressed);
        compression = 1;
        bytes_wasm = bytes(compressed.begin(), compressed.end());
    }
    else {
         bytes_wasm = bytes( wasm.begin(), wasm.end());
    }
      
      tx.operations.push_back ( vm_operation ( accountname, 
                                               setcode { contract_name, 
                                                         0, 
                                                         0, 
                                                         compression,
                                                         bytes_wasm
                                                       } 
                                             ) 
                              );
}

void wallet_api::set_abi_callback( string accountname, string contract_dir, string contract_name, signed_transaction& tx ) {
      fc::path cpath(contract_dir);
      if( cpath.filename().generic_string() == "." ) 
            cpath = cpath.parent_path();

      auto abiPath = (cpath / (cpath.filename().generic_string()+".abi")).generic_string();

      FC_ASSERT( fc::exists( abiPath ), "no abi file found ${f}", ("f", abiPath)  );

      auto abi = fc::raw::pack ( fc::json::from_file(abiPath).as<abi_def>() );

      uint8_t compression = 0;

      if(abi.size() > MAX_UNCOMPRESSION_SIZE){
          std::string uncompressed(abi.begin(), abi.end());
          std::string compressed = fc::zlib_compress(uncompressed);
          compression = 1;
          abi = bytes(compressed.begin(), compressed.end());
      }

      try {
            tx.operations.push_back ( vm_operation ( accountname, 
                                                     setabi { contract_name, 
                                                              compression,
                                                              abi
                                                            } 
                                                   ) 
                                    );
      } EOS_RETHROW_EXCEPTIONS(abi_type_exception,  "Fail to parse ABI JSON")
}

} } // contento::wallet

