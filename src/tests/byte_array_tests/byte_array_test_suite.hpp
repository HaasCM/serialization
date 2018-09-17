/*!
    \file byte_array_test_suite.hpp
    \brief File to define the ByteArrayTestSuite class
*/

#ifndef BYTE_ARRAY_TEST_SUITE
#define BYTE_ARRAY_TEST_SUITE

#include <cppunit/extensions/HelperMacros.h>

#include "byte_array.hpp"

/*!
    \brief Class to describe the behavior and execution of Unit Tests

    This class handles the execution of Unit Tests for the ByteArray class
*/
class ByteArrayTestSuite : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ByteArrayTestSuite);

    CPPUNIT_TEST(test_defaultConstructor);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_copyConstructor);
    CPPUNIT_TEST(test_append);
    CPPUNIT_TEST(test_at);
    CPPUNIT_TEST(test_back);
    CPPUNIT_TEST(test_front);
    CPPUNIT_TEST(test_iterators);
    CPPUNIT_TEST(test_data);
    CPPUNIT_TEST(test_empty);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_operators);

    CPPUNIT_TEST_SUITE_END();

public:
    ByteArrayTestSuite();
    ~ByteArrayTestSuite() = default;

private:
    void test_defaultConstructor();
    void test_constructor();
    void test_copyConstructor();
    void test_append();
    void test_at();
    void test_back();
    void test_front();
    void test_iterators();
    void test_data();
    void test_empty();
    void test_size();
    void test_operators();
};

#endif
