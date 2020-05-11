
//
// yylval = atoi(yytext);
// return INT;
//
//flex: [a-z] [a-z A-z 0-9]* regexp 
// yylval = strdup(yytext);
// return VAL;

// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VARIABLE,
  } kind;
  union {
    int value; // for integer values
    char* var; //for variable expression
    struct { 
      int operator; // PLUS, MINUS, etc , EQUAL LESS GREATER
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};


typedef struct _Cmd Cmd; //Cmd typdef
typedef struct _Expr Expr; // Convenience typedef

//AST for Commands
//(while, if, then, else, = , ; , { , })
struct _Cmd {
  enum {
    C_WHILE,
    C_IF_THEN,
    C_IF_THEN_ELSE,
    C_ASSIGN,
    C_SEMICOLON,
    C_CODEBLOCK,
    C_PRINT,
    C_READ,
    C_INITFUNC
  } kind;
  union {
    Cmd* executeCmd;
    char* IOString;
    struct {
      Expr* conditionExpr;
      Cmd* executeCmd;
    } condexe; //Conditional&Execute
    struct {
      Expr* conditionExpr;
      Cmd* executeCmd1;
      Cmd* executeCmd2;
    } condexeexe; //Conditional&Execute&Execute
    struct {
      char* leftSide; // <- var name
      Expr* rightSide;
    } assign;
    struct {
      Cmd* leftSide;
      Cmd* rightSide;
    } chain;
  } op; 
};


//Constructor functions (Commands)
Cmd* ast_while(Expr* e,Cmd* t);
Cmd* ast_if_then(Expr* e, Cmd* t);
Cmd* ast_if_then_else(Expr* e, Cmd* t, Cmd* t2);
Cmd* ast_assign(char* left, Expr* right);
Cmd* ast_semicolon(Cmd* left, Cmd* right);
Cmd* ast_codeblock(Cmd* t);
Cmd* ast_println(char* var);
Cmd* ast_read_line(char* var);
Cmd* ast_initfunction(Cmd* t);

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_variable(char* var);
#endif