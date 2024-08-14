#pragma once

#ifndef _EXIT_COMMAND_HPP_
#define _EXIT_COMMAND_HPP_

#include "Command.hpp"

class ExitCommand: public Command {
public:
    ExitCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_EXIT_COMMAND_HPP_