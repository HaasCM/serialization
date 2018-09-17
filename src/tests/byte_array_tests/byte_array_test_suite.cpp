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

/*!
  \brief Unit test to test the append interface functions
*/
void ByteArrayTestSuite::test_append() {
    std::vector<char> expected;
    std::string expected_raw = "12341234\0";
    for(const auto &value : expected_raw) {
        expected.push_back(value);
    }

    const char* testData = "1234\0";

    const int TEST_SIZE = 4;
    ByteArray array(testData, TEST_SIZE * sizeof(char));

    ByteArray copy(array);

    array.append(copy);

    auto checkArray = [&](ByteArray arrayToCheck) {
        auto expectedIter = expected.begin();
        auto arrayToCheckIter = arrayToCheck.begin();
        while(expectedIter != expected.end() && arrayToCheckIter != array.end()) {
            CPPUNIT_ASSERT((*expectedIter) == (*arrayToCheckIter));
            expectedIter++;
            arrayToCheckIter++;
        }
    };

    checkArray(array);

    ByteArray arrayTwo(testData, TEST_SIZE * sizeof(char));

    arrayTwo.append(testData, 4);

    checkArray(arrayTwo);

    ByteArray arrayThree(testData, TEST_SIZE * sizeof(char));

    arrayThree.append(testData);

    checkArray(arrayThree);

    ByteArray arrayFour(testData, TEST_SIZE * sizeof(char));

    arrayFour.append("1", 1);
    arrayFour.append("2", 1);
    arrayFour.append("3", 1);
    arrayFour.append("4", 1);
    arrayFour.append("\0", 1);

    checkArray(arrayFour);
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
