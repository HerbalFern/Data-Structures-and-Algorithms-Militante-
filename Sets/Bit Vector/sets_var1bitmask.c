#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned char Set;

void initialize(Set *set);
void insert(Set *set, int elem);
void delete(Set *set, int elem);
bool find(Set set, int elem);
Set Union(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);

void display(Set set);
void displaySetBits(Set set); // militante version sa display
void displayActualNumV1(Set set);
void displayActualNumV2(Set set);



int main() {
    Set A, B, C;

    // Initialize sets
    initialize(&A);
    initialize(&B);

    // Insert elements
    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 5);

    insert(&B, 2);
    insert(&B, 3);
    insert(&B, 4);

    printf("Set A: ");
    display(A);
    printf("\n");

    printf("Set B: ");
    display(B);
    printf("\n");

    // Test find
    printf("Find 3 in A: %d\n", find(A, 3));
    printf("Find 2 in A: %d\n", find(A, 2));

    // Test delete
    delete(&A, 3);
    printf("Set A after deleting 3: ");
    display(A);
    printf("\n");

    // Test Union
    C = Union(A, B);
    printf("Union of A and B: ");
    display(C);
    printf("\n");
    printf("Union of A and B (VALUES): ");    
    displayActualNumV2(C);
    printf("\n");
    

    // Test Intersection
    C = intersection(A, B);
    printf("Intersection of A and B: ");
    display(C);
    printf("\n");
    printf("Intersection of A and B (VALUES): ");
    displayActualNumV2(C);
    printf("\n");

    // Test Difference
    C = difference(A, B);
    printf("Difference of A - B: ");
    display(C);
    printf("\n");
    printf("Difference of A - B (VALUES): ");
    displayActualNumV2(C);
    printf("\n");

    return 0;

}

void initialize(Set *set){
    *set = 0;
}

void insert(Set *set, int elem){
    if (elem > 0 && elem < 9){
        Set mask = 1;
        mask = mask << (elem - 1);
        *set = *set | mask;
    }
}

void delete(Set *set, int elem){
    if (elem > 0 && elem < 9){
        Set mask = 1;
        mask = mask << (elem - 1);
        *set = *set & (~mask);
    }
}


bool find(Set set, int elem){
    Set mask = 1;
    mask = mask << (elem - 1);
    return mask & set;
}




Set Union(Set A, Set B){
    return A | B;
}

Set intersection(Set A, Set B){
    return A & B;
}
Set difference(Set A, Set B){
    return A & (~B);
}

void display(Set set){
    int i = 0;
    for (i = 0; i < 8; i++){
        printf("%u ", (set & 1 << i) ? 1 : 0);
    }        
}

void displaySetBits(Set set){
    Set mask = 1;
    for (mask = mask << (sizeof(Set) * (8 - 1)); mask != 0; mask = mask >> 1){
        printf("%u ", (set & mask) ? 1 : 0);
    }        
}

// reverse ni siya cause we using sir militante's shi
void displayActualNumV1(Set set){
    Set mask = 1;
    mask = mask << (sizeof(Set) * (8 - 1));
    int i;
    printf("{ ");
    for (i = 8; mask != 0; mask = mask >> 1, i--){
        if ((set & mask) != 0){ 
            printf("%d ", i);
        }
    }    
    printf("}");    
}


// bartlett + gpt method
void displayActualNumV2(Set set){
    int i;
    printf("{ ");
    for (i = 0; i < 8 ; i++){
        if ((set & (1 << i)) != 0){ 
            printf("%d ", i + 1);
        }
    }    
    printf("}");    
}