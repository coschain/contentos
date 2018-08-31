#pragma once
#include <contento/protocol/operations.hpp>
#include <contento/protocol/sign_state.hpp>
#include <contento/protocol/types.hpp>

#include <numeric>

namespace contento { namespace protocol {
   struct signature_with_trx_hash {
         signature_with_trx_hash(digest_type d, signature_type sig) : _d(d), _sig(sig) {}

      friend bool operator < ( const signature_with_trx_hash& a, const signature_with_trx_hash& b ) {
        return a._d == b._d ? a._d < b._d : a._sig < b._sig ;
      }

         digest_type     _d;
         signature_type _sig;
   };

   extern flat_map<signature_with_trx_hash ,public_key_type> sig_to_key;

   struct transaction
   {
      uint16_t           ref_block_num    = 0;
      uint32_t           ref_block_prefix = 0;

      fc::time_point_sec expiration;

      vector<operation>  operations;
      extensions_type    extensions;

      digest_type         digest()const;
      transaction_id_type id()const;
      void                validate() const;
      digest_type         sig_digest( const chain_id_type& chain_id )const;

      void set_expiration( fc::time_point_sec expiration_time );
      void set_reference_block( const block_id_type& reference_block );

      vector<operation> extract_admin_ops () const
      {
         vector<operation> ret;
         for ( const auto& op : operations )
         {
            if( is_admin_operation(op) )
               ret.push_back(op);
         }
         return ret;
      }

      template<typename Visitor>
      vector<typename Visitor::result_type> visit( Visitor&& visitor )
      {
         vector<typename Visitor::result_type> results;
         for( auto& op : operations )
            results.push_back(op.visit( std::forward<Visitor>( visitor ) ));
         return results;
      }
      template<typename Visitor>
      vector<typename Visitor::result_type> visit( Visitor&& visitor )const
      {
         vector<typename Visitor::result_type> results;
         for( auto& op : operations )
            results.push_back(op.visit( std::forward<Visitor>( visitor ) ));
         return results;
      }

      void get_required_authorities( flat_set< account_name_type >& active,
                                     flat_set< account_name_type >& owner,
                                     flat_set< account_name_type >& posting,
                                     vector< authority >& other )const;
   };

   struct signed_transaction : public transaction
   {

      signed_transaction( const transaction& trx = transaction() )
         : transaction(trx){}

      const signature_type& sign( const private_key_type& key, const chain_id_type& chain_id );

      signature_type sign( const private_key_type& key, const chain_id_type& chain_id )const;

      set<public_key_type> get_required_signatures(
         const chain_id_type& chain_id,
         const flat_set<public_key_type>& available_keys,
         const authority_getter& get_active,
         const authority_getter& get_owner,
         const authority_getter& get_posting,
         uint32_t max_recursion = CONTENTO_MAX_SIG_CHECK_DEPTH
         )const;

      void verify_authority(
         const chain_id_type& chain_id,
         const authority_getter& get_active,
         const authority_getter& get_owner,
         const authority_getter& get_posting,
         uint32_t max_recursion = CONTENTO_MAX_SIG_CHECK_DEPTH )const;

      void verify_ops_authority(
                            const vector<operation>& ops,
                            const chain_id_type& chain_id,
                            const authority_getter& get_active,
                            const authority_getter& get_owner,
                            const authority_getter& get_posting,
                            uint32_t max_recursion = CONTENTO_MAX_SIG_CHECK_DEPTH )const;

      set<public_key_type> minimize_required_signatures(
         const chain_id_type& chain_id,
         const flat_set<public_key_type>& available_keys,
         const authority_getter& get_active,
         const authority_getter& get_owner,
         const authority_getter& get_posting,
         uint32_t max_recursion = CONTENTO_MAX_SIG_CHECK_DEPTH
         ) const;

      flat_set<public_key_type> get_signature_keys( const chain_id_type& chain_id )const;

      vector<signature_type> signatures;

      digest_type merkle_digest()const;

      void clear() { operations.clear(); signatures.clear(); }
   };

   struct transaction_invoice {
         uint32_t status = 200;
         uint64_t gas_usage = 0;
   };

   struct transaction_wrapper {
         signed_transaction sig_trx;
         transaction_invoice invoice;

         digest_type merkle_digest()const;
   };

   void verify_authority( const vector<operation>& ops, const flat_set<public_key_type>& sigs,
                          const authority_getter& get_active,
                          const authority_getter& get_owner,
                          const authority_getter& get_posting,
                          uint32_t max_recursion = CONTENTO_MAX_SIG_CHECK_DEPTH,
                          bool allow_committe = false,
                          const flat_set< account_name_type >& active_aprovals = flat_set< account_name_type >(),
                          const flat_set< account_name_type >& owner_aprovals = flat_set< account_name_type >(),
                          const flat_set< account_name_type >& posting_approvals = flat_set< account_name_type >());


   struct annotated_signed_transaction {
      annotated_signed_transaction(){}
      annotated_signed_transaction( const signed_transaction& trx ){
            sig_trx = trx;
      }

      transaction_id_type       transaction_id;
      uint32_t                  block_num = 0;
      uint32_t                  transaction_num = 0;

      signed_transaction        sig_trx;
      transaction_invoice       invoice;
   };


   /// @} transactions group

} } // contento::protocol

FC_REFLECT( contento::protocol::transaction, (ref_block_num)(ref_block_prefix)(expiration)(operations)(extensions) )
FC_REFLECT_DERIVED( contento::protocol::signed_transaction, (contento::protocol::transaction), (signatures) );

FC_REFLECT( contento::protocol::annotated_signed_transaction, (sig_trx)(invoice)(transaction_id)(block_num)(transaction_num) );

FC_REFLECT( contento::protocol::transaction_invoice, (status)(gas_usage) );
FC_REFLECT( contento::protocol::transaction_wrapper, (sig_trx)(invoice) );
