#include "Parser.h"
#include "bits/stdc++.h"

using namespace std;

void Parser::parseAndExecute(string cmd)
{
    try
    {
        CommandInfo cmdInfo = cmdParser.parseCommand(cmd);
        if (cmdInfo.command == "PROJECT")
            performProjection(cmdInfo.arguments);
    }
    catch (string error)
    {
        cout << "An error occurred in the execution of the command.\n";
        cout << error << "\n";
    }
}