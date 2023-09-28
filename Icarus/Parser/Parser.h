#pragma once

/*
 * Parser
 * Class definiton for the Parser object, which parses the relational algebra commands and calls the relevant functions
 */

#ifndef PARSER_H
#define PARSER_H

#include "commandParser.cpp";
#include <bits/stdc++.h>
using namespace std;

class Parser
{
private:
    CommandParser cmdParser;
    void performProjection(vector<string> args);

public:
    void parseAndExecute(string cmd);
};

#endif
