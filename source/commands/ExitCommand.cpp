#include "../includes/commands/ExitCommand.hpp"

ExitCommand::ExitCommand(JSONManager* const manager)
    :Command(EXIT_COMMAND_NAME, manager) {}

bool ExitCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        return false;
    }
    
    if (getManagerPtr()->isOpen() && !getManagerPtr()->isSaved()) {
        char userInput;
        std::cout << "Unsaved changes in " << getManagerPtr()->getCurrentFilePath()
        <<   '\n' << "Do you want to save them (y/n): ";
        while (true) {
            std::cin >> userInput;
            userInput = std::tolower(userInput);
            
            if (userInput == 'y') {
                return true;
                
            } else if (userInput == 'n') {
                getManagerPtr()->close();
                std::cout << "Closing " << getManagerPtr()->getCurrentFilePath() << " before exiting." << '\n';
                break;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n': ";
            }
        }
    }

    if (getManagerPtr()->isOpen()) {
        getManagerPtr()->close();
        std::cout << "Closing " << getManagerPtr()->getCurrentFilePath() << " before exiting." << '\n';
    }
    
    std::cout << "...Exiting application..." << '\n';
    exit(0);
}

bool ExitCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() == 1) && (tokenizedCommand[0] == getCommandName())) {
        return true;
    }
    return false;
}