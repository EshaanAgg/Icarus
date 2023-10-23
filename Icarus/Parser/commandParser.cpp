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
    static CommandInfo parseCommand(string &input)
    {
        // Remove leading and trailing whitespace
        string trimmedInput = trim(input);

        string command = "";
        string arg = "";
        vector<string> args;
        int balance = 0;

        for (int i = 0; i < trimmedInput.size(); i++)
        {
            char c = trimmedInput[i];
            if (balance == 0)
            {
                if (c == '(')
                    balance++;
                else
                    command += c;
                continue;
            }

            if (c == '(')
            {
                balance++;
                arg += c;
            }
            else if (c == ')')
            {
                balance--;
                if (balance == 0)
                {
                    args.push_back(arg);
                    i++;
                    while (i < trimmedInput.size())
                    {
                        if (!isspace(trimmedInput[i]))
                            throw "SYNTAX_ERROR: Only one command can be executed in the REPL at a time";
                        i++;
                    }
                }
                arg += c;
            }
            else if (c == ',')
            {
                if (balance == 1)
                {
                    args.push_back(arg);
                    arg = "";
                }
                else
                    arg += c;
            }
            else
                arg += c;
        }

        if (balance != 0)
            throw "INVALID_COMMAND: The brackets are not properly balanced"s;

        vector<string> newArgs;
        for (string &arg : args)
        {
            arg = trim(arg);
            if (arg != "")
                newArgs.push_back(arg);
        }
        return {trim(command), newArgs};
    }

    static bool isCommand(string &input)
    {
        // Remove leading and trailing whitespace
        string trimmedInput = trim(input);

        size_t startPos = trimmedInput.find('(');
        size_t endPos = trimmedInput.find(')');

        return !(startPos == string::npos && endPos == string::npos);
    }

private:
    // Helper function to trim leading and trailing whitespace
    static string trim(string &str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        if (first == string::npos || last == string::npos)
            return "";
        return str.substr(first, last - first + 1);
    }
};
