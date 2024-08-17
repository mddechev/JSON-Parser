#include "../includes/commands/SaveCommand.hpp"
#include <stdexcept>


SaveCommand::SaveCommand(JSONManager* const managerPtr)
    :Command(SAVE_COMMAND_NAME, managerPtr) {}

bool SaveCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        return false;
    }

    if (!getManagerPtr()->save()) {
        std::cout << "No changes made to save in " << getManagerPtr()->getCurrentFilePath() << '\n';
        return true;
    }
    std::cout << "Successfully saved changes in " << getManagerPtr()->getCurrentFilePath() << '\n';
    return true;
}

bool SaveCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() == 1) && (tokenizedCommand[0] == getCommandName())) {
        return true;
    }
    return false;
}