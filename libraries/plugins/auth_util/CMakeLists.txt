file(GLOB HEADERS "include/contento/plugins/auth_util/*.hpp")

add_library( contento_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( contento_auth_util contento_app contento_chain contento_protocol fc )
target_include_directories( contento_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
