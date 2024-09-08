#include "../../includes/json_types/JSONString.hpp"
#include "../../includes/utility/Constants.hpp"

JSONString::JSONString(const String& value)
    :value(value) {}

String JSONString::toString() const {
    return value;
}

JSONValue* JSONString::clone() const {
    return new JSONString(*this);
}

void JSONString::print(std::ostream &outputStream, size_t indent) const {
    // if (value[0] != '\"' && value[value.Length() - 2] != '\"') {
    //     outputStream << '\"' << value << '\"';
    //     return;
    // }
    outputStream << value;
}       

bool JSONString::contains(const String &value) const {
    return this->value.Contains(value);
}
