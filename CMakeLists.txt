# Defines Contentos library target.
project( cosiocc )
cmake_minimum_required( VERSION 3.12 )

include( GNUInstallDirs )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version must DB at least 4.8!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
        message(FATAL_ERROR "Clang version must be at least 3.3!")
    endif()
endif()


list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")


include( InstallDirectoryPermissions )
include( wasm )

MESSAGE( STATUS "BUILD_CONTENTOS_TOOLCHAIN" )

FIND_PACKAGE(Boost 1.58 REQUIRED COMPONENTS ${BOOST_COMPONENTS})

if( WIN32 )
   message( STATUS "Configuring Contentos on WIN32")
   
else( WIN32 ) # Apple AND Linux

    if( APPLE )
        # Apple Specific Options Here

        message( STATUS "Configuring Contentos on OS X" )
        set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -stdlib=libc++ -Wall -Wno-conversion -Wno-deprecated-declarations" )
    else( APPLE )
        # Linux Specific Options Here

        message( STATUS "Configuring Contentos on Linux" )
        set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -Wall" )
        set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

    endif( APPLE )

    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
endif( WIN32 )

add_subdirectory( libraries )
add_subdirectory( programs )
add_subdirectory( contracts )
add_subdirectory( tools )

MESSAGE( STATUS "\n\n             CONFIGURED FOR COS TOOLCHAIN                \n\n" )



