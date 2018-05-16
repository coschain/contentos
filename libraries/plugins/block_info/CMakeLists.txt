file(GLOB HEADERS "include/contento/plugins/block_info/*.hpp")

add_library( contento_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( contento_block_info contento_app contento_chain contento_protocol fc )
target_include_directories( contento_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
