#include "bits/stdc++.h"
#include "Icarus.h"

using namespace std;

string Icarus::loadCSV(const string &filePath)
{
    try
    {
        Table table = Table::createTable(filePath);
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
    catch (string errorCode)
    // Handle the case in which there was an error in parsing the CSV
    {
        cout << "Command aborted due to error! ERROR_CODE: " << errorCode << "\n";
        return "";
    }
}
