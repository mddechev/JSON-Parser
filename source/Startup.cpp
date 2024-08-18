#include "../includes/Startup.hpp"
#include "JSONException.hpp"
#include "json_types/JSONNumber.hpp"
#include "json_types/JSONString.hpp"
#include "json_types/JSONValue.hpp"

void Startup::run() {
    JSONManager* manager = new JSONManager;
    CommandHandler handler(manager);
    
    std::cout << "\n╔═══════════════════════════════════════════════════════╗\n"
              <<   "║      WELCOME TO JSON PARSER CONSOLE APPLICATION       ║\n"
              <<   "╚═══════════════════════════════════════════════════════╝\n";
    
    helpers::printInfo();
    
    try {
        while (true) {
            String command;
            std::cout << '\n' << "> ";
            helpers::getLine(std::cin, command);
            
            if (!handler.handle(command)) {
                std::cout << '\n' << "Command failed. Please try again" << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << '\n';
    }
    
    delete manager;
}

void Startup::runDemo() {
    JSONManager manager;
    try {
        std::cout << "Opening ../JSONfiles/organisation.json" << "\n\n";
        manager.open("../JSONfiles/organisation.json");
        std::cout << "Printing ../JSONfiles/organisation.json" << '\n';
        manager.print();
        std::cout << '\n';
        
        Vector<JSONValue* > searchResults = manager.search("name");
        std::cout << "Search results for name" << '\n';
        std::cout << ARRAY_OPENING_BRACKET << '\n';
        for (size_t i = 0; i < searchResults.Size(); i++) {
            std::cout << "   ";
            searchResults[i]->print();
            std::cout << '\n';
        }
        std::cout << ARRAY_CLOSING_BRACKET << '\n';

        std::cout << "Setting management/directorId to 2" << '\n';
        manager.set("management/directorId", new JSONNumber(2));
        
        std::cout << "After set operation" << '\n';
        manager.print();
        std::cout << '\n' << "Creating management/directorName \"Petar Tudjarov\"" << '\n';
        manager.create("management/directorName", new JSONString("Petar Tudjarov"));
        std::cout << "After create operation" << '\n';
        manager.print();
        std::cout << '\n' << "Removing management/directorName" << '\n';
        manager.remove("management/directorName");
        std::cout << "After remove operation" << '\n';
        manager.print();
    
        std::cout << '\n' << "Closing manager and ../JSONfiles/organisation.json" << '\n';
        manager.close();
    
    } catch (const JSONException& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
}