#pragma once

#ifndef _OPEN_COMMAND_HPP_
#define _OPEN_COMMAND_HPP_

#include "Command.hpp"

class OpenCommand: public Command {
public:
    OpenCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_OPEN_COMMAND_HPP_