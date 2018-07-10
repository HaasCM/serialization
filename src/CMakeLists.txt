cmake_minimum_required(VERSION 3.2)
project(serial_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)

add_subdirectory(serial)
include_directories(include)
include_directories(serial)

add_executable(serial_test ${SOURCE_FILES})
target_link_libraries(serial_test serial)

install(TARGETS serial_test DESTINATION bin)


