/*!
    \file common.hpp
    \brief file to define a mainless application for unit testing
*/

#include <string.h>
#include <getopt.h>
#include <cppunit/TestSuite.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/portability/Stream.h>
#include <cppunit/ui/text/TestRunner.h>

#define MAINLESS_TEST(Suite)\
\
void runTestsTextMode();\
void runTestsXMLMode();\
void runTests(CppUnit::TextUi::TestRunner &runner);\
\
void displayUsage(const char *name);\
void displayVersion(const char *name);\
\
void handleArguments(const int &argc, char* argv[]);\
\
int main(int argc, char* argv[]) {\
    if(argc > 1) {\
        handleArguments(argc, argv);\
    } else {\
        runTestsTextMode();\
    }\
\
}\
\
void handleArguments(const int &argc, char* argv[]) {\
    auto stringsAreEqual = [&](const char* first, const char* second) {\
        return strcmp(first, second) == 0;\
    };\
\
    if (argc > 2) {\
        std::cout << argc << " is an unexpected number of arguments!" << std::endl;\
        displayUsage(argv[0]);\
\
    } else {\
        if (stringsAreEqual(argv[1], "xml")) {\
            runTestsXMLMode();\
\
        } else if(stringsAreEqual(argv[1], "text")) {\
            runTestsTextMode();\
\
        } else if(stringsAreEqual(argv[1], "--help")||\
                  stringsAreEqual(argv[1], "-h")) {\
            displayUsage(argv[0]);\
\
        } else if(stringsAreEqual(argv[1], "--version")||\
                  stringsAreEqual(argv[1], "-v")){\
            displayVersion(argv[0]);\
\
        } else {\
            std::cout << std::endl << "Received unhandled argument " << argv[1]\
                      << "!" << std::endl << std::endl;\
\
            displayUsage(argv[0]);\
        }\
    }\
}\
\
void runTestsTextMode() {\
    CppUnit::TextUi::TestRunner runner;\
    runTests(runner);\
\
}\
\
void runTestsXMLMode() {\
    CppUnit::TextUi::TestRunner runner;\
    CppUnit::OFileStream file("result.xml");\
    CppUnit::XmlOutputter outputter(&runner.result(), file,\
                                    std::string("ISO-8859-1"));\
    runTests(runner);\
    outputter.write();\
}\
\
void runTests(CppUnit::TextUi::TestRunner& runner) {\
    runner.addTest(Suite::suite());\
    runner.run();\
}\
\
void displayUsage(const char *name) {\
    std::cout << "Usage: "<< name <<" [mode]" << std::endl;\
    std::cout << std::endl;\
    std::cout << name << " - Unit Test for Suite" << std::endl;\
    std::cout << std::endl;\
    std::cout << "Positional Arguements:" << std::endl;\
    std::cout << "[mode]: Mode for the unit test to be run in ['text', 'xml']" << std::endl;\
    std::cout << std::endl;\
    std::cout << "Optional Arguments:" << std::endl;\
    std::cout << "-h, --help            Displays this help menu." << std::endl;\
    std::cout << "-v, --version         Displays the version of the unit test" << std::endl;\
\
    return;\
}\
\
void displayVersion(const char *name) {\
    std::cout << name << " - V 0.0.1" << std::endl;\
}\
