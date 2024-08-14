#include "../includes/commands/SetCommand.hpp"
#include "../includes/JSONFactory.hpp"

SetCommand::SetCommand(JSONManager* const managerPtr)
    :Command(SET_COMMAND_NAME, managerPtr) {}

bool SetCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid set command. (set <path/to/key> value)" << '\n';
        return false;
    }
    InputStringStream sStream(tokenizedCommand[2]);   
    try {
        JSONValue* value = JSONFactory::getFactory().createValue(sStream);

        getManagerPtr()->set(tokenizedCommand[1], value);
        return true;
    } catch (const CreationError& e) {
        std::cerr << "Creation error: " << e.what() << '\n';
        return false;
    }
}

bool SetCommand::validate(const Vector<String>& tokenizedCommand) {    
    if ((tokenizedCommand.Size() != 3) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}