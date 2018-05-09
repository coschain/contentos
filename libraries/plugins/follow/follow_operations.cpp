#include <steemit/follow/follow_operations.hpp>

#include <steemit/protocol/operation_util_impl.hpp>

namespace contento { namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } //contento::follow

DEFINE_OPERATION_TYPE( contento::follow::follow_plugin_operation )
