#include "Icarus.h"
#include "Table/Table.h"
#include "bits/stdc++.h"

using namespace std;

string Icarus::loadCSV(const string &filePath)
{
    Table table = Table::createTable(filePath);
    tables.push_back(table);
    tableCount++;

    return table.getName();
}
