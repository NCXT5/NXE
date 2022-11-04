project(NCXT_NXE)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE "${PROJECT_NAME}_SOURCE_FILES" "src/*.cxx")
file(GLOB_RECURSE "${PROJECT_NAME}_HEADER_FILES" "src/*.hxx")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})

include_directories(include)
