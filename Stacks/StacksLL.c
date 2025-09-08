#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} Stack;

void initList(Stack);

void push(Stack*, int);
void pop(Stack*);
void peek(Stack);
int isEmpty(Stack);

int main(){


    return 0;
}

void push(Stack* stack, int data){
    Node* temp = (Node*) malloc(sizeof(Node));
    if (temp != NULL) {
        temp->data = data;
        temp->next = stack->head;
        stack->head = temp;
        printf("Successfully Pushed %d to Stack\n", data);
    }
}

void pop(Stack* stack){
    
    if (stack->head != NULL){
        Node* head;
        head = stack->head;
        Node* temp = head;
        head = head->next;
        free(temp);
    } else {
        printf("List is empty\n");
    }
}

void peek(Stack stack){
    printf("Top: %d", stack.head->data);
}

int isEmpty(Stack stack){
    if(stack.head == NULL){
        
    }
}