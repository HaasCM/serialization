/*!
    \brief File to implement the main function for the template project
*/

#include "byte_array.hpp"
#include "byte_stream.hpp"
#include <istream>
#include <ostream>

#include <chrono>
#include <iostream>
#include <future>
#include <string>
#include <thread>

std::string getUserInput() {
    std::string response;
    std::getline(std::cin, response);
    return response;
}

/*!
    \brief The main function for the template application
    \param argc the count of arguements, the size of argv
    \param argv an array of command line arguments for the template project
    \return an exit code for the application
 */
int main(int argc, const char* argv[]) {
    ByteArray ba(60, 0);
    std::cout << "Size: " << ba.size() << std::endl;
    ByteStream s(&ba, ByteStream::OpenMode::ReadWrite);
    uint8_t value(16);
    std::cout << "Value: " << static_cast<short>(value) << std::endl;
    ByteStream readStream(&ba, ByteStream::OpenMode::ReadWrite);
    readStream << value;
    uint8_t second = 0;
    s >> second;
    std::cout << static_cast<short>(second) << std::endl;

    return 0;
}
