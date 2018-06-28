add_executable( steemd main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling steemd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( STEEM_STATIC_BUILD )
   target_link_libraries( steemd PRIVATE
      "-static-libstdc++ -static-libgcc"
      contento_plugins
      contento_mf_plugins
      contento_app
      contento_witness
      contento_account_history
      contento_chain
      contento_protocol
      fc
      # wasm asmjs passes cfg ast support
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( STEEM_STATIC_BUILD )
   target_link_libraries( steemd PRIVATE
      contento_plugins
      contento_mf_plugins
      contento_app
      contento_witness
      contento_account_history
      contento_chain
      contento_protocol
      fc
      # wasm asmjs passes cfg ast support
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( STEEM_STATIC_BUILD )

target_include_directories( steemd
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../externals/binaryen/src"
                            )

install( TARGETS
   steemd

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
