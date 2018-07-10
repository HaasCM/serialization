cmake_minimum_required(VERSION 3.2)
project(serial C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES byte_array.cpp byte_stream.cpp)
set(HEADER_FILES byte_array.hpp byte_stream.hpp)

add_library(serialstatic STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(serial SHARED ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(serialstatic PROPERTIES OUTPUT_NAME serial)

install(TARGETS serial DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/serial)
