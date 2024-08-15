#include "../includes/commands/CreateCommand.hpp"
#include "../includes/JSONFactory.hpp"

CreateCommand::CreateCommand(JSONManager* const managerPtr)
    :Command(CREATE_COMMAND_NAME, managerPtr) {}

bool CreateCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid create command. (create <path/to/key> value)" << '\n';
        return false;
    }
   
    InputStringStream inputStream(tokenizedCommand[2]);
    
    try {
        JSONValue* value = JSONFactory::getFactory().createValue(inputStream);
        getManagerPtr()->create(tokenizedCommand[1], value);
        delete value;
        return true;
    } catch (const CreationError& e) {
        std::cerr << "Creation error from factory: " << e.what() << '\n';
        return false;
    }
}

bool CreateCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 3) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}