#pragma once

#ifndef _JSON_VALIDATOR_HPP_
#define _JSON_VALIDATOR_HPP_

#include <cctype>
#include <iostream>

class JSONValidator {
public:
    static void validate(std::istream& inputStream);

private:
    static void validateValue(std::istream& inputStream);
    static void validateNumber(std::istream& inputStream);
    static void validateNull(std::istream& inputStream);
    static void validateBool(std::istream& inputStream);
    static void validateString(std::istream& inputStream);
    static void validateArray(std::istream& inputStream);
    static void validateObject(std::istream& iinputStreams);
};

#endif //_JSON_VALIDATOR_HPP_
