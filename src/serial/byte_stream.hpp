/*!
    \file byte_stream.hpp
    \brief File to define the ByteStream class
*/

#ifndef BYTE_STREAM_HPP
#define BYTE_STREAM_HPP

#include <cstdint>

class ByteArray; // forward declare ByteArray

/*!
    \brief Class to handle binary streams to and from ByteArrays
*/
class ByteStream {
    enum class OpenMode {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    enum class ByteOrder {
        BigEndian,
        LittleEndian
    };


    enum class Status {
        Ok,
        ReadPastEnd,
        ReadCorruptData,
        WriteFailed
    };

    ByteStream();
    ByteStream(ByteArray *array, OpenMode mode);

    ~ByteStream();

    bool atEnd() const;

    ByteArray* device() const;
    void setDevice(ByteArray *array, OpenMode mode);

    void read(char *&buffer, uint32_t &count);

    ByteOrder order() const;
    void setByteOrder(ByteOrder bo);

    Status status() const;
    void setStatus(Status status);
    void resetStatus();

    int skipRawData(uint32_t length);

    void writeBytes(const char *s, uint32_t len);

    int writeRawData(const char *s, uint32_t len);

    void operator<<(uint8_t i);
    void operator<<(uint16_t i);
    void operator<<(uint32_t i);
    void operator<<(uint64_t i);
    void operator<<(int8_t i);
    void operator<<(int16_t i);
    void operator<<(int32_t i);
    void operator<<(int64_t i);

    void operator<<(bool b);

    void operator<<(const char *&s);

    void operator<<(float f);
    void operator<<(double d);

    void operator>>(uint8_t &i);
    void operator>>(uint16_t &i);
    void operator>>(uint32_t &i);
    void operator>>(uint64_t &i);
    void operator>>(int8_t &i);
    void operator>>(int16_t &i);
    void operator>>(int32_t &i);
    void operator>>(int64_t &i);

    void operator>>(bool &b);

    void operator>>(const char *&s);

    void operator>>(float &f);
    void operator>>(double &d);

private:
    void checkOpenMode() const;

    ByteArray *mArray;
    OpenMode mMode;
    ByteOrder mOrder;
    Status mStatus;


};
#endif //BYTE_STREAM_HPP
