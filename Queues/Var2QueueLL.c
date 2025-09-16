#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} *LIST;

typedef struct Queue {
    LIST front, rear;
} LLQueue;

void initQueue(LLQueue* Q);
void enqueue(LLQueue* Q, int data);
void dequeue(LLQueue* Q);
int front(LLQueue Q);
bool isEmpty(LLQueue Q);
bool isFull(LLQueue Q);
void printQueue(LLQueue Q);

int main(){

    LLQueue Q;
    initQueue(&Q);

    // Test 1: Enqueue elements
    enqueue(&Q, 10);
    enqueue(&Q, 20);
    enqueue(&Q, 30);
    printf("Queue after enqueuing 10, 20, 30:\n");
    printQueue(Q);  
    // Expected: Rear -> [30][20][10] <- Front 
    // (front = 10, rear = 30)

    // Test 2: Check front
    printf("Front element: %d\n", front(Q));  
    // Expected: 10

    // Test 3: Dequeue one element
    dequeue(&Q);
    printf("Queue after one dequeue:\n");
    printQueue(Q);  
    // Expected: Rear -> [30][20] <- Front 
    // (front = 20, rear = 30)

    // Test 4: Enqueue more
    enqueue(&Q, 40);
    enqueue(&Q, 50);
    printf("Queue after enqueuing 40, 50:\n");
    printQueue(Q);  
    // Expected: Rear -> [50][40][30][20] <- Front 
    // (front = 20, rear = 50)

    // Test 5: Dequeue twice
    dequeue(&Q);
    dequeue(&Q);
    printf("Queue after two more dequeues:\n");
    printQueue(Q);  
    // Expected: Rear -> [50][40] <- Front 
    // (front = 40, rear = 50)

    // Test 6: Check front again
    printf("Front element: %d\n", front(Q));  
    // Expected: 40

    // Test 7: Empty the queue completely
    dequeue(&Q);
    dequeue(&Q);
    printf("Queue after emptying:\n");
    printQueue(Q);  
    // Expected: Rear ->  <- Front 
    // (empty)

    // Test 8: Check isEmpty
    if (isEmpty(Q)) {
        printf("Queue is empty now.\n");  // Expected
    } else {
        printf("Queue is NOT empty.\n");
    }

    // Test 9: Enqueue again after emptying
    enqueue(&Q, 99);
    enqueue(&Q, 100);
    printf("Queue after enqueuing 99, 100:\n");
    printQueue(Q);  
    // Expected: Rear -> [100][99] <- Front 
    // (front = 99, rear = 100)

    return 0;
}

void initQueue(LLQueue* Q){
    Q->front = NULL;
    Q->rear = NULL;
}

void enqueue(LLQueue* Q, int data){

    LIST temp = malloc(sizeof(struct node));
    if (temp == NULL){
        printf("\nmem alloc failed\n");
        return;
    }

    temp->data = data;
    temp->next = NULL;

    if (isEmpty(*Q)==true){
        Q->front = temp;
        Q->rear = temp;
    } else {
        temp->next = Q->rear;
        Q->rear = temp;       
    }

}

void dequeue(LLQueue* Q){
    if (isEmpty(*Q) == true){
        printf("\nQueue is empty, nothing to dequeue\n");
    } else {
        
        LIST* trav; 
        for (trav = &Q->rear; (*trav)->next != NULL; trav = &(*trav)->next){}
        LIST temp = *trav;
        *trav = NULL;
        free(temp);

        if (isEmpty(*Q) == true){
            Q->rear = NULL;
            Q->front = NULL;
        }
    }
}

int front(LLQueue Q){
    return Q.front->data;
}

bool isEmpty(LLQueue Q){
    if (Q.front == NULL){
        return true;
    } return false;
}

bool isFull(LLQueue Q){
    return false; 
}


void printQueue(LLQueue Q) {
    printf("REAR -> ");
    for (LIST trav = Q.rear; trav != NULL; trav = trav->next) {
        printf("[%d] ", trav->data);
    }
    printf("<- FRONT\n");
}