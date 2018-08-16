/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */

#include <cosiolib/cosio.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      COSLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
