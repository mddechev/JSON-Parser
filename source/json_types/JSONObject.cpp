#include "../../includes/json_types/JSONObject.hpp"
#include "../../includes/utility/Constants.hpp"

JSONObject::JSONObject(const JSONObject& other) {
    copy(other);
}

JSONObject::~JSONObject() noexcept {
    free();
}

JSONObject& JSONObject::operator=(const JSONObject &other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

String JSONObject::toString() const {
    String res("{");
    for (size_t i = 0; i < values.Size(); i++) {
        if (i > 0) {
            res += ", ";
        }
        res += '\"';
        res += values[i]->getKey();
        res += "\": ";
        res += values[i]->getValue()->toString();
    }
    res += OBJECT_CLOSING_BRACKET;
    return res;
}

JSONValue* JSONObject::clone() const {
    return new JSONObject(*this);
}

void JSONObject::print(std::ostream &outpuStream, size_t indent) const {
    outpuStream << OBJECT_OPENING_BRACKET << '\n';
        for (size_t i = 0; i < values.Size(); ++i) {
            if (i > 0) outpuStream << ',' << '\n';
            values[i]->print(outpuStream, indent + 1);
        }
        outpuStream << '\n';
        printIndent(outpuStream, indent);
        outpuStream << OBJECT_CLOSING_BRACKET;
}

void JSONObject::search(const String &key, Vector<JSONValue*>& searchResultsArray) const {
    for (size_t i = 0; i < values.Size(); i++) {
        if (values[i]->getKey() == key) {
            searchResultsArray.PushBack(values[i]->getValue()->clone());
        }
        values[i]->search(key, searchResultsArray);
    }
}

void JSONObject::set(const Vector<String> &path, JSONValue *const value) {
    //claude ai
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for object");
    }
    JSONKeyPair* pair = getPair(path[0]);
    if (!pair) {
        if (path.Size() == 1) {
            addPair(path[0], value->clone());
        } else {
            throw InvalidPathError("Path nout found");
        }
    } else {
        if (path.Size() == 1) {
            pair->setValue(value->clone());
        } else {
            Vector<String> subPath;
            for (size_t i = 1; i < path.Size(); i++) {
                subPath.PushBack(path[i]);
            }
            pair->getValue()->set(subPath, value);
        }
    }
}

void JSONObject::create(const Vector<String>& path, JSONValue* const value) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for create operation in object");
    }

    JSONKeyPair* pair = nullptr;
    try {
        pair = getPair(path[0]);
    } catch (const KeyNotFound&) {
        // Key not found, which is expected for creation
        if (path.Size() == 1) {
            // If it's the last part of the path, add the new value
            addPair(path[0], value->clone());
            return;
        } else {
            // Create an intermediate object
            JSONObject* newObject = new JSONObject;
            addPair(path[0], newObject);
            pair = getPair(path[0])->clone();
        }
    }

    if (path.Size() == 1) {
        if (pair) {
            throw JSONException("Element already exists");
        }
        addPair(path[0], value->clone());
    } else {
        if (!pair) {
            throw KeyNotFound("Key not found in object", path[0]);
        }
        
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); ++i) {
            subPath.PushBack(path[i]);
        }
        pair->getValue()->create(subPath, value);
    }
}

void JSONObject::remove(const Vector<String> &path) {
    if (path.IsEmpty()) {
        throw InvalidPathError("Empty path for object");
    }
    JSONKeyPair* pair = getPair(path[0]);

    if (path.Size() == 1) {
        removePair(path[0]);
    } else {
        Vector<String> subPath;
        for (size_t i = 1; i < path.Size(); i++) {
            subPath.PushBack(path[i]);
        }
        pair->getValue()->remove(subPath);
    }
}

bool JSONObject::contains(const String &value) const {   
    for (size_t i = 0; i < values.Size(); i++) {
        if (values[i]->getValue()->contains(value) ||
            values[i]->getValue()->toString().Contains(value)) {
            return true;
        }
    }
    return false;
}

const JSONKeyPair* JSONObject::getPair(const String& key) const {
    return values[getValueIndex(key)];
}


JSONKeyPair* JSONObject::getPair(const String& key) {
    return values[getValueIndex(key)];
}

const JSONValue* JSONObject::getValue(const String &key) const {
    return values[getValueIndex(key)]->getValue();
}

JSONValue* JSONObject::getValue(const String &key) {
    return values[getValueIndex(key)]->getValue();
}

void JSONObject::addPair(const String& key, JSONValue *value) {
    values.PushBack(new JSONKeyPair(key, value));
}

void JSONObject::removePair(const String &key) {
    values.EraseAt(getValueIndex(key));
}

size_t JSONObject::getValueIndex(const String& key) const {
    for (size_t i = 0; i < values.Size(); i++) {
        if (values[i]->getKey() == key) {
            return i;
        }
    }
    throw KeyNotFound("Key not found in object", key);
}

void JSONObject::copy(const JSONObject& other) {
    this->values.Reserve(other.getValues().Size());

    for (size_t i = 0; i < other.getValues().Size(); i++) {
        this->values.PushBack(other.getValues()[i]->clone());
    }
}

void JSONObject::free() {
    for (size_t i = 0; i < values.Size(); i++) {
        delete values[i];
    }
    values.Clear();
}
