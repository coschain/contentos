file(GLOB HEADERS "include/contento/market_history/*.hpp")

add_library( contento_market_history
             market_history_plugin.cpp
             market_history_api.cpp
             ${HEADERS} 
           )

target_link_libraries( contento_market_history contento_chain contento_protocol contento_app )
target_include_directories( contento_market_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_market_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)