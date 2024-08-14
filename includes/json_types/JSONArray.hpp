#pragma once

#ifndef _JSON_ARRAY_HPP_
#define _JSON_ARRAY_HPP_

#include "../json_types/JSONValue.hpp"

class JSONArray: public JSONValue {
public:
    JSONArray() = default;
    JSONArray(const JSONArray& other);
    ~JSONArray() noexcept override;

    JSONArray& operator=(const JSONArray& other);

    String toString() const override;

    JSONValue * clone() const override;

    void print(std::ostream &outputStream = std::cout, size_t indent = 0) const override;

    void search(const String &key, Vector<JSONValue *> &searchResultsArray) const override;

    void set(const Vector<String> &path, JSONValue *const value) override;

    void create(const Vector<String> &path, JSONValue *const value) override;

    void remove(const Vector<String> &path) override;

    bool contains(const String &value) const override;

public:
    Vector<JSONValue*>& getValues() { return values; }
    const Vector<JSONValue*>& getValues() const { return values; }

    void addValue(JSONValue* const value);
    void removeValue(size_t index);

    void setValue(size_t index, JSONValue* const value);

    const JSONValue* const getValue(size_t index) const;
    JSONValue* getValue(size_t index);

private:
    void copy(const JSONArray& other);
    void free();
    
private:
    Vector<JSONValue*> values;
};

#endif //_JSON_ARRAY_HPP_