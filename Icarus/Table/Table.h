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

    // The field width used while printing
    int fieldWidth = 30;

    // Utility to get the file name from file path
    static string parseFileName(const string &filePath);

    // Utilities to display the table in the terminal
    void printHeader();
    void printRow(int index);

public:
    // Used to create a new table from the provided filepath
    // It returns a pointer to the newly created object, which is `nullptr` if there was an error in the execution of the same
    static Table createTable(const string &filePath);

    // Getters, setters and display utilitie
    string getName();
    int getRecordCount();
    int getFieldCount();
    void setName(string name);
    void setFieldWidth(int width);
    vector<string> getHeaders();
    void display();
};

#endif