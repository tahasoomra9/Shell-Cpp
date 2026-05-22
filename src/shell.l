

%{
#include <stdio.h>
#include <string.h>
#include "shell.tab.h" 
%}

%%

\n { return NEWLINE; } 
[ \t] {  }
";" { return SEMICOLON; }
"|" { return PIPE; }
">" { return GREAT; } 
"<" { return LESS; } 
">>" { return GREATGREAT; } 
"<<" { return LESSLESS; }
">&" { return GREATAMPERSAND; }
">>&" { return GREATGREATAMPERSAND; }
"&"  { return AMPERSAND; }
[^ \t\n]+ { yylval.string_val = strdup(yytext);
                    
                    return WORD; }


%%

int main() {
    yylex();
    return 0;
}