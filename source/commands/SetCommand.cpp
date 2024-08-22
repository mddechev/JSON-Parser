#include "../includes/commands/SetCommand.hpp"
#include "../includes/JSONFactory.hpp"
#include "JSONValidator.hpp"

SetCommand::SetCommand(JSONManager* const managerPtr)
    :Command(SET_COMMAND_NAME, managerPtr) {}

bool SetCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid set command. (set <path/to/key> value)" << '\n';
        return false;
    }
    
    String path(tokenizedCommand[1]);
    InputStringStream inputStreamValue(tokenizedCommand[2]);   

    try {
        JSONValue* valueToSet = JSONFactory::getFactory().createValue(inputStreamValue);

        getManagerPtr()->set(path, valueToSet);
        return true;

    } catch (const CreationError& e) {
        std::cerr << "Invalid JSON value: " << e.what() << '\n';
        return false;
    }
}

bool SetCommand::validate(const Vector<String>& tokenizedCommand) {    
    if ((tokenizedCommand.Size() != 3) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}