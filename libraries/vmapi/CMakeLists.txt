file(GLOB HEADERS "include/contento/vmapi/*.hpp")

add_library( contento_vmapi
             contento_vm_api.cpp
             ${HEADERS}
           )

target_link_libraries( contento_vmapi contento_chain contento_protocol fc contento_app )
target_include_directories( contento_vmapi
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

INSTALL( FILES ${HEADERS} DESTINATION "include/contento/vmapi" )
