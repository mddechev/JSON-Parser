#include "../includes/commands/CreateCommand.hpp"
#include "../includes/JSONFactory.hpp"

CreateCommand::CreateCommand(JSONManager* const managerPtr)
    :Command(CREATE_COMMAND_NAME, managerPtr) {}

bool CreateCommand::execute(const Vector<String>& tokenizedCommand) {
    if (!validate(tokenizedCommand)) {
        std::cerr << "Invalid create command. (create <path/to/key> value)" << '\n';
        return false;
    }
    String path(tokenizedCommand[1]);
    InputStringStream inputStreamValue(tokenizedCommand[2]);

    try {
        JSONValue* valueToCreate = JSONFactory::getFactory().createValue(inputStreamValue);
        getManagerPtr()->create(path, valueToCreate);
        return true;
    } catch (const CreationError& e) {
        std::cerr << "Invalid JSON value: " << e.what() << '\n';
        return false;
    }
}

bool CreateCommand::validate(const Vector<String>& tokenizedCommand) {
    if ((tokenizedCommand.Size() != 3) || (tokenizedCommand[0] != getCommandName())) {
        return false;
    }
    return true;
}