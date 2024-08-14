#pragma once

#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <iostream>
#include <cstring> 
#include <sstream>

class String {
public:
    String();
    String(size_t capacity);
    String(const char* data);
    ~String();

    String(const String& other);
    String& operator=(const String& other);
    String(String&& other);
    String& operator=(String&& other);

    String& operator+=(const String& other);
    String& operator+=(char const *other);
    String& operator+=(char const other);

    String operator+(const String& other);
    String operator+(const char* other);
    String operator+(const char other);
    friend String operator+(const char* str, const String& other);

    char& operator[](const size_t position);
    const char& operator[](const size_t position) const;
    friend std::ostream& operator<<(std::ostream &os, const String& str);
    friend std::istream& operator>>(std::istream &is, String& str);
    bool operator>(const String& other) const;
    bool operator>(const char* other) const;
    friend bool operator>(const char* other, const String& str);
    bool operator>=(const String& str) const;
    bool operator>=(const char* other) const;
    bool operator<(const String& other) const;
    bool operator<(const char* other) const;
    bool operator<=(const String& other) const;
    bool operator<=(const char* other) const;

    bool operator==(const String& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const String& other) const;
    bool operator!=(const char* other) const;
    
    const char* C_str() const { return data; }
    size_t Length() const { return size; }
    bool IsEmpty() const;
    void Clear();
    void Reuse();
    String Substr(size_t pos = 0, int len = npos) const;

    bool Contains(const String& other) const;
    bool Contains(const char* other) const;

private:
    static const size_t INITIAL_CAPACITY = 4;
    static const size_t INITIAL_SIZE = 0;
    static const size_t INCREMENT_STEP = 2;
    static const int npos = -1;

private:
    void Resize(size_t newCapacity);
    void AllocateByCapacity(size_t capacity);
    void AllocateAndCopy(const char* dataToCopy);
    void Copy(const String& other);
    void Move(String&& other);
    void Free();

private:
    char* data;
    size_t capacity;
    size_t size;
};

class InputStringStream: public std::istringstream {
public:
    InputStringStream(const String& string);
};

#endif //_STRING_HPP_
