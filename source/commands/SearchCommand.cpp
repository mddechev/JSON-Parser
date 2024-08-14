#include "../includes/commands/SearchCommand.hpp"
#include <exception>
#include <stdexcept>

SearchCommand::SearchCommand(JSONManager* const manager)
    :Command(SEARCH_COMMAND_NAME, manager) {}

bool SearchCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid search command. (search <key>)" << '\n';
        return false;
    }
    try {
        Vector<JSONValue*> searchResults = getManagerPtr()->search(tokenizedCommand[1]);
        std::cout << "Search results for " << tokenizedCommand[1] << '\n';
        std::cout << ARRAY_OPENING_BRACKET << '\n';
        for (size_t i = 0; i < searchResults.Size(); i++) {
            std::cout << "  ";
            searchResults[i]->print();
            std::cout << '\n';
        }
        std::cout << ARRAY_CLOSING_BRACKET << '\n';
        return true;
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return false;
    }   
}

bool SearchCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}