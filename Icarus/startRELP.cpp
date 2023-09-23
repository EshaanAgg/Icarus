#include "Icarus.h"
#include <bits/stdc++.h>

void Icarus::startRELP()
{
    std::string input;

    while (true)
    {
        std::cout << REPLDemarcator;
        std::getline(std::cin, input);

        if (input == "EXIT")
        {
            std::cout << "Exiting the REPL. All your loaded data will be lost. Thanks!";
            break;
        }
        else if (input.substr(0, 5) == "LOAD(")
        {
            std::string filePath = "" loadCSV(filePath);
        }
        else
            std::cout << "Unknown command: " << input << std::endl;
    }
}