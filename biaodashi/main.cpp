#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define STACK_INIT_SIZE 100000
typedef struct{
    char elem[STACK_INIT_SIZE];
    int stacksize;
    int top;
}OP;
typedef struct{
    float val[STACK_INIT_SIZE];
    int stacksize;
    int top;
}VAL;
void print_menu(void){
    printf("=============表达式求值=============\n\n");
    printf("1)算数表达式           2）多项式表达式\n\n");
    printf("3)退出\n\n");
    printf("请输入选项：");
}
bool isoperator(char ch){
    if(ch=='(') return true;
    else if(ch==')') return true;
    else if(ch=='+') return true;
    else if(ch=='-') return true;
    else if(ch=='*') return true;
    else if(ch=='/') return true;
    else if(ch=='#') return true;
    else return false;
}
bool isright(char ch){
    if(ch=='(') return true;
    else if(ch==')') return true;
    else if(ch=='+') return true;
    else if(ch=='-') return true;
    else if(ch=='*') return true;
    else if(ch=='/') return true;
    else if(ch=='#') return true;
    else if(ch>='0'&&ch<='9') return true;
    else if(ch=='.') return true;
    else if(ch=='\n') return true;
    else return false;
}
void Push_OP(OP &SOP,char e){
    SOP.elem[++SOP.top]=e;
}
void Push_VAL(VAL &SVAL,float e){
    SVAL.val[++SVAL.top]=e;
}
bool Pop_OP(OP &SOP,char *e){
    if(SOP.top==-1) return false;
    *e=SOP.elem[SOP.top--];
    return true;
}
bool Pop_VAL(VAL &SVAL,float *e){
    if(SVAL.top==-1) return false;
    *e=SVAL.val[SVAL.top--];
    return true;
}
float operate(float a,char c,float b){
    if(c=='+') return a+b;
    if(c=='-') return a-b;
    if(c=='*') return a*b;
    if(c=='/'){
        if(b==0){
            printf("ERROR!数学错误！除数为0！\n");
            return 0;
        }
        else return a/b;
    }
    return 0;
}
bool GetTop_OP(OP SOP,char *ch){
    if(SOP.top==-1) return false;
    *ch=SOP.elem[SOP.top];
    return true;
}
bool GetTop_VAL(VAL SVAL,float *e){
    if(SVAL.top==-1) return false;
    *e=SVAL.val[SVAL.top];
    return true;
}
bool preop(char c,char ch){
    if((ch=='*'||ch=='/')&&(c=='+'||c=='-'))
        return false;
    if(c=='#') return false;
    if(ch=='#') return true;
    if(c=='(') return false;
    return true;
}
void EvaluateExp(char exp[],float *x){
    OP SOP;SOP.top=-1;SOP.stacksize=STACK_INIT_SIZE;Push_OP(SOP,'#');
    VAL SVAL;SVAL.top=-1;SVAL.stacksize=STACK_INIT_SIZE;
    char *p=exp;char ch;char anumber[STACK_INIT_SIZE]="0";
    float aval=0;int i=0;float b=0,a=0;char c;float e=0;char ch1;
    while(SOP.top!=-1){
        ch=*p++;
        p--;p--;ch1=*p;p++;p++;
        i=0;
        if(ch=='-'){
            if(isoperator(c)){
                anumber[i]=ch;i++;ch=*p++;
                while(!isoperator(ch)){
                    anumber[i]=ch;
                    ch=*p++;
                    i++;
                }
                anumber[i]='\0';
                aval=atof(anumber);
                Push_VAL(SVAL,aval);
            }
        }
        if(!isoperator(ch)){
            while(!isoperator(ch)){
                anumber[i]=ch;
                ch=*p++;
                i++;
            }
            anumber[i]='\0';
            aval=atof(anumber);
            Push_VAL(SVAL,aval);
        }
        switch(ch){
            case '(':
                Push_OP(SOP,ch);break;
            case ')':
                while(Pop_OP(SOP,&c)&&c!='('){
                    Pop_VAL(SVAL,&b);Pop_VAL(SVAL,&a);
                    Push_VAL(SVAL,operate(a,c,b));
                }
                break;
            default:
                while(GetTop_OP(SOP,&c)&&preop(c,ch)){
                    Pop_OP(SOP,&c);
                    Pop_VAL(SVAL,&b);Pop_VAL(SVAL,&a);
                    Push_VAL(SVAL,operate(a,c,b));
                }
                if(ch!='#') Push_OP(SOP,ch);
                if(ch=='#') Pop_OP(SOP,&c);
                break;
        }
    }
    GetTop_VAL(SVAL,&e);
    SOP.top=-1;SVAL.top=-1;
    *x=e;
}
int get_number(void){
    int i;
    while(scanf("%d",&i)!=1||(i<1||i>3)){
        printf("ERROR!请输入1~3的数字!请重新输入！\n");
        while(getchar()!='\n') continue;
    }
    return i;
}
bool match(char exp[]){
    int matchstat=1;char ch;char e;
    OP S;S.top=-1;S.stacksize=STACK_INIT_SIZE;char *p;
    p=exp;
    ch=*p++;
    if(!isright(ch)) matchstat=0;
    while(ch!='#'&&matchstat){
        switch(ch){
            case '(':
                Push_OP(S,ch);
                break;
            case ')':
                if(!Pop_OP(S,&e)||e!='(') matchstat=0;
                break;
        }//switch
        ch=*p++;if(!isright(ch)) matchstat=0;
    }//while
    if(matchstat&S.top==-1) return true;
    else return false;
}
int main(){
    OP SOP;
    print_menu();
    float x=0;
    char exp[STACK_INIT_SIZE];
    char exp_0[STACK_INIT_SIZE];
    int i=0;
    while(1){
        i=get_number();
        switch (i) {
            case 1:
                while(getchar()!='\n') continue;
                printf("请输入表达式（以#结束）\n");
                scanf("%s",exp);
                while(getchar()!='\n') continue;
                if(!match(exp)){
                    printf("ERROR！语法错误！\n");
                }
                else{
                    EvaluateExp(exp,&x);
                    printf("该表达式值为%f\n",x);
                }
                print_menu();
                break;
            case 2:
                printf("功能未开放！\n");
                print_menu();
                break;
            case 3:
                printf("Bye\n");
                exit(0);
                break;
        }
    }
}
