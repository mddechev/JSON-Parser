#include "../../includes/utility//Helpers.hpp"

namespace helpers {
    Vector<String> tokenizeLineToStrings(const String& line, char delimiter) {
        Vector<String> result;
        String current;
        for (size_t i = 0; i < line.Length(); i++) {
            if (line[i] == delimiter) {
                if (!current.IsEmpty()) {
                    result.PushBack(current);
                    current.Reuse();
                } 
            } else {
                current += line[i];
            }
        }

        if (!current.IsEmpty()) {
            result.PushBack(current);
        }
        return result;
    }
   
    void getLine(std::istream& inputStream, String& result, size_t length, const char delimiter) {
        result.Reuse();
        char character;
        size_t count = 0;

        while (count < length && inputStream.get(character) && character != delimiter) {
            result += character;
            ++count;
        }    
    }

    //list of commands box written by claude Ai
    void printInfo(std::ostream& outputStream) {
        outputStream << "\n╔═════════════════════════ LIST  OF COMMANDS ════════════════════════════╗\n"
                     <<   "║      validate <path/to/file>         open <path/to/file>               ║\n"
                     <<   "║      print                           set <path/to/value> <value>       ║\n"
                     <<   "║      create <path> <value>           delete <path/to/value>            ║\n"
                          "║      search <key>                    contains <value>                  ║\n"
                     <<   "║      save                            saveas <path/to/file>             ║\n"
                     <<   "║      close                           exit                              ║\n"
                     <<   "╚════════════════════════════════════════════════════════════════════════╝\n\n";
    }

    bool isDigit(const char character) {
        return character >= '0' && character <= '9';
    }
}