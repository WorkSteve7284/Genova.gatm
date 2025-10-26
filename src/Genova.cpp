#include "Genova.h"
#include <iostream>
#include <string>

void Genova::start() {
    std::cout << "Welcome to Genova - type 'help' for commands.";
    std::string input;
    while(true){
        std::cout << "\n> ";
        std::getline(std::cin,input);
        if(input=="exit"){ std::cout << "Goodbye!\n"; break; }
        input = variables.substitute(input);
        tools.handle(input);
    }
}
