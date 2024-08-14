#include "../includes/commands/PrintCommand.hpp"

PrintCommand::PrintCommand(JSONManager* const manager)
    :Command(PRINT_COMMAND_NAME, manager) {}

bool PrintCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        return false;
    }
    std::cout << "Printing data....\n";
    getManagerPtr()->print();
    return true;
}

bool PrintCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() == 1) && (tokenizedCommand[0] == getCommandName())) {
        return true;
    }
    return false;
}