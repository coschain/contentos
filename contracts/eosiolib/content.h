/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/types.h>
  
extern "C" {

  int on_content_call(const char* ptr, size_t length, char* dst, size_t bufLen);
  
}
