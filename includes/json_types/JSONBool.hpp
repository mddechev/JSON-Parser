#ifndef _JSON_BOOL_HPP_
#define _JSON_BOOL_HPP_

#include "../json_types/JSONValue.hpp"

class JSONBool: public JSONValue {
public:
    explicit JSONBool(bool value);

    String toString() const override;

    JSONValue * clone() const override;

    void print(std::ostream &outputStream = std::cout, size_t indent = 0) const override;

    bool contains(const String &value) const override;

private:
    bool value;
};

#endif //_JSON_BOOL_HPP_