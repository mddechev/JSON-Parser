#pragma once

#ifndef _JSON_PARSER_HPP_
#define _JSON_PARSER_HPP_

#include "json_types/JSONNull.hpp"
#include "../includes/json_types/JSONArray.hpp"
#include "../includes/json_types/JSONObject.hpp"

class JSONFactory;

class JSONParser {
public:
    static JSONNull parseNull(std::istream& inputStream);

    static double parseNumber(std::istream& inputStream);

    static bool parseBool(std::istream& inputStream);

    static String parseString(std::istream& inputStream);

    static void parseArray(std::istream& inputStream, JSONArray* toBeFilledArray);

    static void parseObject(std::istream& inputStream, JSONObject* toBeFilledObject);
};

#endif //_JSON_PARSER_HPP_