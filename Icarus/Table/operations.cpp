#include <bits/stdc++.h>
#include "Table.h"

using namespace std;

Table Table::project(vector<string> fieldNames) {
    vector <int> columnIndices;

    // Ensure that all the fieldNames provided match with the fields of the exisitng table
    for (string &fieldName: fieldNames) {
        bool found = false;
        for (int i = 0; i<size(headers); i++) if (headers[i] == fieldName) {
            found = true;
            columnIndices.push_back(i);
            break;
        }
        if (!found) {
            cerr << "The provided column name (" << fieldName << ") does not exist in the table " << name << ".\n";
            throw "INVALID_COLUMN_NAME_ERROR";
        }
    }

    // Define all the necessary attributes of the new table object
    Table newTable;
    newTable.fieldCount = size(columnIndices);
    newTable.recordCount = recordCount;
    newTable.data = vector <vector<string>> (recordCount, vector<string> (newTable.fieldCount));

    // Populate the data into the new table with the help of the previous table
    for (int recNo = 0; recNo < recordCount; recNo++) for (int fieldNo = 0; fieldNo < newTable.fieldCount; fieldNo++) 
        newTable.data[recNo][fieldNo] = data[recNo][columnIndices[fieldNo]];

    return newTable;
}

void Table::rename(Table &table, string newName) {
    table.setName(newName);
}