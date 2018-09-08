cmake_minimum_required(VERSION 3.2)



if(NOT DEFINED PROJECT_ROOT_DIR)
    set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)
endif(NOT DEFINED PROJECT_ROOT_DIR)

include(${PROJECT_ROOT_DIR}/cmake_modules/uninstall.cmake)

add_subdirectory(byte_stream_tests)
add_subdirectory(byte_array_tests)
