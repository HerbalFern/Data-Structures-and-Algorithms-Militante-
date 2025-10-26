#include <stdio.h>
#include <stdbool.h>

typedef unsigned char SET; 

void initialize(SET* set);
void insert (SET *set, int element);
void delete (SET* set, int element);
bool find (SET* set, int element);
SET Union (SET A, SET B);
SET intersection (SET A, SET B);
SET difference (SET A, SET B);

void display(SET set);

int main(){

    SET A, B, C;
    initialize(&A);
    initialize(&B);

    // --- TEST 1: INSERT ELEMENTS ---
    // Insert elements into A: 0, 2, 4
    insert(&A, 0);
    insert(&A, 2);
    insert(&A, 4);

    // Insert elements into B: 1, 2, 3, 5
    insert(&B, 1);
    insert(&B, 2);
    insert(&B, 3);
    insert(&B, 5);

    printf("Set A elements: ");
    display(A);
    printf("\n");

    printf("Set B elements: ");
    display(B);
    printf("\n");

    // --- TEST 2: FIND ELEMENTS ---
    // Check if 2 is in A
    printf("Find 2 in A: %s\n", find(&A, 2) ? "true" : "false");
    // Check if 3 is in A
    printf("Find 3 in A: %s\n", find(&A, 3) ? "true" : "false");

    // --- TEST 3: UNION ---
    C = Union(A, B);
    printf("Union of A and B: ");
    display(C);
    printf("\n");

    // --- TEST 4: INTERSECTION ---
    C = intersection(A, B);
    printf("Intersection of A and B: ");
    display(C);
    printf("\n");

    // --- TEST 5: DIFFERENCE ---
    C = difference(A, B);
    printf("Difference of A - B: ");
    display(C);
    printf("\n");

    // --- TEST 6: DELETE ELEMENTS ---
    delete(&A, 2);
    printf("A after deleting element 2: ");
    display(A);
    printf("\n");

    return 0;
}

void initialize(SET* set){
    *set = 0;
}


void insert(SET* set, int element){
    if (element < 8 && element > -1)
    *set = (*set) | (1 << (sizeof(SET) * element));  
}

void delete (SET* set, int element){
    if (element < 8 && element > -1)
    *set = (*set) & ~(1 << (sizeof(SET) * element));  
}

bool find (SET* set, int element){
    return (*set & (1<<(sizeof(SET) * element)));
}

SET Union (SET A, SET B){
    return (A | B);
}

SET intersection (SET A, SET B){
    return (A & B);
}

SET difference (SET A, SET B){
    return (A & (~B));
}

// need display

void display(SET set){
    int mask = 1; 
    for (int i = 0; i < 8; i++){
        if ((set & (mask << i)) != 0){
            printf("%d ", i);
        } 
    }
}
