/*!
    \file byte_stream.cpp
    \brief file to add implementation of the ByteStream class
*/
#include "byte_stream.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <cstring>

#ifdef LINUX
    #include <endian.h>
#endif

#ifdef WIN32
    #include "stdlib.h"
#endif

#ifdef MACOS
    #include <endian.h>
#endif
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

/*!
    \brief Returns the open mode of the ByteStream
    \return the open mode of the byte stream
*/
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
    if(mArray && mode() != OpenMode::ReadOnly) {
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

/*!
    \brief Returns the status of the byte stream

    Statuses
    Ok - Status is ok
    ReadPastEnd - ByteStream tried to read past the buffer
    WriteFailed - Write to the buffer failed

    \return returns thr status of the byte stream
*/
ByteStream::Status ByteStream::status() const {
    return mStatus;
}

/*!
    \brief Function which allows the user/developer to set the status
    \param status the desired status to set the stream to
*/
void ByteStream::setStatus(ByteStream::Status status) {
    mStatus = status;
}

/*!
    \brief Function used to reset the status of the stream
 */
void ByteStream::resetStatus() {
    mStatus = Status::Ok;
}

/*!
    \brief Function to skip length number of bytes
    \param length the length of bytes to skip over
    \return returns the length of bytes skipped
*/
uint32_t ByteStream::skipRawData(uint32_t length) {
    if(moveWillStayInBounds(length)) {
        mIter += length;
        return length;
    } else {
        return 0;
    }
}

/*!
    \brief Function which writes len bytes from the buffer s into the device
    \param s the buffer to write bytes from
    \param len the number of bytes to write
 */
void ByteStream::writeBytes(const char* s, uint64_t len) {
    if(!s || mode() == OpenMode::ReadOnly || status() != Status::Ok) {
        return;
    }

    if(moveWillStayInBounds(len)) {
        std::copy(s, s+len, mIter);
    }
}

/*!
    \brief Function to read in raw data into the stream with length len
    \param s the char* to read in
    \param len the length of bytes to read in
    \return returns the number of bytes read in
*/
int ByteStream::writeRawData(const char* s, uint32_t len) {
    if(!s || mode() == OpenMode::ReadOnly || status() != Status::Ok) {
        return -1;
    } else if(moveWillStayInBounds(len)) {
        std::copy(s,s+len, mIter);
        mIter += len;
        return static_cast<int>(len);
    } else {
        return -1;
    }
}

/*!
    \brief Function to read raw data from the string
    \param s the char* to read into
    \param len the length of bytes to read
    \return returns the number of bytes read
 */
int ByteStream::readRawData(char *s, uint32_t len) {
    if(!s || mode() == OpenMode::WriteOnly || status() != Status::Ok) {
        return -1;
    } else if(moveWillStayInBounds(len)) {
        std::copy(mIter, mIter + len, s);
        mIter += len;
        return static_cast<int>(len);
    } else {
        return -1;
    }
}

/*!
    \brief Operator to write a uint8_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(uint8_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a uint16_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(uint16_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a uint32_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(uint32_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a uint64_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(uint64_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a int8_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(int8_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a int16_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(int16_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a int32_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(int32_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a int64_t into the device
    \param i the values to write into
*/
void ByteStream::operator<<(int64_t i) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

/*!
    \brief Operator to write a boolean into the device
    \param i the values to write into
*/
void ByteStream::operator<<(bool b) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(b))) {
        std::copy(&b, &b+sizeof(b), mIter);
        mIter += sizeof(b);
    }
}

/*!
    \brief Operator to write a char* which is null ended into the device
    \param The buffer to write in
*/
void ByteStream::operator<<(const char*& s) {
    assert(!isReadOnly());

    writeBytes(s, strlen(s));
}

/*!
    \brief Writes a floating point number to the stream using IEEE 754
    \param f the float to read in
*/
void ByteStream::operator<<(float f) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(int32_t))) {
        std::copy(&f, &f+sizeof(f), mIter);
        mIter += sizeof(f);
    }
}

/*!
    \brief Writes a floating point number to the stream using IEEE 754
    \param d the double to read in
*/
void ByteStream::operator<<(double d) {
    assert(!isReadOnly());

    if(moveWillStayInBounds(sizeof(int64_t))) {
        std::copy(&d, &d+sizeof(d), mIter);
        mIter += sizeof(d);
    }
}

/*!
    \brief Reads a uint8_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(uint8_t& i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a uint16_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(uint16_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a uint32_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(uint32_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a uint64_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(uint64_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a int8_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(int8_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a int16_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(int16_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a int32_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(int32_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

/*!
    \brief Reads a int64_t from the stream into a value
    \param i the value to read into
*/
void ByteStream::operator>>(int64_t &i) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(mIter, mIter+sizeof(i), &i);
    }
}

void ByteStream::operator>>(bool &b) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(bool))) {
        std::copy(mIter, mIter+sizeof(bool), &b);
    }
}

void ByteStream::operator>>(const char *&s) {

}

void ByteStream::operator>>(float &f) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(int32_t))) {
        std::copy(mIter, mIter+sizeof(int32_t), &f);
    }
}

void ByteStream::operator>>(double &d) {
    assert(!isWriteOnly());

    if(moveWillStayInBounds(sizeof(int64_t))) {
        std::copy(mIter, mIter+sizeof(int64_t), &d);
    }
}

/*!
    \brief Checks to see if the iterator move will stay in bounds
    \param move the moves to make with the iterator
    \return true if it will stay in bounds, otherwise false
*/
bool ByteStream::moveWillStayInBounds(const uint64_t move) {
    if(!mArray) {
        return false;
    }


    if(move > std::numeric_limits<int64_t>::max()) {
        return false;
    }

    if(mIter + static_cast<int64_t>(move) <= mArray->end() && mStatus == Status::Ok) {
        return true;
    } else {
        mStatus = Status::ReadWritePastEnd;
        return false;
    }
}

/*!
    \brief Function to return if the steam is read only of the Byte Stream
    \return true if read only, otherwise false
*/
bool ByteStream::isReadOnly() const {
    return mMode == OpenMode::ReadOnly;
}

/*!
    \brief Function to return if the steam is write only of the Byte Stream
    \return true if write only, otherwise false
*/
bool ByteStream::isWriteOnly() const {
    return mMode == OpenMode::WriteOnly;
}

template<typename T>
T ByteStream::toBigEndian(T value) {
    switch(sizeof(T)) {
        case 1:

        case 2:
            #ifdef LINUX
            return htobe16(value);
            #endif
        case 3:
            #ifdef LINUX
            return htobe32(value);
            #endif
        case 4:
            #ifdef LINUX
            return htobe64(value);
            #endif
    }
}

template<typename T>
T ByteStream::toLitteEndian(T value){
    switch(sizeof(T)) {
        case 1:

        case 2:
            #ifdef LINUX
            return htole16(value);
            #endif
        case 3:
            #ifdef LINUX
            return htole32(value);
            #endif
        case 4:
            #ifdef LINUX
            return htole64(value);
            #endif
    }
}
