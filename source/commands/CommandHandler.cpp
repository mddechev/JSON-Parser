#include "../../includes/commands//CommandHandler.hpp"
#include "../../includes/commands/ValidateCommand.hpp"
#include "../../includes/commands/PrintCommand.hpp"
#include "../../includes/commands/OpenCommand.hpp"
#include "../../includes/commands/CloseCommand.hpp"
#include "../../includes/commands/SaveCommand.hpp"
#include "../../includes/commands/ExitCommand.hpp"
#include "../../includes/commands/SaveAsCommand.hpp"
#include "../../includes/commands/SearchCommand.hpp"
#include "../../includes/commands/ContainsCommand.hpp"
#include "../../includes/commands/SetCommand.hpp"
#include "../../includes/commands/CreateCommand.hpp"
#include "../../includes/commands/DeleteCommand.hpp"
#include "../../includes/commands/MoveCommand.hpp"
#include "utility/Constants.hpp"

CommandHandler::CommandHandler(JSONManager* const managerPtr) {
    Command* supportedCommands[SUPPORTED_COMMANDS_COUNT] = {
        new ValidateCommand(managerPtr),
        new PrintCommand(managerPtr),
        new OpenCommand(managerPtr),
        new CloseCommand(managerPtr),
        new SaveCommand(managerPtr),
        new SaveAsCommand(managerPtr),
        new ExitCommand(managerPtr),
        new SearchCommand(managerPtr),
        new ContainsCommand(managerPtr),
        new SetCommand(managerPtr),
        new CreateCommand(managerPtr),
        new DeleteCommand(managerPtr),
    };
    
    for (size_t i = 0; i < SUPPORTED_COMMANDS_COUNT; i++) {
        this->supportedCommands.PushBack(supportedCommands[i]);
    }
}

CommandHandler::~CommandHandler() {
    for (size_t i = 0; i < supportedCommands.Size(); i++) {
        delete supportedCommands[i];
    }
}

bool CommandHandler::handle(const String &command) {
    Vector<String> tokenizedCommand = helpers::tokenizeLineToStrings(command, ' ');

    if (tokenizedCommand.IsEmpty()) {
        return true;
    }
    
    try {
        Command* fetchedCommand = getCommandByName(tokenizedCommand[0]);

        if (!fetchedCommand) {
            std::cerr << "Command not found. Please enter valid command" << '\n';
            return true;
        }

        return fetchedCommand->execute(tokenizedCommand);
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return true;
    }
}

Command* CommandHandler::getCommandByName(const String& name) const {
    for (size_t i = 0; i < supportedCommands.Size(); i++) {
        if (supportedCommands[i]->getCommandName() == name) {
            return supportedCommands[i];
        }
    }
    return nullptr;
}
