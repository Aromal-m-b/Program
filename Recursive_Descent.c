#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

/* E->TE'
 * T->FT'
 * E'->+TE'|-TE'
 * T'->*FT'|/FT'
 * F->(E)|alnum
 */

int i,error;
char input[30];

void E();
void T();
void F();
void Eprime();
void Tprime();

void main(){
        i=error=0;
        printf("\nEnter the expression to evaluvate :");
        scanf("%s",input);
        E();
        if(strlen(input) == i && error == 0)
                printf("\nValid Expression");
        else
                printf("\nInvalid Expression");
}

void E(){
        T();
        Eprime();
}

void T(){
        F();
        Tprime();
}

void F(){
        if(input[i] == '('){
                i++;
                E();
                if(input[i] == ')')
                        i++;
                else
                        error = 1;
        }
        else if(isalnum(input[i]))
                i++;
        else
                error = 1;
}

void Tprime(){
        if(input[i] == '/' || input[i] == '*'){
                i++;
                F();
                Tprime();
        }
}

void Eprime(){
        if(input[i] == '+' || input[i] == '-'){
                i++;
                T();
                Eprime();
        }
}
