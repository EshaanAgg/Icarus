#include <bits/stdc++.h>
#include "../Icarus.h"

using namespace std;

Table Parser::parseAndExecute(string cmd)
{
    try
    {
        CommandInfo cmdInfo = cmdParser.parseCommand(cmd);
        if (supportedCommands.find(cmdInfo.command) == supportedCommands.end())
        {
            string message = "INVALID_COMMAND: The following is not a recognised command: " + cmdInfo.command;
            throw message;
        }

        // Match the command to its corresponding handler
        if (cmdInfo.command == "PROJECT")
            return performProjection(cmdInfo.arguments);
        else if (cmdInfo.command == "RENAME")
            return performRename(cmdInfo.arguments);
        else if (cmdInfo.command == "SELECT")
            return performSelect(cmdInfo.arguments);

        throw "PROGRAMMING_ERROR: All supported command's haven't been registered a handler."s;
    }
    catch (string error)
    {
        cout << "An error occurred in the execution of the command.\n";
        throw error;
    }
}