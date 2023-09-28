#include <bits/stdc++.h>
#include "Parser.h"

using namespace std;

void Parser::performProjection(vector<string> args)
{
    if (args.size() < 2)
        throw "INVALID_ARGS: Projection operation requires >= 2 arguments: (TableName, fieldName1, fieldName2, ...)";
}
