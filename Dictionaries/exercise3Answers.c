// FERN ANDREI A. ROSELLO       BSIT - 2

/*

ANSWER TO NUMBER 3 IN THE CODE BELOW

Answers to Number 4 & 5

4. Closed hashing (open addressing) avoids using extra memory for linked lists by storing all elements directly in the hash table. 
This makes memory access faster and more cache-efficient compared to open hashing, which requires pointers and separate storage for 
chains.

5. Open hashing (separate chaining) handles collisions more efficiently when the table becomes full, as new elements can still be added 
to linked lists without probing. It also makes deletion simpler since removing an element doesn’t require shifting or rehashing other 
entries.


*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 10
#define EMPTY '*'
#define DELETED '~'

typedef char Dictionary[MAX];

int hash (char data);

void initDictionary(Dictionary D);

void insert(char data, Dictionary D);
void delete(char data, Dictionary D);
bool member(char data, Dictionary D);
void display(Dictionary D);

int main(){

    Dictionary D;
    initDictionary(D);

    insert('A', D);
    insert('A', D);
    insert('B', D);
    insert('B', D);
    insert('H', D);
    delete('A', D);
    insert('A', D);
    delete('A', D);

    display(D);

    (member('A', D)) ? printf("Member is present\n") : printf("Member is not present\n");
    return 0;
}

void initDictionary(Dictionary D){
    int i;
    for (i = 0; i < MAX; i++){
        D[i] = EMPTY;
    }
}

int hash (char data){
    char hashlist[MAX] = "abcdefghij";
    char hashvalue[MAX] = {3, 9, 4, 3, 9, 0, 1, 3, 0, 3};
    int i;
    for (i = 0; i < MAX && hashlist[i] != tolower(data) ;i++){}

    return hashvalue[i];
}

void insert(char data, Dictionary D){
    int i, iLimMAX;
    for (i = hash(data), iLimMAX = 0; D[i] != EMPTY && D[i] != data && iLimMAX < MAX; i = (i + 1) % MAX , iLimMAX++){}
    if  (iLimMAX == MAX){
        printf("\nDictionary is Full\n");
    } else if (D[i]==data){
        printf("\'%c\' is already in the dictionary\n", data);
    } else {
        D[i] = data;
    }
}

void delete(char data, Dictionary D){
    int i, iLimMAX;
    for (i = hash(data), iLimMAX = 0; D[i] != data && D[i] != EMPTY && iLimMAX < MAX; i = (i + 1) % MAX, iLimMAX++){}
    if (D[i] == data) D[i] = DELETED;
    else {
        printf("\n\'%c\' is not in the Dictionary\n");
    }
}

bool member(char data, Dictionary D){
    int i, iLimMAX;
    for (i = hash(data), iLimMAX = 0; iLimMAX < MAX && D[i] != data && D[i] != EMPTY; i = (i+1) % MAX, iLimMAX++){}
    return (D[i] == data);
}

  //for (i = h, iLimMAX = 0;iLimMAX < MAX && (D[i] != EMPTY && D[i] != data) ; i = (i+1) % MAX, iLimMAX++){}


void display(Dictionary D){
int i;
for (i = 0; i < MAX; i++){
    if (D[i] == DELETED){
        printf("[%d] : DELETED\n", i);
    } else if (D[i] == EMPTY){
        printf("[%d] : EMPTY\n", i);
    } else {
        printf("[%d] : %c\n", i, D[i]);
    }
}
}