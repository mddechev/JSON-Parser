#pragma once

#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <cstddef>

const char ARRAY_OPENING_BRACKET = '[';
const char ARRAY_CLOSING_BRACKET = ']';
const char OBJECT_OPENING_BRACKET = '{';
const char OBJECT_CLOSING_BRACKET = '}';
const char DOUBLE_QUOTE = '\"';

const char OPEN_COMMAND_NAME[] = "open";
const char VALIDATE_COMMAND_NAME[] = "validate";
const char CLOSE_COMMAND_NAME[] = "close";
const char EXIT_COMMAND_NAME[] = "exit";
const char CREATE_COMMAND_NAME[] = "create";
const char SET_COMMAND_NAME[] = "set";
const char DELETE_COMMAND_NAME[] = "delete";
const char SAVE_COMMAND_NAME[] = "save";
const char SAVE_AS_COMMAND_NAME[] = "saveas";
const char PRINT_COMMAND_NAME[] = "print";
const char MOVE_COMMAND_NAME[] = "move";
const char CONTAINS_COMMAND_NAME[] = "contains";
const char SEARCH_COMMAND_NAME[] = "search";

const size_t SUPPORTED_COMMANDS_COUNT = 12;
const size_t NULL_LEN = 4;

#endif //_CONSTANTS_HPP_



