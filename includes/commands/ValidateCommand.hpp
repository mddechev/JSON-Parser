#pragma once

#ifndef _VALIDATE_COMMAND_HPP_
#define _VALIDATE_COMMAND_HPP_

#include "Command.hpp"

class ValidateCommand: public Command {
public:
    ValidateCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;
private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_VALIDATE_COMMAND_HPP_