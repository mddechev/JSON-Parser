#include "../includes/commands/PrintCommand.hpp"

PrintCommand::PrintCommand(JSONManager* const managerPtr)
    :Command(constants::PRINT_COMMAND_NAME, managerPtr) {}

bool PrintCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        return false;
    }
    getManagerPtr()->print();
    return true;
}

bool PrintCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() == 1) && (tokenizedCommand[0] == getCommandName())) {
        return true;
    }
    return false;
}