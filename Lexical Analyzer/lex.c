#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(){

        int i=0,j,k=0,l=1,flag=0;
        char keyword[30][30] = {"int","main","for","if","else","while","do"};
        char ch,str[20];
        FILE *input, *output;
        input = fopen("var.c","r");
        output = fopen("output.txt","w");
        fprintf(output,"Line No.\t\t Token No.\t\t Token\t\t Lexeme\n");
        while(!feof(input)){
                ch = fgetc(input);
                if (ch=='*'||ch=='-'||ch=='+'||ch=='/'){
                        fprintf(output,"%d\t\t %d\t\t Operators\t\t %c\n",l,k,ch);
                        k++;
                }
                else if(ch==';'||ch==':'||ch=='{'||ch=='}'||ch=='('||ch==')'||ch=='['||ch==']'||ch=='@'||ch=='?'||ch=='!'||ch=='%'){
                        fprintf(output,"%d\t\t %d\t\t Spectial Symbols\t\t %c\n",l,k,ch);
                        k++;
                }
                else if(isdigit(ch)){
                        fprintf(output,"%d\t\t %d\t\t Digit\t\t %c\n",l,k,ch);
                        k++;
                }
                else if(isalpha(ch)){
                        i=0;
                        str[i]=ch;
                        i++;
                        ch = fgetc(input);
                        while(isalnum(ch) && ch!=' '){
                                str[i] = ch;
                                ch = fgetc(input);
                                i++;
                        }
                        str[i]='\0';
                        for(j=0;j<30;j++){
                                if(strcmp(keyword[j],str)==0){
                                        flag=1;
                                }
                        }
                        if(flag){
                                fprintf(output,"%d\t\t %d\t\t Keyword\t\t %s\n",l,k,str);
                                k++;
                        }
                        else{
                                fprintf(output,"%d\t\t %d\t\t Identifier\t\t %s\n",l,k,str);
                                k++;
                        }

                }
                else if(ch=='\n'){
                        l++;
                }

        }
        fclose(input);
        fclose(output);
        return 0;
}
