#pragma once

#ifndef _JSON_STRING_HPP_
#define _JSON_STRING_HPP_

#include "../json_types/JSONValue.hpp"

class JSONString: public JSONValue {
public:
    JSONString(const String& value);

    String toString() const override;

    JSONValue * clone() const override;

    void print(std::ostream &outputStream = std::cout, size_t indent = 0) const override;

    bool contains(const String &value) const override;

private:
    String value;
};

#endif //_JSON_STRING_HPP_