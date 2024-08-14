#pragma once

#ifndef _SET_COMMAND_HPP_
#define _SET_COMMAND_HPP_

#include "Command.hpp"

class SetCommand: public Command {
public:
    SetCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_SET_COMMAND_HPP_