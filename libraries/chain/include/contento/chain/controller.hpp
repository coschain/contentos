#pragma once

#include <contento/chain/types.hpp>
#include <contento/chain/abi_serializer.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/wasm_interface.hpp>
#include <contento/protocol/operations.hpp>

namespace chainbase
{
   class database;
} // chainbase

namespace contento { namespace chain {
   class apply_context;
   class account_object;
   class contract_balance_object;
   struct controller_impl;
   using contento::protocol::operation;

   using apply_handler = std::function<void(apply_context&)>;

   class vm_content_api_interface {
   public:
      virtual std::vector<char> on_vm_request( const std::vector<char>& req_body ) = 0;
   };

   class transaction_context;
   class op_excute_callback {
   public:
      virtual bool execute_operation(const transaction_context& trx_context, const operation& op ) = 0;
   };


   class controller {
      public:

         controller(::chainbase::database &db);
         ~controller();

         void add_indices();
       bool is_producing_block() const;

         ::chainbase::database& db()const;

         const account_object&                 get_account( account_name n )const;
         void adjust_balance( const account_object& a, const asset& delta );
         void adjust_contract_balance( const account_object& a, account_name contract,const asset& delta );
         const dynamic_global_property_object& get_global_properties() const;
         const time_point_sec head_block_time() const;
         const apply_handler* find_apply_handler( account_name contract, scope_name scope, action_name act )const;
         wasm_interface& get_wasm_interface();


         optional<abi_serializer> get_abi_serializer( account_name n, account_name contract)const {
            if( n.good() ) {
               try {
                  const auto& a = get_account( n );
                  abi_def abi;
                  if( abi_serializer::to_abi( a.all_contract.get_abi(contract), abi ))
                     return abi_serializer( abi );
               } FC_CAPTURE_AND_LOG((n))
            }
            return optional<abi_serializer>();
         }

         template<typename T>
         fc::variant to_variant_with_abi( const T& obj ) {
            fc::variant pretty_output;
            abi_serializer::to_variant( obj, pretty_output, [&]( account_name n, account_name contract ){ return get_abi_serializer( n, contract ); });
            return pretty_output;
         }

         void set_vm_interface(vm_content_api_interface* ptr){
            _vm_interface = ptr;
         }

         vm_content_api_interface* get_vm_interface(){
            return _vm_interface;
         }

         void set_op_excute_callback(op_excute_callback* ptr){
            _vm_op_excutor = ptr;
         }

         op_excute_callback* get_op_excutor(){
            return _vm_op_excutor;
         }

      private:
         vm_content_api_interface*  _vm_interface;
         op_excute_callback*        _vm_op_excutor;
         std::unique_ptr<controller_impl> my;

   };

} }  /// contento::chain
