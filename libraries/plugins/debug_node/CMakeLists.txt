file(GLOB HEADERS "include/contento/plugins/debug_node/*.hpp")

add_library( contento_debug_node
             ${HEADERS}
             debug_node_plugin.cpp
             debug_node_api.cpp
           )

target_link_libraries( contento_debug_node contento_app contento_chain contento_protocol fc )
target_include_directories( contento_debug_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS contento_debug_node
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
       )
INSTALL( FILES ${HEADERS} DESTINATION "include/contento/plugins/debug_node" )
