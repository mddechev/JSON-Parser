#include "../includes/JSONFactory.hpp"
#include "../includes/json_types/JSONArray.hpp"
#include "../includes/JSONException.hpp"
#include "../includes/json_types/JSONObject.hpp"
#include "../includes/JSONParser.hpp"
#include "../includes/json_types/JSONNumber.hpp"
#include "../includes/json_types/JSONBool.hpp"
#include "../includes/json_types/JSONNull.hpp"
#include "../includes/json_types/JSONString.hpp"
#include "../includes/utility/Constants.hpp"
#include "utility/Helpers.hpp"

JSONFactory& JSONFactory::getFactory() {
    static JSONFactory theFactroy;
    return theFactroy;
}

JSONValue* JSONFactory::createValue(std::istream& inputStream) {
    char firstChar;
    inputStream >> firstChar;
    
    inputStream.unget();

    if (firstChar == '-' || helpers::isDigit(firstChar)) {
        return createNumber(inputStream);

    } else if (firstChar == 'n') {
        return createNull(inputStream);

    } else if (firstChar == 't' || firstChar == 'f') {
        return createBool(inputStream);

    } else if (firstChar == DOUBLE_QUOTE) {
        return createString(inputStream); 

    } else if (firstChar == ARRAY_OPENING_BRACKET) {
        return createArray(inputStream);

    } else if (firstChar == OBJECT_OPENING_BRACKET) {
        return createObject(inputStream);

    } else {
        throw CreationError("Invalid character in factory");
    }
}


JSONValue* JSONFactory::createNumber(std::istream &inputStream) {
    return new JSONNumber(JSONParser::parseNumber(inputStream));
}

JSONValue* JSONFactory::createBool(std::istream &inputStream) {
    return new JSONBool(JSONParser::parseBool(inputStream));
}

JSONValue* JSONFactory::createNull(std::istream &inputStream) {
    return new JSONNull(JSONParser::parseNull(inputStream));
}

JSONValue* JSONFactory::createString(std::istream &inputStream) {
    return new JSONString(JSONParser::parseString(inputStream));
}

JSONValue* JSONFactory::createArray(std::istream& inputStream) {
    JSONArray* resultArray = new JSONArray();
    JSONParser::parseArray(inputStream, resultArray);
    return resultArray;
}

JSONValue* JSONFactory::createObject(std::istream &inputStream) {
    JSONObject* resultObject = new JSONObject();
    JSONParser::parseObject(inputStream, resultObject);
    return resultObject;
}