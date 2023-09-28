#include <bits/stdc++.h>

using namespace std;

struct CommandInfo
{
    string command;
    vector<string> arguments;
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
        {
            string message = "INVALID_RA_COMMAND: There was an error in parsing the RA command due to invalid command format around : " + input;
            throw message;
        }

        string command = trimmedInput.substr(0, startPos);
        string argList = trimmedInput.substr(startPos + 1, endPos - startPos - 1);

        vector<string> arguments;
        size_t argStart = 0;
        size_t argEnd = 0;

        while (argEnd != string::npos)
        {
            argEnd = argList.find(',', argStart);
            string arg;
            if (argEnd != string::npos)
            {
                arg = argList.substr(argStart, argEnd - argStart);
                argStart = argEnd + 1;
            }
            else
                arg = argList.substr(argStart);
            string trimmedArg = trim(arg);
            if (trimmedArg.size() != 0)
                arguments.push_back(trimmedArg);
        }

        return {command, arguments};
    }

    static bool isCommand(const string &input)
    {
        // Remove leading and trailing whitespace
        string trimmedInput = trim(input);

        size_t startPos = trimmedInput.find('(');
        size_t endPos = trimmedInput.find(')');

        return !(startPos == string::npos && endPos == string::npos);
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
