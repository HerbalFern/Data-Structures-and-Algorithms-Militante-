#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
    int data;
    struct node* next;
} *List;

typedef List Dictionary[MAX];

void insert(int data, Dictionary D);
void delete(int data, Dictionary D);
int member (int data, Dictionary D);
int hash(int data);
void displayDics(Dictionary D);

int main (){
    
    Dictionary D = {NULL};
    
    insert(0, D);
    insert(20, D);
    insert(30, D);
    insert(13, D);
    insert(33, D);
    insert(45, D);
    insert(28, D);
    insert(48, D);
    insert(108, D);
    insert(38, D);
    
    delete(108, D);
    delete(200, D);
    displayDics(D);

    return 0;
}

int hash(int data){
    return data%10;
}

void insert(int data, Dictionary D){
    int h = hash(data);
    
    List temp = malloc(sizeof(struct node));
    if (temp == NULL){
        printf("\nmemaloc failed\n");
        return;
    }
    
    temp->next = NULL;
    temp->data = data;


    List* trav; 
    for (trav = &D[h]; *trav != NULL && (*trav)->data < data; trav = &(*trav)->next){}
    temp->next = *trav;
    *trav = temp;
    

    printf("Inserted %d into the dictionary\n", data);
}

void delete(int data, Dictionary D){
    int h = hash(data);


    List* trav; 
    for (trav = &D[h]; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next){}
    if (*trav != NULL){
        List temp = *trav;
        *trav = temp->next;
        free(temp);
        printf("Deleted %d from the dictionary\n", data);
    } else {
        printf("Could not find %d in the Dictionary\n", data);
    }
}

int member (int data, Dictionary D){
    int h = hash(data);

    List trav;
    for (trav = D[h]; trav != NULL && trav->data != data; trav = trav->next){}
    if (trav != NULL){
        return 1;
    } else {
        return 0;
    }
}

void displayDics(Dictionary D){
    List trav;
    for (int i = 0; i < MAX; i++){
        printf("[%d]: ", i);
        for (trav = D[i]; trav != NULL;trav = trav->next){
            printf("%d -> ", trav->data);
        }
        printf("NULL");
        printf("\n");
    }
}

