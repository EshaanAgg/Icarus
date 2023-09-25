#include <bits/stdc++.h>
#include "Icarus.h"

using namespace std;

void Icarus::handleExit()
{
    cout << "Exiting the REPL. All your loaded data will be lost. Thanks!\n";
}

void Icarus::handleHi()
{
    cout << "Hi! I am Icarus, a simple REPL that allows you to perform Relational Algebra operations! Type a command to get started.\nYou can also refer to the documentation as to how to use the various commands!\n";
}

void Icarus::handleLoadCSV(string &input)
{
    string filePath = input.substr(5);
    string name = loadCSV(filePath);
    // If the name is a blank string, that means there was an error which the CSV file parsing
    if (name != "")
        cout << "The CSV file was loaded successfully as the table `" << name << "`.\n";
    else
        cout << "No table loaded.\n";
}

void Icarus::handleUnknown(string &input)
{
    cout << "Unknown command: " << input << endl;
}