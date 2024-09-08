#include "../../includes/json_types/JSONKeyPair.hpp"

JSONKeyPair::JSONKeyPair(const String& key, JSONValue* value)
    :key(key), value(value) { 
    // this->value = value;
}

JSONKeyPair::JSONKeyPair(const JSONKeyPair& other) {
    copyFrom(other);
}

JSONKeyPair::JSONKeyPair(JSONKeyPair&& other) noexcept {
    moveFrom(std::move(other));
}

JSONKeyPair::~JSONKeyPair() {
    free();
}

JSONKeyPair& JSONKeyPair::operator=(const JSONKeyPair& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

JSONKeyPair& JSONKeyPair::operator=(JSONKeyPair&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void JSONKeyPair::print(std::ostream& outputStream, size_t indent) const {
        printIndent(outputStream, indent);
        outputStream << key << ": ";
        value->print(outputStream, indent);
}

void JSONKeyPair::search(const String &key, Vector<JSONValue *> &searchResultsArray) const {
    value->search(key, searchResultsArray);
}

void JSONKeyPair::set(const Vector<String> &path, JSONValue *const value) {
    if (path.Size() == 1) {
        setValue(value);

    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); i++) {
            subPath.PushBack(path[i]);
        }
        this->value->set(subPath, value);
    }
}

void JSONKeyPair::create(const Vector<String>& path, JSONValue* const value) {
    this->value->create(path, value);
}

void JSONKeyPair::remove(const Vector<String> &path) {
    this->value->remove(path);
}

bool JSONKeyPair::contains(const String &value) const {
    return this->value->contains(value);
}

void JSONKeyPair::setValue(JSONValue *value) {
    delete this->value;
    this->value = value->clone();
}

void JSONKeyPair::copyFrom(const JSONKeyPair& other) {
    this->key = other.key;
    this->value = other.value->clone();
}

void JSONKeyPair::moveFrom(JSONKeyPair&& other) noexcept{
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