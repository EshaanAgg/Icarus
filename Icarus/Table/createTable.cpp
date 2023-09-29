#include <bits/stdc++.h>
#include "Table.h"

using namespace std;

string Table::parseFileName(const string &filePath)
{
    size_t slashPos = filePath.find_last_of("/\\"); // Find the last slash or backslash
    size_t dotPos = filePath.find_last_of(".");     // Find the last . (used to specify extension)

    if (dotPos == string::npos)
        dotPos = filePath.size();
    if (slashPos == string::npos)
        slashPos = -1;

    int len = dotPos - 1 - slashPos;
    return filePath.substr(slashPos + 1, len);
}

Table Table::createTableFromStream(istream &stream, string tableName)
{
    // Create placeholders for data
    vector<string> headers;
    set<string> headerSet;
    vector<vector<string>> data;

    // Read the header line
    string headerLine;
    if (getline(stream, headerLine))
    {
        istringstream headerStream(headerLine);
        string header;
        while (getline(headerStream, header, ','))
        {
            if (headerSet.find(header) != headerSet.end())
            {
                cerr << "ERROR: The CSV file has two fields with the same name: `" << header << "` which is not allowed. Please modify the file to resolve this error" << endl;
                throw "NON_UNIQUE_HEADER_NAMES_IN_CSV"s;
            }
            headers.push_back(header);
            headerSet.insert(header);
        }
    }
    else
    {
        cerr << "ERROR: Empty CSV file. Please ensure that the first line of the file should contain the headers." << endl;
        throw "EMPTY_CSV_FILE"s;
    }

    // Read the data lines
    string line;
    int lineNumber = 0;
    while (getline(stream, line))
    {
        lineNumber++;

        vector<string> rowData;
        istringstream dataStream(line);
        string field;
        while (getline(dataStream, field, ','))
            rowData.push_back(field);

        // Check if the number of fields matches the number of headers
        if (rowData.size() != headers.size())
        {
            cerr << "ERROR: Number of fields in the row does not match header." << endl;
            cerr << "Data Line: " << lineNumber << endl;
            throw "INCONSISTENT_DATA_IN_CSV"s;
        }

        data.push_back(rowData);
    }

    // Create the new Table instance and return the same
    Table table = Table();
    table.data = data;
    table.headers = headers;
    table.fieldCount = headers.size();
    table.recordCount = lineNumber;
    table.name = tableName;

    return table;
}

Table Table::createTable(const string &filePath)
{
    // Check if the file exists
    ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Unable to open file " << filePath << endl;
        throw "FILE_CANT_BE_OPENED"s;
    }

    Table table = createTableFromStream(file, Table::parseFileName(filePath));
    file.close();
    return table;
}

string Table::getTimestamp()
{
    time_t currentTime = time(nullptr);
    return to_string(currentTime);
}

Table Table::createTableFromData(const string &data)
{
    istringstream inputStringStream(data);
    return createTableFromStream(inputStringStream, "TEMP_" + getTimestamp());
}