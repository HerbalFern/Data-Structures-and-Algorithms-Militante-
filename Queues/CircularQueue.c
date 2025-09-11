#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int items[MAX];
    int count; 
} List;


typedef struct queue {
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);


int main() {
    Queue* q = initialize();

    printf("Initial queue (empty): ");
    display(q); // []
    printf("\n");

    enqueue(q, 10);  // [10]
    enqueue(q, 20);  // [10, 20]
    enqueue(q, 30);  // [10, 20, 30]
    enqueue(q, 40);  // [10, 20, 30, 40]
    printf("After enqueues: ");
    display(q);
    printf("\n");

    printf("Front element: %d\n", front(q)); // should be 10

    printf("Dequeued: %d\n", dequeue(q)); // removes 10 -> [20, 30, 40]
    printf("Dequeued: %d\n", dequeue(q)); // removes 20 -> [30, 40]
    printf("After 2 dequeues: ");
    display(q);
    printf("\n");

    enqueue(q, 50);  // [30, 40, 50]
    enqueue(q, 60);  // wrap-around! -> [30, 40, 50, 60]
    printf("After more enqueues (wrap-around): ");
    display(q);
    printf("\n");

    printf("Dequeued: %d\n", dequeue(q)); // removes 30 -> [40, 50, 60]
    printf("After dequeue: ");
    display(q);
    printf("\n");

    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q)); // clears queue
    }

    printf("\nAfter clearing queue: ");
    display(q); // []

    return 0;
}

Queue* initialize(){
    Queue* Q = (Queue*) malloc(sizeof(Queue));
    Q->front = -1;
    Q->rear = -1;
    Q->list.count = 0;

    return Q;
}

bool isFull(Queue* q){
    if (q->list.count == MAX){
        return true;
    } return false; 
}


bool isEmpty(Queue* q){
    if (q->list.count == 0){
        return true;
    } return false;
}

void enqueue(Queue* q, int value){
    if (isFull(q) == false){
        if (isEmpty(q) == true){
            q->front = 0;
            q->rear = 0;
        } else {
            q->rear = (q->rear + 1) % MAX;
        }
        q->list.items[q->rear] = value;
        q->list.count++;
    } else {
        printf("Queue is full\n");
    }
}


int dequeue(Queue* q){
    if (isEmpty(q) == true){
        printf("Nothing to dequeue, the queue is currently empty\n");
    } else {
        /* AY TANGINA TO CIRCUMVENT THE FUCKING SLOW ASS INSERT FIRST, GI CIRCULAR NALNG SIYA SO ANG FRONT 
            MAREMOVE
        */
        int temp = q->list.items[q->front];
        if(q->list.count == 1){
            q->front = -1;
            q->rear = -1;
            q->list.count = 0;
        } else {
            q->front = (q->front + 1) % MAX; 
            q->list.count--;
        }
        return temp;
    }
}

int front(Queue* q){
    return q->list.items[q->front];
}


void display(Queue* q){
    
    int i = q->front;
    if (isEmpty(q) == false){ 
        printf("FRONT -> ");   
        do{
            printf("[%d] ", q->list.items[i]);
            i = (i+1) % MAX;
        } while (i != (q->rear+1) % MAX);
        printf(" <- REAR\n");
    } else {
        printf("Queue is empty\n");
    }
}

