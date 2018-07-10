/*!
    \brief File to define the ByteArray class

*/

#ifndef BYTE_ARRAY_HPP
#define BYTE_ARRAY_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include <streambuf>


/*!
    \brief Class which wraps a std::vector for serialization containers
*/
class ByteArray : public std::streambuf {
public:
    typedef std::vector<char>::iterator iterator;
    typedef std::vector<char>::const_iterator const_iterator;

    ByteArray();
    ByteArray(const char* data, int size = -1);
    ByteArray(int size, char ch);
    ByteArray(const ByteArray &other);

    ~ByteArray();

    void append(const ByteArray &array);
    void append(int count, char ch);
    void append(const char* data);
    void append(const char* data, int size);

    char at(int i) const;
    char back() const;
    char front() const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin();
    const_iterator cend();

    const char* constData();
    char* data();

    int size() const;

    bool empty() const;

    char& operator[](int idx);
    char operator[](int idx) const;

protected:
    void setExtents();

private:
    std::vector<char> mData; //!< the serialized data

};

#endif // APP_HPP
