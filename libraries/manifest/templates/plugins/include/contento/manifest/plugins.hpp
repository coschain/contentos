
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace contento { namespace app {

class abstract_plugin;
class application;

} }

namespace contento { namespace plugin {

void initialize_plugin_factories();
std::shared_ptr< contento::app::abstract_plugin > create_plugin( const std::string& name, contento::app::application* app );
std::vector< std::string > get_available_plugins();

} }
