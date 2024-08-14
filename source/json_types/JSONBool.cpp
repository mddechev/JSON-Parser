#include "../../includes/json_types/JSONBool.hpp"

JSONBool::JSONBool(bool value)
    :value(value) {}

String JSONBool::toString() const {
    return value ? String("true") : String("false");
}

JSONValue* JSONBool::clone() const {
    return new JSONBool(*this);
}

void JSONBool::print(std::ostream &outputStream, size_t indent) const {
    outputStream << (value ? "true" : "false");
}

bool JSONBool::contains(const String &value) const {
    return this->toString() == value;
}
