// #include "../includes/commands/MoveCommand.hpp"
// #include <exception>

// MoveCommand::MoveCommand(JSONManager* const manager)
//     :Command(MOVE_COMMAND_NAME, manager) {}

// bool MoveCommand::execute(const Vector<String>& tokenizedCmd) {
//     if (!validate(tokenizedCmd)) {
//         std::cout << "Invalid move command. (move from/path to/path)\n";
//         return false;
//     }
//     try {
//         getManager()->move(tokenizedCmd[1], tokenizedCmd[2]);
//         return true;
//     } catch (const std::exception& e) {
//         std::cerr << "Exception in move execute: " << e.what() << '\n';
//         return false;
//     }
//     return true;
// }

// bool MoveCommand::validate(const Vector<String>& tokenizedCmd) {
//     if ((tokenizedCmd.Size() != 3) || (tokenizedCmd[0] != getName())) {
//         return false;
//     }
//     return true;
// }