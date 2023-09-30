#pragma once

/*
 * Parser
 * Used for the parsing of the relation algrebra commands and executing the same
 */

#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include "commandParser.cpp"

class Icarus;

using namespace std;

class Parser
{
private:
    set<string> supportedCommands = {"PROJECT", "RENAME", "SELECT", "PRODUCT", "SAVE"};
    CommandParser cmdParser;
    Icarus *icarus = nullptr;

    Table performProjection(vector<string> args);
    Table performRename(vector<string> args);
    Table performSelect(vector<string> args);
    Table performCrossProduct(vector<string> args);
    Table performSave(vector<string> args);

    void getTable(Table &tableHolder, string arg);

public:
    // Used to set the parent Icarus object
    void setIcarus(Icarus *ic);

    Table parseAndExecute(string cmd);
};

#endif