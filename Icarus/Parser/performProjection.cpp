#include <bits/stdc++.h>
#include "../Icarus.h"

using namespace std;

Table Parser::performProjection(vector<string> args)
{
    if (args.size() < 2)
        throw "INVALID_ARGS: Projection operation requires >= 2 arguments: (TableName, fieldName1, fieldName2, ...)";

    Table table;
    if (cmdParser.isCommand(args[0]))
        table = parseAndExecute(args[0]);
    else
    {
        int index = icarus->getTableIndex(args[0]);
        if (index == -1)
            throw "INVALID_ARGS: There is no table with the name `" + args[0] + "`";
        table = icarus->tables[index];
    }

    // Remove the table name from the arguments list
    args.erase(args.begin());

    try
    {
        return table.project(args);
    }
    catch (string error)
    {
        throw error;
    }
}
