cmake_minimum_required(VERSION 3.2)
project(serial C CXX)

if(NOT DEFINED PROJECT_ROOT_DIR)
    set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)
endif(NOT DEFINED PROJECT_ROOT_DIR)

include(${PROJECT_ROOT_DIR}/cmake_modules/uninstall.cmake)

if (WIN32)
    message("windows operating system")
    add_definitions(-DWIN32)
endif(WIN32)
if(UNIX AND NOT APPLE)
    message("Linux detected")
    add_definitions(-DLINUX)
endif(UNIX AND NOT APPLE)

if(UNIX AND APPLE)
    message("MACOS detected")
    add_definitions(-DMACOS)
endif(UNIX AND APPLE)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES byte_array.cpp byte_stream.cpp)
set(HEADER_FILES byte_array.hpp byte_stream.hpp)

add_library(serialstatic STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(serial SHARED ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(serialstatic PROPERTIES OUTPUT_NAME serial)

install(TARGETS serial DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/serial)
