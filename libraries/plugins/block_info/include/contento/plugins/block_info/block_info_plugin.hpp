
#pragma once

#include <contento/app/plugin.hpp>
#include <contento/plugins/block_info/block_info.hpp>

#include <string>
#include <vector>

namespace contento { namespace protocol {
struct signed_block;
} }

namespace contento { namespace plugin { namespace block_info {

using contento::app::application;

class block_info_plugin : public contento::app::plugin
{
   public:
      block_info_plugin( application* app );
      virtual ~block_info_plugin();

      virtual std::string plugin_name()const override;
      virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;

      void on_applied_block( const chain::signed_block& b );

      std::vector< block_info > _block_info;

      boost::signals2::scoped_connection _applied_block_conn;
};

} } }
