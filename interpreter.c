#include <stdio.h>
#include <string.h>
#include "parser.h"

#define SHELLWIDTH 80
int nRoot;
void printExpr(Expr* expr, int ntab);
void printCmd(Cmd* cmd, int ntab);
void printString(char* string, int ntab);

void centerText(char* text, int width) {
    int padlen = (width - strlen(text)) / 2;
    printf("%*s%s%*s\n", padlen, "", text, padlen, "");
} 

int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS: 
        result = vLeft + vRight; 
        break;
      case MINUS: 
        result = vLeft - vRight; 
        break;
      case MULT: 
        result = vLeft * vRight; 
        break;
      case DIV: 
        result = vLeft / vRight; 
        break;
      case REST: 
        result = vLeft % vRight; 
        break;
      case EQUAL:
        result = (vLeft == vRight);
        break;
      case DIFFERENT:
        result = (vLeft != vRight);
        break;
      case GREATER: 
        result = (vLeft > vRight);
        break;
      case LESS:
        result = (vLeft < vRight);
        break;
      case EQGREATER:
        result = (vLeft >= vRight);
        break;
      case EQLESS:
        result = (vLeft <= vRight);
        break;
      default: yyerror("Unknown operator!");
    }
  }
  else {
    printf("Error!\n");
  }
  return result;
}

void printVar(char* name, int ntab) {
   int i = 0;
  for ( i = 0 ; i < ntab ; i++)
    printf("\t");
  printf("| %s |",name);
} 

void printCmd(Cmd* cmd, int ntab) {
  int result = 0;
  int i = 0;
  for ( i = 0 ; i < ntab ; i++)
    printf("\t");

  switch(cmd->kind) {
    case C_WHILE: {
      printf("| WHILE |\n\n\n");
      printExpr(cmd->op.condexe.conditionExpr,ntab-1);
      printCmd(cmd->op.condexe.executeCmd,ntab+1);
    } break;
    case C_IF_THEN: {
      printf("| IF THEN |\n\n\n");
      printExpr(cmd->op.condexe.conditionExpr,ntab-1);
      printCmd(cmd->op.condexe.executeCmd,ntab+1);
    } break;
    case C_IF_THEN_ELSE: {
      printf("| IF THEN ELSE |\n\n\n");
      printExpr(cmd->op.condexe.conditionExpr,ntab-1);
      printCmd(cmd->op.condexeexe.executeCmd1,ntab);
      printCmd(cmd->op.condexeexe.executeCmd2,ntab+1);
    } break;
    case C_ASSIGN: {
      printf("| ASSIGN |\n\n\n");
      printVar(cmd->op.assign.leftSide,ntab+1);
      printExpr(cmd->op.assign.rightSide,ntab);
      printf("\n\n\n");
    } break;
    case C_SEMICOLON: {
      //printf("| SEMICOLON |\n\n\n");
      printCmd(cmd->op.chain.leftSide,ntab-2);
      printCmd(cmd->op.chain.rightSide,ntab+2);
    } break;
    case C_CODEBLOCK: {
      //printf("| CODEBLOCK |\n\n\n");
      printCmd(cmd->op.chain.leftSide,ntab-1);
    } break;
    case C_PRINT: {
      printf("| println! |\n\n\n");
      printString(cmd->op.IOString,ntab+2);
      //printCmd(cmd->op.chain.leftSide,ntab-1);
    } break;
    case C_READ: {
      printf("| read_line |\n\n\n");
      printString(cmd->op.IOString,ntab+2);
      //printCmd(cmd->op.chain.leftSide,ntab-1);
    } break;
    case C_INITFUNC: {
      printf("| fn main() |\n\n\n");
      printCmd(cmd->op.chain.leftSide,ntab-1);
    } break;
    default: yyerror("Unknown operator!");
  }
}

void printString(char* string, int ntab) {
  int i = 0;
  for ( i = 0 ; i < ntab ; i++){
    printf("\t");
  }
  printf("| %s |\n\n\n",string);
}

void printExpr(Expr* expr, int ntab) {
  int result = 0;

  for(int i=0; i<ntab; i++){
    printf("\t");
  }
  if (expr->kind == E_INTEGER) {
    result = expr->attr.value;
    printf("| %d |", result); 
  } 
  else if (expr->kind == E_OPERATION) {
    switch (expr->attr.op.operator) {
      case PLUS:  
        printf("| + |\n\n\n");      
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case MINUS:
        printf("| - |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case MULT:
        printf("| * |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case DIV:
        printf("| / |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case REST:
        printf("| %% |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case EQUAL:
        printf("| == |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case DIFFERENT:
        printf("| != |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case GREATER:
        printf("| > |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case LESS:
        printf("| < |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case EQGREATER:
        printf("| >= |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      case EQLESS:
        printf("| <= |\n\n\n");
        printExpr(expr->attr.op.left, ntab-1);
        printExpr(expr->attr.op.right, ntab+1);
        break;
      default: yyerror("Unknown operator!");
    }
  }
}



int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
      printCmd(root,3);
  }
  printf("\n\n\n");
  return 0;
}
