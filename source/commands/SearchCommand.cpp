#include "../includes/commands/SearchCommand.hpp"
#include "utility/Constants.hpp"
#include <exception>
#include <stdexcept>

SearchCommand::SearchCommand(JSONManager* const managerPtr)
    :Command(constants::SEARCH_COMMAND_NAME, managerPtr) {}

bool SearchCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid search command. (search <key>)" << '\n';
        return false;
    }

    String keyForSearching = tokenizedCommand[1];

    Vector<JSONValue*> searchResults = getManagerPtr()->search(keyForSearching);

    if (searchResults.IsEmpty()) {
        std::cout  << "No values found for " << keyForSearching << '\n';
        return true;
    }

    std::cout << "Search results for " << keyForSearching << '\n';
    
    if (searchResults.Size() == 1) {
        searchResults[0]->print();
        std::cout << '\n';
        return true;
    }

    std::cout << constants::ARRAY_OPENING_BRACKET << '\n';
    for (size_t i = 0; i < searchResults.Size(); i++) {
        std::cout << "   ";
        searchResults[i]->print();
        std::cout << '\n';
    }
    std::cout << constants::ARRAY_CLOSING_BRACKET << '\n';
    return true;
}

bool SearchCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}