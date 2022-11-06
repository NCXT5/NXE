cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NXE)

function(nxe_add_library NXE_LIBRARY_NAME)
    file(GLOB_RECURSE NXE_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/lib/*.cc)
    file(GLOB_RECURSE NXE_LIBRARY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/lib/*.h)

    add_library(${PROJECT_NAME}_${NXE_LIBRARY_NAME} ${NXE_LIBRARY_SOURCES} ${NXE_LIBRARY_HEADERS})
    add_library(${PROJECT_NAME}::${NXE_LIBRARY_NAME} ALIAS ${PROJECT_NAME}_${NXE_LIBRARY_NAME})
    target_include_directories(${PROJECT_NAME}_${NXE_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/include)
endfunction()

nxe_add_library(util)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME}_dev ${CMAKE_CURRENT_SOURCE_DIR}/dev/main.cc)
    target_link_libraries(${PROJECT_NAME}_dev ${PROJECT_NAME}::util)
endif()
