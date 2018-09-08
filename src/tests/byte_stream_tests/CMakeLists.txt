cmake_minimum_required(VERSION 3.2)


if(NOT DEFINED PROJECT_ROOT_DIR)
    set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/../../..)
endif(NOT DEFINED PROJECT_ROOT_DIR)

include(${PROJECT_ROOT_DIR}/cmake_modules/uninstall.cmake)

set(CMAKE_MODULE_PATH ${PROJECT_ROOT_DIR}/cmake_modules/)
FIND_PACKAGE(CppUnit REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp byte_stream_test_suite.cpp)

set(HEADER_FILES byte_stream_test_suite.hpp)

add_executable(test_byte_stream ${SOURCE_FILES} ${HEADER_FILES})

include_directories(${CPPUNIT_INCLUDE_DIRS})

target_link_libraries(test_byte_stream ${CPPUNIT_LIBRARIES})

install(TARGETS test_byte_stream DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/unit_tests)
