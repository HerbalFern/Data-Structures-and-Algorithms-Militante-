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


int main(){

    



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

}
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

