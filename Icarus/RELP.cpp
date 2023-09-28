#include "Icarus.h"
#include "Parser/Parser.h"
#include <bits/stdc++.h>

using namespace std;

void Icarus::startREPL()
{
    string input;
    while (true)
    {
        cout << REPLDemarcator;
        getline(cin, input);
        execute(input);
    }
}

void Icarus::execute(string input)
{
    // First check for all the non-nestable commands
    if (input == "EXIT")
    {
        handleExit();
        exit(0);
    }
    else if (input == "HI")
        handleHi();
    else if (input == "SHOW TABLES")
        showTables();
    else if (input.substr(0, 4) == "SHOW")
    {
        string tableName = input.substr(5);
        showTable(tableName);
    }
    else if (input.substr(0, 5) == "LOAD ")
        handleLoadCSV(input);
    // In the default case, the blank string of input must be ignored.
    else if (input != "")
    {
        try
        {
            parser.parseAndExecute(input);
        }
        catch (string errorCode)
        {
            cout << "Tried executing the same with as a Relational Algrebra command but recieved the following errorCode: " << errorCode << "\n";
        }
    }
}