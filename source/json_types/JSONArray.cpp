#include "../../includes/json_types/JSONArray.hpp"
#include "../../includes/utility/Constants.hpp"
#include "../../includes/json_types/JSONObject.hpp"
#include "JSONException.hpp"
#include "json_types/JSONValue.hpp"
#include "utility/Vector.hpp"
#include <cstddef>

JSONArray::JSONArray(const JSONArray& other) {
    copyFrom(other);
}

JSONArray::JSONArray(JSONArray&& other) noexcept {
    moveFrom(std::move(other));
}

JSONArray::~JSONArray() noexcept {
    free();
}

JSONArray& JSONArray::operator=(const JSONArray& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

JSONArray& JSONArray::operator=(JSONArray&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

String JSONArray::toString() const {
    String res = constants::ARRAY_OPENING_BRACKET;
    for (size_t i = 0; i < values.Size(); i++) {
        if (i > 0) {
            res += ", ";
        }
        res += values[i]->toString();
    }
    res += constants::ARRAY_CLOSING_BRACKET;
    return res;
}

JSONValue* JSONArray::clone() const {
    return new JSONArray(*this);
}

void JSONArray::print(std::ostream &outputStream, size_t indent) const {
    outputStream << constants::ARRAY_OPENING_BRACKET << '\n';
        for (size_t i = 0; i < values.Size(); ++i) {
            if (i > 0) {
                outputStream << ',' << '\n';
            }
            printIndent(outputStream, indent + 1);
            values[i]->print(outputStream, indent + 1);
        }
        outputStream << "\n";
        printIndent(outputStream, indent);
        outputStream << constants::ARRAY_CLOSING_BRACKET;
}

void JSONArray::search(const String &key, Vector<JSONValue *> &searchResultsArray) const {
    for (size_t i = 0; i < values.Size(); i++) {
        values[i]->search(key, searchResultsArray);
    }
}

//written with the help of Claude Ai
void JSONArray::set(const Vector<String> &path, JSONValue *const value) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Invalid path for array");
    }
    
    size_t index = std::stoul(path[0].C_str());
    if (index >= values.Size()) {
        throw std::out_of_range("Array index out of bounds");
    }

    if (path.Size() == 1) {
        delete values[index];
        values[index] = value->clone();
    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); i++) {
            subPath.PushBack(path[i]);
        }
        values[index]->set(subPath, value);
    }
}

//written with the help of Claude Ai
void JSONArray::create(const Vector<String>& path, JSONValue* const value) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for create operation in array");
    }

    size_t index;
    try {
        index = std::stoul(path[0].C_str());
    } catch (const std::exception&) {
        throw InvalidPathError("Invalid array index in path");
    }

    if (path.Size() == 1) {
        if (index > values.Size()) {
            throw InvalidPathError("Array index out of bounds for creation");
        }
        if (index == values.Size()) {
            values.PushBack(value->clone());
        } else {
            throw JSONException("Element already exists at index");
        }
    } else {
        if (index >= values.Size()) {
            throw InvalidPathError("Array index out of bounds for nested creation");
        }
        
    
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); ++i) {
            subPath.PushBack(path[i]);
        }
        values[index]->create(subPath, value);
    }
}

void JSONArray::remove(const Vector<String> &path) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Invalid path for array");
    }

    size_t index;
    try {
        index = std::stoul(path[0].C_str());
    } catch (const std::exception& e) {
        throw InvalidPathError("Invalid array index in path");
    }
    
    if (index >= values.Size()) {
        throw std::out_of_range("Array index out of range");
    }

    if (path.Size() == 1) {
        delete values[index];
        values.EraseAt(index);
    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); i++) {
            subPath.PushBack(path[i]);
        }
        values[index]->remove(subPath);
    }
}

bool JSONArray::contains(const String &value) const {
    for (size_t i = 0; i < values.Size(); i++) {
        if (values[i]->contains(value) || values[i]->toString().Contains(value)) {
            return true;
        }
    }
    return false;
}


void JSONArray::free() {
    for (size_t i = 0; i < values.Size(); i++) {
        delete values[i];
    }
}

void JSONArray::copyFrom(const JSONArray& other) {
    this->values.Reserve(other.values.Size());

    for (size_t i = 0; i < other.values.Size(); i++) {
        this->values.PushBack(other.values[i]->clone());
    }
}

void JSONArray::moveFrom(JSONArray&& other) noexcept {
    values = std::move(other.values);
}