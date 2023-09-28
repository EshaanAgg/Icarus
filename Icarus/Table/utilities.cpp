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
    int count = min(10, recordCount);

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

    cout << endl;
    printHeader();
    for (int i = 0; i < count; i++)
        printRow(i);
    cout << "\n";
}