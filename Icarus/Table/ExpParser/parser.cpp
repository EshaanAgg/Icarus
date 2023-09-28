#include <bits/stdc++.h>
#include "ExpParser.h"

using namespace std;

ExpParser::ExpParser(string &expression)
{
    this->expression = expression;
    pos = 0;
}

void ExpParser::resetParser()
{
    pos = 0;
}

char ExpParser::peek()
{
    if (pos < expression.size())
        return expression[pos];
    return '\0';
}

char ExpParser::consume()
{
    if (pos < expression.size())
        return expression[pos++];
    return '\0';
}

// We consider `.` to be an alphabet as the same can be used to dereference the parent tables in case of fields
bool ExpParser::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.';
}

Token ExpParser::getNextToken()
{
    // Ignore the whitespace and move to the next continuous part of text
    while (isspace(peek()))
        consume();

    // Compare and seach for different kinds of tokens, and throw errors if they are not consistent
    if (isdigit(peek()))
    {
        string num;
        while (isdigit(peek()))
            num += consume();
        return {TOK_NUMBER, num};
    }

    if (isAlpha(peek()))
    {
        string fieldName;
        while (isAlpha(peek()))
            fieldName += consume();
        if (fields.find(fieldName) == fields.end())
        {
            throw "Invalid field name: `"s + fieldName + "`. The same could not be figured out unambiguosly from the provided table(s). Please ensdure the correct spelling, or try redeferencing according with parent table."s;
        }
        return {TOK_FIELD, fields[fieldName]};
    }

    if (peek() == '(')
    {
        consume();
        return {TOK_OPEN_BRACE, "("};
    }

    if (peek() == '(')
    {
        consume();
        return {TOK_CLOSE_BRACE, ")"};
    }

    if (peek() == '=')
    {
        consume();
        return {TOK_OP_EQUAL, "="};
    }

    if (peek() == '>')
    {
        consume();
        if (peek() == '=')
        {
            consume();
            return {TOK_OP_GE, ">="};
        }
        return {TOK_OP_GREATER, ">"};
    }

    if (peek() == '<')
    {
        consume();
        if (peek() == '=')
        {
            consume();
            return {TOK_OP_LE, "<="};
        }
        return {TOK_OP_LESS, "<"};
    }

    if (peek() == '!')
    {
        consume();
        if (peek() == '=')
        {
            consume();
            return {TOK_OP_NOT_EQUAL, "!="};
        }

        throw "Invalid syntax. = symbol is expected after ! to form the NOT EQUALS (!=) operator"s;
    }

    if (peek() == '&')
    {
        consume();
        if (peek() == '&')
        {
            consume();
            return {TOK_OP_AND, "&&"};
        }

        throw "Invalid syntax. & symbol is expected after & to form the AND (&&) operator"s;
    }

    if (peek() == '|')
    {
        consume();
        if (peek() == '|')
        {
            consume();
            return {TOK_OP_OR, "||"};
        }

        throw "Invalid syntax. | symbol is expected after & to form the OR (||) operator"s;
    }

    if (peek() == '\0')
        return {TOK_END, '\0'};

    throw "Unrecognized character in the expression: "s + peek();
}