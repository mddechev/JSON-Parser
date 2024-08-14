#pragma once

#ifndef _JSON_NULL_HPP_
#define _JSON_NULL_HPP_

#include "../json_types/JSONValue.hpp"

class JSONNull: public JSONValue {
public:
    JSONNull() = default;

    String toString() const override;

    JSONValue * clone() const override;

    void print(std::ostream &outputStream = std::cout, size_t indent = 0) const override;
        
    bool contains(const String &value) const override;
    
private:
    static const String value;
};

#endif //_JSON_NULL_HPP_


