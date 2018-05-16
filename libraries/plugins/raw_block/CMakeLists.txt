file(GLOB HEADERS "include/contento/plugins/raw_block/*.hpp")

add_library( contento_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( contento_raw_block contento_app contento_chain contento_protocol fc )
target_include_directories( contento_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
