#include <bits/stdc++.h>
#include "Table.h"

using namespace std;

string Table::getName()
{
    return name;
}

int Table::getFieldCount()
{
    return fieldCount;
}

int Table::getRecordCount()
{
    return recordCount;
}

void Table::setName(string newName)
{
    name = newName;
}

vector<string> Table::getHeaders()
{
    return headers;
}

void Table::setFieldWidth(int width)
{
    fieldWidth = width;
}

vector<vector<string>> Table::getData()
{
    return data;
}

void Table::printHeader()
{
    cout << left;
    for (string &header : headers)
        cout << setw(fieldWidth) << header;

    cout << "\n"
         << setfill('-') << setw(fieldWidth * fieldCount) << "" << setfill(' ') << endl;
}

void Table::printRow(int index)
{
    cout << left;
    for (auto &item : data[index])
        cout << setw(fieldWidth) << item;
    cout << "\n";
}

void Table::display(bool ask)
{
    int count = recordCount;

    if (ask)
    {
        cout << "Enter the number of rows to display (between 0 and " << recordCount << "): ";
        cin >> count;

        if (count < 0 || count > recordCount)
        {
            cout << "The number of rows entered is invalid. Aborting the operation.\n";
            return;
        }
    }

    printHeader();
    for (int i = 0; i < count; i++)
        printRow(i);
    cout << "\n";
}

void Table::removeDuplicates()
{
    set<vector<string>> dataSet;
    vector<vector<string>> newData;

    for (vector<string> &row : data)
        if (dataSet.find(row) == dataSet.end())
        {
            dataSet.insert(row);
            newData.push_back(row);
        }

    data = newData;
    recordCount = data.size();
}

int Table::getHeaderIndice(string header)
{
    for (int i = 0; i < headers.size(); i++)
        if (headers[i] == header)
            return i;
    return -1;
}

vector<vector<int>> Table::getCommonHeaderIndices(Table &extTable)
{
    vector<int> ind1, ind2;

    for (int i = 0; i < headers.size(); i++)
    {
        int index = extTable.getHeaderIndice(headers[i]);
        if (index != -1)
        {
            ind1.push_back(i);
            ind2.push_back(index);
        }
    }

    return {ind1, ind2};
}
