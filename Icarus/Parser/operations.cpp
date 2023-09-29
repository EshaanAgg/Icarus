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

    // Check for integrity of the names
    int index = icarus->getTableIndex(args[0]);
    if (index == -1)
    {
        string message = "INVALID_ARGS: There is no table with the name `" + args[0] + "`";
        throw message;
    }
    if (icarus->tableNames.find(args[1]) != icarus->tableNames.end())
    {
        string message = "INVALID_ARGS: A table with name `" + args[1] + "` already exists. The new name provided should be unique.";
        throw message;
    }

    // Update the table name in the `tableNames` set
    icarus->tableNames.erase(icarus->tableNames.find(args[0]));
    icarus->tableNames.insert(args[1]);

    Table::rename(icarus->tables[index], args[1]);
    string data = "OldName, NewName\n" + args[0] + "," + args[1];
    return Table::createTableFromData(data);
}

Table Parser::performSelect(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Select operation requires 2 arguments: (Table, Selection Condition)"s;

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
        return table.select(args[1]);
    }
    catch (string error)
    {
        throw error;
    }
}