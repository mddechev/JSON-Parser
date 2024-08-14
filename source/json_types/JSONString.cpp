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
    if (value[0] == DOUBLE_QUOTE || value[value.Length() - 2] == DOUBLE_QUOTE) {
        outputStream << value;
        return;
    }
    outputStream << DOUBLE_QUOTE << value << DOUBLE_QUOTE;
}       

bool JSONString::contains(const String &value) const {
    return this->value.Contains(value);
}
