set(SOURCES main.cpp)
find_package(LLVM 4.0 REQUIRED CONFIG)

link_directories(${LLVM_LIBRARY_DIR})

add_executable(rpc_apigen ${SOURCES})

set( CMAKE_CXX_STANDARD 14 )

if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

target_link_libraries(rpc_apigen rpc_api_generator)

IF(NOT "$ENV{OPENSSL_ROOT_DIR}" STREQUAL "")
  set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR} )
  set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
ENDIF()

add_custom_target( build_content_vmapi_hpp ALL
COMMAND "${CMAKE_CURRENT_BINARY_DIR}/rpc_apigen"
  -extra-arg=-c -extra-arg=--std=c++14 -extra-arg=-D__GNUC__=4 -extra-arg=-D__x86_64__
  -extra-arg=-I${LLVM_INCLUDE_DIRS}/c++/v1/
  -extra-arg=-I${LLVM_LIBRARY_DIR}/clang/${LLVM_VERSION}/include
  -extra-arg=-I${OPENSSL_INCLUDE_DIR}
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/fc/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/chainbase/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/wasm-jit/Include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/softfloat/source/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/builtins/  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/externals/binaryen/src/ 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/app/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/chain/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/protocol/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/net/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/plugins/tags/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/plugins/witness/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/plugins/follow/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/vmapi/include  
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/utilities/include/ 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/wallet/include  
  -extra-arg=-I${CMAKE_BINARY_DIR}/libraries/chain/include 
  -extra-arg=-I${CMAKE_SOURCE_DIR}/libraries/plugins/private_message/include  
  -destination-file=${CMAKE_CURRENT_BINARY_DIR}/gen_rpc_api.json  
  -context=${CMAKE_SOURCE_DIR}/libraries  
  ${CMAKE_SOURCE_DIR}/libraries/app/include/contento/app/database_api.hpp
)

add_dependencies( build_content_vmapi_hpp rpc_apigen )

add_custom_target( gen_content_api ALL
COMMAND python
  ${CMAKE_CURRENT_SOURCE_DIR}/jsonapi2hpp.py
  ${CMAKE_CURRENT_BINARY_DIR}/gen_rpc_api.json 
  ${CMAKE_CURRENT_BINARY_DIR}/content.hpp  
)
add_dependencies( gen_content_api build_content_vmapi_hpp )


install( TARGETS
   rpc_apigen
   RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
   LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)
