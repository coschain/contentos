file(GLOB HEADERS "include/contento/protocol/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( contento_protocol

             types.cpp
             authority.cpp
             chain_id_type.cpp
             operations.cpp
             sign_state.cpp
             operation_util_impl.cpp
             contento_operations.cpp
             transaction.cpp
             block.cpp
             asset.cpp
             version.cpp
             get_config.cpp

             ${HEADERS}
           )

target_link_libraries( contento_protocol fc )
target_include_directories( contento_protocol
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

INSTALL( TARGETS
   contento_protocol

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

INSTALL( FILES ${HEADERS} DESTINATION "include/contento/protocol" )
