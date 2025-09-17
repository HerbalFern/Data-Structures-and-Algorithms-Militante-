#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10


typedef enum {FALSE, TRUE} Bool;
typedef enum {MALE, FEMALE, LGTBQ} Gender;

typedef struct{
    char name[32];
    int experience;
}actor;

typedef struct{
    char charName[32];
    actor act;
    int auraPoints;
}disneyChar;

typedef struct{
    actor actorList[MAX];
    int front;
    int rear;
}applicantQueue;

typedef struct{
    disneyChar DC[10];
    int count;
}disneyList;

actor front(applicantQueue Q);
actor dequeue(applicantQueue *Q);
void enqueue(applicantQueue* Q, actor A);

bool isEmpty(applicantQueue Q){
    return ((Q.rear + 1) % MAX == Q.front) ? true : false;
}



int main(void)
{
    disneyList dList = {{
            {"Mickey",   {"XXX", 0}, 1000},
            {"Goofy",   {"XXX", 0}, 500},
            {"Minnie",     {"XXX", 0}, 600},
            {"Snow White",     {"XXX", 0}, 1100},
            {"Gingerbread Man",   {"XXX", 0}, 1500}
            }, 5
            };

    int jlc = 0;
    actor jobless[5];

    // Initialize applicantQueue with 5 actors
    applicantQueue aQueue = {{
            {"Fern", 1100},
            {"Torcy", 200},
            {"Raze", 500},
            {"Althea", 1200},
            {"Denise", 1500}
            }, 0, 4};


            
    actor temp;
    while (!isEmpty(aQueue)) {
        temp = dequeue(&aQueue);
        int i;
        for (i = 0; i < dList.count; i++){
            if (temp.experience >= dList.DC[i].auraPoints){
                if (strcmp(dList.DC[i].act.name, "XXX") == 0){                    
                    if (i < dList.count){
                        dList.DC[i].act = temp;   
                    } 
                    break;
                } else {
                    continue;
                }
            } 
        }
    }

    printf("\nCharacters with Actors: \n");
    for (int i = 0; i < dList.count; i++){
        printf("%s [%d] | %s [%d]\n", dList.DC[i].charName, dList.DC[i].auraPoints, dList.DC[i].act.name, dList.DC[i].act.experience);
    }
    
    printf("\nWay Trabaho: \n");
    for (int j = 0; j < jlc; j++){
        printf("%s [%d]\n", jobless[j].name, jobless[j].experience);
    }
    

    return 0;
}

actor front(applicantQueue Q){
     actor temp = {"xxxx", 0};
     return ((Q.front + 1) % MAX != Q.rear) ? Q.actorList[Q.front] : temp;
}

actor dequeue(applicantQueue *Q){
    actor temp = {"xxxx", 0};
    if ((Q->rear + 1) % MAX != Q->front){
        temp = Q->actorList[Q->front];
        Q->front = (Q->front + 1) % MAX;
    } 
    return temp;
}

void enqueue(applicantQueue* Q, actor A){
    if ((Q->rear + 2) % MAX != Q->front){
        Q->rear = (Q->rear + 1) % MAX;
        Q->actorList[Q->rear] = A;
    }
}
