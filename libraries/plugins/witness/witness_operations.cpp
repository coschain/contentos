#include <contento/witness/witness_operations.hpp>

#include <contento/protocol/operation_util_impl.hpp>

namespace contento { namespace witness {

void enable_content_editing_operation::validate()const
{
   chain::validate_account_name( account );
}

} } // contento::witness

DEFINE_OPERATION_TYPE( contento::witness::witness_plugin_operation )
