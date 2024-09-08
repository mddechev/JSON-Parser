#include "../includes/JSONManager.hpp"
#include "../includes/JSONException.hpp"
#include "../includes/JSONFactory.hpp"
#include "../includes/JSONValidator.hpp"
#include <fstream>
#include <ios>
#include "../includes/utility/Helpers.hpp"
#include "../includes/json_types/JSONObject.hpp"
#include "utility/Vector.hpp"

JSONManager::JSONManager()
    :root(nullptr), isFileOpen(false), isModified(false) {}

JSONManager::JSONManager(const JSONManager& other) {
    copy(other);
}

JSONManager::~JSONManager() {
    free();
}

JSONManager& JSONManager::operator=(const JSONManager& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

void JSONManager::open(const String& filePath) {
    if(isFileOpen) {
        throw FileError("JSON file already opened", currentFilePath);
    }

    std::ifstream file(filePath.C_str());
    if (!file.is_open()) {
        throw FileError("Couldn't open. Check the file path", filePath);

    } else if (!file) {
        throw FileError("File error", filePath);
    }

    JSONValidator::validate(file);

    file.clear();
    file.seekg(0);

    char character;
    bool isEmpty = true;
    while (file.get(character)) {
        if (!std::isspace(character)) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) {
        root = nullptr;
        std::cout << "Empty file detected." << '\n';

    } else {
        file.clear();
        file.seekg(0);
        parseJSON(file);
    }

    currentFilePath = filePath;
    isFileOpen = true;
    isModified = false;
} 

bool JSONManager::save() {
    checkFileOpen();
    if (!isModified) {
        return false;
    }
    saveToFile(currentFilePath);
    isModified = false;
    return true;
}

void JSONManager::saveAs(const String &filePath) const {
    checkFileOpen();
    saveToFile(filePath);
}

void JSONManager::close() {
    checkFileOpen();
    free();
}

void JSONManager::print(std::ostream& outputStream) const {
    // if (root) {
    //     root->print(outputStream);
    // } else {
    //     outputStream << "No JSON data loaded to print" << '\n';
    // }
    // outputStream << '\n';
    if(!root) {
        outputStream << "No JSON data loaded to print" << '\n';
        return;
    }
    root->print(outputStream);
    outputStream << '\n';
}

void JSONManager::validate(const String& filePath) const {
    std::ifstream file(filePath.C_str());

    if (!file.is_open()) {
        throw FileError("Couldn't open", filePath);
    }

    JSONValidator::validate(file);
}

Vector<JSONValue*> JSONManager::search(const String& key) const {
    checkFileOpen();

    Vector<JSONValue*> searchResultsArray;
    root->search(key, searchResultsArray);

    return searchResultsArray;
}

void JSONManager::set(const String& path, JSONValue *const value) {
    checkFileOpen();

    Vector<String> tokenizedPath = helpers::tokenizeLineToStrings(path, '/');

    if (tokenizedPath.IsEmpty()) {
        throw InvalidPathError("Empty path for set operation");
    }

    if(!root) {
        throw JSONException("No JSON data loaded to set");
    }
    root->set(tokenizedPath, value);
    isModified = true;
}


void JSONManager::create(const String& path, JSONValue* const value) {
    checkFileOpen();
    Vector<String> tokenizedPath = helpers::tokenizeLineToStrings(path, '/');

    if (tokenizedPath.IsEmpty()) {
        throw InvalidPathError("Empty path for create operation");
    }

    //if file is empty create an object
    if (!root) {
        root = new JSONObject;
    }

    try {
        root->create(tokenizedPath, value);
        isModified = true;
    } catch (const JSONException& e) {
        delete value;
        throw;
    }
}


void JSONManager::remove(const String& path) {
    checkFileOpen();

    Vector<String> tokenizedPath = helpers::tokenizeLineToStrings(path, '/');
    if (!root) {
        throw JSONException("No JSON data loaded to remove");
    }
    
    root->remove(tokenizedPath);
    isModified = true;
}


bool JSONManager::contains(const String &value) const {
    checkFileOpen();

    if (!root) {
        throw JSONException("No JSON data loaded to check for containing");
    }
    return root->contains(value);
}


void JSONManager::checkFileOpen() const {
    if(!isFileOpen) {
            throw JSONException("No JSON document currently loaded");
    }   
}

void JSONManager::saveToFile(const String& filePath) const{
    std::ofstream destinationFile(filePath.C_str());
    if(!destinationFile) {
        throw FileError("Couldn't open", filePath);
    }
    if(!root) {
        return;
    }
    root->print(destinationFile);

    destinationFile.close();

    if (destinationFile.fail()) {
        throw FileError("Error occured while saving the file", filePath);
    }
}

void JSONManager::parseJSON(std::istream& inputStream) {
    root = JSONFactory::getFactory().createValue(inputStream);
}

void JSONManager::copy(const JSONManager& other) {
    if (!other.root) {
        this->root = nullptr;
    }
    this->root = other.root->clone();
    this->currentFilePath = other.currentFilePath;
    this->isFileOpen = other.isFileOpen;
    this->isModified = other.isModified;
}

void JSONManager::free() {
    delete root;
    root = nullptr;
    isFileOpen = false;
    isModified = false;
}