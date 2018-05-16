file(GLOB HEADERS "include/contento/delayed_node/*.hpp")

add_library( contento_delayed_node
             delayed_node_plugin.cpp
             ${HEADERS}
            )

target_link_libraries( contento_delayed_node contento_chain contento_protocol contento_app )
target_include_directories( contento_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   contento_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
