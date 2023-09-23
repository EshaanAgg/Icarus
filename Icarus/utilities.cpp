#include <bits/stdc++.h>
#include "Icarus.h"

using namespace std;

void Icarus::showTables()
{
    cout << "There are currently " << tableCount << "table(s) loaded in the database.\n\n";

    // Diplay the headers and the divider line
    cout << left << setw(fieldWidth) << "Table Name" << setw(fieldWidth) << "Field Count" << setw(fieldWidth) << "Row Count";
    cout << "\n"
         << setfill('-') << setw(fieldWidth * 3) << "" << setfill(' ') << endl;

    // Display all the data
    for (Table &table : tables)
        cout << left << setw(fieldWidth) << table.getName() << setw(fieldWidth) << table.getFieldCount() << setw(fieldWidth) << table.getRecordCount() << "\n";
}

void Icarus::showTable(string tableName)
{
    if (tableNames.find(tableName) == tableNames.end())
    {
        cout << "There exists no table with such name.\n";
        return;
    }

    for (Table &table : tables)
        if (table.getName() == tableName)
            table.display();
}