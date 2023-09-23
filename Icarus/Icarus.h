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
    int tableCount = 0;

    string loadCSV(const std::string &filePath);

public:
    // Starts the interactive playground
    void startRELP();
};

#endif
