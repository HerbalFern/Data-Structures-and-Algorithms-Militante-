#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 15


typedef struct node {
    int data;
    struct node* next;
} *NODE, Node;

typedef NODE Dictionary[MAX];


void initialize(Dictionary D);
int hash(int data);


void insert(Dictionary D, int data);
void delete(Dictionary D, int elem);
bool member(Dictionary D, int elem);




int main(){
    
    Dictionary D;   

    

    return 0;
}