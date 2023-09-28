#include <bits/stdc++.h>
#include "../Icarus.h"

using namespace std;

Table Parser::performProjection(vector<string> args)
{
    if (args.size() < 2)
        throw "INVALID_ARGS: Projection operation requires >= 2 arguments: (TableName, fieldName1, fieldName2, ...)"s;

    try
    {
        Table table;
        if (cmdParser.isCommand(args[0]))
            table = parseAndExecute(args[0]);
        else
        {
            int index = icarus->getTableIndex(args[0]);
            if (index == -1)
            {
                string message = "INVALID_ARGS: There is no table with the name `" + args[0] + "`";
                throw message;
            }
            table = icarus->tables[index];
        }

        // Remove the table name from the arguments list
        args.erase(args.begin());
        return table.project(args);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performRename(vector<string> args)
{
    if (args.size() < 2)
        throw "INVALID_ARGS: Rename operation requires 2 arguments: (OldTableName, NewTableName)"s;

    Table table;
    int index = icarus->getTableIndex(args[0]);
    if (index == -1)
    {
        string message = "INVALID_ARGS: There is no table with the name `" + args[0] + "`";
        throw message;
    }
    Table::rename(icarus->tables[index], args[1]);

    string data = "OldName, NewName\n" + args[0] + "," + args[1];
    return Table::createTableFromData(data);
}