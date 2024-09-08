#ifndef _JSON_EXCEPTION_HPP_
#define _JSON_EXCEPTION_HPP_


#include <stdexcept>
#include <exception>
#include "../includes/utility/String.hpp"

class JSONException: public std::exception {
public:
    explicit JSONException(const String& message);
    ~JSONException() noexcept = default;

    const char* what() const noexcept override;
protected:
    const String& getMessage() const { return message; }
    
private:
    String message;
};

class CreationError: public JSONException {
public:
    explicit CreationError(const String& msg = "Failed to create value");
};

class InvalidJSONSyntax: public JSONException {
public:
    explicit InvalidJSONSyntax(const String& msg = "Invalid JSON syntax");
};

class KeyNotFound: public JSONException {
public:
    explicit KeyNotFound(const String& msg = "Key not found", const String& key = "");
    ~KeyNotFound() noexcept = default;

    const char * what() const noexcept override;
private:
    String key;
};

class ElementNotFound: public JSONException {
public:
    explicit ElementNotFound(const String& msg = "Element not found");
};

class InvalidPathError: public JSONException {
public:
    explicit InvalidPathError(const String& msg = "Invalid path error");
};

class FileError: public JSONException {
public:
    explicit FileError(const String& msg, const String& fileName);
    ~FileError() noexcept = default;

    const char* what() const noexcept override;

private:
    String fileName;
};

#endif //_JSON_EXCEPTION_HPP_
