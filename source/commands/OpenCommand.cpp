#include "../includes/commands/OpenCommand.hpp"
#include "JSONException.hpp"

OpenCommand::OpenCommand(JSONManager* const managerPtr)
    :Command(OPEN_COMMAND_NAME, managerPtr) {}
    
bool OpenCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid open command. (open <path/to/file/name>)" << '\n';
        return false;
    }
    try {
        getManagerPtr()->open(tokenizedCommand[1]);
        std::cout << "Successfully opened: " << tokenizedCommand[1] << '\n';
        return true;
    } catch (const FileError& e) {
        std::cerr << "File error: " << e.what() << '\n';
        return false;
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << "Validation error - " << e.what() << '\n';
        return false;
    }
}

bool OpenCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}