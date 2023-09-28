#include <bits/stdc++.h>
#include "ExpParser.h"

using namespace std;

bool ExpParser::isComparisionOperator(Token &token)
{
    return token.type == TOK_OP_EQUAL || token.type == TOK_OP_GREATER || token.type == TOK_OP_LESS || token.type == TOK_OP_GE || token.type == TOK_OP_LE || token.type == TOK_OP_NOT_EQUAL;
}

bool ExpParser::isLogicalOperator(Token &token)
{
    return token.type == TOK_OP_AND || token.type == TOK_OP_OR;
}

bool ExpParser::precedenceHigher(TokenType &t1, TokenType &t2)
{
    map<TokenType, int> precedence;
    precedence[TOK_OP_LE] = 2;
    precedence[TOK_OP_GE] = 2;
    precedence[TOK_OP_LESS] = 2;
    precedence[TOK_OP_GREATER] = 2;
    precedence[TOK_OP_EQUAL] = 2;
    precedence[TOK_OP_NOT_EQUAL] = 2;
    precedence[TOK_OP_AND] = 1;
    precedence[TOK_OP_OR] = 0;

    return precedence[t1] >= precedence[t2];
}

bool ExpParser::applyComparisionOperator(TokenType &op, string &operand1, string &operand2)
{
    bool result;
    if (op == TOK_OP_GREATER)
        result = operand1 > operand2;
    else if (op == TOK_OP_LESS)
        result = operand1 < operand2;
    else if (op == TOK_OP_EQUAL)
        result = operand1 == operand2;
    else if (op == TOK_OP_GE)
        result = operand1 >= operand2;
    else if (op == TOK_OP_LE)
        result = operand1 <= operand2;
    else if (op == TOK_OP_NOT_EQUAL)
        result = operand1 != operand2;
    return result;
}

bool ExpParser::applyLogicalOperator(TokenType &op, bool &operand1, bool &operand2)
{
    if (op == TOK_OP_AND)
        return operand1 && operand2;
    else if (op == TOK_OP_OR)
        return operand1 || operand2;
}

bool ExpParser::evaluateExpression()
{
    stack<TokenType> operators;
    stack<bool> operands;

    Token token = getNextToken();

    // Conversion of Infix to Postfix with evaulation of comparision operators and syntax checking
    while (token.type != TOK_END)
    {
        if (token.type == TOK_FIELD)
        {
            string value1 = token.value;

            Token op = getNextToken();
            if (!isComparisionOperator(op))
                throw "INVALID_SYNTAX: A field name must be followed by a comparision operator";

            Token field2 = getNextToken();
            if (token.type != TOK_FIELD)
                throw "INVALID_SYNTAX: A comparision operator must be followed by a field name";
            string value2 = field2.value;

            operands.push(applyComparisionOperator(op.type, value1, value2));
        }
        else if (isLogicalOperator(token))
        {
            while (!operators.empty() && operators.top() != TOK_OPEN_BRACE && precedenceHigher(operators.top(), token.type))
            {
                TokenType op = operators.top();
                operators.pop();
                bool operand2 = operands.top();
                operands.pop();
                bool operand1 = operands.top();
                operands.pop();

                operands.push(applyLogicalOperator(op, operand1, operand2));
            }
            operators.push(token.type);
        }
        else if (token.type == TOK_OPEN_BRACE)
            operators.push(token.type);
        else if (token.type == TOK_CLOSE_BRACE)
        {
            while (!operators.empty() && operators.top() != TOK_OPEN_BRACE)
            {
                TokenType op = operators.top();
                operators.pop();
                bool operand2 = operands.top();
                operands.pop();
                bool operand1 = operands.top();
                operands.pop();

                operands.push(applyLogicalOperator(op, operand1, operand2));
            }

            if (!operators.empty() && operators.top() == TOK_CLOSE_BRACE)
                operators.pop();
        }

        token = getNextToken();
    }

    while (!operators.empty())
    {
        TokenType op = operators.top();
        operators.pop();
        bool operand2 = operands.top();
        operands.pop();
        bool operand1 = operands.top();
        operands.pop();

        operands.push(applyLogicalOperator(op, operand1, operand2));
    }

    return operands.top();
}

bool ExpParser::checkRow(Table &table, int rowIndex)
{
    string tableName = table.getName();
    vector<string> headers = table.getHeaders();
    vector<vector<string>> data = table.getData();

    for (int index = 0; index < headers.size(); index++)
    {
        fields[headers[index]] = data[rowIndex][index];
        string dereferencingName = tableName + "." + headers[index];
        fields[dereferencingName] = data[rowIndex][index];
    }
};