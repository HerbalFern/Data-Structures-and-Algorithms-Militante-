#include <stdio.h>
#include <stdbool.h>
#define MAX 15
#define EMPTY -1
#define DELETED -5

typedef int Dictionary[MAX];

int hash(int data);

void insert(int, Dictionary);
void delete(int, Dictionary);
bool member(int, Dictionary);

void initializeDic(Dictionary);

void display(Dictionary);

int main(){
    Dictionary D;
    initializeDic(D);
    
    printf("=== Testing Dictionary Functions ===\n\n");

    printf("Inserting values: 10, 25, 30, 45, 20\n");
    insert(10, D);
    insert(25, D);
    insert(30, D);
    insert(45, D);
    insert(20, D);

    printf("\nCurrent Dictionary:\n");
    display(D);

    printf("\nChecking membership:\n");
    printf("Is 25 in dictionary? %s\n", member(25, D) ? "Yes" : "No");
    printf("Is 99 in dictionary? %s\n", member(99, D) ? "Yes" : "No");

    printf("\nDeleting 25 and 10...\n");
    delete(25, D);
    delete(10, D);

    printf("\nDictionary after deletion:\n");
    display(D);

    printf("\nRe-checking membership:\n");
    printf("Is 25 in dictionary? %s\n", member(25, D) ? "Yes" : "No");
    printf("Is 10 in dictionary? %s\n", member(10, D) ? "Yes" : "No");

    printf("\nTrying to re-insert 30 (duplicate)...\n");
    insert(30, D);

    printf("\nTrying to insert 35...\n");
    insert(35, D);

    printf("\nFinal Dictionary:\n");
    display(D);

    return 0;
}


void insert(int data, Dictionary D){
    int i, iLimMAX, h = hash(data);
    
    for (i = h, iLimMAX = 0; iLimMAX < MAX && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX, iLimMAX++) {}    
    if (D[i]==data){
        printf("\nNumber is already there cuh\n");
    } else if (iLimMAX == MAX) {
        printf("\nts dictionary full cuh\n");
    } else {
        D[i] = data;
    }
}



void delete(int data, Dictionary D){
    int i, iLimMAX, h = hash(data);
    for (i = h, iLimMAX = 0;iLimMAX < MAX && D[i] != data; i = (i+1) % MAX, iLimMAX++){}
    if (iLimMAX != MAX) D[i] = DELETED;
}

bool member(int data, Dictionary D){
    int i, iLimMAX, h = hash(data);
    for (i = h, iLimMAX = 0;iLimMAX < MAX && (D[i] != EMPTY && D[i] != data) ; i = (i+1) % MAX, iLimMAX++){}
    if (D[i] == data){
        return true;
    } return false;
}


int hash(int data){
    return data % 10;
}

void initializeDic(Dictionary D){
    int i;
    for (i = 0; i < MAX; i++){
        D[i] = EMPTY; 
    }
}

void display(Dictionary D){
    int i;
    for (i = 0; i < MAX; i++){
        if (D[i] == DELETED){
            printf("[%d] : DELETED\n", i);
        } else if (D[i] == EMPTY){
            printf("[%d] : EMPTY\n", i);
        } else {
            printf("[%d] : %d\n", i, D[i]);
        }
    }
}