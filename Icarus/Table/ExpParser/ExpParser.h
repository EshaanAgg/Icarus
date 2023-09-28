#pragma once

/*
 * Expression Parser
 * Class to parse expressions and perform the conditional checks
 */

#ifndef EXP_PARSER_H
#define EXP_PARSER_H

#include <bits/stdc++.h>
#include "../Table.h"

using namespace std;

// Token types
enum TokenType
{
    TOK_END,
    TOK_NUMBER,
    TOK_FIELD,
    TOK_OP_EQUAL,
    TOK_OP_GREATER,
    TOK_OP_LESS,
    TOK_OP_GE,
    TOK_OP_LE,
    TOK_OP_NOT_EQUAL,
    TOK_OP_AND,
    TOK_OP_OR,
    TOK_OPEN_BRACE,
    TOK_CLOSE_BRACE,
};

// Token structure
struct Token
{
    TokenType type;
    string value;
};

class ExpParser
{
private:
    string expression;
    size_t pos;
    map<string, string> fields;

    char peek();
    char consume();
    bool isAlpha(char c);

    Token getNextToken();

    bool isComparisionOperator(Token &token);
    bool applyComparisionOperator(TokenType &op, string &op1, string &op2);
    bool isLogicalOperator(Token &token);
    bool applyLogicalOperator(TokenType &op, bool &op1, bool &op2);
    bool precedenceHigher(TokenType &t1, TokenType &t2);
    bool evaluateExpression();

public:
    ExpParser(string &expression);
    void resetParser();
    bool checkRow(Table &table, int rowIndex);
};

#endif