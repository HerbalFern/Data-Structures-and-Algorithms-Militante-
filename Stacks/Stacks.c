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
int peek(arrStack);

void displayStack(arrStack stack);

int main(){

    arrStack stack;
    initStack(&stack);


    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 5);

    
    

    displayStack(stack);
    
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

int peek(arrStack stack){
    if (isEmpty(stack) != 1) return stack.data[stack.top];
}

void displayStack(arrStack stack){
    printf("Stack: \n");
    while (isEmpty(stack)!=1){
        printf("| %d |\n", peek(stack));
        pop(&stack);
    }
    printf("\n");
}