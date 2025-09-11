#include <stdio.h>
#include <stdlib.h>
#define MAX 30
/*
# ASSIGNMENT:
- InsertFirst
- InserSorted
- DeleteFirst
- DeleteElem
*/


typedef struct {
    int elem[MAX];
    int count; 
} List; 

void insertFirst(List* L, int elem);
void insertSorted(List* L, int elem);
void deleteFirst(List* L);
void deleteElem(List* L, int elem);



int main(){

    List L;
    L.count = 0; 
    insertFirst(&L, 6);
    insertFirst(&L, 3);
    insertFirst(&L, 2);
    insertFirst(&L, 1);
    deleteFirst(&L);
    deleteElem(&L, 5);
    insertSorted(&L, 1);
    insertSorted(&L, 4);

    for (int i = 0; i < L.count; i++){
        printf("%d ", L.elem[i]);
    }
    return 0;
}

void insertFirst(List* L, int elem){
    if (L->count != MAX){
        for (int i = L->count; i > 0; i--){
            L->elem[i] = L->elem[i-1];
        }
        L->count++; 
        L->elem[0] = elem;
    } 
}
void insertSorted(List* L, int elem){
    if (L->count != MAX){
        int i, j;
        for (i = 0; L->count && L->elem[i+1] < elem; i++){}
        for (j = L->count; j > i; j--){
            L->elem[j] = L->elem[j-1];
        }
        L->count++; 
        L->elem[i] = elem;
    }
}

void deleteFirst(List* L){
    if (L->count != 0){
        for (int i = 0; i < L->count - 1; i++){
            L->elem[i] = L->elem[i+1];
        }
        L->count--;
    }
}

void deleteElem(List* L, int elem){
    if (L->count != 0){
        int i, j;
        for (i = 0; i <= L->count && L->elem[i] != elem; i++){}
        if (i < L->count){
            for (j = i; j < L->count - 1; j++){
                L->elem[j] = L->elem[j+1];
            }
            L->count--;
        }
        
    }
}