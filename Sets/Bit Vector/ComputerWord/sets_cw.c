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

    // add main

    return 0;
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
            printf("%d ");
        } 
    }
}
