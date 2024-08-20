#include "../includes/commands/ValidateCommand.hpp"

ValidateCommand::ValidateCommand(JSONManager* const managerPtr)
    :Command(VALIDATE_COMMAND_NAME, managerPtr) {}

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
   try {
        getManagerPtr()->validate(tokenizedCommand[1]);
        std::cout << "Successfull validation of " << tokenizedCommand[1] << '\n';
        return true;
   } catch (const InvalidJSONSyntax& e) {
        std::cerr << "Validation error - " << e.what() << '\n';
        return true;
    } catch (const FileError& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
}