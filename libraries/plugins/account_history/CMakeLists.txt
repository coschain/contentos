file(GLOB HEADERS "include/contento/account_history/*.hpp")

add_library( contento_account_history
             account_history_plugin.cpp
           )

target_link_libraries( contento_account_history contento_chain contento_protocol contento_app )
target_include_directories( contento_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
