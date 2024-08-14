#pragma once

#ifndef _DELETE_COMMAND_HPP_
#define _DELETE_COMMAND_HPP_

#include "Command.hpp"

class DeleteCommand: public Command {
public:
    DeleteCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_DELETE_COMMAND_HPP_