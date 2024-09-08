#ifndef _SEARCH_COMMAND_HPP_
#define _SEARCH_COMMAND_HPP_

#include "Command.hpp"

class SearchCommand: public Command {
public:
    SearchCommand(JSONManager* const managerPtr);
        
    bool execute(const Vector<String>& tokenizedCommand) override;

private:
    bool validate(const Vector<String>& tokenizedCommand) override;
};

#endif //_SEARCH_COMMAND_HPP_