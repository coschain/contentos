file(GLOB COMMON_SOURCES "common/*.cpp")

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling tests with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

file(GLOB UNIT_TESTS "tests/*.cpp")
add_executable( chain_test ${UNIT_TESTS} ${COMMON_SOURCES} )
target_link_libraries( chain_test chainbase contento_chain contento_protocol contento_app contento_account_history  contento_witness contento_debug_node fc ${PLATFORM_SPECIFIC_LIBS} )

#file(GLOB PLUGIN_TESTS "plugin_tests/*.cpp")
#add_executable( plugin_test ${PLUGIN_TESTS} ${COMMON_SOURCES} )
#target_link_libraries( plugin_test contento_chain contento_protocol contento_app contento_account_history  contento_witness contento_debug_node fc ${PLATFORM_SPECIFIC_LIBS} )

file(GLOB_RECURSE CONTENTO_TESTS "contento/*.cpp")
add_executable( contento_test ${CONTENTO_TESTS} ${COMMON_SOURCES} )
target_link_libraries( contento_test contento_chain contento_protocol contento_app contento_account_history  contento_witness contento_debug_node fc ${PLATFORM_SPECIFIC_LIBS} )

file(GLOB MIX_TESTS "mix/*.cpp")
add_executable( mix_test ${MIX_TESTS} ${COMMON_SOURCES} )
target_link_libraries( mix_test contento_chain contento_protocol contento_app contento_account_history  contento_witness contento_debug_node fc ${PLATFORM_SPECIFIC_LIBS} )

add_dependencies(contento_test hello storage)

if(MSVC)
  set_source_files_properties( tests/serialization_tests.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

#add_subdirectory( generate_empty_blocks )
