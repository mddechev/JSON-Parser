#include "../includes/JSONManager.hpp"
#include "../includes/JSONException.hpp"
#include "../includes/JSONFactory.hpp"
#include "../includes/JSONValidator.hpp"
#include <fstream>
#include <stdexcept>
#include "../includes/utility/Helpers.hpp"
#include "../includes/json_types/JSONObject.hpp"
#include "utility/Vector.hpp"

JSONManager::JSONManager()
    :root(nullptr), isFileOpen(false), isModified(false) {}

JSONManager::~JSONManager() {
    delete root;
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

    char ch;
    bool isEmpty = true;
    while (file.get(ch)) {
        if (!std::isspace(ch)) {
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

void JSONManager::saveAs(const String &filePath) {
    checkFileOpen();
    saveToFile(filePath);
}

void JSONManager::close() {
    checkFileOpen();
    delete root;
    root = nullptr;
    isFileOpen = false;
}

void JSONManager::print(std::ostream& outputStream) const {
    if (root) {
        root->print(outputStream);
    } else {
        outputStream << "No JSON data loaded to print" << '\n';
    }
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
    
    // if (tokenizedPath.IsEmpty()) {
    //     throw InvalidPathError("Empty path for remove operation");
    // }
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

// // claude ai second try
// void JSONManager::move(const String& fromPath, const String& toPath) {
//     Vector<String> tokenizedFromPath = helpers::tokenizeLineToStrings(fromPath, '/');
//     Vector<String> tokenizedToPath = helpers::tokenizeLineToStrings(toPath, '/');
//     checkFileOpen();
//     if (!root) {
//         throw JSONException("No JSON document is currently open");
//     } 

//     if (tokenizedFromPath.IsEmpty() || tokenizedToPath.IsEmpty()) {
//         throw InvalidPathError("Invalid path for move operation");
//     }
//     try {
//         root->move(tokenizedFromPath, tokenizedToPath);
//         isModified = true;  // Set this to true to ensure changes are saved
//         std::cout << "Successfully moved from ";
//         tokenizedFromPath.Print(std::cout, '/');
//         std::cout << " to ";
//         tokenizedToPath.Print(std::cout, '/');
//         std::cout << '\n';
//     } catch (const JSONException& e) {
//         std::cerr << "Error during move operation: " << e.what() << '\n';
//     }
// }

void JSONManager::checkFileOpen() const {
    if(!isFileOpen) {
            throw std::runtime_error("No JSON document currently loaded");
    }   
}

void JSONManager::saveToFile(const String& filePath) {
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
