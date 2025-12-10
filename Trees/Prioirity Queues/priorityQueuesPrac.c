#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct list {
    char* name;
    int priority;
} Person; 

typedef struct heap {
    Person list[MAX];
    int lastidx;
} Heap;

// minheap
void heapifyUp(Heap*, int);
void heapifyDown(Heap*, int, int);

void swap(Person* A, Person* B); 
void insert(Heap* H, int priority, const char* name);
Person deleteMin(Heap* H);

void initHeap(Heap* H){
    H->lastidx = -1;
}

int main(){
    Heap H;
    initHeap(&H);

    printf("=== INSERTING INITIAL VALUES ===\n");
    insert(&H, 5, "Alice");
    insert(&H, 2, "Bob");
    insert(&H, 8, "Charlie");
    insert(&H, 1, "Dave");
    insert(&H, 3, "Eve");

    printf("\n=== DELETE ALL (RUN 1) ===\n");
    while (H.lastidx != -1){
        Person p = deleteMin(&H);
        printf("Name: %s - Priority: %d\n", p.name, p.priority);
        free(p.name);
    }

    printf("\n=== REINSERT DIFFERENT SET ===\n");
    insert(&H, 10, "Zara");
    insert(&H, 6, "Mike");
    insert(&H, 6, "Nina");       // duplicate priority
    insert(&H, 4, "Oscar");
    insert(&H, 12, "Paul");
    insert(&H, 1, "Quincy");    // new smallest

    printf("\n=== DELETE TWO ITEMS ONLY ===\n");
    for (int i = 0; i < 2; i++){
        Person p = deleteMin(&H);
        printf("Deleted: %s - %d\n", p.name, p.priority);
        free(p.name);
    }

    printf("\n=== INSERT MORE AFTER PARTIAL DELETE ===\n");
    insert(&H, 3, "Rita");
    insert(&H, 2, "Sam");
    insert(&H, 9, "Tina");

    printf("\n=== FINAL DELETE ALL ===\n");
    while (H.lastidx != -1){
        Person p = deleteMin(&H);
        printf("Name: %s - Priority: %d\n", p.name, p.priority);
        free(p.name);
    }

    return 0;
}


void swap(Person* A, Person* B){
    Person temp = *A;
    *A = *B;
    *B = temp;
}

void heapifyUp(Heap* H, int i){
    int parent = (i - 1) / 2;
    if (H->list[i].priority < H->list[parent].priority && i > 0){
        swap(&H->list[i], &H->list[parent]); 
        heapifyUp(H, parent);
    }
}


void heapifyDown(Heap* H, int size, int i){
    int min = i;
    int LC = (2 * i) + 1;
    int RC = (2 * i) + 2;


    if (LC < size && H->list[LC].priority < H->list[min].priority){
        min = LC;
    }

    if (RC < size && H->list[RC].priority < H->list[min].priority){
        min = RC;
    }

    if (min != i){
        swap(&H->list[min], &H->list[i]);
        heapifyDown(H, size, min);
    }
}


void insert(Heap* H, int priority, const char* name){
    if (H->lastidx != MAX - 1){
        H->list[++H->lastidx].priority = priority;
        H->list[H->lastidx].name = malloc(sizeof(char) * 30);
        strcpy(H->list[H->lastidx].name, name);
        
        heapifyUp(H, H->lastidx);
    }
}


Person deleteMin(Heap* H){
    Person temp = {NULL, 0};
    if (H->lastidx != -1){
        temp = H->list[0];
        Person data = H->list[H->lastidx--];
        H->list[0] = data;

        heapifyDown(H, H->lastidx + 1, 0);
    }
    
    return temp;
}
