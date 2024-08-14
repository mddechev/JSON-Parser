#include "../includes/JSONException.hpp"

JSONException::JSONException(const String& message)
    :message(message) {}

const char* JSONException::what() const noexcept {
    return message.C_str();
}

InvalidJSONSyntax::InvalidJSONSyntax(const String& message)
    :JSONException(message) {}

CreationError::CreationError(const String& msg)
    :JSONException(msg) {}

KeyNotFound::KeyNotFound(const String& message, const String& key)
    :JSONException(message), key(key) {}

const char* KeyNotFound::what() const noexcept {
    static String fullMessage(getMessage());
    if (!key.IsEmpty()) {
        fullMessage += ": \"";
        fullMessage += key;
        fullMessage += '\"';
    }
    return fullMessage.C_str();
}

ElementNotFound::ElementNotFound(const String& message)
    :JSONException(message) {}

InvalidPathError::InvalidPathError(const String& message)
    :JSONException(message) {}

FileError::FileError(const String& message, const String& fileName)
    :JSONException(message), fileName(fileName) {}

const char* FileError::what() const noexcept {
    static String fullMessage(getMessage());
    fullMessage += ": ";
    fullMessage += fileName;
    return fullMessage.C_str();
}