configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/contento/chain/core_symbol.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/core_symbol.hpp)

file(GLOB HEADERS "include/contento/chain/*.hpp" 
                  "include/contento/chain/util/*.hpp"
                  "include/contento/chain/contracts/*.hpp"
                  "${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/core_symbol.hpp" )

if( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/include/contento/chain/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND cat-parts "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
   add_dependencies( build_hardfork_hpp cat-parts )
else( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND "${CMAKE_SOURCE_DIR}/programs/build_helpers/cat_parts.py" "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
endif( MSVC )


set_source_files_properties( "${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/hardfork.hpp" PROPERTIES GENERATED TRUE )

## SORT .cpp by most likely to change / break compile
add_library( contento_chain

             # As database takes the longest to compile, start it first
             database.cpp
             controller.cpp
             fork_database.cpp
             witness_schedule.cpp

             contento_evaluator.cpp

             contento_objects.cpp
             shared_authority.cpp
             block_log.cpp

             util/reward.cpp

             merkle.cpp
             transaction_context.cpp
             contento_contract.cpp
             contento_contract_abi.cpp

              wast_to_wasm.cpp
              wasm_interface.cpp
              wasm_contento_validation.cpp
              wasm_contento_injection.cpp
              apply_context.cpp
              abi_serializer.cpp
              wasm_price.cpp

             webassembly/wavm.cpp
             webassembly/binaryen.cpp

             ${HEADERS}
             ${hardfork_hpp_file}
             "${CMAKE_CURRENT_BINARY_DIR}/include/contento/chain/hardfork.hpp"
           )

add_dependencies( contento_chain contento_protocol build_hardfork_hpp )
target_link_libraries( contento_chain contento_protocol fc chainbase graphene_schema ${PATCH_MERGE_LIB}
                       IR WAST WASM Runtime wasm asmjs passes cfg ast emscripten-optimizer support softfloat builtins )
target_include_directories( contento_chain
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" 
                            "${CMAKE_CURRENT_BINARY_DIR}/include"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../wasm-jit/Include"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../utilities/Include"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../../externals/binaryen/src" )

if(MSVC)
  set_source_files_properties( database.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   contento_chain

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/contento/chain" )
