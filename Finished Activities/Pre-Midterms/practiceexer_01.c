#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 20


typedef struct charlist {
    char elem[MAX];
    int count;
} CharList;

bool findElem(CharList L, char C);
void insertElem(CharList* L, char C);


int main(){

    CharList L;
    L.count = 0;

    insertElem(&L, 'C');
    insertElem(&L, 'O');
    insertElem(&L, 'O');
    insertElem(&L, 'L');
    insertElem(&L, 'K');
    insertElem(&L, 'I');
    insertElem(&L, 'D');
    insertElem(&L, 'S');
    insertElem(&L, 'I');
    insertElem(&L, 'N');
    insertElem(&L, 'T');
    insertElem(&L, 'H');
    insertElem(&L, 'E');
    insertElem(&L, 'H');
    insertElem(&L, 'O');
    insertElem(&L, 'U');
    insertElem(&L, 'S');
    insertElem(&L, 'E');
    insertElem(&L, 'Z');
    insertElem(&L, 'S');
    insertElem(&L, 'S');
    
    (findElem(L, 'Z') == 1) ? printf("Found") : printf("Not Found");

    return 0;
}

void insertElem(CharList* L, char C){
    if (L->count != MAX - 1){
    L->elem[L->count++] = C;
    printf("Inserted %c. Count is currently %d\n", C, L->count);
    } else {
        printf("List is Full\n");
    }
}

bool findElem(CharList L, char C){
    int i;
    for (i = 0; i <= L.count && L.elem[i] != C; i++){}
    return (i < L.count) ?  true :  false;
}
