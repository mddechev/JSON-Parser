#pragma once

#ifndef _JSON_NUMBER_HPP_
#define _JSON_NUMBER_HPP_

#include "../json_types/JSONValue.hpp"

class JSONNumber: public JSONValue {
public:
    explicit JSONNumber(double value);

    String toString() const override;

    JSONValue * clone() const override;

    void print(std::ostream &outputStream = std::cout, size_t indent = 0) const override;

    bool contains(const String &value) const override;
    
private:
    double value;
};

#endif //_JSON_NUMBER_HPP_