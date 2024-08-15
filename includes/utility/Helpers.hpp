#pragma once

#ifndef _HELPERS_HPP_
#define macro _HELPERS_HPP_

#include "../utility/String.hpp"
#include "../utility/Vector.hpp"

namespace helpers {
    Vector<String> tokenizeLineToStrings(const String& line, char delimiter = '/');

    void getLine(std::istream& inputStream, String& result, size_t length = 1024, const char delimiter = '\n');

    void printInfo(std::ostream& outputStream = std::cout);

    bool isDigit(const char character);
}
#endif //_HELPERS_HPP_