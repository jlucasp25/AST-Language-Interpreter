%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }


\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}

"+" 		{ return PLUS; 			}
"-" 		{ return MINUS;			}
"*" 		{ return MULT;			}
"/" 		{ return DIV;  			}
"%" 		{ return REST; 			}
"==" 		{ return EQUAL;			}
"!=" 		{ return DIFFERENT;		}
"<"	 		{ return LESS;			}
">" 		{ return GREATER;		}
"<=" 		{ return EQLESS;		}
">=" 		{ return EQGREATER;		}
"while" 	{ return WHILE;			}
"let" 		{ return LET;			}
"="			{ return ASSIGNEQUAL;	}
";" 		{ return SEMICOLON;		}
"{" 		{ return OPENBRACE;		}
"}" 		{ return CLOSEBRACE;	}
"("			{ return OPENPAR;		}
")"			{ return CLOSEPAR;		}
"if" 		{ return IF;			}
"then" 		{ return THEN;			}
"else" 		{ return ELSE;			}
"println!"	{ return PRINT;			}
"read_line" { return READ;			}
"fn main()"	{ return INITFUNC;		}


[a-zA-Z][a-zA-Z0-9]* {
   yylval.varValue = strdup(yytext);
   return VAR;
}

.  { yyerror("unexpected character"); }
%%

