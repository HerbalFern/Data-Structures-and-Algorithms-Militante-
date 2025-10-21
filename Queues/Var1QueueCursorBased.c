#include <stdio.h>
#include <stdbool.h>

#define MAX 15

typedef struct node {
    int data;
    int link;
} List;

typedef struct vheap {
    List elems[MAX];
    int avail;
} vHeap;

typedef struct queue {
    int front;
    int rear;
    int count;
    vHeap VH;
} Queue;

typedef int clist; 

void initQueue(Queue* Q);
int allocSpace(Queue* Q);
void deallocSpace(Queue* Q, int pos);

void enqueue(Queue* Q, int data);
void dequeue(Queue* Q);

bool isFull(Queue Q);
bool isEmpty(Queue Q);

void display(Queue Q){
    if (isEmpty(Q)){
        printf("\nts queue empty twin fr\n");
    }
    printf("Virtual Heap Queue Elements: \n");
    printf("Front -> ");
    for (int i = Q.front; i != -1; i = Q.VH.elems[i].link){
        printf("[%d] ", Q.VH.elems[i].data);
    }
    printf("<- Rear");

}

int main(){

    Queue Q;
    initQueue(&Q);
    
    enqueue(&Q, 5);
    enqueue(&Q, 4);
    enqueue(&Q, 3);
    enqueue(&Q, 2);
    enqueue(&Q, 1);

    display(Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);

    display(Q);

    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);


    return 0;
}

void initQueue(Queue* Q){
    Q->count = 0;
    Q->front = -1;
    Q->rear = -1;

    int i;
    Q->VH.avail = 0;
    for (int i = 0; i < MAX - 1; i++){
        Q->VH.elems[i].link = i+1;
    }
    Q->VH.elems[MAX - 1].link = -1;
}

int allocSpace(Queue* Q){
    int temp = Q->VH.avail;
    if (temp != -1){
        Q->VH.avail = Q->VH.elems[temp].link;
    }
    return temp;
}

void deallocSpace(Queue* Q, int pos){
    Q->VH.elems[pos].link = Q->VH.avail;
    Q->VH.avail = pos;
}


void enqueue(Queue* Q, int data){
    
    int temp = allocSpace(Q);
    if (temp == -1){
        printf("\nMemory Allocation Failed\n");
        return;
    }

    if (isFull(*Q)){
        printf("\nVirtual Heap is Full, Cannot Enqueue\n");
        return;
    }

    Q->VH.elems[temp].link = -1;
    Q->VH.elems[temp].data = data;
    

    if (isEmpty(*Q)){
        Q->front = temp;
        Q->rear = temp;
    
       
    } else {
        Q->VH.elems[Q->rear].link = temp;
        Q->rear = temp;
    }
    Q->count++;
}

void dequeue(Queue* Q){
    
    if (!isEmpty(*Q)){
        int temp = Q->front;
        Q->front = Q->VH.elems[Q->front].link;
        deallocSpace(Q, temp);

        if (isEmpty(*Q)){
            Q->rear == -1;
        }

    } else {
        printf("\nList is Empty, Cannot Dequeue\n");
    }
}


bool isFull(Queue Q){
    return (Q.count == MAX) ? true : false;
}

bool isEmpty(Queue Q){
    return (Q.front == -1) ? true : false;
}