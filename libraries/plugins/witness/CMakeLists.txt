file(GLOB HEADERS "include/contento/witness/*.hpp")

add_library( contento_witness
             witness_plugin.cpp
             witness_evaluators.cpp
             witness_operations.cpp
             ${HEADERS} 
           )

target_link_libraries( contento_witness contento_chain contento_protocol contento_app )
target_include_directories( contento_witness
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   contento_witness

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
