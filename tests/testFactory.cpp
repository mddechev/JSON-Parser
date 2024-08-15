#include "JSONException.hpp"
#include "JSONFactory.hpp"
#include "utility/String.hpp"

void testNumberCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull number creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testBoolCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
   JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull bool creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testStringCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull string creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testNullCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull null creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testObjectCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull object creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testArrayCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull array creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

void testValueCreation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    JSONValue* value = nullptr;
    try {
        value = JSONFactory::getFactory().createValue(iss);
        value->print();
        std::cout << '\n';

        std::cout << "Successfull value creation" << "\n\n";
        delete value;
    } catch (const CreationError& e) {
        std::cerr << e.what() << '\n';
    }
}

int main() {
    testNumberCreation("2003");
    testBoolCreation("true");
    testBoolCreation("false");
    testNullCreation("null");
    testStringCreation("\"this is a string\"");
    testArrayCreation("[1, true, null, \"string\", [1, 2, 3] ]");
    testObjectCreation("{\"name\": \"Djaro\", \"age\": 56, \"mobBoss\": true}");
    testValueCreation("{\"student\": {\"name\": \"Mihail\", \"age\": 21, \"uni\": {\"name\": \"fmi\", \"minalIzpit\": false} } }");
    return 0;
}