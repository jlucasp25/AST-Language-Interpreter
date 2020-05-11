// AST constructor functions

#include <stdlib.h> // for malloc
#include <string.h>
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_variable(char* var) {
    Expr* node = (Expr*) malloc(sizeof(Expr));
    node->kind = E_VARIABLE;
    node->attr.var = strdup(var);
    return node;
}

////////////////////////
//Command constructors//
////////////////////////

Cmd* ast_while(Expr* e,Cmd* t) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_WHILE;
  node->op.condexe.conditionExpr = e;
  node->op.condexe.executeCmd = t;
  return node;
}

Cmd* ast_if_then(Expr* e, Cmd* t) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_IF_THEN;
  node->op.condexe.conditionExpr = e;
  node->op.condexe.executeCmd = t;
  return node;
}

Cmd* ast_if_then_else(Expr* e, Cmd* t, Cmd* t2) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_IF_THEN_ELSE;
  node->op.condexeexe.conditionExpr = e;
  node->op.condexeexe.executeCmd1 = t; //then
  node->op.condexeexe.executeCmd2 = t2; //else
  return node;
}

Cmd* ast_assign(char* left, Expr* right) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_ASSIGN;
  node->op.assign.leftSide = strdup(left);
  node->op.assign.rightSide = right;
  return node;
}

Cmd* ast_semicolon(Cmd* left, Cmd* right) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_SEMICOLON;
  node->op.chain.leftSide = left;
  node->op.chain.rightSide = right;
  return node;
}

Cmd* ast_codeblock(Cmd* t) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_CODEBLOCK;
  node->op.executeCmd = t;
  return node;
}

Cmd* ast_println(char* var) {
  Cmd* node = (Cmd*) malloc(sizeof(Expr));
  node->kind = C_PRINT;
  node->op.IOString = strdup(var);
  return node;
}

Cmd* ast_read_line(char* var) {
  Cmd* node = (Cmd*) malloc(sizeof(Expr));
  node->kind = C_READ;
  node->op.IOString = strdup(var);
  return node;
}

Cmd* ast_initfunction(Cmd* t) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_INITFUNC;
  node->op.executeCmd = t;
  return node;
}