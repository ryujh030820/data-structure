#include <stdio.h>
#include <stdlib.h>
#define SEEK_SET 0

typedef struct Node *polyPointer;
typedef struct Node {
    int coef;
    int expon;
    polyPointer link;
}Node;

typedef struct ListHead {
    Node* head;
}ListHead;

//head reset
ListHead* createLinkedList(void) {
    ListHead* L;
    L=(ListHead*)malloc(sizeof(ListHead));
    L->head=NULL;
    return L;
}

void addNode(ListHead* L, int coef, int expon) {
    Node* newNode;
    Node* p;
    newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->link = NULL;

    if(L->head == NULL) {
        L->head = newNode;
        return;
    }

    p = L->head;

    if(expon>L->head->expon) {
        newNode->link=p;
        L->head=newNode;
    }
    else {
        while(p->link != NULL && p->link->expon > expon) {
            p = p->link;
        }

        newNode->link = p->link;
        p->link = newNode;
    }
}

//다항식 리스트에 마지막 노드 삽입 연산
void addLastNode(ListHead* L, int coef, int expon){
    Node* newNode;
    Node* p;
    newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->link = NULL;
    if(L->head == NULL){
        L->head = newNode;
        return;
    }
    else {
        p = L->head;
        while(p->link != NULL) {
            p = p->link;
        }
        p->link = newNode;
    }
}

//두 다항식의 합을 구하는 연산
void addPoly(ListHead* A, ListHead* B, ListHead* C){
    Node* pA = A->head;
    Node* pB = B->head;
    int sum;
    
    while(pA && pB){
        if(pA->expon == pB->expon){
            sum = pA->coef + pB->coef;
            addLastNode(C, sum, pA->expon);
            pA=pA->link; pB=pB->link;
        }
        else if(pA->expon > pB->expon){
            addLastNode(C, pA->coef, pA->expon);
            pA=pA->link;
        }
        else{
            addLastNode(C, pB->coef, pB->expon);
            pB=pB->link;
        }
    }
    for( ; pA!=NULL; pA=pA->link)
        addLastNode(C, pA->coef, pA->expon);
    for( ; pB!=NULL; pB=pB->link)
        addLastNode(C, pB->coef, pB->expon);
}

//다항식 리스트를 출력하는 연산
void printPoly(ListHead* L) {
    Node* p = L->head;
    printf("\nC = %3.0dx^%d", p->coef, p->expon);
    p=p->link;
    for(;p;p=p->link){
        if(p->coef<0){
        printf(" %dx^%d", p->coef, p->expon);
        }
        else{
            printf(" + %dx^%d", p->coef, p->expon);
        }
    }
}

int main(void) {
    FILE *fp=fopen("input.txt","r");

    char c;
    int termA=0,termB=0,coef,expon,n=0;
    ListHead* A, *B, *C;

    A=createLinkedList();
    B=createLinkedList();
    C=createLinkedList();

    if(fp==NULL) {
        fprintf(stderr,"Cannot open the file");
        exit(EXIT_FAILURE);
    }

    //A 다항식 입력받기
    while((c=fgetc(fp))!='\n') {
        if(c=='(') {
            termA++;
        }
        n++;
    }

    fseek(fp,0,SEEK_SET);

    for(int i=0;i<termA;i++) {
        fscanf(fp,"(%d,%d)",&coef,&expon);
        addNode(A,coef,expon);
    }

    //B 다항식 입력받기
    while((c=fgetc(fp))!=EOF) {
        if(c=='(') {
            termB++;
        }
    }

    fseek(fp,+n,SEEK_SET);

    fscanf(fp,"\n(%d,%d)",&coef,&expon);
    addNode(B,coef,expon);

    for(int i=0;i<termB-1;i++) {
        fscanf(fp,"(%d,%d)",&coef,&expon);
        addNode(B,coef,expon);
    }

    addPoly(A,B,C);

    printPoly(C);

    return 0;
}