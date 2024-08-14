#include "../includes/commands/SaveCommand.hpp"
#include <stdexcept>


SaveCommand::SaveCommand(JSONManager* const managerPtr)
    :Command(SAVE_COMMAND_NAME, managerPtr) {}

bool SaveCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        return false;
    }
    try {
        getManagerPtr()->save();
    } catch (const FileError& e) {
        std::cerr << e.what() << '\n';
        return true;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return true;
    }
    std::cout << "Saved changes in " << getManagerPtr()->getCurrentFilePath() << '\n';
    return true;
}

bool SaveCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() == 1) && (tokenizedCommand[0] == getCommandName())) {
        return true;
    }
    return false;
}