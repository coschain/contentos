/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#pragma once

#include <cosiolib/types.h>
  
extern "C" {

  int on_content_call(const char* ptr, size_t length, char* dst, size_t bufLen);
  bool excute_operation(const char* ptr, size_t length);
}
