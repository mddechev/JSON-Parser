#pragma once

#ifndef _START_UP_HPP_
#define _START_UP_HPP_

#include "../includes/JSONManager.hpp"
#include "../includes/commands/CommandHandler.hpp"

class Startup {
public:
    static void run();
    static void runDemo();
};

#endif //_START_UP_HPP_