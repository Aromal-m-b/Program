%{
#include<stdio.h>
int valid = 1;
%}

%token letter digit
%%

start : letter s

s : digit s
  | letter s
|
;

%%

int yyerror(){
        valid = 0;
        printf("\nInvalid identifier");
        return 0;
}

int main(){
        printf("\nEnter an Identifier :");
        yyparse();
        if(valid)
                printf("\nValid Identifier");
        return 1;
}
