/*!
    \file byte_stream.cpp
    \brief file to add implementation of the ByteStream class
*/
#include "byte_stream.hpp"
#include <algorithm>
#include <cassert>
#include <cstring>

/*!
    \brief Default constructor for the ByteStream class

    This initializes a ByteStream class without a device to read or write to
*/
ByteStream::ByteStream() :
mArray(nullptr),
mMode(OpenMode::ReadWrite),
mOrder(ByteOrder::BigEndian),
mStatus(Status::Ok){

}

/*!
    \brief Constructs a ByteStream that operates on a ByteArray array.
    \param array The ByteArray to operate on
    \param mode The mode to read or write from the byte array on
*/
ByteStream::ByteStream(ByteArray* array, ByteStream::OpenMode mode) :
mArray(array),
mMode(mode),
mOrder(ByteOrder::BigEndian),
mStatus(Status::Ok),
mIter(mArray->begin()){

}

/*!
    \brief Default destructor for the ByteStream class

    Since we do not take ownership of the byte array we don't reallocate.
*/
ByteStream::~ByteStream() = default;

/*!
    \brief Returns true if the buffer iterator has reached the end, or if there
    is no buffer at all; otherwise this function returns false
    \return returns true if at the end
*/
bool ByteStream::atEnd() const {
    if(!mArray || mIter == mArray->end()) {
        return false;
    } else {
        return true;
    }
}

/*!
    \brief Returns a pointer to the array, if there is no array returns nullptr
    \return returns pointer to the attached array
*/
ByteArray*ByteStream::device() const {
    // Even though just a return mArray would work here, this reads better
    if(mArray) {
        return mArray;
    } else {
        return nullptr;
    }
}

ByteStream::OpenMode ByteStream::mode() const {
    return mMode;
}

/*!
    \brief Sets the current device using the current open mode
    \param array the array to set to
*/
void ByteStream::setDevice(ByteArray* array) {
    mArray = array;
    mIter = mArray->begin();
    resetStatus();
}

/*!
    \brief Sets the current array to array
    \param array the array to set the stream to
    \param mode the open mode for the device
*/
void ByteStream::setDevice(ByteArray* array, ByteStream::OpenMode mode) {
    this->setDevice(array);
    mMode = mode;
}

/*!
    \brief Reads from the stream into buffer and sets count to the size read
    \param buffer the buffer to allocate and read into
    \param count the count that was read
 */
void ByteStream::read(char*& buffer, uint32_t& count) {
    if(mArray) {
        // Verify that we allocate the out parameter
        if(buffer) {
            delete[] buffer;
        }

        count = static_cast<uint32_t>(mArray->size());
        buffer = new char[count];

        std::copy(mArray->begin(), mArray->end(), buffer);
    } else {
        count = 0;
        buffer = nullptr;
    }
}

/*!
    \brief Returns the byteorder for the stream
    \return the byte order for the stream
*/
ByteStream::ByteOrder ByteStream::order() const {
    return mOrder;
}

/*!
    \brief Sets the current ByteOrder to bo
    \param bo the byte order to set to
*/
void ByteStream::setByteOrder(ByteStream::ByteOrder bo) {
    mOrder = bo;
}

ByteStream::Status ByteStream::status() const
{

}

void ByteStream::setStatus(ByteStream::Status status)
{

}

void ByteStream::resetStatus()
{

}

int ByteStream::skipRawData(uint32_t length)
{

}

void ByteStream::writeBytes(const char* s, uint32_t len)
{

}

int ByteStream::writeRawData(const char* s, uint32_t len)
{

}
