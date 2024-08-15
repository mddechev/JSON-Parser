#include "../includes/JSONValidator.hpp"
#include "../includes/JSONException.hpp"
#include "../includes/utility/Constants.hpp"
#include "utility/Helpers.hpp"

void JSONValidator::validate(std::istream &inputStream) {
    char firstChar;
    while (inputStream.get(firstChar) && std::isspace(firstChar)) {}

    if (inputStream.eof()) {
        return; //empty file counts as valid
    }

    inputStream.unget();

    validateValue(inputStream);

    while (inputStream >> firstChar) {
        if (!std::isspace(firstChar)) {
            throw InvalidJSONSyntax("Unexpected content after JSON value");
        }
    }
}


void JSONValidator::validateValue(std::istream& inputStream) {
    char firstChar;
    inputStream >> firstChar;
    inputStream.unget();

    if (firstChar == '-' || helpers::isDigit(firstChar)) {
        validateNumber(inputStream);

    } else if (firstChar == 'n') {
        validateNull(inputStream);

    } else if (firstChar == 't' || firstChar == 'f') {
        validateBool(inputStream);

    } else if (firstChar == DOUBLE_QUOTE) {
        validateString(inputStream);

    } else if (firstChar == ARRAY_OPENING_BRACKET) {
        validateArray(inputStream);

    } else if (firstChar == OBJECT_OPENING_BRACKET) {
        validateObject(inputStream);

    } else {
        throw InvalidJSONSyntax("Invalid value in validator");
    }
}

void JSONValidator::validateNumber(std::istream& inputStream) {
    double number;
    inputStream >> number;

    if (inputStream.fail()) {
        inputStream.clear();
        throw InvalidJSONSyntax("Invalid number format");
    }
}

void JSONValidator::validateNull(std::istream &inputStream) {
    String nullStr;
    char character;
    for (size_t i = 0; i < NULL_LEN; i++) {
        inputStream.get(character);
        nullStr += character;
    }
    if (nullStr != "null") {
        throw InvalidJSONSyntax("Invalid null");
    }
}

void JSONValidator::validateBool(std::istream &inputStream) {
    bool result;
    inputStream >> std::boolalpha >> result;

    if (inputStream.fail()) {
        inputStream.clear();
        throw InvalidJSONSyntax("Invalid bool");
    }
}

void JSONValidator::validateString(std::istream &inputStream) {
    size_t quotesCounter = 0;

    char character;
    inputStream >> character;
    if (character != DOUBLE_QUOTE) {
        throw InvalidJSONSyntax("Invalid JSON strng: string must begin with \"");
    }
    inputStream.unget();

    while (inputStream.get(character)) {
        if (character == DOUBLE_QUOTE) {
            quotesCounter++;
        }
        if (quotesCounter == 2 || character =='\n') {
            break;
        }
    }
    if (quotesCounter != 2) {
        throw InvalidJSONSyntax("Invalid JSON string: String must end with \"");
    }
}

void JSONValidator::validateArray(std::istream &inputStream) {
    char character;
    inputStream >> character;

    if (character != ARRAY_OPENING_BRACKET) {
        throw InvalidJSONSyntax("Invald JSON array: array must start with '['");
    }

    inputStream >> character;
    if (character == ARRAY_CLOSING_BRACKET) {
        //validating empty array
        return;
    }

    inputStream.unget();
    while (inputStream.good()) {
        validateValue(inputStream);

        inputStream >> character;

        if (character == ':' || character == '.') {
            throw InvalidJSONSyntax("Expected a ',' after a value in array");
        }
        if (character != ',') {
            break;
        }
    }
    inputStream.unget();
    inputStream >> character;
    if (character != ARRAY_CLOSING_BRACKET) {
        throw InvalidJSONSyntax("Invalid JSON array: array must end with ']'");
    }
}

void JSONValidator::validateObject(std::istream &inputStream) {
    char character;
    inputStream >> character;

    if (character != OBJECT_OPENING_BRACKET) {
        throw InvalidJSONSyntax("Invalid JSON object: object must begin with '{'");
    }

    inputStream >> character;

    if (character == OBJECT_CLOSING_BRACKET) {
        //validating empty object
        return;
    }

    inputStream.unget();
    bool firstPair = true;
    while (true) {
        if (!firstPair) {
            inputStream >> character;

            if (character == OBJECT_CLOSING_BRACKET) {
                break;
            }
            if (character != ',') {
                throw InvalidJSONSyntax("Invalid object: expected ',' or '}' after value");
            }
        }

        // Validate key
        inputStream >> character;

        if (character != DOUBLE_QUOTE) {
            throw InvalidJSONSyntax("Invalid object: key must be a \"string\"");
        }

        inputStream.unget();
        validateString(inputStream);

        // Validate colon
        inputStream >> character;
        
        if (character != ':') {
            throw InvalidJSONSyntax("Invalid key-value pair: expected ':' after key");
        }

        // Validate value
        validateValue(inputStream);

        firstPair = false;
    }
}

