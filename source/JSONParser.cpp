#include "../includes/JSONParser.hpp"
#include "../includes/JSONFactory.hpp"
#include "../includes/utility/Constants.hpp"
#include "json_types/JSONNull.hpp"


JSONNull JSONParser::parseNull(std::istream &inputStream) {
    String nullStr;
    char character;
    for (int i = 0; i < 4; ++i) {
        if (inputStream.get(character)) {
            nullStr += character;
        } else {
            break;
        }
    }
    
    if (nullStr == "null") {
        return JSONNull();
    } else {
        throw InvalidJSONSyntax("Failed to create null value");
    }
    return JSONNull();
}

double JSONParser::parseNumber(std::istream &inputStream) {
        double result;
        inputStream >> result;

        return result;
}

bool JSONParser::parseBool(std::istream &inputStream) {
    bool result;
    inputStream >> std::boolalpha >> result;
    return result;
}

String JSONParser::parseString(std::istream& inputStream) {
    String result;
    size_t quotesCount = 0;

    char character;
    while (inputStream.get(character)) {
        result += character;
       
        if (character == DOUBLE_QUOTE) {
            quotesCount++;
        }
        if (quotesCount == 2 || character == '\n') {
            break;
        }
    }
    return result;
}

void JSONParser::parseArray(std::istream& inputStream, JSONArray* toBeFilledArray) {
    char character;
    inputStream >> character;
    
    inputStream >> character;
    if (character == ARRAY_CLOSING_BRACKET) {
        std::cout << "parsing result: empty array\n";
        return; // Empty array
    }

    inputStream.unget();
    while (inputStream.good()) {
        JSONValue* value = nullptr;
        if (character == ARRAY_OPENING_BRACKET) {
            // Nested array
            JSONArray* nestedArray = new JSONArray();
            parseArray(inputStream, nestedArray);
            value = nestedArray;
        } else {
            value = JSONFactory::getFactory().createValue(inputStream);
        }
        
        toBeFilledArray->getValues().PushBack(value);

        inputStream >> character;

        if (character == ARRAY_CLOSING_BRACKET) {
            break;
        }
        if (character != ',') {
            break;
        }
    }
}

void JSONParser::parseObject(std::istream &inputStream, JSONObject *toBeFilledObject) {
    //claude AI
    char character;
    inputStream >> character;

    while (inputStream.good()) {
        inputStream >> character;
        if (character == OBJECT_CLOSING_BRACKET) {
            //empty object parsed
            break;
        }

        inputStream.unget();
        String key = parseString(inputStream);
        key = key.Substr(1, key.Length() - 2);

        inputStream >> character;
        
        JSONValue* value = JSONFactory::getFactory().createValue(inputStream);
       
        toBeFilledObject->addPair(key, value);

        inputStream >> character;
        if (character == OBJECT_CLOSING_BRACKET) {
            break;
        }
    }
}

