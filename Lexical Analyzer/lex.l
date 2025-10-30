%{
int comment = 0 ;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%
#.* {if(!comment)printf("\n\t %s is preporocessor directives",yytext);}
int|float|bool|double|void|return|break|continue|switch|while|do|if|else|for|goto|typedef|struct {if(!comment)printf("\n\t %s is a Keyword",yytext);}
"/*" {comment = 1;printf("\n\t %s is a commment",yytext);}
{identifier}\( {if(!comment)printf("\n\t %s is a Function",yytext);}
\{ {if(!comment)printf("\n\t Block Begins");}
\} {if(!comment)printf("\n\t Block Ends");}
{identifier}(\[[0-9]*\])? {if(!comment)printf("\n\t %s is an Identifier",yytext);}
\".*\" {if(!comment)printf("\n\t %s is a string",yytext);}
\)(\:)? {if(!comment)printf("\n\t");ECHO;printf("\n");}
\( ECHO;
= {if(!comment)printf("\n\t %s is an Assignment Operator",yytext);}
\+ {if(!comment)printf("\n\t %s is an Addition Operator",yytext);}
\<=|\>=|\<|\>|== {if(!comment)printf("\n\t %s is a Relational Operator",yytext);}
[0-9]+ {if(!comment)printf("\n\t %s is an Number",yytext);}
%%

int main(){
        FILE *file;
        file = fopen("var.c","r");
        yyin = file;
        yylex();
        printf("\n");
        return 0 ;
}

int yywrap(){
        return 1;
}
