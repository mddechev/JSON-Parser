#include "../includes/JSONValidator.hpp"
#include "JSONException.hpp"
#include "utility/String.hpp"
#include <fstream>

void testNumber(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON number validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }

}

void testString(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON string validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testBool(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON bool validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testNull(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON null validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testArray(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON array validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testObject(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON object validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testNestedArray(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout <<"Successfull JSON nested array validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
    }
}

void testValidation(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << "Invalid JSON stream: " << e.what() << '\n';
    }
}

void testFileValidation(const String& filePath) {
    std::ifstream file(filePath.C_str());
    if (!file.is_open()) {
        std::cerr << "Couldn't open file " << filePath << '\n';
        return;
    }
    try {
        JSONValidator::validate(file);
        std::cout << "Successfull validation of " << filePath << '\n'; 
        file.close();
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << "Invalid JSON file: " << e.what() << '\n';
    }
}

int main() {
    testNumber("23");
    testString("\"string\"");
    testBool("true");
    testNull("null");
    testArray("[1, true, null, \"string\"]");
    testObject("{\"name\": \"Mihail\", \"age\": 21, \"taken\": false, \"job\": null}");
    testNestedArray("[12, [true, null], \"string\"]");
    testValidation("{\"student\": {\"name\": \"Mihail\", \"age\": 21, \"friends\": {\"name\": \"Atanas\"}}}");
    return 0;
}