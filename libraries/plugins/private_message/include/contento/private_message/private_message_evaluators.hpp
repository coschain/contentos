#pragma once

#include <contento/chain/evaluator.hpp>

#include <contento/private_message/private_message_operations.hpp>
#include <contento/private_message/private_message_plugin.hpp>

namespace contento { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, contento::private_message::private_message_plugin_operation, private_message )

} }
