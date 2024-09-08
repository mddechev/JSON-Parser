#ifndef _SAVE_AS_COMMAND_HPP_
#define _SAVE_AS_COMMAND_HPP_

#include "Command.hpp"

class SaveAsCommand: public Command {
public:
    SaveAsCommand(JSONManager* const managerPtr);

    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_SAVE_AS_COMMAND_HPP_