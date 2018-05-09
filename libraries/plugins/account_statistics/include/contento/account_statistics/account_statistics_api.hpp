#pragma once

#include <steemit/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace contento{ namespace app {
   struct api_context;
} }

namespace contento { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const contento::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // contento::account_statistics

FC_API( contento::account_statistics::account_statistics_api, )