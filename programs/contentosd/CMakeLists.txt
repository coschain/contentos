add_executable( contentosd main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling contentosd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( CONTENTOS_STATIC_BUILD )
   target_link_libraries( contentosd PRIVATE
      "-static-libstdc++ -static-libgcc"
      contento_plugins
      contento_mf_plugins
      contento_app
      contento_witness
      contento_account_history
      contento_chain
      contento_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( CONTENTOS_STATIC_BUILD )
   target_link_libraries( contentosd PRIVATE
      contento_plugins
      contento_mf_plugins
      contento_app
      contento_witness
      contento_account_history
      contento_chain
      contento_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( CONTENTOS_STATIC_BUILD )

install( TARGETS
   contentosd

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
