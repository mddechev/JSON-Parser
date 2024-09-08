#ifndef _JSON_MANAGER_HPP_
#define _JSON_MANAGER_HPP_

#include "../includes/json_types/JSONValue.hpp"
#include "../includes/json_types/JSONArray.hpp"

class JSONManager {
public:
    JSONManager();
    JSONManager(const JSONManager& other);
    ~JSONManager();

    JSONManager& operator=(const JSONManager& other);

    void open(const String& filePath);

    bool save();

    void saveAs(const String& filePath) const;

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
    void copy(const JSONManager& other);
    void free();
    void checkFileOpen() const;
    void saveToFile(const String& fileName) const;
    void parseJSON(std::istream& is); 

private:
    JSONValue* root;
    String currentFilePath;
    bool isFileOpen;
    bool isModified;
};


#endif //_JSON_MANAGER_HPP_