file(GLOB HEADERS "include/contento/tags/*.hpp")

add_library( contento_tags
             tags_plugin.cpp
             ${HEADERS} )

target_link_libraries( contento_tags contento_chain contento_protocol contento_app )
target_include_directories( contento_tags
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_tags

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
