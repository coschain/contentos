/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/types.h>

/**
 *  @defgroup chainapi Chain API
 *  @brief Define API for querying internal chain state
 *  @ingroup contractdev
 */

extern "C" {
   /**
    * Return the set of active producers
    * @param producers - a pointer to an buffer of account_names
    * @param datalen - byte length of buffer, 0 to report required size
    * @return the number of bytes actually populated, or number of bytes that can be copied if datalen==0 passed
    *
    *  Example:
    *  @code
    *  account_name producers[21];
    *  uint32_t bytes_populated = (producers, sizeof(account_name)*21);
    *  @endcode
    */

   uint64_t get_contract_balance();

   void transfer(const account_name& name, int64_t value);

   int64_t get_value();

   ///@ } chaincapi
}
