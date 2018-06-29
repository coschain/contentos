set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON)

add_executable( etest main.cpp )
target_link_libraries( etest eosio_chain eosio_testing eos_utilities fc ${PLATFORM_SPECIFIC_LIBS} )
target_include_directories( etest PUBLIC 
                            ${CMAKE_SOURCE_DIR}/libraries/eos-testing/include
                            ${CMAKE_CURRENT_BINARY_DIR}/include
                            )

install( TARGETS
   etest

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
