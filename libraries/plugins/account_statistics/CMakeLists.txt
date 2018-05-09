file(GLOB HEADERS "include/contento/account_statistics/*.hpp")

add_library( contento_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
             ${HEADERS} 
           )

target_link_libraries( contento_account_statistics contento_chain contento_protocol contento_app )
target_include_directories( contento_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)