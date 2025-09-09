#include <stdio.h>
#include <stdlib.h>

/*

Insert at the beginning.
Insert at the end.
Insert at a specific position.
Insert after a given node.
Insert before a given node.


*/

typedef struct node {
    int data;
    struct node* next;
} Node, *NODE;

void insertFirst(NODE* head, int data);
void insertLast(NODE* head, int data);
void insertAfterNode(NODE* head, int data, int elem);
void insertAtPos(NODE* head, int pos, int data);
void insertBeforeNode(NODE* head, int data, int elem);
void insertSorted(NODE* head, int data);


void deleteElem(NODE* head, int elem);
void deleteFirst(NODE* head);
void deleteLast(NODE* head);
void deleteAtIndex(NODE* head, int idx);
void deleteMult(NODE* head, int elem);

void printList(NODE head){
    for (NODE trav = head; trav != NULL; trav = trav->next){
        printf("%d -> ", trav->data);
    }
    printf("NULL\n");
}

int main(){
    NODE head = NULL;

    printf("=== INSERT TESTS ===\n");

    // Test insertSorted on an initially empty list
    insertSorted(&head, 10);  // List: 10
    printList(head);

    insertSorted(&head, 5);   // List: 5 -> 10
    printList(head);

    insertSorted(&head, 20);  // List: 5 -> 10 -> 20
    printList(head);

    insertSorted(&head, 15);  // List: 5 -> 10 -> 15 -> 20
    printList(head);

    // insertFirst
    insertFirst(&head, 1);    // List: 1 -> 5 -> 10 -> 15 -> 20
    printList(head);

    // insertLast
    insertLast(&head, 25);    // List: 1 -> 5 -> 10 -> 15 -> 20 -> 25
    printList(head);

    // insertAfterNode
    insertAfterNode(&head, 12, 10); // after 10: 1 -> 5 -> 10 -> 12 -> 15 -> 20 -> 25
    printList(head);

    // insertBeforeNode
    insertBeforeNode(&head, 8, 10); // before 10: 1 -> 5 -> 8 -> 10 -> 12 -> 15 -> 20 -> 25
    printList(head);

    // insertAtPos
    insertAtPos(&head, 3, 7); // pos=3 (0-based): 1 -> 5 -> 8 -> 7 -> 10 -> 12 -> 15 -> 20 -> 25
    printList(head);

    printf("\n=== DELETE TESTS ===\n");

    // deleteFirst
    deleteFirst(&head);   // remove 1
    // List: 5 -> 8 -> 7 -> 10 -> 12 -> 15 -> 20 -> 25
    printList(head);

    // deleteLast
    deleteLast(&head);    // remove 25
    // List: 5 -> 8 -> 7 -> 10 -> 12 -> 15 -> 20
    printList(head);

    // deleteElem
    deleteElem(&head, 7); // remove 7
    // List: 5 -> 8 -> 10 -> 12 -> 15 -> 20
    printList(head);

    // deleteAtIndex
    deleteAtIndex(&head, 2); // remove index 2 (0-based, element=10)
    // List: 5 -> 8 -> 12 -> 15 -> 20
    printList(head);

    // prepare for deleteMult
    insertLast(&head, 8);
    insertLast(&head, 30);
    insertLast(&head, 8);
    // List: 5 -> 8 -> 12 -> 15 -> 20 -> 8 -> 30 -> 8
    printList(head);

    // deleteMult
    deleteMult(&head, 8); // remove all 8s
    // List: 5 -> 12 -> 15 -> 20 -> 30
    printList(head);

    return 0;
}

void insertAtPos(NODE* head, int pos, int data){
    NODE* trav;
    int i;
    for (i = 0, trav = head; *trav != NULL && i < pos; i++, trav = &(*trav)->next){}
    NODE temp = (NODE) malloc(sizeof(Node));
    if (temp != NULL){
        if (i < pos){
            printf("Index is out of bounds\n");
        } else {
            temp->data = data;
            temp->next = *trav;
            *trav = temp;
        }
    }
}

void insertFirst(NODE* head, int data){
    NODE temp = (NODE) malloc(sizeof(Node));
    if (temp != NULL){
        temp->next = *head;
        temp->data = data;
        *head = temp;
    }
}


void insertLast(NODE* head, int data){
    NODE temp = (NODE) malloc(sizeof(Node));
    NODE* trav;
    if (temp != NULL){
        for (trav = head; *trav != NULL; trav = &(*trav)->next){}
        temp->data = data;  
        temp->next = NULL;
        *trav = temp;        
    }
}


void insertAfterNode(NODE* head, int data, int elem){
    NODE temp = (NODE) malloc(sizeof(Node));
    NODE* trav;
    if (temp != NULL){
        for (trav = head; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->next){}
        if (*trav != NULL){
            temp->data = data;  
            temp->next = (*trav)->next;
            (*trav)->next = temp;       
        } else {
            printf("Element could not be found\n");
        }
    }
}

void insertBeforeNode(NODE* head, int data, int elem){
    NODE temp = (NODE) malloc(sizeof(Node));
    NODE* trav;
    if (temp != NULL){
        for (trav = head; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->next){}
        temp->data = data;  
        temp->next = *trav;
        *trav = temp;       
    }

}


// only applies if list is sorted in ascendant order
void insertSorted(NODE* head, int data){
    NODE temp = (NODE) malloc(sizeof(Node));
    NODE* trav;

    if (temp != NULL){
        for (trav = head; *trav != NULL && (*trav)->data < data; trav = &(*trav)->next){}
        temp->data = data;
        temp->next = *trav;
        *trav = temp;
    }
}



void deleteElem(NODE* head, int elem){
    NODE temp;
    NODE *trav;
    
    for (trav = head; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->next){}
    if (*trav != NULL){ 
        temp = *trav;
        *trav = temp->next;
        free(temp);
    } else {
        printf("Cannot Delete. Element %d not on the list\n", elem);
    }

}


void deleteFirst(NODE* head){
    NODE temp; 

    if (*head != NULL){
        temp = *head;
        *head = temp->next;
        free(temp);
    } else {
        printf("Cannot Delete First Element, List is Empty\n");
    }
}


void deleteLast(NODE* head){
    
    if (*head != NULL){    
        NODE* trav, temp;    
        for(trav = head; (*trav)->next != NULL; trav = &(*trav)->next){}
        temp = *trav;
        *trav = NULL;
        free(temp);
    }
}


void deleteAtIndex(NODE* head, int idx){
    if (*head != NULL){    
        NODE* trav, temp;
        int i;    
        for(i = 0, trav = head; *trav != NULL && i < idx ; i++, trav = &(*trav)->next){}
        temp = *trav;
        *trav = temp->next;
        free(temp);
    } else {
        printf("List is empty, Cannot delete\n");
    }
}


void deleteMult(NODE* head, int elem){
    NODE* trav, temp;
    if (*head != NULL){
        for (trav = head; *trav != NULL;){
            if ((*trav)->data == elem){
                temp = *trav;
                *trav = temp->next;
                free(temp);        
            } else {
                trav = &(*trav)->next;
            }
        }
    }
}
