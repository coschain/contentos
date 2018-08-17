#include <contento/protocol/operations.hpp>

#include <contento/protocol/operation_util_impl.hpp>

namespace contento { namespace protocol {

struct is_market_op_visitor {
   typedef bool result_type;

   template<typename T>
   bool operator()( T&& v )const { return false; }
   bool operator()( const limit_order_create_operation& )const { return true; }
   bool operator()( const limit_order_cancel_operation& )const { return true; }
   bool operator()( const transfer_operation& )const { return true; }
   bool operator()( const transfer_to_vesting_operation& )const { return true; }
};

bool is_market_operation( const operation& op ) {
   return op.visit( is_market_op_visitor() );
}

struct is_vop_visitor
{
   typedef bool result_type;

   template< typename T >
   bool operator()( const T& v )const { return v.is_virtual(); }
};

struct is_admin_visitor
{
   typedef bool result_type;

   template< typename T >
   bool operator()( const T& v ) const { return false; }

   bool operator()( const comment_report_operation& op ) const
   {
      if( op.is_ack ) 
         return true;
      return false;
   }
};

struct is_vm_op_visitor {
   typedef bool result_type;

   template<typename T>
   bool operator()( T&& v )const { return false; }
   bool operator()( const vm_operation& )const { return true; }
};

bool is_virtual_operation( const operation& op )
{
   return op.visit( is_vop_visitor() );
}

// indicate if the operation needs admin authority
bool is_admin_operation( const operation& op )
{
   return op.visit( is_admin_visitor() );
}

bool is_vm_operation( const operation& op ){
   return op.visit( is_vm_op_visitor() );
}


} } // contento::protocol


DEFINE_OPERATION_TYPE( contento::protocol::operation )
