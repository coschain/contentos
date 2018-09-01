file(GLOB HEADERS "include/contento/gas_estimate/*.hpp")

add_library( contento_gas_estimate
             contento_gas_estimate.cpp
             ${HEADERS}
           )

target_link_libraries( contento_gas_estimate contento_chain contento_protocol fc contento_app )
target_include_directories( contento_gas_estimate
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

INSTALL( FILES ${HEADERS} DESTINATION "include/contento/gas_estimate" )
