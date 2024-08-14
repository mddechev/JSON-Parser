#include "../includes/commands/ContainsCommand.hpp"

ContainsCommand::ContainsCommand(JSONManager* const managerPtr)
    :Command(CONTAINS_COMMAND_NAME, managerPtr) {}

bool ContainsCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid contains command. (contains <value>)" << '\n';
        return false;
    }
    if (getManagerPtr()->contains(tokenizedCommand[1])) {
        std::cout << "True" << '\n';
        return true;
    } 
    std::cout << "False" << '\n';
    return true;
}

bool ContainsCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }

    return true;
}
