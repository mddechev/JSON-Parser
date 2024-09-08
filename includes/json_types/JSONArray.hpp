#ifndef _JSON_ARRAY_HPP_
#define _JSON_ARRAY_HPP_

#include "../json_types/JSONValue.hpp"

class JSONArray: public JSONValue {
public:
    JSONArray() = default;
    JSONArray(const JSONArray& other);
    JSONArray(JSONArray&& other) noexcept;
    ~JSONArray() noexcept override;

    JSONArray& operator=(const JSONArray& other);
    JSONArray& operator=(JSONArray&& other) noexcept;

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
    
private:
    void copyFrom(const JSONArray& other);
    void moveFrom(JSONArray&& other) noexcept;
    void free();
    
private:
    Vector<JSONValue*> values;
};

#endif //_JSON_ARRAY_HPP_