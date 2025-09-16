#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void displayList(List L);



int main() {
    List L;
    L = initialize(L);

    printf("After initialize:\n");
    displayList(L);

    // Test insertPos
    printf("\n\nTesting insertPos...\n");
    L = insertPos(L, 10, 0);  // insert at start
    L = insertPos(L, 20, 1);  // insert at end
    L = insertPos(L, 15, 1);  // insert in middle
    displayList(L);

    // Test deletePos
    printf("\n\nTesting deletePos...\n");
    L = deletePos(L, 1);  // delete 15
    displayList(L);
    L = deletePos(L, 0);  // delete first element (10)
    displayList(L);

    // Test locate
    printf("\n\nTesting locate...\n");
    int pos = locate(L, 20);
    printf("Locate 20: %d\n", pos);
    pos = locate(L, 99);
    printf("Locate 99 (not in list): %d\n", pos);

    // Test insertSorted
    printf("\n\nTesting insertSorted...\n");
    L = insertSorted(L, 30);
    L = insertSorted(L, 25);
    L = insertSorted(L, 35);
    displayList(L);

    printf("\n\nAll tests done.\n");
    return 0;
}

List initialize(List L){
    L.count = 0;
    return L;
}


List insertPos(List L, int data, int position){
    int i;

    if (L.count == MAX){
        printf("List is Full. Cannot Insert Further\n");
        return L;
    }

    if (position <= L.count && position >= 0){
        for (i = L.count ; i > position; i--){
            L.elem[i] = L.elem[i-1];
        }

        L.elem[position] = data;
        L.count++;
    } else {
        printf("Position is out of bounds.\n");
    }


    return L;
}

List deletePos(List L, int position){
    
    if (L.count == 0){
        printf("List is empty. Nothing to delete\n");
        return L;
    }

    if (position < L.count && position >= 0){
        int i;
        for (i = position; i < L.count - 1; i++){
            L.elem[i] = L.elem[i+1];
        }
        L.count--;

        return L;
    }
}

int locate(List L, int data){
    int i;
    for (i = 0; i < L.count && L.elem[i] != data; i++){}
    
    return (i < L.count) ? i : -1;
}


List insertSorted(List L, int data){

    if (L.count == MAX){
        printf("List is Full. Cannot Insert Further\n");
        return L;
    }

    int i;
    for (i = L.count - 1; L.elem[i] > data && i >= 0; i--){
            L.elem[i+1] = L.elem[i];
    }
    
    
    L.elem[i+1] = data;
    L.count++;

    return L;
}


void displayList(List L){
    printf("Printed List: ");
    for (int i = 0; i < L.count; i++){
        printf("[%d] ", L.elem[i]);
    } printf("\n");
}
