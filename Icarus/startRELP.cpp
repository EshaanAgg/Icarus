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
        else if (input.substr(0, 5) == "LOAD ")
        {
            string filePath = input.substr(5);
            string name = loadCSV(filePath);
            cout << "The CSV file was loaded successfully as the table " << name << "\n";
        }
        else
            std::cout << "Unknown command: " << input << endl;
    }
}