#include "../includes/commands/SaveAsCommand.hpp"


SaveAsCommand::SaveAsCommand(JSONManager* const managerPtr)
    :Command(constants::SAVE_AS_COMMAND_NAME, managerPtr) {}

bool SaveAsCommand::execute(const Vector<String>& tokenizedCmd) {

    if (!validate(tokenizedCmd)) {
        std::cerr << "Invalid saveas command. (saveas <path/to/file/name>)" << '\n';
        return false;
    }

    String saveAsFilePath = tokenizedCmd[1];

    getManagerPtr()->saveAs(saveAsFilePath);
    std::cout << "Saved to " << saveAsFilePath << '\n'; 
    return true;
}

bool SaveAsCommand::validate(const Vector<String>& tokenizedCmd) {
    if ((tokenizedCmd.Size() != 2) || (tokenizedCmd[0] != getCommandName())) {
        return false;
    }
    return true;
}