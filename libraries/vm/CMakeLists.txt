configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/contento/chain/core_symbol.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/core_symbol.hpp)

file(GLOB HEADERS "include/contento/chain/*.hpp"
                  "include/contento/chain/contracts/*.hpp"
                  "${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/core_symbol.hpp" )

#set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -stdlib=libc++ -Wall -Wno-conversion" )

## SORT .cpp by most likely to change / break compile
add_library( vm
             merkle.cpp
             name.cpp
             contento_contract.cpp
             contento_contract_abi.cpp
             chain_id_type.cpp

              wast_to_wasm.cpp
              wasm_interface.cpp
              wasm_contento_validation.cpp
              wasm_contento_injection.cpp
              apply_context.cpp
              abi_serializer.cpp
              asset.cpp

             webassembly/wavm.cpp
             webassembly/binaryen.cpp

             ${HEADERS}
             )

target_link_libraries( vm graphene_utilities fc chainbase Logging IR WAST WASM Runtime
      wasm asmjs passes cfg ast emscripten-optimizer support softfloat builtins
                     )
target_include_directories( vm
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" 
                                   "${CMAKE_CURRENT_BINARY_DIR}/include"
                                   "${CMAKE_CURRENT_SOURCE_DIR}/../wasm-jit/Include"
                                   "${CMAKE_CURRENT_SOURCE_DIR}/../utilities/Include"
                                   "${CMAKE_CURRENT_SOURCE_DIR}/../../externals/binaryen/src"
                            )

set_target_properties( vm PROPERTIES PUBLIC_HEADER "${HEADERS}" )
install( TARGETS vm 
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib
)
#install_directory_permissions( DIRECTORY ${CMAKE_INSTALL_FULL_INCLUDEDIR}/contento/chain )
#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)
