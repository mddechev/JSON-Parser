#pragma once

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "../utility/String.hpp"
#include "../utility//Vector.hpp"
#include "../JSONManager.hpp"
#include "../includes/utility/Constants.hpp"

class Command {
public:
    Command(const String& commandName, JSONManager* const managerPtr);
    
    virtual ~Command() = default;

    const String& getCommandName() const { return commandName; }

    virtual bool execute(const Vector<String>& tokenizedCommand) = 0;

protected:
    JSONManager* getManagerPtr() { return managerPtr; }

private:
    virtual bool validate(const Vector<String>& tokenizedCommand) = 0;

private:
    String commandName;
    JSONManager* managerPtr;
};

#endif //_COMMAND_HPP_