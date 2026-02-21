%code requires {
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
}

%{
#include <cstdlib>
#include <cstdio>

#include "astnodes.h"
#include "cSymbolTable.h"
#include "cBlockNode.h"
#include "cVarDeclNode.h"
#include "cArrayDeclNode.h"
#include "cStructDeclNode.h"
#include "cFuncDeclNode.h"

#include "cVarExprNode.h"
#include "cIntExprNode.h"
#include "cFloatExprNode.h"
#include "cStringExprNode.h"
#include "cArrayExprNode.h"
#include "cMemberExprNode.h"
#include "cFuncCallNode.h"

#include "cPrintNode.h"

#define CHECK_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; } }

#define PROP_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; YYERROR; } }

extern cSymbolTable g_symbolTable;
extern cAstNode* yyast_root;
int yylex();
void SemanticParseError(std::string error);
void yyerror(const char *msg)
{
    fprintf(stderr, "Parse error: %s\n", msg);
}
static bool g_semanticErrorHappened = false;
%}

%union {
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
}

%token <symbol> IDENTIFIER
%token <symbol> CHAR INT LONG FLOAT DOUBLE
%token <int_val> INT_VAL
%token <float_val> FLOAT_VAL
%token <str_val> STRING_LIT
%token LOCAL GLOBAL LOOKUP INSERT
%token OPEN CLOSE

%token IF ELSE ENDIF PRINT RETURN STRUCT ARRAY
%token EQUALS NOT_EQUALS GE LE AND OR

%type <symbol> type
%type <decl_node> decl
%type <decls_node> decls
%type <params_node> param_list
%type <stmt_node> stmt
%type <block_node> block
%type <stmts_node> stmts
%type <expr_node> expr
%type <program_node> program

%%

program:
    block
    {
        $$ = new cProgramNode($1);
        yyast_root = $$;
    }
;

block:
    OPEN decls stmts CLOSE
    {
        $$ = new cBlockNode($2, $3);
    }
;


decls:
      /* empty */
        { $$ = nullptr; }

    | decls decl
        {
            if ($1)
            {
                $1->Insert($2);
                $$ = $1;
            }
            else
            {
                $$ = new cDeclsNode($2);
            }
        }
;

type:
      CHAR   { $$ = $1; }
    | INT    { $$ = $1; }
    | LONG   { $$ = $1; }
    | FLOAT  { $$ = $1; }
    | DOUBLE { $$ = $1; }
;

decl:
      type IDENTIFIER
        { $$ = new cVarDeclNode($1, $2); PROP_ERROR(); }

    | type IDENTIFIER '[' INT_VAL ']'
        { $$ = new cArrayDeclNode($1, $2, $4); PROP_ERROR(); }

    | STRUCT IDENTIFIER OPEN decls CLOSE
        { $$ = new cStructDeclNode($4, $2); PROP_ERROR(); }

    | type IDENTIFIER '(' param_list ')' ';'
        { $$ = new cFuncDeclNode($1, $2, $4, nullptr, nullptr); PROP_ERROR(); }

    | type IDENTIFIER '(' param_list ')' OPEN stmts CLOSE
        { $$ = new cFuncDeclNode($1, $2, $4, nullptr, $7); PROP_ERROR(); }
;

param_list:
      /* empty */
        { $$ = nullptr; }

    | expr
        {
            $$ = new cParamsNode();
            $$->Insert($1);
        }

    | param_list ',' expr
        {
            $1->Insert($3);
            $$ = $1;
        }
;

stmt:
      PRINT STRING_LIT ';'
        { $$ = new cPrintNode(new cStringExprNode($2)); }

    | expr ';'
        { $$ = $1; }
;

stmts:
		{ $$ = nullptr; }

    | stmt
        { $$ = new cStmtsNode($1); }

    | stmts stmt
        {
            $1->Insert($2);
            $$ = $1;
        }
;

expr:
      IDENTIFIER
        { $$ = new cVarExprNode($1); }

    | INT_VAL
        { $$ = new cIntExprNode($1); }

    | FLOAT_VAL
        { $$ = new cFloatExprNode($1); }

    | STRING_LIT
        { $$ = new cStringExprNode($1); }

    | expr '[' expr ']'
        { $$ = new cArrayExprNode($1, $3); }

    | expr '.' IDENTIFIER
        { $$ = new cMemberExprNode($1, $3); }

    | IDENTIFIER '(' param_list ')'
        { $$ = new cFuncCallNode($1, $3); }
;

%%

void SemanticParseError(std::string error)
{
    std::cout << "ERROR: " << error << " near line "
              << yylineno << "\n";
    g_semanticErrorHappened = true;
    yynerrs++;
}
