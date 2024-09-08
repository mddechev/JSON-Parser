#ifndef _CONTAINS_COMMAND_HPP_
#define _CONTAINS_COMMAND_HPP_

#include "Command.hpp"

class ContainsCommand: public Command {
public:
    ContainsCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_CONTAINS_COMMAND_HPP_