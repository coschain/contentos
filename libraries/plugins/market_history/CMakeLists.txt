file(GLOB HEADERS "include/contento/market_history/*.hpp")

add_library( steemit_market_history
             market_history_plugin.cpp
             market_history_api.cpp
             ${HEADERS} 
           )

target_link_libraries( steemit_market_history steemit_chain steemit_protocol steemit_app )
target_include_directories( steemit_market_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   steemit_market_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)