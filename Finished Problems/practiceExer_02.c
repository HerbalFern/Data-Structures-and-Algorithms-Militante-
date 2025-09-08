#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char elem;
    struct node *link;
} *charList;

void insertElem(charList* head, char elem);
bool findElem(charList head, char find);


int main(){

    charList L = NULL;
    insertElem(&L, 'C');
    insertElem(&L, 'O');
    insertElem(&L, 'O');
    insertElem(&L, 'L');

    for (charList trav = L; trav != NULL; trav = trav->link){
        printf("%c", trav->elem);
    }

    (findElem(L, 'O') == true) ? printf("\nFound") : printf("\nNot Found"); 

    return 0;
}

void insertElem(charList* head, char elem){
    charList temp = malloc(sizeof(struct node));
    if (temp == NULL){
        printf("\nmem alloc failed\n");
        return;
    }

    temp->elem = elem;
    temp->link = NULL;
    charList* trav;
    for (trav = head; *trav != NULL; trav = &(*trav)->link){}
    
    *trav = temp;
}

bool findElem(charList head, char find){
    charList trav;
    for (trav = head; trav != NULL && trav->elem != find ; trav = trav->link){}
    return (trav == NULL) ? false : true;
}