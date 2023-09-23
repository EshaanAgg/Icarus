#pragma once

/*
 * Icarus
 * Class definiton for the Icarus REPL
 */

#ifndef ICARUS_H
#define ICARUS_H

#include <string>
using namespace std;

class Icarus
{
private:
    string REPLDemarcator = ">> ";
    void loadCSV(const std::string &filePath);

public:
    // Starts the interactive playground
    void startRELP();
};

#endif
