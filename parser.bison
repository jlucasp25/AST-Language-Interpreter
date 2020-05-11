// Tokens
%token 
  INT  
  PLUS
  MINUS
  MULT
  DIV
  REST
  EQUAL
  DIFFERENT
  GREATER
  LESS
  EQGREATER
  EQLESS
  IF
  THEN
  ELSE
  LET
  ASSIGNEQUAL
  SEMICOLON
  OPENBRACE
  CLOSEBRACE
  OPENPAR
  CLOSEPAR
  WHILE
  VAR
  PRINT
  READ
  INITFUNC

// Operator associativity & precedence
%left ASSIGN
%left PLUS MINUS
%left MULT DIV REST
%left GREATER LESS EQGREATER EQLESS
%left EQUAL DIFFERENT


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* varValue;
  Expr* exprValue;
  Cmd* cmdValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <cmdValue> cmd
%type <varValue> VAR

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Cmd* root;
}

%%
program: cmd { root = $1; }
cmd:
  LET VAR ASSIGNEQUAL expr {
    $$ = ast_assign($2,$4);
  }
  |
  IF expr cmd {
    $$ = ast_if_then($2,$3);
  }
  |
  IF expr cmd ELSE cmd {
    $$ = ast_if_then_else($2, $3, $5);
  }
  |
  WHILE expr cmd {
    $$ = ast_while($2, $3);
  }
  |
  cmd SEMICOLON cmd {
    $$ = ast_semicolon($1, $3);
  }
  |
  OPENBRACE cmd CLOSEBRACE {
    $$ = ast_codeblock($2);
  }
  |
  PRINT OPENPAR VAR CLOSEPAR {
    $$ = ast_println($3);
  }
  |
  READ OPENPAR VAR CLOSEPAR {
    $$ = ast_read_line($3);
  }
  |
  INITFUNC cmd {
    $$ = ast_initfunction($2);
  }
  ;
expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  }
  | 
  expr MINUS expr { 
    $$ = ast_operation(MINUS, $1, $3); 
  }
  | 
  expr MULT expr { 
    $$ = ast_operation(MULT, $1, $3); 
  }
  | 
  expr DIV expr { 
    $$ = ast_operation(DIV, $1, $3); 
  }
  | 
  expr REST expr { 
    $$ = ast_operation(REST, $1, $3); 
  }
  | 
  expr EQUAL expr { 
    $$ = ast_operation(EQUAL, $1, $3); 
  }
  | 
  expr DIFFERENT expr { 
    $$ = ast_operation(DIFFERENT, $1, $3); 
  }
  | 
  expr GREATER expr { 
    $$ = ast_operation(GREATER, $1, $3); 
  }
  | 
  expr LESS expr { 
    $$ = ast_operation(LESS, $1, $3); 
  }
  | 
  expr EQGREATER expr { 
    $$ = ast_operation(EQGREATER, $1, $3); 
  }
  | 
  expr EQLESS expr { 
    $$ = ast_operation(EQLESS, $1, $3); 
  }
  |
  VAR {
    $$ = ast_variable($1);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

