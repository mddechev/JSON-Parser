#pragma once

#ifndef _CLOSE_COMMAND_HPP_
#define _CLOSE_COMMAND_HPP_

#include "Command.hpp"

class CloseCommand: public Command {
public:
    CloseCommand(JSONManager* const managerPtr);
    
    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_CLOSE_COMMAND_HPP_