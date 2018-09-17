/*!
    \file byte_array_test_suite.cpp
    \brief File to define the implementation of the ByteArrayTestSuite
*/

#include "byte_array_test_suite.hpp"
#include "common.hpp"

/*!
    \brief Default constructor for the Byte Array unit test class
*/
ByteArrayTestSuite::ByteArrayTestSuite() = default;

/*!
    \brief tests the implementation of the ByteArray default constructor

    Constructors an empty byte array, and makes sure that the safety checks
    work for the class.
*/
void ByteArrayTestSuite::test_defaultConstructor() {
    ByteArray array;

    CPPUNIT_ASSERT(array.empty());
    CPPUNIT_ASSERT(array.size() == 0);
    CPPUNIT_ASSERT(array.begin() == array.end());
    CPPUNIT_ASSERT(array.cbegin() == array.cend());
}

/*!
    \brief Tests the implementation of specialized constructors

    Tests char/size constructor for proper implementation and
    tests the char pointer size constructor
*/
void ByteArrayTestSuite::test_constructor() {
    const char* testData = "0000";

    const int TEST_SIZE = 4;
    ByteArray array(testData, TEST_SIZE * sizeof(char));
    CPPUNIT_ASSERT(!array.empty());
    CPPUNIT_ASSERT(array.size() == TEST_SIZE);
    CPPUNIT_ASSERT(array.end() - array.begin() == TEST_SIZE);
}


/*!
    \brief Unit test to test the functionality of the copy constructor
*/
void ByteArrayTestSuite::test_copyConstructor() {
    const char* testData = "1234";

    const int TEST_SIZE = 4;
    ByteArray array(testData, TEST_SIZE * sizeof(char));

    ByteArray copy(array);

    CPPUNIT_ASSERT(!array.empty() && !copy.empty());
    CPPUNIT_ASSERT(array.size() == TEST_SIZE && copy.size() == TEST_SIZE);
    CPPUNIT_ASSERT(array.end() - array.begin() == TEST_SIZE &&
                   copy.end() - copy.begin() == TEST_SIZE);

    auto copyIter = copy.begin();
    auto arrayIter = array.begin();
    while(copyIter != copy.end() && arrayIter != array.end()) {
        CPPUNIT_ASSERT((*copyIter) == (*arrayIter));
        copyIter++;
        arrayIter++;
    }
}

void ByteArrayTestSuite::test_append()
{

}

void ByteArrayTestSuite::test_at()
{

}

void ByteArrayTestSuite::test_back()
{

}

void ByteArrayTestSuite::test_front()
{

}

void ByteArrayTestSuite::test_iterators()
{

}

void ByteArrayTestSuite::test_data()
{

}

void ByteArrayTestSuite::test_empty()
{

}

void ByteArrayTestSuite::test_size()
{

}

void ByteArrayTestSuite::test_operators()
{

}

MAINLESS_TEST(ByteArrayTestSuite)
