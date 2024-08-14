#include "../includes/JSONValidator.hpp"
#include "JSONException.hpp"
#include "utility/String.hpp"

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

void testNestedObject(const String& JSONtext) {
    InputStringStream iss(JSONtext);
    try {
        std::cout << JSONtext << '\n';
        JSONValidator::validate(iss);
        std::cout << "Successfull JSON nested object validation" << "\n\n";
        
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << e.what() << '\n';
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
    testNestedObject("{\"student\": {\"name\": \"Mihail\", \"age\": 21, \"friends\": {\"name\": \"Atanas\"}}}");
    return 0;
}