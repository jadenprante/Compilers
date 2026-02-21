/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LANGPARSE_H_INCLUDED
# define YY_YY_LANGPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "lang.y"

    #include "cAstNode.h"
    #include "cExprNode.h"
    #include "cStmtNode.h"
    #include "cStmtsNode.h"
    #include "cDeclNode.h"
    #include "cDeclsNode.h"
    #include "cProgramNode.h"
    #include "cParamsNode.h"
    #include "cFuncCallNode.h"
    #include "cArrayExprNode.h"

#line 62 "langparse.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CHAR = 259,                    /* CHAR  */
    INT = 260,                     /* INT  */
    LONG = 261,                    /* LONG  */
    FLOAT = 262,                   /* FLOAT  */
    DOUBLE = 263,                  /* DOUBLE  */
    INT_VAL = 264,                 /* INT_VAL  */
    FLOAT_VAL = 265,               /* FLOAT_VAL  */
    STRING_LIT = 266,              /* STRING_LIT  */
    LOCAL = 267,                   /* LOCAL  */
    GLOBAL = 268,                  /* GLOBAL  */
    LOOKUP = 269,                  /* LOOKUP  */
    INSERT = 270,                  /* INSERT  */
    OPEN = 271,                    /* OPEN  */
    CLOSE = 272,                   /* CLOSE  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    ENDIF = 275,                   /* ENDIF  */
    PRINT = 276,                   /* PRINT  */
    RETURN = 277,                  /* RETURN  */
    STRUCT = 278,                  /* STRUCT  */
    ARRAY = 279,                   /* ARRAY  */
    EQUALS = 280,                  /* EQUALS  */
    NOT_EQUALS = 281,              /* NOT_EQUALS  */
    GE = 282,                      /* GE  */
    LE = 283,                      /* LE  */
    AND = 284,                     /* AND  */
    OR = 285                       /* OR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 53 "lang.y"

    int int_val;
    float float_val;
    char* str_val;
    cSymbol* symbol;

    cExprNode* expr_node;
    cStmtNode* stmt_node;
    cStmtsNode* stmts_node;

    cDeclNode* decl_node;
    cDeclsNode* decls_node;

    cParamsNode* params_node;

    cProgramNode* program_node;
	cBlockNode* block_node;

#line 128 "langparse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LANGPARSE_H_INCLUDED  */
