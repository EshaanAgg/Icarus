#include <bits/stdc++.h>
#include "Icarus.h"

using namespace std;

void Icarus::showTables()
{
    cout << "There are currently " << tableCount << " table(s) loaded in the database.\n\n";

    // Diplay the headers and the divider line
    cout << left << setw(fieldWidth) << "Table Name" << setw(fieldWidth) << "Field Count" << setw(fieldWidth) << "Row Count" << endl;
    cout << setfill('-') << setw(fieldWidth * 3) << "" << setfill(' ') << endl;

    // Display all the data
    for (Table &table : tables)
        cout << left << setw(fieldWidth) << table.getName() << setw(fieldWidth) << table.getFieldCount() << setw(fieldWidth) << table.getRecordCount() << "\n";
    cout << "\n";
}

void Icarus::showTable(string tableName)
{
    if (tableNames.find(tableName) == tableNames.end())
    {
        cout << "There exists no table with such name.\n";
        return;
    }

    cout << "\n";
    for (Table &table : tables)
        if (table.getName() == tableName)
            table.display();
}

int Icarus::getTableIndex(string tableName) {
    for (int i = 0; i<size(tables); i++) if (tables[i].getName() == tableName) return i;
    return -1;
}

void Icarus::setFieldWidth(int width) {
    fieldWidth = width;
}