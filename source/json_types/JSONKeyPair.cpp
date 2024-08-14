#include "../../includes/json_types/JSONKeyPair.hpp"

JSONKeyPair::JSONKeyPair(const String& key, JSONValue* value)
    :key(key), value(nullptr) { 
    this->value = value;
}

JSONKeyPair::JSONKeyPair(const JSONKeyPair& other)
    :value(nullptr) {
    copy(other);
}

JSONKeyPair::~JSONKeyPair() {
    free();
}

JSONKeyPair& JSONKeyPair::operator=(const JSONKeyPair &other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

JSONKeyPair* JSONKeyPair::clone() const {
    return new JSONKeyPair(*this);
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

// void JSONKeyPair::create(const Vector<String> &path, JSONValue *const value) {
//     this->value->create(path, value);
// }

void JSONKeyPair::create(const Vector<String>& path, JSONValue* const value) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for create operation in key-value pair");
    }
    
    Vector<String> subPath;
    for (size_t i = 0; i < path.Size(); ++i) {
        subPath.PushBack(path[i]);
    }
    this->value->create(subPath, value);
}

void JSONKeyPair::remove(const Vector<String> &path) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for remove operation in key-pair");
    }

    if (path.Size() == 1) {
        throw JSONException("Cannot remove from JSONKeyPair directly");
    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); i++) {
            subPath.PushBack(path[i]);
        }
        this->value->remove(subPath);
    }
}

bool JSONKeyPair::contains(const String &value) const {
    return this->value->contains(value);
}

// void JSONKeyPair::move(const Vector<String> &from, const Vector<String> &to) {
//     if (from.IsEmpty()) {
//         throw InvalidPathError("Invalid source path for move operation in key-pair");
//     }

//     if (from.Size() == 1) {
//         //we are moving the entire value of this key-pair
//         if (to.IsEmpty()) {
//             throw InvalidPathError("Invalid destination path for key - pair");
//         }
//         //the actual move will be handled by the parent class
//         return;
//     }

//     Vector<String> subFrom;
//     for (size_t i = 1; i < from.Size(); i++) {
//         subFrom.PushBack(from[i]);
//     }

//     if (this->value) {
//         this->value->move(subFrom, to);
//     } else {
//         throw JSONException("Cannot move from null value");
//     }
// }

void JSONKeyPair::setValue(JSONValue *value) {
    free();
    this->value = value->clone();
}

void JSONKeyPair::setKey(const String& key) {
    this->key = key;
}

void JSONKeyPair::copy(const JSONKeyPair& other) {
    this->key = other.key;
    this->value = other.value->clone();
}

void JSONKeyPair::free() {
    delete value;
    value = nullptr;
}

void JSONKeyPair::printIndent(std::ostream& os, size_t indent) {
    for (size_t i = 0; i < indent; i++) {
        os << "  ";
    }
}