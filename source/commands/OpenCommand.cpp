#include "../includes/commands/OpenCommand.hpp"
#include "JSONException.hpp"

OpenCommand::OpenCommand(JSONManager* const managerPtr)
    :Command(constants::OPEN_COMMAND_NAME, managerPtr) {}
    
bool OpenCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid open command. (open <path/to/file/name>)" << '\n';
        return false;
    }

    String filePath = tokenizedCommand[1];
    try {
        getManagerPtr()->open(filePath);
        std::cout << "Successfully opened: " << filePath << '\n';
        return true;
    } catch (const FileError& e) {
        std::cerr << "File error: " << e.what() << '\n';
        return false;
    } catch (const InvalidJSONSyntax& e) {
        std::cerr << "Invalid JSON in " << filePath << ": " << e.what() << '\n';
        return false;
    }
}

bool OpenCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 2) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}