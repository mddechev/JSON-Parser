#include "../../includes/json_types/JSONKeyPair.hpp"

JSONKeyPair::JSONKeyPair(const String& key, JSONValue* value)
    :key(key), value(nullptr) { 
    this->value = value;
}

JSONKeyPair::JSONKeyPair(const JSONKeyPair& other) {
    copy(other);
}

JSONKeyPair::JSONKeyPair(JSONKeyPair&& other) noexcept {
    move(std::move(other));
}

JSONKeyPair::~JSONKeyPair() {
    free();
}

JSONKeyPair& JSONKeyPair::operator=(const JSONKeyPair& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

JSONKeyPair& JSONKeyPair::operator=(JSONKeyPair&& other) noexcept {
    if (this != &other) {
        free();
        move(std::move(other));
    }
    return *this;
}

void JSONKeyPair::print(std::ostream& outputStream, size_t indent) const {
        printIndent(outputStream, indent);
        outputStream << "\"" << key << "\": ";
        if (value) {
        value->print(outputStream, indent);
        } else {
            outputStream << "null";
        }
}

void JSONKeyPair::search(const String &key, Vector<JSONValue *> &searchResultsArray) const {
    value->search(key, searchResultsArray);
}

void JSONKeyPair::set(const Vector<String> &path, JSONValue *const value) {
    //claude ai
    if (path.Size() == 1) {
        delete this->value;
        this->value = value->clone();
    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); ++i) {
            subPath.PushBack(path[i]);
        }
        this->value->set(subPath, value);
    }
}

void JSONKeyPair::create(const Vector<String>& path, JSONValue* const value) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for create operation in key-value pair");
    }
    
    // Vector<String> subPath;
    // for (size_t i = 0; i < path.Size(); ++i) {
    //     subPath.PushBack(path[i]);
    // }
    this->value->create(path, value);
}

void JSONKeyPair::remove(const Vector<String> &path) {
    // if (path.IsEmpty()) {
    //     throw InvalidPathError("Empty path for remove operation in key-pair");
    // }

    // if (path.Size() == 1) {
    //     throw JSONException("Cannot remove from JSONKeyPair directly");
    // } else {
    //     Vector<String> subPath;
    //     for (size_t i = 1; i < path.Size(); i++) {
    //         subPath.PushBack(path[i]);
    //     }
    //     this->value->remove(subPath);
    // }
    this->value->remove(path);
}

bool JSONKeyPair::contains(const String &value) const {
    return this->value->contains(value);
}

void JSONKeyPair::setValue(JSONValue *value) {
    free();
    this->value = value->clone();
}

// void JSONKeyPair::setKey(const String& key) {
//     this->key = key;
// }

void JSONKeyPair::copy(const JSONKeyPair& other) {
    this->key = other.key;
    this->value = other.value->clone();
}

void JSONKeyPair::move(JSONKeyPair&& other) noexcept{
    this->key = other.key;
    this->value = other.value;

    other.key.Clear();
    other.value = nullptr;
}

void JSONKeyPair::free() {
    delete value;
    value = nullptr;
}

void JSONKeyPair::printIndent(std::ostream& outputStream, size_t indent) {
    for (size_t i = 0; i < indent; i++) {
        outputStream << "  ";
    }
}