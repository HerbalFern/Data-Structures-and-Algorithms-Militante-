#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char SET;

void initialize(SET* set);
void insert(SET* set, int element);
void delete(SET* set, int element);
bool find(SET set, int element);

SET intersection(SET A, SET B);
SET UNION(SET A, SET B);
SET difference(SET A, SET B);

void display (SET A);

int main() {
    SET A, B, C;

    // Initialize sets
    initialize(&A);
    initialize(&B);
    initialize(&C);

    printf("=== INSERT TESTS ===\n");
    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 5);

    insert(&B, 3);
    insert(&B, 4);
    insert(&B, 6);

    printf("Set A: ");
    display(A);        // Expected: 1 3 5 
    printf("\n");

    printf("Set B: ");
    display(B);        // Expected: 3 4 6
    printf("\n\n");

    printf("=== FIND TESTS ===\n");
    printf("Find 3 in A: %s\n", find(A, 3) ? "FOUND" : "NOT FOUND"); // FOUND
    printf("Find 4 in A: %s\n", find(A, 4) ? "FOUND" : "NOT FOUND"); // NOT FOUND
    printf("Find 6 in B: %s\n", find(B, 6) ? "FOUND" : "NOT FOUND"); // FOUND
    printf("\n");

    printf("=== DELETE TESTS ===\n");
    delete(&A, 3);

    printf("Set A after deleting 3: ");
    display(A);        // Expected: 1 5
    printf("\n\n");

    printf("=== UNION TEST ===\n");
    C = UNION(A, B);

    printf("A ∪ B: ");
    display(C);        // Expected: 1 4 5 6
    printf("\n\n");

    printf("=== INTERSECTION TEST ===\n");
    C = intersection(A, B);

    printf("A ∩ B: ");
    display(C);        // Expected: (none) because A is {1,5}
    printf("\n\n");

    printf("=== DIFFERENCE TEST ===\n");
    C = difference(B, A);  // B - A

    printf("B - A: ");
    display(C);        // Expected: 3 4 6
    printf("\n");

    return 0;
}


void initialize(SET* set){
    *set = 0;
}       
 

void insert(SET* set, int element){
    if (element > -1 && element < 8){
        SET mask = 1 << element; 
        *set = *set | mask;
    }
}

void delete(SET* set, int element){
    if (element > -1 && element < 8){
        SET mask = 1 << element; 
        *set = *set & ~(mask);
    }
}

bool find(SET set, int element){
    return set & (1 << element);
}

SET intersection(SET A, SET B){
    return A & B;
}

SET UNION(SET A, SET B){
    return A | B;
}

SET difference(SET A, SET B){
    return A & ~(B);
}

void display (SET A){
    SET mask = 1;
    for (int i = 0; i < 8; i++){
        if (((mask << i) & A) != 0){
            printf("%d ", i);
        }
    }    
}