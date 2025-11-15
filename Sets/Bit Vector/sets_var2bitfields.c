#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    unsigned int field : 8;
} Set;


void initialize(Set *set);
void insert(Set *set, int elem);
void delete(Set *set, int elem);
bool find(Set set, int elem);
Set Union(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);

void display(Set set);
void displaySetBits(Set set);
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
    set->field = 0;
}

void insert(Set *set, int elem){
    if (elem > 0 && elem < 9){
        Set mask = {1};
        mask.field = mask.field << (elem - 1);
        set->field = set->field | mask.field;
    }
}

void delete(Set *set, int elem){
    if (elem > 0 && elem < 9){
        Set mask = {1};
        mask.field = mask.field << (elem - 1);
        set->field = set->field & (~mask.field);
    }
}


bool find(Set set, int elem){
    Set mask = {1};
    mask.field = mask.field << (elem - 1);
    return mask.field & set.field;
}




Set Union(Set A, Set B){
    Set C = {A.field | B.field};
    return C;
}

Set intersection(Set A, Set B){
    Set C = {A.field & B.field};
    return C;
}
Set difference(Set A, Set B){
    Set C = {A.field & (~B.field)};
    return C;
}

void display(Set set){
    for (int i = 0; i < 8; i++){
        printf("%u ", ((set.field & (1 << i)) != 0) ? 1 : 0);
    } 
}


// displays bits based on binary bit position.
void displaySetBits(Set set){
    Set mask = {1};
    for (mask.field = mask.field << 7; mask.field != 0; mask.field = mask.field >> 1){
        printf("%u ", (set.field & mask.field) ? 1 : 0);
    }        
}


// displays the numbers in ascending order cause naka base ra siya sa bit position. 
void displayActualNumV1(Set set){
    Set mask = {1};
    mask.field = mask.field << 7;
    int i;
    printf("{ ");
    for (i = 8; mask.field != 0; mask.field = mask.field >> 1, i--){
        if ((set.field & mask.field) != 0){ 
            printf("%d ", i);
        }
    }    
    printf("}");    
}

void displayActualNumV2(Set set){
    int i;
    printf("{ ");
    for (i = 0; i < 8; i++){
        if ((set.field & (1 << i)) != 0){ 
            printf("%d ", i+1);
        }
    }    
    printf("}");
}


