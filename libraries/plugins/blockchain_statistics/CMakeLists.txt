file(GLOB HEADERS "include/contento/blockchain_statistics/*.hpp")

add_library( contento_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
             ${HEADERS} 
           )

target_link_libraries( contento_blockchain_statistics contento_chain contento_protocol contento_app )
target_include_directories( contento_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)