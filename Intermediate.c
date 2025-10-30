#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 100
int top = -1;
char stack[MAX];

void push(char *c){
        stack[++top];
}

char pop(){
        return stack[top--];
}

int priority(char ch){
        if(ch == '^')
                return 3;
        else if(ch == '*' || ch == '/')
                return 2;
        else if(ch == '+' || ch == '-')
                return 1;
        else
                return 0;
}

void in_post(char infix[],char postfix[]){
        int i = 0;
        int j= 0 ;
        for(i =0 ;infix[i];i++){
                if(isalnum(infix[i])){
                        postfix[j++] = infix[i];
                }
                else if(infix[i] == '('){
                        push('(');
                }
                else if(infix[i] == ')'){
                        while(stack[top]!=')'){
                                postfix[j++] = pop();
                        }
                        pop();
                }
                else{
                        while(priority(stack[top]>=priority(infix[i]))){
                                postfix[j++] = pop();
                        }
                        push(infix[i]);
                }
        }
        while(top>=0){
                postfix[j++] = pop();
        }
        postifx[j] = '\0';
}

void threeaddr(char *str){
        int t1 = 90;
        char t2,t3;
        for(int i=0;i<strlen(str);i++){
                if(isalnum(str[i]))
                        push(str[i]);
                else{
                        t3 = pop();
                        t2 = pop();
                        printf("%s : %s %s %s\n",t1,t2,str[i],t3);
                        push(t1--);
                }
        }
}

int main(){
        char postfix[MAX],infix[MAX];
        printf("Enter the expression :");
        scanf("%s",infix);
        in_post(infix,postfix);
        threeaddr(postfix);
        return 0;
}
