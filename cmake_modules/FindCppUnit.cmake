set(CPPUNIT_ROOT_DIR
    "${CPPUNIT_ROOT_DIR}"
    CACHE
    PATH
    "Directory to search")

find_library(CPPUNIT_LIBRARY_RELEASE
    NAMES
    cppunit
    HINTS
    "${CPPUNIT_ROOT_DIR}")

find_library(CPPUNIT_LIBRARY_DEBUG
    NAMES
    cppunitd
    HINTS
    "${CPPUNIT_ROOT_DIR}")

include(SelectLibraryConfigurations)
select_library_configurations(CPPUNIT)

# Might want to look close to the library first for the includes.
get_filename_component(_libdir "${CPPUNIT_LIBRARY_RELEASE}" PATH)

find_path(CPPUNIT_INCLUDE_DIR
    NAMES
    cppunit/TestCase.h
    HINTS
    "${_libdir}/.."
    PATHS
    "${CPPUNIT_ROOT_DIR}"
    PATH_SUFFIXES
    include/)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cppunit
    DEFAULT_MSG
    CPPUNIT_LIBRARY
    CPPUNIT_INCLUDE_DIR)

if(CPPUNIT_FOUND)
    set(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
    set(CPPUNIT_INCLUDE_DIRS "${CPPUNIT_INCLUDE_DIR}")
    mark_as_advanced(CPPUNIT_ROOT_DIR)
endif()

mark_as_advanced(CPPUNIT_INCLUDE_DIR
    CPPUNIT_LIBRARY_RELEASE
    CPPUNIT_LIBRARY_DEBUG)
