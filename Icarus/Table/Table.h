#pragma once

/*
 * Table
 * Class definiton for the Table object which is stored on the Icarus
 * Used to represent a relation in Relational Algebra
 */

#ifndef TABLE_H
#define TABLE_H

#include <bits/stdc++.h>
using namespace std;

class Table
{
private:
    // Internal data of the Table class
    vector<string> headers;
    vector<vector<string>> data;
    int recordCount = 0;
    int fieldCount = 0;
    string name;

    // Utility to get the file name from file path
    string parseFileName(const string &filePath);

public:
    // Used to create a new table from the provided filepath
    static Table createTable(const string &filePath);

    // Traditonal getters
    string getName();
};

#endif
