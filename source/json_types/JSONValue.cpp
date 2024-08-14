#include "../../includes/json_types/JSONValue.hpp"
#include "JSONException.hpp"

void JSONValue::search(const String &key, Vector<JSONValue*>& searchResultsArray) const {}

void JSONValue::set(const Vector<String> &path, JSONValue *const value) {
    InvalidPathError();
}

void JSONValue::create(const Vector<String> &path, JSONValue *const value) {
    throw InvalidPathError();
}

void JSONValue::remove(const Vector<String> &path) {
    throw InvalidPathError();
}

bool JSONValue::contains(const String &value) const {
    return false;
}

// void JSONValue::move(const Vector<String> &fromPath, const Vector<String> toPath) {
//     throw InvalidPathError();
// }

void JSONValue::printIndent(std::ostream& outputStream, size_t indent) {
    for (size_t i = 0; i < indent; i++) {
        outputStream << "  ";
    }
}