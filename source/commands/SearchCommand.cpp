#include "../includes/commands/SearchCommand.hpp"
#include <exception>
#include <stdexcept>

SearchCommand::SearchCommand(JSONManager* const managerPtr)
    :Command(SEARCH_COMMAND_NAME, managerPtr) {}

bool SearchCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid search command. (search <key>)" << '\n';
        return false;
    }

    Vector<JSONValue*> searchResults = getManagerPtr()->search(tokenizedCommand[1]);

    if (searchResults.IsEmpty()) {
        std::cout  << "No values found for key: " << tokenizedCommand[1] << '\n';
        return true;
    }

    std::cout << "Search results for " << tokenizedCommand[1] << '\n';
    
    if (searchResults.Size() == 1) {
        searchResults[0]->print();
        std::cout << '\n';
        return true;
    }

    std::cout << ARRAY_OPENING_BRACKET << '\n';
    for (size_t i = 0; i < searchResults.Size(); i++) {
        std::cout << "  ";
        searchResults[i]->print();
        std::cout << '\n';
    }
    std::cout << ARRAY_CLOSING_BRACKET << '\n';
    return true;
}

bool SearchCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}