#pragma once

#include <contento/chain/abi_serializer.hpp>
#include <contento/chain/account_object.hpp>
#include <contento/chain/wasm_interface.hpp>

namespace chainbase {
   class database;
}


namespace contento { namespace chain {
    class apply_context;
   struct controller_impl;
   //using chainbase::database;

   using apply_handler = std::function<void(apply_context&)>;

   ////class fork_database;

   class vm_content_api_interface {
   public:
      virtual std::vector<char> on_vm_request( const std::vector<char>& req_body ) = 0;
   };


   class controller {
      public:

         controller(chainbase::database &db);
         ~controller();

         void add_indices();
       bool is_producing_block() const;

         chainbase::database& db()const;

         const account_object&                 get_account( account_name n )const;
         const dynamic_global_property_object& get_global_properties() const;
         const time_point_sec head_block_time() const;
         const apply_handler* find_apply_handler( account_name contract, scope_name scope, action_name act )const;
         wasm_interface& get_wasm_interface();


         optional<abi_serializer> get_abi_serializer( account_name n )const {
            if( n.good() ) {
               try {
                  const auto& a = get_account( n );
                  abi_def abi;
                  if( abi_serializer::to_abi( a.abi, abi ))
                     return abi_serializer( abi );
               } FC_CAPTURE_AND_LOG((n))
            }
            return optional<abi_serializer>();
         }

         template<typename T>
         fc::variant to_variant_with_abi( const T& obj ) {
            fc::variant pretty_output;
            abi_serializer::to_variant( obj, pretty_output, [&]( account_name n ){ return get_abi_serializer( n ); });
            return pretty_output;
         }

         void set_vm_interface(vm_content_api_interface* ptr){
            _vm_interface = ptr;
         }

         vm_content_api_interface* get_vm_interface(){
            return _vm_interface;
         }

      private:
         vm_content_api_interface* _vm_interface;
         std::unique_ptr<controller_impl> my;

   };

} }  /// contento::chain
