#include "JSONException.hpp"
#include "JSONFactory.hpp"
#include "JSONManager.hpp"
#include "json_types/JSONValue.hpp"
#include "utility/Helpers.hpp"
#include "utility/String.hpp"

void testOpen(const String& filePath) {
    JSONManager manager;
    try {
        manager.open(filePath);

        std::cout << "Successfully opened " << filePath << '\n';

        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testSaveAs(const String& filePath, const String& saveAsFilePath) {
    JSONManager manager;
    try {
        manager.open(filePath);

        manager.saveAs(saveAsFilePath);
        std::cout << "Successfully saved to " << saveAsFilePath << '\n';
        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testPrint(const String& filePath) {
    JSONManager manager;
    try {
        manager.open(filePath);

        manager.print();

        std::cout << '\n' << "Successfully printed data from " << filePath << '\n';

        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
} 

void testValidate(const String& filePath) {
    JSONManager manager;
    try {
        manager.validate(filePath);
        std::cout << "Validation successfull of " << filePath << '\n'; 
    } catch (const JSONException& e) {
        std::cerr <<"Invalid JSON:" << e.what() << '\n';
    }
}

void testSearch(const String& filePath, const String& key) {
    JSONManager manager;
    try {
        manager.open(filePath);

        Vector<JSONValue*> searchResults = manager.search(key);

        for (size_t i = 0; i < searchResults.Size(); i++) {
            searchResults[i]->print();
            std::cout << ", ";
        }
        std::cout << '\n' << "Successfull search for " << key << '\n';
        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testSet(const String& filePath, const String& valuePath, JSONValue* const value) {
    JSONManager manager;
    try {
        manager.open(filePath);
        std::cout << "Before set\n";
        manager.print();
        std::cout << '\n';

        manager.set(valuePath, value);
        std::cout << "After set\n";
        manager.print();
        std::cout << '\n' << "Successfull set operation for value at " << valuePath << '\n';

        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testCreate(const String& filePath, const String& valuePath, JSONValue* const value) {
    JSONManager manager;
    try {
       manager.open(filePath);
        std::cout << "Before create\n";
        manager.print();
        std::cout << '\n';

        manager.create(valuePath, value);
        manager.save();
        std::cout << "After create\n";
        manager.print();
        std::cout << '\n' << "Successfull create operation at " << valuePath << '\n';

        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testCreateWithInuptStringStream(const String& filePath, const String& valuePath, const String& JSONtext) {
    JSONManager manager;
    InputStringStream inputStream(JSONtext);
    JSONValue* value = JSONFactory::getFactory().createValue(inputStream);

    try {
        std::cout << "Value to be created" << '\n';
        value->print();
        std::cout << '\n';

        manager.open(filePath);
        std::cout << "Before creation" << '\n';
        manager.print();
        std::cout << '\n';

        manager.create(valuePath, value);
        std::cout << "After creation" << '\n';
        manager.print();
        std::cout << '\n' << "Successfull creation at " << value << '\n';

        manager.close();
        delete value;
    } catch (const CreationError& e) {
        delete value;
        std::cerr << e.what() << '\n';
    } catch (const JSONException& e) {
        delete value;
        std::cerr << e.what() << '\n';
    }
}

void testRemove(const String& filePath, const String& valuePath) {
    JSONManager manager;
    try {
        manager.open(filePath);
        std::cout << "Before removing\n";
        manager.print();
        std::cout << '\n';

        manager.remove(valuePath);
        std::cout << "After removing\n";
        manager.print();

        std::cout << '\n' << "Successfully removed value from path " << valuePath << '\n';

        manager.close();
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}


int main() {
    testOpen("../JSONfiles/file.json");
    return 0;
}