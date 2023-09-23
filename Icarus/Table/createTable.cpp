#include "Table.h"
#include "bits/stdc++.h"

using namespace std;

string Table::parseFileName(const string &filePath)
{
    size_t slashPos = filePath.find_last_of("/\\"); // Find the last slash or backslash
    if (slashPos != std::string::npos)
        // If a slash or backslash is found, return the substring after it, excluding the .csv at the end
        return filePath.substr(slashPos + 1, filePath.size() - 4);
    else
        // If not found, return the whole string excluding the .csv extension at the end
        return filePath.substr(0, filePath.size() - 4);
}

Table Table::createTable(const string &filePath)
{
    // Check if the file exists
    ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Unable to open file " << filePath << std::endl;
        return;
    }

    // Create placeholders for data
    vector<string> headers;
    vector<vector<string>> data;

    // Read the header line
    string headerLine;
    if (getline(file, headerLine))
    {
        istringstream headerStream(headerLine);
        string header;
        while (getline(headerStream, header, ','))
            headers.push_back(header);
    }
    else
    {
        cerr << "ERROR: Empty CSV file. Please ensure that the first line of the file should contain the headers." << endl;
        return;
    }

    // Read the data lines
    string line;
    int lineNumber = 0;
    while (getline(file, line))
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
            return;
        }

        data.push_back(rowData);
    }

    file.close();

    // Create the new Table instance and return the same
    Table table;
    table.data = data;
    table.headers = headers;
    table.fieldCount = headers.size();
    table.recordCount = lineNumber;
    table.name = table.parseFileName(filePath);

    return table;
}