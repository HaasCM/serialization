cmake_minimum_required(VERSION 3.2)


if(NOT DEFINED PROJECT_ROOT_DIR)
    set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/../../..)
endif(NOT DEFINED PROJECT_ROOT_DIR)

if(TARGET serialstatic)
    message("-- Serialization Module already exists")
elseif(EXISTS ${PROJECT_ROOT_DIR}/src/serial/CMakeLists.txt)
    add_subdirectory(${PROJECT_ROOT_DIR}/src/serial serial)
    if(TARGET serialstatic)
        message("-- Found Serialization Module after adding subdirectory")
    else()
        message("-- Could not find the Serialization Module!")
    endif()
else()
endif()

find_path(SERIALIZATION_DIR
    NAMES byte_array.hpp
    HINTS "${PROJECT_ROOT_DIR}/src/serial/"
    PATHS "${PROJECT_ROOT_DIR}/src/serial/")

include_directories(${SERIALIZATION_DIR})

include(${PROJECT_ROOT_DIR}/cmake_modules/uninstall.cmake)

set(CMAKE_MODULE_PATH ${PROJECT_ROOT_DIR}/cmake_modules/)
FIND_PACKAGE(CppUnit REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../common)

set(SOURCE_FILES byte_array_test_suite.cpp)

set(HEADER_FILES byte_array_test_suite.hpp ../common/common.hpp)

add_executable(test_byte_array ${SOURCE_FILES} ${HEADER_FILES})

include_directories(${CPPUNIT_INCLUDE_DIRS})

target_link_libraries(test_byte_array ${CPPUNIT_LIBRARIES})
target_link_libraries(test_byte_array serialstatic)

install(TARGETS test_byte_array DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/unit_tests)
