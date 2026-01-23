//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

bool FindPROG();
bool FindSTMTS();
bool FindSTMT();
bool FindEXPR();
bool FindEXPR_P();
bool FindTERM();
bool FindTERM_P();
bool FindFACTOR();

//--------------------------------------------------
// PROGRAM → STMTS end
bool FindPROG()
{
    if (!FindSTMTS())
        return false;

    int token = AdvanceToken();
    if (token != END && token != 0)
    {
        Error("end");
        return false;
    }

    std::cout << "Found a Program\n";
    return true;
}

//--------------------------------------------------
// STMTS → STMT STMTS | ε
bool FindSTMTS()
{
    int token = PeekToken();

    if (token == END || token == 0)
        return true;

    if (!FindSTMT())
    {
        // error recovery: skip to semicolon or end
        while (PeekToken() != SEMI &&
            PeekToken() != END &&
            PeekToken() != 0)
            AdvanceToken();

        if (PeekToken() == SEMI)
            AdvanceToken();
    }

    return FindSTMTS();
}

//--------------------------------------------------
// STMT → identifier = EXPR ;
//      | EXPR ;
bool FindSTMT()
{
    int token = PeekToken();

    // Possible assignment or expression
    if (token == IDENTIFIER)
    {
        int id = AdvanceToken();     // consume identifier
        int next = PeekToken();      // look ahead

        if (next == ASSIGN)
        {
            AdvanceToken(); // consume '='

            if (!FindEXPR())
                return false;

            if (AdvanceToken() != SEMI)
            {
                Error(";");
                return false;
            }

            std::cout << "Found a statement\n";
            return true;
        }

        // Not assignment → put identifier back for EXPR
        UngetToken(id);
    }

    // Expression statement
    if (!FindEXPR())
        return false;

    if (AdvanceToken() != SEMI)
    {
        Error(";");
        return false;
    }

    std::cout << "Found a statement\n";
    return true;
}


//--------------------------------------------------
// EXPR → TERM EXPR'
bool FindEXPR()
{
    if (!FindTERM())
        return false;

    return FindEXPR_P();
}

//--------------------------------------------------
// EXPR' → (+ | -) TERM EXPR' | ε
bool FindEXPR_P()
{
    int token = PeekToken();

    if (token == PLUS || token == MINUS)
    {
        AdvanceToken(); // + or -

        if (!FindTERM())
            return false;

        return FindEXPR_P();
    }

    return true;
}

//--------------------------------------------------
// TERM → FACTOR TERM'
bool FindTERM()
{
    if (!FindFACTOR())
        return false;

    return FindTERM_P();
}

//--------------------------------------------------
// TERM' → (* | /) FACTOR TERM' | ε
bool FindTERM_P()
{
    int token = PeekToken();

    if (token == TIMES || token == DIV)
    {
        AdvanceToken(); // * or /

        if (!FindFACTOR())
            return false;

        return FindTERM_P();
    }

    return true;
}

//--------------------------------------------------
// FACTOR → num | identifier | ( EXPR )
bool FindFACTOR()
{
    int token = PeekToken();

    if (token == NUM)
    {
        AdvanceToken();
        return true;
    }

    if (token == IDENTIFIER)
    {
        AdvanceToken();
        return true;
    }

    if (token == '(')
    {
        AdvanceToken(); // '('

        if (!FindEXPR())
            return false;

        if (AdvanceToken() != ')')
        {
            Error(")");
            return false;
        }

        return true;
    }

    Error("NUM");
    AdvanceToken();
    return false;
}