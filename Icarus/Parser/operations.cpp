#include <bits/stdc++.h>
#include "../Icarus.h"

using namespace std;

// Utility to populate the `tableHolder` variable from the `arg`. Arg can be a Relational Algrabra operator which returns a table or it can be a table name in the memory as well.
void Parser::getTable(Table &tableHolder, string arg)
{
    if (cmdParser.isCommand(arg))
        tableHolder = parseAndExecute(arg);
    else
    {
        int index = icarus->getTableIndex(arg);
        if (index == -1)
        {
            string message = "INVALID_ARGS: There is no table with the name `" + arg + "`";
            throw message;
        }
        tableHolder = icarus->tables[index];
    }
}

Table Parser::performProjection(vector<string> args)
{
    if (args.size() < 2)
        throw "INVALID_ARGS: Projection operation requires >= 2 arguments: (TableName, fieldName1, fieldName2, ...). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table;
        getTable(table, args[0]);

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
        throw "INVALID_ARGS: Rename operation requires 2 arguments: (OldTableName, NewTableName). You supplied "s + to_string(args.size()) + " arguments."s;

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
        throw "INVALID_ARGS: Select operation requires 2 arguments: (Table, Selection Condition). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table;
        getTable(table, args[0]);

        return table.select(args[1]);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performCrossProduct(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Cross product operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        if (table1.getName() == table2.getName())
            throw "INVALID_ARGS: It is not allowed to take the cross product of two table with the same name"s;
        return table1.crossProduct(table2);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performSave(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Save operation requires 2 arguments: (table, tableName). You supplied "s + to_string(args.size()) + " arguments."s;

    Table table;
    getTable(table, args[0]);

    if (icarus->tableNames.find(args[1]) != icarus->tableNames.end())
        throw "INVALID_ARGS: Table with the provided name already exists: "s + args[1];

    // Save the table
    table.setName(args[1]);
    icarus->tableNames.insert(args[1]);
    icarus->tables.push_back(table);
    icarus->tableCount++;

    string data = "System Message\nTable added successfully";
    return Table::createTableFromData(data);
}

Table Parser::performJoin(vector<string> args)
{
    if (args.size() != 3)
        throw "INVALID_ARGS: Join operation requires 3 arguments: (Table1, Table2, JoinCondition). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        return table1.join(table2, args[2]);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performNaturalJoin(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Natural Join operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        return table1.naturalJoin(table2);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performUnion(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Union operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        if (!table1.unionCompatible(table2))
            throw "The provided tables are not union compatible and thus union can't be performed on them."s;
        return table1.Union(table2);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performIntersection(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Intersection operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        if (!table1.unionCompatible(table2))
            throw "The provided tables are not union compatible and thus intersection can't be performed on them."s;
        return table1.intersection(table2);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performDifference(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Difference operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        if (!table1.unionCompatible(table2))
            throw "The provided tables are not union compatible and thus difference can't be performed on them."s;
        return table1.difference(table2);
    }
    catch (string error)
    {
        throw error;
    }
}

Table Parser::performDivide(vector<string> args)
{
    if (args.size() != 2)
        throw "INVALID_ARGS: Difference operation requires 2 arguments: (Table1, Table2). You supplied "s + to_string(args.size()) + " arguments."s;

    try
    {
        Table table1, table2;
        getTable(table1, args[0]);
        getTable(table2, args[1]);

        return table1.divide(table2);
    }
    catch (string error)
    {
        throw error;
    }
}