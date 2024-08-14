#pragma once

#ifndef _JSON_FACTORY_HPP_
#define _JSON_FACTORY_HPP_

#include "../includes/json_types/JSONValue.hpp"

class JSONFactory {
public:
    static JSONFactory& getFactory();

    JSONValue* createValue(std::istream& is);

private:
    JSONValue* createNumber(std::istream& is);
    JSONValue* createBool(std::istream& is);
    JSONValue* createNull(std::istream& is);
    JSONValue* createString(std::istream& is);
    JSONValue* createArray(std::istream& is);
    JSONValue* createObject(std::istream& is);

private:
    JSONFactory() = default;
    JSONFactory(const JSONFactory&) = delete;
    JSONFactory& operator=(const JSONFactory&) = delete;
};

#endif //_JSON_FACTORY_HPP_