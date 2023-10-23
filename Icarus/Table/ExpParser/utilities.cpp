#include <bits/stdc++.h>
#include "ExpParser.h"

using namespace std;

// Helper functions to check the nature of the operators
bool ExpParser::isComparisionOperator(Token &token)
{
    return token.type == TOK_OP_EQUAL || token.type == TOK_OP_GREATER || token.type == TOK_OP_LESS || token.type == TOK_OP_GE || token.type == TOK_OP_LE || token.type == TOK_OP_NOT_EQUAL;
}

bool ExpParser::isLogicalOperator(Token &token)
{
    return token.type == TOK_OP_AND || token.type == TOK_OP_OR;
}

bool ExpParser::isValue(Token &token)
{
    return token.type == TOK_NUMBER || token.type == TOK_FIELD || token.type == TOK_STRING;
}

// Get the precedence of operators for evalutaion
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

// Performs the comparision check for both numeric types and string types
bool ExpParser::applyComparisionOperator(TokenType &op, string &operand1, string &operand2, bool asNumber)
{
    // Comparision as number
    if (asNumber)
    {
        try
        {
            double op1 = stod(operand1);
            double op2 = stod(operand2);
            bool result;
            if (op == TOK_OP_GREATER)
                result = op1 > op2;
            else if (op == TOK_OP_LESS)
                result = op1 < op2;
            else if (op == TOK_OP_EQUAL)
                result = op1 == op2;
            else if (op == TOK_OP_GE)
                result = op1 >= op2;
            else if (op == TOK_OP_LE)
                result = op1 <= op2;
            else if (op == TOK_OP_NOT_EQUAL)
                result = op1 != op2;
            return result;
        }
        catch (invalid_argument &e)
        {
            cerr << "Invalid Argument: " << e.what() << endl;
            throw "Provided a number token but the value of the field could not be serialized to a numberic type.";
        }
    }

    // Compare as strings
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

// Performs the logical check on two operands
bool ExpParser::applyLogicalOperator(TokenType &op, bool &operand1, bool &operand2)
{
    if (op == TOK_OP_AND)
        return operand1 && operand2;
    else if (op == TOK_OP_OR)
        return operand1 || operand2;

    throw "PROGRAMMER_ERROR: Unimplemented logical operator"s;
}

bool ExpParser::evaluateExpression()
{
    stack<TokenType> operators;
    stack<bool> operands;

    Token token = getNextToken();

    // Conversion of Infix to Postfix with evaulation of comparision operators and syntax checking
    while (token.type != TOK_END)
    {
        // Handle value tokens and there evaluation to binary operands
        if (isValue(token))
        {
            TokenType type1 = token.type;
            string value1 = token.value;

            Token op = getNextToken();
            if (!isComparisionOperator(op))
                throw "INVALID_SYNTAX: A value token (string, number or field name) must be followed by a comparision operator.";

            Token field2 = getNextToken();
            if (token.type != TOK_FIELD)
                throw "INVALID_SYNTAX: A comparision operator must be followed by a value token (string, number or field name).";
            string value2 = field2.value;

            bool asNumber = type1 == TOK_NUMBER || field2.type == TOK_NUMBER;
            operands.push(applyComparisionOperator(op.type, value1, value2, asNumber));
        }
        // Handle logial operators
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
        // Handle braces for the nesting of expressions
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

// Public method to set the field values
void ExpParser::setFieldValue(string field, string value)
{
    fields[field] = value;
}