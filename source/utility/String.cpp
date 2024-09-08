#include "../../includes/utility//String.hpp"
#include <sstream>
#include <stdexcept>
#include <new>

String::String()
    :capacity(INITIAL_CAPACITY), size(INITIAL_SIZE) {
   
    AllocateByCapacity(capacity);
}

String::String(size_t capacity)
    : size(INITIAL_SIZE) {

    AllocateByCapacity(capacity);
    
}

String::String(const char* src) {
   try {
        AllocateAndCopy(src);
   } catch (const std::invalid_argument& e) {
        Free();
        throw;
   }
}

String::String(const String& other) {
    
    Copy(other);
}

String::String(String&& other) noexcept {
    Move(std::move(other));
}

String::~String() {
    Free();
}

String& String::operator=(const String& other) {
    if (this != &other) {
        Free();
        Copy(other);
    }
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        Free();
        Move(std::move(other));
    }
    return *this;
}

String& String::operator+=(const String& other) {
    if (this->size + other.size + 1 > this->capacity) {
        Resize((this->size + other.size + 1) * INCREMENT_STEP);
    }
    strcat(this->data, other.data);
    this->size += other.size;
    return *this;
}

String& String::operator+=(char const *other) {
    size_t tempLen = strlen(other);
    if (this->size + tempLen > this->capacity) {
        Resize((this->size + tempLen) * INCREMENT_STEP);
    }
    strcat(this->data, other);
    this->size += tempLen;
    return *this;
}

String& String::operator+=(char const other) {
    if (this->size + 2 > this->capacity) {
        Resize(this->capacity * INCREMENT_STEP);
    }
    this->data[this->size++] = other;
    this->data[this->size] = '\0';
    return *this;
}

String String::operator+(const String& other) {
    String result(*this);
    result += other;
    return result;
}


String String::operator+(const char* other) {
    String result(*this);
    result += other;
    return result;
}

String String::operator+(const char other) {
    String result(*this);
    result += other;
    return result;
}

String operator+(const char* str, const String& other) {
    String result(str);
    result += other;
    return result;
}

char& String::operator[](const size_t position) {
    if (position >= size) {
        throw std::out_of_range("Position out of range");
    }
    return data[position];
}

const char& String::operator[](const size_t position) const {
    if (position >= size) {
        throw std::out_of_range("Position out of range");
    }
    return data[position];
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, String& str) {
    char ch;
    while(is.get(ch)) {
        if (ch == ' ' || ch == '\n') {
            break;
        }
        str += ch;
    }
    return is;
}

bool String::operator>(const String& other) const {
    return strcmp(this->data, other.data) > 0;
}

bool String::operator>(const char* other) const {
    return strcmp(this->data, other) > 0;
}

bool operator>(const char* other, const String& str) {
    return strcmp(other, str.data) > 0;
}

bool String::operator>=(const String& other) const {
    return !(*this < other);
}

bool String::operator>=(const char* other) const {
    return !(*this < other);
}

bool String::operator<(const String& other) const {
    return other > *this;
}

bool String::operator<(const char* other) const {
    return other > *this;
}

bool String::operator<=(const String& other) const {
    return !(*this > other);
}

bool String::operator<=(const char* other) const {
    return !(*this > other);
}

bool String::operator==(const String& other) const {
    return *this >= other && *this <= other;
}

bool String::operator==(const char* other) const {
     return *this >= other && *this <= other;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator!=(const char* other) const {
    return !(*this == other);
}

bool String::IsEmpty() const {
    return size == 0;
}

void String::Clear() {
    Free();
    capacity = 0;
    size = 0;
    // if (data) {
    //     data[0] = '\0';
    // }
    // size = 0;
}

void String::Reuse() {
    if (data) {
        data[0] = '\0';
    }
    size = 0;
}

String String::Substr(size_t pos, int len) const {
    if (pos >= size) {
        throw std::out_of_range("Position out of range");
    }
    if (len == NPOS || pos + len > size) {
        len = size - pos;
    }
    char* substrData = new char[len + 1];
    strncpy(substrData, data + pos, len);
    substrData[len] = '\0';

    // String result(substrData);
    // delete[] substrData;

    return String(substrData);
}

bool String::Contains(const String& other) const {
    return strstr(this->data, other.data) != nullptr;
}

bool String::Contains(const char* other) const {
    return strstr(this->data, other) != nullptr;
}

void String::Resize(size_t newCapacity) {
    char* newData = new char[newCapacity];
    strcpy(newData, data);

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void String::AllocateByCapacity(size_t capacity) {
    this->data = new char[capacity];
   
    this->data[0] = '\0';
    this->capacity = capacity;
}

void String::AllocateAndCopy(const char* src) {
    if (!src) {
        throw std::invalid_argument("Source cannot be nullptr");
    }
    // size = strlen(src) + 1;
    size = strlen(src);
    capacity = (size + 1) * INCREMENT_STEP;
    // capacity = size * INCREMENT_STEP;
    data = new char[capacity];
    strcpy(data, src);
}


void String::Copy(const String& other) {
    this->data = new char[strlen(other.data) + 1];
    strcpy(this->data, other.data);
    
    this->capacity = other.capacity;
    this->size = other.size;
}

void String::Move(String&& other) noexcept {
    this->data = other.data;
    this->capacity = other.capacity;
    this->size = other.size;

    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

void String::Free() {
    delete[] data;
    this->data = nullptr;
}


InputStringStream::InputStringStream(const String& string)
    :std::istringstream(string.C_str()) {}