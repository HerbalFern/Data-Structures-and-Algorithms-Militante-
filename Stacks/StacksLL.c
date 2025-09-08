#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} Stack;

void initList(Stack*);

void push(Stack*, int);
void pop(Stack*);
void peek(Stack);
int isEmpty(Stack);

void printStack(Stack stack);

int main(){
    Stack stack;
    initList(&stack);
    push(&stack, 4);
    push(&stack, 3);
    push(&stack, 2);

    peek(stack);

    push(&stack, 1);
    pop(&stack);

    printStack(stack);

    return 0;
}

void push(Stack* stack, int data){
    Node* temp = (Node*) malloc(sizeof(Node));
    Node** head = &stack->head;
    if (temp != NULL) {
        temp->data = data;
        temp->next = *head;
        *head = temp;
        printf("Successfully Pushed %d to Stack\n", data);
        stack->count++;
    } 
}

void pop(Stack* stack){
    
    if (isEmpty(*stack) == 0){
        Node* temp = stack->head;
        
        printf("Popping %d from the Stack\n", temp->data);
        
        stack->head = stack->head->next;
        free(temp);
    }
}

void peek(Stack stack){
    (stack.count > 0) ? printf("Top: %d\n", stack.head->data) : printf("Stack is empty. \n");
}

int isEmpty(Stack stack){
    if(stack.head == NULL){
        return 1;
    } return 0;
}

void initList(Stack* stack){
    stack->count = 0;
    stack->head = NULL;
}

void printStack(Stack stack){
    Node* trav;
    for (trav = stack.head; trav != NULL; trav = trav->next){
        printf("| %d |\n", trav->data);
    } printf("=====\n");
}   