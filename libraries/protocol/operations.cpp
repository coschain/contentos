#include <steemit/protocol/operations.hpp>

#include <steemit/protocol/operation_util_impl.hpp>

namespace steemit { namespace protocol {

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

bool is_virtual_operation( const operation& op )
{
   return op.visit( is_vop_visitor() );
}

// indicate if the operation needs admin authority
bool is_admin_operation( const operation& op )
{
   return op.visit( is_admin_visitor() );
}

} } // steemit::protocol

DEFINE_OPERATION_TYPE( steemit::protocol::operation )
