/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <cosiolib/types.h>

/**
 *  @defgroup chainapi Chain API
 *  @brief Define API for querying internal chain state
 *  @ingroup contractdev
 */

extern "C" {
   /**
    * return contract's balance
    * @return contract's balance
    */
   int64_t get_contract_balance();

    /**
     * transfer contract's balance to name's account
     * @param name : balance receiver
     * @param value : amount to transfer
     */
   void transfer( account_name name, int64_t value );

    /**
     * get caller's value that want to give to contract
     * @return caller's value
     */
   int64_t get_value();
 
    /**
     * check if caller bring value, it's will cause a assert fall if caller bring value
     */
    void pay_prohibited();

   ///@ } chaincapi
}
