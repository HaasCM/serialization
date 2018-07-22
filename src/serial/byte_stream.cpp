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

uint32_t ByteStream::skipRawData(uint32_t length) {
    if(moveWillStayInBounds(length)) {
        mIter += length;
        return length;
    } else {
        return 0;
    }
}

void ByteStream::writeBytes(const char* s, uint64_t len) {
    if(!s || mode() == OpenMode::ReadOnly || status() != Status::Ok) {
        return;
    }

    if(moveWillStayInBounds(len)) {
        std::copy(s, s+len, mIter);
    }
}

int ByteStream::writeRawData(const char* s, uint32_t len) {
    if(!s || mode() == OpenMode::ReadOnly || status() != Status::Ok) {
        return -1;
    } else if(moveWillStayInBounds(len)) {
        std::copy(s,s+len, mIter);
        return static_cast<int>(len);
    } else {
        return -1;
    }
}

void ByteStream::operator<<(uint8_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(uint16_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(uint32_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(uint64_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(int8_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(int16_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(int32_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(int64_t i) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(i))) {
        std::copy(&i, &i+sizeof(i), mIter);
        mIter += sizeof(i);
    }
}

void ByteStream::operator<<(bool b) {
    assert(!isReadOnly());
    if(moveWillStayInBounds(sizeof(b))) {
        std::copy(&b, &b+sizeof(b), mIter);
        mIter += sizeof(b);
    }
}

void ByteStream::operator<<(const char*& s) {
    assert(!isReadOnly());

    writeBytes(s, strlen(s));
}

void ByteStream::operator<<(float f) {
    assert(!isReadOnly());
}

void ByteStream::operator<<(double d) {
    assert(!isReadOnly());
}

void ByteStream::operator>>(uint8_t& i) {
    std::copy(mArray->begin(), mArray->begin()+sizeof(i), &i);
}

bool ByteStream::moveWillStayInBounds(const uint64_t move) {
    if(!mArray) {
        return false;
    }

    if(mIter + move >= mArray->end() && mStatus == Status::Ok) {
        return true;
    } else {
        mStatus = Status::ReadWritePastEnd;
        return false;
    }
}

constexpr bool ByteStream::isReadOnly() const {
    return mMode == OpenMode::ReadOnly;
}

constexpr bool ByteStream::isWriteOnly() const {
    return mMode == OpenMode::WriteOnly;
}
