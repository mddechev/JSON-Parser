#ifndef _JSON_VALUE_HPP_
#define _JSON_VALUE_HPP_

#include <cstddef>
#include <iostream>
#include "../utility/String.hpp"
#include "../utility//Vector.hpp"
#include "../JSONException.hpp"

class JSONValue {
public:
    virtual ~JSONValue() = default;
    
    virtual String toString() const = 0;

    virtual JSONValue* clone() const = 0;

    virtual void print(std::ostream& outputStream = std::cout, size_t indent = 0) const = 0; 

    virtual void search(const String& key, Vector<JSONValue*>& searchResultsArray) const;

    virtual void set(const Vector<String>& path, JSONValue* const value);

    virtual void create(const Vector<String>& path, JSONValue* const value);

    virtual void remove(const Vector<String>& path);

    virtual bool contains(const String& value) const = 0;
    
protected:
    static void printIndent(std::ostream& outputStream, size_t indent);
};

#endif //_JSON_VALUE_HPP_