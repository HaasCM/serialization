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
    s << value;
    for(const auto &byte : ba) {
        std::cout << byte <<std::endl;
    }

    uint8_t second = 0;
    s >> second;
    std::cout << static_cast<short>(second) << std::endl;

    auto future = std::async(std::launch::async, getUserInput);
    while(true) {

        if(future.wait_for(std::chrono::seconds(0)) ==
           std::future_status::ready) {
            auto response = future.get();
            future = std::async(std::launch::async, getUserInput);
            std::cout << "Response : " << response << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //std::this_thread::yield();
    }

    return 0;
}
