#pragma once

#ifndef _JSON_MANAGER_HPP_
#define _JSON_MANAGER_HPP_

#include "../includes/json_types/JSONValue.hpp"
#include "../includes/json_types/JSONArray.hpp"

class JSONManager {
public:
    JSONManager();
    ~JSONManager();

    void open(const String& filePath);

    bool save();

    void saveAs(const String& filePath);

    void close();

    void print(std::ostream& outputStream = std::cout) const;

    void validate(const String& filePath) const;

    Vector<JSONValue*> search(const String& key) const;

    void set(const String& path, JSONValue* const value);

    void create(const String& path, JSONValue* const value);

    void remove(const String& path);

    bool contains(const String& value) const;

    bool isSaved() const { return !isModified; }

    bool isOpen() const { return isFileOpen; }

    const String& getCurrentFilePath() const { return currentFilePath; }

private:
    void checkFileOpen() const;
    void saveToFile(const String& fileName);
    void parseJSON(std::istream& is); 

private:
    JSONValue* root;
    String currentFilePath;
    bool isFileOpen;
    bool isModified;
};


#endif //_JSON_MANAGER_HPP_