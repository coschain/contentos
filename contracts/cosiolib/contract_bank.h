/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <cosiolib/types.h>
#include <cosiolib/asset.hpp>

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
   void get_contract_balance(const cosio::asset& ast);

    /**
     * transfer contract's balance to name's account
     * @param account : balance receiver
     * @param value : amount to transfer
     */
    void transfer( account_name* account, const cosio::asset& value);

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