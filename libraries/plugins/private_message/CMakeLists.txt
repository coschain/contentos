file(GLOB HEADERS "include/contento/private_message/*.hpp")

add_library( contento_private_message
             private_message_plugin.cpp
             ${HEADERS}
           )

target_link_libraries( contento_private_message contento_chain contento_protocol contento_app )
target_include_directories( contento_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
