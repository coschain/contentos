add_executable( db_util main.cpp)


target_link_libraries( db_util PRIVATE
    dorothy
    ${CMAKE_DL_LIBS}
    ${PLATFORM_SPECIFIC_LIBS}
)

## target_include_directories( db_util PUBLIC
##     "/usr/local/include/hsql"
##    "${CMAKE_CURRENT_SOURCE_DIR}/include"
##)

install( TARGETS
   db_util
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)