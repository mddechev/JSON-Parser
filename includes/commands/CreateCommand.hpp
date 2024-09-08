#ifndef _CREATE_COMMAND_HPP_
#define _CREATE_COMMAND_HPP_

#include "Command.hpp"

class CreateCommand: public Command {
public:
    CreateCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_CREATE_COMMAND_HPP_