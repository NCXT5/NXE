cmake_minimum_required(VERSION 3.2)
project(NCXT_Fenix)

include(lib/cmake/test.cmake)

set(NCXT_Fenix_VERSION_MAJOR 0)
set(NCXT_Fenix_VERSION_MINOR 1)
set(NCXT_Fenix_VERSION_PATCH 0)
set(NCXT_Fenix_VERSION ${NCXT_Fenix_VERSION_MAJOR}.${NCXT_Fenix_VERSION_MINOR}.${NCXT_Fenix_VERSION_PATCH})

file(GLOB_RECURSE NCXT_Fenix_IMPLS "lib/*.cxx")
file(GLOB_RECURSE NCXT_Fenix_HEADERS "include/*.hxx")

add_library(NCXT_Fenix_LIB ${NCXT_Fenix_IMPLS} ${NCXT_Fenix_HEADERS})

target_include_directories(NCXT_Fenix_LIB PUBLIC include)

set_target_properties(NCXT_Fenix_LIB PROPERTIES
    VERSION ${NCXT_Fenix_VERSION}
    SOVERSION ${NCXT_Fenix_VERSION_MAJOR}
    PUBLIC_HEADER "${NCXT_Fenix_HEADERS}"
    CXX_STANDARD 23
    LINKER_LANGUAGE CXX)

add_subdirectory(project/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_unit_test_dir(${CMAKE_CURRENT_SOURCE_DIR}/test)
