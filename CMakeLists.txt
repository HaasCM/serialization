cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(APP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/serial)

add_subdirectory(src)

find_package(Doxygen)

set(doxygen_infile ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.cfg)

add_custom_target(doc
                  COMMAND ${DOXYGEN_EXECUTABLE} ${doxygen_infile}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                  SOURCES ${doxygen_infile}
                  COMMENT "Generating Documentation with doxygen")
