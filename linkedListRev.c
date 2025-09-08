#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node, *NODE;

void insertAtPos(NODE* head, int pos, int data);

int main(){



    return 0;
}

void insertAtPos(NODE* head, int pos, int data){
    NODE* trav;
    int i;
    for (i = 0, trav = head; *trav != NULL && i < pos; i++, trav = &(*trav)->next){}
    NODE temp = (NODE) malloc(sizeof(Node));
    if (temp != NULL){
        if (i < pos){
            printf("Index is out of bounds");
        } else {
            temp->data = data;
            temp->next = *trav;
            temp = *trav;
        }
    }
}
