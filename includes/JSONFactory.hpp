#ifndef _JSON_FACTORY_HPP_
#define _JSON_FACTORY_HPP_

#include "../includes/json_types/JSONValue.hpp"

class JSONFactory {
public:
    static JSONFactory& getFactory();

    JSONValue* createValue(std::istream& inputStream);

private:
    JSONValue* createNumber(std::istream& inputStream);
    JSONValue* createBool(std::istream& inputStream);
    JSONValue* createNull(std::istream& inputStream);
    JSONValue* createString(std::istream& inputStream);
    JSONValue* createArray(std::istream& inputStream);
    JSONValue* createObject(std::istream& inputStream);

private:
    JSONFactory() = default;
    JSONFactory(const JSONFactory&) = delete;
    JSONFactory& operator=(const JSONFactory&) = delete;
};

#endif //_JSON_FACTORY_HPP_