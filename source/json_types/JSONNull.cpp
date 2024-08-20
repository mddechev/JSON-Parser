#include "../../includes/json_types/JSONNull.hpp"

const String JSONNull::value = "null";

void JSONNull::print(std::ostream &outputStream, size_t indent) const {
    outputStream << JSONNull::value;
}

String JSONNull::toString() const {
    return value;
}

JSONValue* JSONNull::clone() const {
    return new JSONNull();
}

bool JSONNull::contains(const String &value) const {
    return value == "null";
}