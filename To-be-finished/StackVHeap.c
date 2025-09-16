#include <stdio.h>
#include <stdbool.h>
#define MAX 15

typedef struct node {
    int data;
    int link;
} Node;

typedef struct vheap {
    Node elems[MAX];
    int avail;
} vHeap;

typedef int clist;

typedef struct stack {
    clist top;
    vHeap VH;
    int count;
} Stack;


void initList(clist* CL);
void initVHeap(vHeap* VH);

int allocSpace(vHeap* VH);
void deallocSpace(vHeap* VH, int pos);

void initStack(Stack* S);


bool isFull(Stack S);
bool isEmpty(Stack S);

void push(Stack* S, int data);
void pop(Stack* S);
int top(Stack S);

void displayStack(Stack S);

int main(){

    Stack S;
    initStack(&S);

    push(&S, 5);
    push(&S, 4);
    push(&S, 3);
    push(&S, 2);
    push(&S, 1);
    
    displayStack(S);

    pop(&S);
    pop(&S);
    
    displayStack(S);

    pop(&S);
    pop(&S);
    pop(&S);

    displayStack(S);


    return 0;
}


void initList(clist* CL){
    *CL = -1;
}

void initVHeap(vHeap* VH){
    VH->avail = 0;
    int i;
    for (i = 0; i < MAX - 1; i++){
        VH->elems[i].link = i + 1;
    }
    VH->elems[MAX-1].link = -1;
}

void initStack(Stack* S){
    S->count = 0;
    initList(&S->top);
    initVHeap(&S->VH);
}

int allocSpace(vHeap* VH){
    int temp = VH->avail;
    if (temp != -1){
        VH->avail = VH->elems[temp].link;
    } 
    return temp;
}

void deallocSpace(vHeap* VH, int pos){
    VH->elems[pos].link = VH->avail;
    VH->avail = pos;
}

bool isFull(Stack S){
    if (S.count == MAX){
        return true;
    } return false;
}

bool isEmpty(Stack S){
    return (S.top == -1) ? true : false;
}

void push(Stack* S, int data){
    if (!isFull(*S)){
        clist temp = allocSpace(&S->VH);
        if (temp != -1){
            S->VH.elems[temp].data = data;
            S->VH.elems[temp].link = S->top;
            S->top = temp;
            S->count++;
        } else {
            printf("\nMem alloc failed\n");
        }
    } else {
        printf("\nList is Full\n");
    }
}

void pop(Stack* S){
    if (!isEmpty(*S)){
        clist temp;
        temp = S->top;
        S->top = S->VH.elems[temp].link;
        deallocSpace(&S->VH, temp);
        
        S->count--;
    } else {
        printf("\nStack is empty, nothing to pop\n");
    }
}


int top(Stack S){
    return S.VH.elems[S.top].data;
}

void displayStack(Stack S){
    clist trav;
    printf("\nStack:\nTOP -> ");
    for (trav = S.top; trav != -1; trav = S.VH.elems[trav].link){
        printf("[%d]", S.VH.elems[trav].data);
    }
}
