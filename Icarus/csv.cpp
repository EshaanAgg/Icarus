#include "Icarus.h"
#include "Table/Table.h"
#include "bits/stdc++.h"

using namespace std;

string Icarus::loadCSV(const string &filePath)
{
    Table *tablePtr = Table::createTable(filePath);
    // Handle the case in which there was an error in parsing the CSV
    if (tablePtr == nullptr)
    {
        cout << "Command aborted due to error!\n";
        return "";
    }

    Table table = *tablePtr;

    while (tableNames.find(table.getName()) != tableNames.end())
    {
        cout << "There is already a table with the name assigned to this table (" << table.getName() << "). Please enter a new distinct name: ";
        string newName;
        cin >> newName;
        table.setName(newName);
    }

    tableNames.insert(table.getName());
    tables.push_back(table);
    tableCount++;

    return table.getName();
}
