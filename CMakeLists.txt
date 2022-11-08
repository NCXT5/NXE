cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(nxe)
enable_testing()

function(nxe_add_library NXE_LIBRARY_NAME)
    # Add library
    file(GLOB_RECURSE NXE_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/lib/*.cc)
    file(GLOB_RECURSE NXE_LIBRARY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/lib/*.h)

    add_library(${PROJECT_NAME}_${NXE_LIBRARY_NAME} ${NXE_LIBRARY_SOURCES} ${NXE_LIBRARY_HEADERS})
    add_library(${PROJECT_NAME}::${NXE_LIBRARY_NAME} ALIAS ${PROJECT_NAME}_${NXE_LIBRARY_NAME})
    target_include_directories(${PROJECT_NAME}_${NXE_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/include)

    # Set linker properties
    set_target_properties(${PROJECT_NAME}_${NXE_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

    # Code generation
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/include/${PROJECT_NAME}/${NXE_LIBRARY_NAME}.h "#pragma once\n")

    # Recursively write all includes
    function(nxe_add_library_write_include NXE_LIBRARY_NAME NXE_LIBRARY_INCLUDE_PATH)
        file(GLOB_RECURSE NXE_LIBRARY_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/lib/${NXE_LIBRARY_INCLUDE_PATH}/*.h)
        foreach(NXE_LIBRARY_INCLUDE_FILE ${NXE_LIBRARY_INCLUDE_FILES})
            file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/include/${PROJECT_NAME}/${NXE_LIBRARY_NAME}.h "\n#include \"${NXE_LIBRARY_INCLUDE_FILE}\"")
        endforeach()
    endfunction()

    nxe_add_library_write_include(${NXE_LIBRARY_NAME} "")

    # Install
    install(TARGETS ${PROJECT_NAME}_${NXE_LIBRARY_NAME} DESTINATION lib)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/include/ DESTINATION include)

    # Add tests
    file(GLOB_RECURSE NXE_LIBRARY_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/${NXE_LIBRARY_NAME}/test/*.cc)

    foreach(NXE_LIBRARY_TEST ${NXE_LIBRARY_TESTS})
        get_filename_component(NXE_LIBRARY_TEST_NAME ${NXE_LIBRARY_TEST} NAME_WE)
        add_executable(${PROJECT_NAME}_${NXE_LIBRARY_NAME}_${NXE_LIBRARY_TEST_NAME} ${NXE_LIBRARY_TEST})
        target_link_libraries(${PROJECT_NAME}_${NXE_LIBRARY_NAME}_${NXE_LIBRARY_TEST_NAME} ${PROJECT_NAME}::${NXE_LIBRARY_NAME})
        add_test(${PROJECT_NAME}_${NXE_LIBRARY_NAME}_${NXE_LIBRARY_TEST_NAME} ${PROJECT_NAME}_${NXE_LIBRARY_NAME}_${NXE_LIBRARY_TEST_NAME})
    endforeach()
endfunction()

nxe_add_library(util)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME}_dev ${CMAKE_CURRENT_SOURCE_DIR}/dev/main.cc)
    target_link_libraries(${PROJECT_NAME}_dev ${PROJECT_NAME}::util)
endif()
