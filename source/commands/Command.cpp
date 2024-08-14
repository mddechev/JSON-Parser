#include "../includes/commands/Command.hpp"

Command::Command(const String& commandName, JSONManager* const managerPtr)
    :commandName(commandName), managerPtr(managerPtr) {}