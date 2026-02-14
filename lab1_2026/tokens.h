#pragma once

//**************************************
// tokens.h
//
// Defines the values for the tokens returned by yylex
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#define IDENTIFIER  1014        // <a C style identifier>
#define LOCAL       1015
#define GLOBAL      1016
#define LOOKUP      1017
#define INSERT      1018
#define OPEN        1019
#define CLOSE       1020

// Lab 2 code
#define PROGRAM     1000
#define IF          1001
#define ELSE        1002
#define ENDIF       1003
#define WHILE       1004
#define PRINT       1005
#define PRINTS      1006
#define CHAR        1007
#define INT         1008
#define LONG        1009
#define FLOAT       1010
#define DOUBLE      1011
#define STRUCT      1012
#define ARRAY       1013
#define RETURN      1124  //  ensure this doesn’t conflict with IDENTIFIER

// Constants / literals
#define INT_VAL     1021
#define FLOAT_VAL   1022
#define STRING_LIT  1023

// Operators
#define NOT_EQUALS  1024
#define EQUALS      1025
#define AND         1026
#define OR          1027
#define GE          1028
#define LE          1029

// Junk
#define JUNK_TOKEN  2000
