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
    vector<string> headers;
    vector<vector<string>> data;
    int recordCount = 0;
    int fieldCount = 0;
    string name;

    // The field width used while printing
    int fieldWidth = 30;

    // Utility to get the file name from file path
    static string parseFileName(const string &filePath);

    static Table createTableFromStream(istream &stream, string tableName);

    // Utilities to display the table in the terminal
    void printHeader();
    void printRow(int index);

public:
    // Used to create a new table from the provided filepath
    // It returns a pointer to the newly created object, which is `nullptr` if there was an error in the execution of the same
    static Table createTable(const string &filePath);

    // Used as a utility function to create table's on the fly by other components of the REPL
    static Table createTableFromData(const string &data);

    // Projects the specified fieldNames from the given table into a new table with uninitialized name
    // May throw a string error if the provided arguments are logically incoherent with respect to the table
    Table project(vector<string> fieldNames);

    Table select(string filterQuery);

    // Takes a reference to a table, and renames the same to the desired new name
    static void rename(Table &table, string newName);

    // As all the RA operations are sets, we need a utility to remove duplicate data entries
    void removeDuplicates();

    // Getters, setters and display utilities
    string getName();
    int getRecordCount();
    int getFieldCount();
    vector<vector<string>> getData();
    void setName(string name);
    void setFieldWidth(int width);
    vector<string> getHeaders();
    // Requires the bool `ask`, which tells the compiler whether to ask for the number of rows or not. If `ask` if false, the first 10 rows are printed.
    void display(bool ask);
};

#endif