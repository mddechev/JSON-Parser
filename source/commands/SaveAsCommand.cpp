#include "../includes/commands/SaveAsCommand.hpp"


SaveAsCommand::SaveAsCommand(JSONManager* const managerPtr)
    :Command(SAVE_AS_COMMAND_NAME, managerPtr) {}

bool SaveAsCommand::execute(const Vector<String>& tokenizedCmd) {
    if (!validate(tokenizedCmd)) {
        std::cerr << "Invalid saveas command. (saveas <path/to/file/name>)" << '\n';
        return false;
    }
    getManagerPtr()->saveAs(tokenizedCmd[1]);
    std::cout << "Saved to " << tokenizedCmd[1] << '\n'; 
    return true;
}

bool SaveAsCommand::validate(const Vector<String>& tokenizedCmd) {
    if ((tokenizedCmd.Size() != 2) || (tokenizedCmd[0] != getCommandName())) {
        return false;
    }
    return true;
}