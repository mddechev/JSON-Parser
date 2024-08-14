#pragma once

#ifndef _JSON_KEY_PAIR_HPP_
#define _JSON_KEY_PAIR_HPP_

#include "../json_types/JSONValue.hpp"

class JSONKeyPair {
public:
    JSONKeyPair(const String& key, JSONValue* value);
    JSONKeyPair(const JSONKeyPair& other);
    ~JSONKeyPair();

    JSONKeyPair& operator=(const JSONKeyPair& other);

    JSONKeyPair* clone() const;

    void print(std::ostream& outputStream = std::cout, size_t indent = 0) const;

    void search(const String& key, Vector<JSONValue*>& searchResultsArray) const;

    void set(const Vector<String>& path, JSONValue* const value);

    void create(const Vector<String>& path, JSONValue* const value);

    void remove(const Vector<String>& path);

    bool contains(const String& value) const;

public:
    void setValue(JSONValue* value);
    void setKey(const String& key);

    const String& getKey() const { return key; }
    String& getKey() { return key;}
    
    const JSONValue* const getValue() const { return value; }
    JSONValue* getValue() { return value; }

private:
    static void printIndent(std::ostream& os, size_t indent);
    
private:
    void copy(const JSONKeyPair& other);
    void free();

private:
    String key;
    JSONValue* value;
};

#endif //_JSON_KEY_PAIR_HPP_