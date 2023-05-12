//작동 안함. 시간 남을때 수정
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 1000

typedef enum {lparen,rparen,plus,minus,times,divide,mod,eos,operand}precedence;
  
//typedef int element;
typedef precedence element;
 
// ===== 스택 코드의 시작 ===== 
typedef struct {
   element data[MAX_STACK_SIZE];
   int top;
} StackType;
 
// 스택 초기화 함수
void init_stack(StackType *s)
{
   s->top = -1;
}
 
// 공백 상태 검출 함수
int is_empty(StackType *s)
{
   return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
   return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, element item)
{
   if (is_full(s)) {
      fprintf(stderr, "스택 포화 에러\n");
      return;
   }
   else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType *s)
{
   if (is_empty(s)) {
      fprintf(stderr, "스택 공백 에러\n");
      exit(1);
   }
   else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType *s)
{
   if (is_empty(s)) {
      fprintf(stderr, "스택 공백 에러\n");
      exit(1);
   }
   else return s->data[s->top];
}

static int isp[]={0,19,12,12,13,13,13,0};
static int icp[]={20,19,12,12,13,13,13,0};

//char expr[]="62/3-42*+";
char expr[]="2*(3+5)*4";

precedence getToken(char* symbol,int *n) {
    *symbol=expr[(*n)++];

    switch(*symbol) {
        case '(':
            return lparen;
        case ')':
            return rparen;
        case '+':
            return plus;
        case '-':
            return minus;
        case '/':
            return divide;
        case '*':
            return times;
        case '%':
            return mod;
        case '\0':
            return eos;
        default:
            return operand;
    }
}

int eval(void) { //후위 표기식을 연산
    precedence token;
    char symbol;
    int op1,op2;
    int n=0; //수식 스트링을 위한 카운터
    int top=-1;
    token=getToken(&symbol,&n);
    StackType s;
    init_stack(&s);
    
    while(token!=eos) {
        if(token==operand) {
            push(&s,symbol-'0');
        }
        else {
            op2=pop(&s);
            op1=pop(&s);
            
            switch(token) {
                case plus:
                    push(&s,op1+op2);
                    break;
                case minus:
                    push(&s,op1-op2);
                    break;
                case times:
                    push(&s,op1*op2);
                    break;
                case divide:
                    push(&s,op1/op2);
                    break;
                case mod:
                    push(&s,op1%op2);
                    break;
            }
        }
        token=getToken(&symbol,&n);
    }
    return pop(&s); //결과를 반환
}

void printToken(precedence token) {
    switch(token) {
        case lparen:
            printf("(");
            break;
        case rparen:
            printf(")");
            break;
        case plus:
            printf("+");
            break;
        case minus:
            printf("-");
            break;
        case times:
            printf("*");
            break;
        case divide:
            printf("/");
            break;
        case mod:
            printf("%%");
    }
}

void postfix(void) { //수식을 후위 표기식으로 출력
    char symbol;
    precedence token;
    StackType s;
    init_stack(&s);
    int n=0;
    int top=-1;
    push(&s,eos); //eos를 스택에 삽입한다.

    for(token=getToken(&symbol,n);token!=eos;token==getToken(&symbol,&n)) {
        if(token==operand) {
            printf("%c",symbol);
        }
        else if(token==rparen) {
            while(peek(&s)!=lparen) {
                printToken(pop(&s));
            }
            pop(&s); //왼쪽 괄호를 버린다.
        }
        else {
            while(isp[peek(&s)]>=icp[token]) {
                printToken(pop(&top));
            }
            push(&s,token);
        }
    }

    while((token=pop(&top))!=eos) {
        printToken(token);
    }
    printf("\n");
} //isp=스택안 icp=스택밖

int main(void) {
    postfix();

    return 0;
}