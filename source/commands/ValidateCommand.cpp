#include "../includes/commands/ValidateCommand.hpp"

ValidateCommand::ValidateCommand(JSONManager* const manager)
    :Command(VALIDATE_COMMAND_NAME, manager) {}

bool ValidateCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}

bool ValidateCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid validate command. (validate <path/to/file/name>)" << '\n';
        return false;
    }
    if (getManagerPtr()->validate(tokenizedCommand[1])) {
        std::cout << "Successful validation of " << tokenizedCommand[1] << '\n';
        return true;
    }
    return false;
}