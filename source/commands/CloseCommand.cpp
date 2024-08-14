#include "../includes/commands/CloseCommand.hpp"

CloseCommand::CloseCommand(JSONManager* const manager)
    :Command(CLOSE_COMMAND_NAME, manager) {}

bool CloseCommand::execute(const Vector<String>& tokenizedCmd) {
    if (!validate(tokenizedCmd)) {
        return false;
    }
    
    if (!getManagerPtr()->isSaved()) {
        char userInput;
        std::cout << "Unsaved changes in " << getManagerPtr()->getCurrentFilePath()
        <<   '\n' << "Do you want to save them (y/n): ";
        while (true) {
            std::cin >> userInput;
            userInput = std::tolower(userInput);
            
            if (userInput == 'y') {
                return true;
            } else if (userInput == 'n') {
                break;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n': ";
            }
        }

    }
    getManagerPtr()->close();
    std::cout << "Successfully closed " << getManagerPtr()->getCurrentFilePath() << '\n';
    return true;
}

bool CloseCommand::validate(const Vector<String>& tokenizedCmd) {
    if ((tokenizedCmd.Size() == 1) && (tokenizedCmd[0] == getCommandName())) {
        return true;
    }
    return false;
}