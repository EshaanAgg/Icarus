#pragma once

/*
 * Icarus
 * Class definiton for the Icarus REPL cum database that manages all and stores all the tables.
 */

#ifndef ICARUS_H
#define ICARUS_H

#include <string>
#include "Table/Table.h"
using namespace std;

class Icarus
{
private:
    string REPLDemarcator = ">> ";
    vector<Table> tables;
    set<string> tableNames;
    int tableCount = 0;
    int fieldWidth = 40;

    void showTables();
    void showTable(string tableName);
    // Given a `tableName` returns the index in the tables vector corresponding to it's location. Return -1 if not found
    int getTableIndex(string tableName);

    // Handlers for each of the respective commands
    void handleExit();
    void handleHi();
    void handleLoadCSV(string &input);
    void handleUnknown(string &input);

public:
    // Starts the interactive playground
    void startRELP();
    void setFieldWidth(int width);
    // Returns the name of the table that is formed after parsing the .csv file at the given location
    string loadCSV(const string &filePath);
    void execute(string input);
};

#endif
