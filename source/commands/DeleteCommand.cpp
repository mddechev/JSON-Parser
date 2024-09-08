#include "../includes/commands/DeleteCommand.hpp"

DeleteCommand::DeleteCommand(JSONManager* const managerPtr)
    :Command(constants::DELETE_COMMAND_NAME, managerPtr) {}

bool DeleteCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid delete command. (delete <path/to/value>)" << '\n';
        return false;
    }
    getManagerPtr()->remove(tokenizedCommand[1]);
    return true;
}

bool DeleteCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}