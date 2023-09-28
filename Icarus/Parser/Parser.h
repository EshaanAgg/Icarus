#pragma once

/*
 * Parser
 * TODO
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
    set<string> supportedCommands = {"PROJECT"};
    CommandParser cmdParser;
    Icarus *icarus = nullptr;

    Table performProjection(vector<string> args);

public:
    // Used to set the parent Icarus object
    void setIcarus(Icarus *ic);

    Table parseAndExecute(string cmd);
};

#endif