#include "Icarus.h"
#include <bits/stdc++.h>

using namespace std;

void Icarus::startRELP()
{
    string input;

    while (true)
    {
        cout << REPLDemarcator;
        getline(std::cin, input);

        if (input == "EXIT")
        {
            cout << "Exiting the REPL. All your loaded data will be lost. Thanks!";
            break;
        }
        else if (input == "HI")
            cout << "Hi! I am Icarus, a simple REPL that allows you to perform Relational Algebra operations! Type a command to get started.\n";
        else if (input.substr(0, 5) == "LOAD ")
        {
            string filePath = input.substr(5);
            string name = loadCSV(filePath);
            // If the name is a blank string, that means there was an error which the CSV file parsing
            if (name != "")
                cout << "The CSV file was loaded successfully as the table " << name << ".\n";
            else
                cout << "No table loaded.\n";
        }
        else
            std::cout << "Unknown command: " << input << endl;
    }
}