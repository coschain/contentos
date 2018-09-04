/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once

#include <cosiolib/types.h>
#include <cosiolib/asset.hpp>

extern "C" {
   /**
    * return contract's balance
    * @return contract's balance
    */
   void get_contract_balance_internal(const cosio::asset& ast);

    /**
     * transfer contract's balance to account
     * @param account : balance receiver
     * @param value : amount to transfer
     */
    void take_out( account_name* account, const cosio::asset& value);

    /**
     * get caller's value that want to give to contract
     * @return caller's value
     */
   int64_t get_value_internal();
 
    /**
     * check if caller bring value, it's will cause a assert fall if caller bring value
     */
    void pay_prohibited();

   ///@ } chaincapi
}
