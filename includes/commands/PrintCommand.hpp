#pragma once

#ifndef _PRINT_COMMAND_HPP_
#define _PRINT_COMMAND_HPP_

#include "Command.hpp"

class PrintCommand: public Command {
public:
    PrintCommand(JSONManager* const managerPtr);
        
    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_PRINT_COMMAND_HPP_