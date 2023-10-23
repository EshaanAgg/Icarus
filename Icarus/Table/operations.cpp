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

Table Table::join(Table &externalTable, string filterQuery)
{
    Table crossTable = crossProduct(externalTable);
    Table joinTable = crossTable.select(filterQuery);

    joinTable.name = "JOIN_" + getTimestamp();
    return joinTable;
}

Table Table::naturalJoin(Table &externalTable)
{
    vector<vector<int>> commonIndices = getCommonHeaderIndices(externalTable);

    if (commonIndices[0].size() == 0)
        throw "INVALID_TABLES: The provided tables have no columns with the same name. Tables that are to be naturally-joined must have atleast one common field."s;

    set<int> skipIndices(commonIndices[1].begin(), commonIndices[1].end());

    Table newTable;

    // Populate the headers in the new table
    newTable.fieldCount = fieldCount + externalTable.fieldCount - skipIndices.size();
    newTable.headers = headers;
    for (int i = 0; i < externalTable.fieldCount; i++)
        if (skipIndices.find(i) == skipIndices.end())
            newTable.headers.push_back(externalTable.headers[i]);

    vector<vector<string>> extData = externalTable.data;

    // Populate the data
    for (vector<string> row1 : data)
        for (vector<string> row2 : extData)
        {
            // Check if we should populate these set of rows of not
            bool match = true;
            for (int i1 : commonIndices[0])
            {
                if (!match)
                    break;
                for (int i2 : commonIndices[1])
                    if (row1[i1] != row2[i2])
                    {
                        match = false;
                        break;
                    }
            }
            if (!match)
                continue;

            // Populate the data
            vector<string> dataRow(row1.begin(), row1.end());
            for (int i = 0; i < externalTable.fieldCount; i++)
                if (skipIndices.find(i) == skipIndices.end())
                    dataRow.push_back(row2[i]);

            newTable.data.push_back(dataRow);
        }

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "NATURAL_" + getTimestamp();
    return newTable;
}

Table Table::Union(Table &externalTable)
{
    Table newTable;
    newTable.fieldCount = fieldCount;
    newTable.headers = headers;
    newTable.data = data;

    vector<int> headerOrder = getCommonHeaderIndices(externalTable)[1];
    for (vector<string> &row : externalTable.data)
    {
        vector<string> dataRow;
        for (int i : headerOrder)
            dataRow.push_back(row[i]);
        newTable.data.push_back(dataRow);
    }

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "UNION_" + getTimestamp();
    return newTable;
}

Table Table::intersection(Table &externalTable)
{
    Table newTable;
    newTable.fieldCount = fieldCount;
    newTable.headers = headers;

    set<vector<string>> dataSet(data.begin(), data.end());

    vector<int> headerOrder = getCommonHeaderIndices(externalTable)[1];
    for (vector<string> &row : externalTable.data)
    {
        vector<string> dataRow;
        for (int i : headerOrder)
            dataRow.push_back(row[i]);
        if (dataSet.find(dataRow) != dataSet.end())
            newTable.data.push_back(dataRow);
    }

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "INTERSECTION_" + getTimestamp();
    return newTable;
}

Table Table::difference(Table &externalTable)
{
    Table newTable;
    newTable.fieldCount = fieldCount;
    newTable.headers = headers;

    // Populate the external table's data as a set in the order of the headers of the primary table
    set<vector<string>> dataSet;
    vector<int> headerOrder = getCommonHeaderIndices(externalTable)[1];
    for (vector<string> &row : externalTable.data)
    {
        vector<string> dataRow;
        for (int i : headerOrder)
            dataRow.push_back(row[i]);
        dataSet.insert(dataRow);
    }

    // Populate the new table
    for (vector<string> &row : data)
        if (dataSet.find(row) == dataSet.end())
            newTable.data.push_back(row);

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "DIFFERENCE_" + getTimestamp();
    return newTable;
}

Table Table::divide(Table &externalTable)
{
    // Calculate the common and not common indices between the two tables and also check for division compatibility
    vector<int> notCommonIndices, commonIndices;
    for (string header : externalTable.headers)
    {
        bool found = false;
        for (int i = 0; i < fieldCount; i++)
        {
            if (headers[i] == header)
            {
                found = true;
                commonIndices.push_back(i);
                break;
            }
        }
        if (!found)
            throw "INVALID TABLES: The divisor table has the header: "s + header + " which is not present in the dividend table"s;
    }

    for (int i = 0; i < fieldCount; i++)
    {
        bool found = false;
        for (int j : commonIndices)
            if (i == j)
            {
                found = true;
                break;
            }
        if (!found)
            notCommonIndices.push_back(i);
    }

    Table newTable;
    newTable.fieldCount = notCommonIndices.size();
    for (int i : notCommonIndices)
        newTable.headers.push_back(headers[i]);

    // Create a set of the possible rows that can be the data of the new table
    set<vector<string>> possibleRows;
    for (auto &row : data)
    {
        vector<string> candidateRow;
        for (int i : notCommonIndices)
            candidateRow.push_back(row[i]);
        possibleRows.insert(candidateRow);
    }

    // Create a set from the original data restructed as notCommonFields followed by commonFields
    set<vector<string>> searchSet;
    for (auto &row : data)
    {
        vector<string> candidateRow;
        for (int i : notCommonIndices)
            candidateRow.push_back(row[i]);
        for (int i : commonIndices)
            candidateRow.push_back(row[i]);
        searchSet.insert(candidateRow);
    }

    // Loop for the possibleRows and add the suitable ones to the data of the newTable
    for (auto itr = possibleRows.begin(); itr != possibleRows.end(); itr++)
    {
        vector<string> prefixFields = *itr;
        bool canAdd = true;
        for (auto suffixFields : externalTable.data)
        {
            vector<string> row(prefixFields.begin(), prefixFields.end());
            row.insert(row.end(), suffixFields.begin(), suffixFields.end());
            if (searchSet.find(row) == searchSet.end())
            {
                canAdd = false;
                break;
            }
        }
        if (canAdd)
            newTable.data.push_back(prefixFields);
    }

    newTable.removeDuplicates();
    newTable.recordCount = newTable.data.size();
    newTable.name = "DIVIDE_" + getTimestamp();
    return newTable;
}