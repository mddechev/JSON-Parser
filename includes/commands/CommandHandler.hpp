#pragma once

#ifndef _COMMAND_HANDLER_HPP_
#define _COMMAND_HANDLER_HPP_

#include "Command.hpp"
#include "../utility/Helpers.hpp"
#include "../utility/Vector.hpp"

class CommandHandler {
public:
    CommandHandler(JSONManager* const managerPtr);
    ~CommandHandler();

    bool handle(const String& commandName);

private:
    Command* getCommandByName(const String& commandName) const;

private:
    Vector<Command*> supportedCommands;
};

#endif //_COMMAND_HANDLER_HPP_