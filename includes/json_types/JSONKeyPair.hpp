#pragma once

#ifndef _JSON_KEY_PAIR_HPP_
#define _JSON_KEY_PAIR_HPP_

#include "../json_types/JSONValue.hpp"

class JSONKeyPair {
public:
    JSONKeyPair(const String& key, JSONValue* value);
    JSONKeyPair(const JSONKeyPair& other);
    JSONKeyPair(JSONKeyPair&& other) noexcept;
    ~JSONKeyPair();

    JSONKeyPair& operator=(const JSONKeyPair& other);
    JSONKeyPair& operator=(JSONKeyPair&& other) noexcept;
    
    void print(std::ostream& outputStream = std::cout, size_t indent = 0) const;

    void search(const String& key, Vector<JSONValue*>& searchResultsArray) const;

    void set(const Vector<String>& path, JSONValue* const value);

    void create(const Vector<String>& path, JSONValue* const value);

    void remove(const Vector<String>& path);

    bool contains(const String& value) const;

public:
    void setValue(JSONValue* value);

    const String& getKey() const { return key; }
    String& getKey() { return key;}

    const JSONValue* const getValue() const { return value; }
    JSONValue* getValue() { return value; }

private:
    static void printIndent(std::ostream& outputStream, size_t indent);
    
private:
    void copy(const JSONKeyPair& other);
    void move(JSONKeyPair&& other) noexcept; 
    void free();

private:
    String key;
    JSONValue* value;
};

#endif //_JSON_KEY_PAIR_HPP_