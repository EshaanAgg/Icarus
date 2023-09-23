#include "Icarus.h"
#include "Table/Table.h"
#include "bits/stdc++.h"

using namespace std;

string Icarus::loadCSV(const string &filePath)
{
    Table *table = Table::createTable(filePath);
    // Handle the case in which there was an error in parsing the CSV
    if (table == nullptr)
    {
        cout << "Command aborted due to error!\n";
        return "";
    }

    tables.push_back(*table);
    tableCount++;

    return (*table).getName();
}
