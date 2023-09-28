#include <bits/stdc++.h>
using namespace std;

struct CommandInfo
{
    string command;
    vector<std::string> arguments;
    bool isRACommand;
};

// A class to encapsulate parsing of commands
class CommandParser
{
public:
    // Validates the passed commands and returns a CommandInfo struct
    static CommandInfo parseCommand(const string &input)
    {
        // Remove leading and trailing whitespace
        string trimmedInput = trim(input);

        size_t startPos = trimmedInput.find('(');
        size_t endPos = trimmedInput.find(')');

        if (startPos == string::npos || endPos == string::npos || startPos >= endPos)
            throw "INVALID_RA_COMMAND: There was an error in parsing the RA command due to invalid command format around : " + input;

        string command = trimmedInput.substr(0, startPos);
        string argList = trimmedInput.substr(startPos + 1, endPos - startPos - 1);

        vector<string> arguments;
        size_t argStart = 0;
        size_t argEnd = 0;

        while (argEnd != string::npos)
        {
            argEnd = argList.find(',', argStart);
            string arg;
            if (argEnd != std::string::npos)
            {
                arg = argList.substr(argStart, argEnd - argStart);
                argStart = argEnd + 1;
            }
            else
                arg = argList.substr(argStart);
            arguments.push_back(trim(arg));
        }

        return {command, arguments, true};
    }

private:
    // Helper function to trim leading and trailing whitespace
    static string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        if (first == string::npos || last == string::npos)
            return "";
        return str.substr(first, last - first + 1);
    }
};
