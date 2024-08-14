#pragma once

#ifndef _SAVE_COMMAND_HPP_
#define _SAVE_COMMAND_HPP_

#include "Command.hpp"

class SaveCommand: public Command {
public:
    SaveCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_SAVE_COMMAND_HPP_