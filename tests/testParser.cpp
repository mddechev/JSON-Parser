#include "JSONParser.hpp"
#include "json_types/JSONArray.hpp"
#include "json_types/JSONObject.hpp"
#include "json_types/JSONNumber.hpp"
#include "json_types/JSONNull.hpp"
#include "json_types/JSONString.hpp"
#include "json_types/JSONBool.hpp"
#include "JSONFactory.hpp"
#include "utility/String.hpp"
#include <cassert>

void testNullParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONNull value(JSONParser::parseNull(isstream));
        value.print();
        std::cout << '\n';
        std::cout << "Successfull JSON null parsing" << "\n\n";
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testNumberParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONNumber value(JSONParser::parseNumber(isstream));
        value.print();
        std::cout << '\n';
        std::cout << "Successfull JSON number parsing" << "\n\n";
    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testBoolParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONBool value(JSONParser::parseBool(isstream));
        value.print();
        std::cout << '\n';

        std::cout << "Successfull JSON bool parsing" << "\n\n";

    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testStringParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONString value(JSONParser::parseString(isstream));
        value.print();
        std::cout << '\n';

        std::cout << "Successfull JSON string parsing" << "\n\n";

    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testArrayParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONArray array;
        JSONParser::parseArray(isstream, &array);
        array.print();
        std::cout << '\n';

        std::cout << "Successfull JSON array parsing" << "\n\n";

    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

void testObjectParsing(const String& JSONtext) {
    InputStringStream isstream(JSONtext);
    try {
        JSONObject object;
        JSONParser::parseObject(isstream, &object);
        object.print();
        std::cout << '\n';

        std::cout << "Successfull JSON object parsing" << "\n\n";

    } catch (const JSONException& e) {
        std::cerr << e.what() << '\n';
    }
}

int main() {
    testNullParsing("null");
    testNumberParsing("23");
    testBoolParsing("true");
    testStringParsing("\"this is string\"");
    testArrayParsing("[1, true, null, \"string\"]");
    testObjectParsing("{\"name\": \"Miroslav\", \"age\": 35}");
    return 0;
}