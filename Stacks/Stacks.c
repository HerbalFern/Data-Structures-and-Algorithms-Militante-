#include <stdio.h>
#define MAX 30

typedef struct node {
    int data[MAX];
    int top;
} arrStack;

void initStack(arrStack*);
int isEmpty(arrStack);
int isFull(arrStack);
void push(arrStack*, int);
void pop(arrStack*);
void peek(arrStack);


int main(){

    arrStack stack;
    initStack(&stack);

    peek(stack);

    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);

    peek(stack);

    pop(&stack);
    
    peek(stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    peek(stack);
    
    return 0;
}

int isEmpty(arrStack stack){
    return (stack.top == -1) ? 1 : 0;
}

int isFull(arrStack stack){
    return (stack.top == MAX - 1) ? 1 : 0;
}

void initStack(arrStack* stack){
    stack->top = -1;
}

void push(arrStack* stack, int data){
    (isFull(*stack) == 0) ? stack->data[++(stack->top)] = data : printf("Stack is full\n"); 
}

void pop(arrStack* stack){
    (isEmpty(*stack) == 0) ? stack->top-- : printf("Stack is empty. Cannot Pop\n");
}

void peek(arrStack stack){
    (isEmpty(stack) == 0) ? printf("Top: %d\n", stack.data[stack.top]) : printf("Stack is empty. No Top\n");
}