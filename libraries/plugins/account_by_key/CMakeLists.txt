file(GLOB HEADERS "include/contento/account_by_key/*.hpp")

add_library( contento_account_by_key
             account_by_key_plugin.cpp
             account_by_key_api.cpp
             ${HEADERS}
           )

target_link_libraries( contento_account_by_key contento_chain contento_protocol contento_app )
target_include_directories( contento_account_by_key
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_account_by_key

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
