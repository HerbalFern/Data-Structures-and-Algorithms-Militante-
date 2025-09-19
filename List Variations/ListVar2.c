#include <stdio.h>
#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
} List;

void initialize(List* L);
void insertPos(List* L, int data, int pos);
void deletePos(List* L, int position);
int locate(List* L, int data);
int retrieve(List* L, int position);

void insertSorted(List* L, int data);
void display(List* L);
void resize(List* L);

void makeNULL(List* L);


int main(){

    return 0;
}