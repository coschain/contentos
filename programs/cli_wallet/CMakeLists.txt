add_executable( cli_wallet main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling cli_wallet with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( CONTENTOS_STATIC_BUILD )
   # I don't know why contento_app is required twice in the following line, I just know the linker breaks if it isn't.
   target_link_libraries( cli_wallet PRIVATE
                          "-static-libstdc++ -static-libgcc -lreadline"
                          contento_app graphene_net contento_chain contento_protocol graphene_utilities contento_wallet contento_private_message contento_app contento_follow fc ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )
else( CONTENTOS_STATIC_BUILD )
   target_link_libraries( cli_wallet PRIVATE
                          contento_app graphene_net contento_chain contento_protocol graphene_utilities contento_wallet contento_private_message contento_app contento_follow fc ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )
endif( CONTENTOS_STATIC_BUILD )

if(MSVC)
  set_source_files_properties( main.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   cli_wallet

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
