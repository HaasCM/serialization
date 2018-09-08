cmake_minimum_required(VERSION 3.2)
project(serial_test)

if(NOT DEFINED PROJECT_ROOT_DIR)
    set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
endif(NOT DEFINED PROJECT_ROOT_DIR)

include(${PROJECT_ROOT_DIR}/cmake_modules/uninstall.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_subdirectory(serial)
include_directories(include)
include_directories(serial)

find_package(Threads)

add_executable(serial_test ${SOURCE_FILES})
target_link_libraries(serial_test serial ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS serial_test DESTINATION bin)


