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

    // Returns the name of the table that is formed after parsing the .csv file at the given location
    string loadCSV(const std::string &filePath);
    void showTables();

public:
    // Starts the interactive playground
    void startRELP();
};

#endif
