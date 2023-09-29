#include <bits/stdc++.h>
#include "Table.h"
#include "ExpParser/ExpParser.h"

using namespace std;

Table Table::project(vector<string> fieldNames)
{
    vector<int> columnIndices;

    // Ensure that all the fieldNames provided match with the fields of the exisitng table
    for (string &fieldName : fieldNames)
    {
        bool found = false;
        for (int i = 0; i < size(headers); i++)
            if (headers[i] == fieldName)
            {
                found = true;
                columnIndices.push_back(i);
                break;
            }
        if (!found)
        {
            cerr << "The provided column name (" << fieldName << ") does not exist in the table " << name << ".\n";
            throw "INVALID_COLUMN_NAME_ERROR"s;
        }
    }

    // Define all the necessary attributes of the new table object
    Table newTable;
    newTable.headers = fieldNames;
    newTable.fieldCount = size(columnIndices);
    newTable.recordCount = recordCount;
    newTable.data = vector<vector<string>>(recordCount, vector<string>(newTable.fieldCount));

    // Populate the data into the new table with the help of the previous table
    for (int recNo = 0; recNo < recordCount; recNo++)
        for (int fieldNo = 0; fieldNo < newTable.fieldCount; fieldNo++)
            newTable.data[recNo][fieldNo] = data[recNo][columnIndices[fieldNo]];

    newTable.name = "PROJ_" + getTimestamp();
    newTable.removeDuplicates();
    return newTable;
}

void Table::rename(Table &table, string newName)
{
    table.setName(newName);
}

Table Table::select(string filterQuery)
{
    Table newTable;
    newTable.fieldCount = fieldCount;
    ExpParser parser(filterQuery);

    try
    {
        for (vector<string> &row : data)
        {
            parser.resetParser();
            for (int index = 0; index < headers.size(); index++)
            {
                string dereferencingName = name + "." + headers[index];
                parser.setFieldValue(headers[index], row[index]);
                parser.setFieldValue(dereferencingName, row[index]);
            }
            if (parser.evaluateExpression())
                newTable.data.push_back(row);
        }
    }
    catch (string err)
    {
        cout << "There was an error in the selection query.\n";
        throw err;
    }

    newTable.recordCount = newTable.data.size();
    newTable.headers = headers;
    newTable.removeDuplicates();

    return newTable;
}

Table Table::crossProduct(Table &extTable)
{
    Table newTable;
    newTable.fieldCount = fieldCount + extTable.fieldCount;

    vector<string> extHeaders = extTable.getHeaders();
    set<string> headerSet(headers.begin(), headers.end());
    set<string> extHeaderSet(extHeaders.begin(), extHeaders.end());
    vector<vector<string>> extData = extTable.getData();

    // Populate the headers from the tables
    for (string &header : headers)
    {
        if (extHeaderSet.find(header) != extHeaderSet.end())
            newTable.headers.push_back(name + "." + header);
        else
            newTable.headers.push_back(header);
    }
    for (string &header : extHeaders)
    {
        if (headerSet.find(header) != headerSet.end())
            newTable.headers.push_back(extTable.getName() + "." + header);
        else
            newTable.headers.push_back(header);
    }

    // Populate the data
    for (vector<string> row1 : data)
        for (vector<string> row2 : extData)
        {
            vector<string> row(row1.begin(), row1.end());
            row.insert(row.end(), row2.begin(), row2.end());
            newTable.data.push_back(row);
        }

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "CROSS_" + getTimestamp();
    return newTable;
}
