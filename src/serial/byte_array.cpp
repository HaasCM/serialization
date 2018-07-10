/*!
    \brief file to implement the ByteArray class
*/
#include "byte_array.hpp"
#include <cstring>


/*!
    \brief Default constructor for the ByteArray

    Generates an empty ByteArray
*/
ByteArray::ByteArray()
: mData(std::vector<char>()){
    setExtents();
}

/*!
    \brief Creates a ByteArray from the data at *data, and reads in size bytes

    The ByteArray will not take ownership of the data at *data, it will make
    a copy of that data.

    \param data the pointer to the data
    \param size the amount of data to copy
*/
ByteArray::ByteArray(const char* data, int size)
: mData(std::vector<char>(data, data+size)){
    setExtents();
}

/*!
    \brief Generates a ByteArray of size and fills it with ch
    \param size the size of the Array
    \param ch the default value to set
*/
ByteArray::ByteArray(int size, char ch)
: mData(std::vector<char>(static_cast<unsigned long>(size), ch)){
    setExtents();
}

/*!
    \brief Copy constructor for the ByteArray
    \param other the ByteArray to copy
*/
ByteArray::ByteArray(const ByteArray& other)
: mData(other.mData){
    setExtents();
}

/*!
    \brief Appends a ByteArray to this byte array
    \param array the array to append to this one
*/
void ByteArray::append(const ByteArray& array) {
    mData.insert(mData.end(), array.mData.begin(), array.mData.end());
    setExtents();
}

/*!
    \brief Appends ch to this array count times
    \param count the amount of ch's to append
    \param ch the value to append
*/
void ByteArray::append(int count, char ch) {
    for(int i = 0; i < count; i++) {
        mData.push_back(ch);
    }
    setExtents();
}

/*!
    \brief Appends the data to this array
    \param data
*/
void ByteArray::append(const char* data) {
    mData.insert(mData.end(), data, data + strlen(data));
    setExtents();
}

/*!
    \brief Appends the size data at char to the ByteArray
    \param data the data to be appended
    \param size the size of the data to append
*/
void ByteArray::append(const char* data, int size) {
    mData.insert(mData.end(), data, data + size);
    setExtents();
}

/*!
    \brief Gets the data at index
    \param i the index of the data to retrieve
    \return a copy of the char at the index
*/
char ByteArray::at(int i) const {
    return mData[static_cast<std::vector<char>::size_type>(i)];
}

/*!
    \brief Returns a copy of the last element in the array
    \return the last element in the array
*/
char ByteArray::back() const {
    return mData.back();
}

/*!
    \brief Returns a copy of the first element in the array
    \return returns a copy of the first element in the array
*/
char ByteArray::front() const {
    return mData.front();
}

/*!
    \brief Returns an iterator at the front of the array
    \return an iterator at the front
*/
ByteArray::iterator ByteArray::begin() {
    return mData.begin();
}

/*!
    \brief Returns an iterator at the end of the array
    \return Returns an iterator a the end of the array
*/
ByteArray::iterator ByteArray::end() {
    return mData.end();
}

/*!
  \brief returns an iterator to the begining of the function that is const
  \return a const iterator at the begining
*/
ByteArray::const_iterator ByteArray::begin() const {
    return mData.cbegin();
}

/*!
    \brief Returns a iterator to the end of the array which is const
    \return returns a const iterator at the end
*/
ByteArray::const_iterator ByteArray::end() const {
    return mData.cend();
}

/*!
    \brief Returns an iterator to the begining of the array which is const
    \return returns a const iterator to the begining of the array
*/
ByteArray::const_iterator ByteArray::cbegin() {
    return mData.cbegin();
}

/*!
 * \brief Returns an iterator to the end of hte array which is const
 * \return returns a const iterator at the end of the array
 */
ByteArray::const_iterator ByteArray::cend() {
    return mData.cend();
}

/*!
    \brief If the vector is not empty it returns a pointer to the first element

    otherwise it returns a nullptr

    \return a pointer to the first element if full
*/
const char*ByteArray::constData() {
    if(!mData.empty()) {
        return mData.data();
    }
    return nullptr;
}

/*!
  \brief Checks the size of the array and returns a pointer to the first element
  \return returns a pointer to the first element if full
*/
char*ByteArray::data() {
    if(!mData.empty()) {
        return mData.data();
    }

    return nullptr;
}

/*!
    \brief Returns the size of the array
    \return Returns the size of the array
*/
int ByteArray::size() const {
    return static_cast<int>(mData.size());
}

bool ByteArray::empty() const {
    return mData.empty();
}

/*!
 * \brief ByteArray::operator []
 * \param idx
 * \return
 */
char& ByteArray::operator[](int idx) {
    return mData[static_cast<std::vector<char>::size_type>(idx)];
}

/*!
 * \brief ByteArray::operator []
 * \param idx
 * \return
 */
char ByteArray::operator[](int idx) const {
    return mData[static_cast<std::vector<char>::size_type>(idx)];
}

void ByteArray::setExtents() {
    setg(mData.data(), mData.data(), mData.data() + mData.size());
}

/*!
    \brief Default destructor for the ByteArray class
*/
ByteArray::~ByteArray() = default;


