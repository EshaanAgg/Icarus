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
        else if (cmdInfo.command == "PRODUCT")
            return performCrossProduct(cmdInfo.arguments);
        else if (cmdInfo.command == "SAVE")
            return performSave(cmdInfo.arguments);
        else if (cmdInfo.command == "JOIN")
            return performJoin(cmdInfo.arguments);
        else if (cmdInfo.command == "NATURAL")
            return performNaturalJoin(cmdInfo.arguments);
        else if (cmdInfo.command == "UNION")
            return performUnion(cmdInfo.arguments);
        else if (cmdInfo.command == "INTERSECTION")
            return performIntersection(cmdInfo.arguments);
        else if (cmdInfo.command == "DIFF")
            return performDifference(cmdInfo.arguments);
        else if (cmdInfo.command == "DIVIDE")
            return performDivide(cmdInfo.arguments);

        throw "PROGRAMMING_ERROR: All supported command's haven't been registered a handler."s;
    }
    catch (string error)
    {
        cout << "An error occurred in the execution of the command.\n";
        throw error;
    }
}