#include "../../includes/json_types/JSONArray.hpp"
#include "../../includes/utility/Constants.hpp"
#include "../../includes/json_types/JSONObject.hpp"

JSONArray::~JSONArray() noexcept {
    free();
}

JSONArray::JSONArray(const JSONArray& other) {
    copy(other);
}

JSONArray& JSONArray::operator=(const JSONArray &other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

String JSONArray::toString() const {
    String res = ARRAY_OPENING_BRACKET;
    for (size_t i = 0; i < values.Size(); i++) {
        if (i > 0) {
            res += ", ";
        }
        res += values[i]->toString();
    }
    res += ARRAY_CLOSING_BRACKET;
    return res;
}

JSONValue* JSONArray::clone() const {
    return new JSONArray(*this);
}

void JSONArray::print(std::ostream &outputStream, size_t indent) const {
    outputStream << ARRAY_OPENING_BRACKET << '\n';
        for (size_t i = 0; i < values.Size(); ++i) {
            if (i > 0) outputStream << ',' << '\n';
            printIndent(outputStream, indent + 1);
            values[i]->print(outputStream, indent + 1);
        }
        outputStream << "\n";
        printIndent(outputStream, indent);
        outputStream << ARRAY_CLOSING_BRACKET;
}

void JSONArray::search(const String &key, Vector<JSONValue *> &searchResultsArray) const {
    for (size_t i = 0; i < values.Size(); i++) {
        values[i]->search(key, searchResultsArray);
    }
}

void JSONArray::set(const Vector<String> &path, JSONValue *const value) {
    //Claude ai
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

void JSONArray::addValue(JSONValue* const value) {
    values.PushBack(value);
}

void JSONArray::removeValue(size_t index) {
    values.EraseAt(index);
}

void JSONArray::setValue(size_t index, JSONValue* const value) {
    if (index >= this->values.Size()) {
        throw std::out_of_range("index out of range");
    }
    this->values[index] = value->clone();
}

const JSONValue* const JSONArray::getValue(size_t index) const {
    if (index >= values.Size()) {
        throw std::out_of_range("Index out of range");
    }
    return values[index];
}

JSONValue* JSONArray::getValue(size_t index) {
    if (index >= values.Size()) {
        throw std::out_of_range("Index out of range");
    }
    return values[index];
}

void JSONArray::free() {
    for (size_t i = 0; i < values.Size(); i++) {
        delete values[i];
    }
}

void JSONArray::copy(const JSONArray& other) {
    this->values.Reserve(other.getValues().Size());

    for (size_t i = 0; i < other.getValues().Size(); i++) {
        this->values.PushBack(other.getValues()[i]->clone());
    }
}