#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  
#include <stdbool.h>

#define MAX 20
#define EMPTY '*'
#define DELETED '-'

// var2 

typedef struct node {
    char data;
    int link;
} Node;

typedef struct dictionary {
    Node dicTable[MAX];
    int last;
} *Dictionary, DIC;

void initVar2(Dictionary D);

int hash(char data);

void insert(Dictionary D, char data);
void delete(Dictionary D, char data);
bool member(Dictionary D, char data);

void display(Dictionary D);
int main(){
    DIC D;
    Dictionary dict = &D;

    initVar2(dict);
    display(dict);

    printf("=== TEST CASES ===\n");

    // Insertions
    insert(dict, 'a');  // first insert
    insert(dict, 'k');  // collision with 'a'
    insert(dict, 'b');
    insert(dict, 'u');  
    insert(dict, 'k');  // duplicate insert
    insert(dict, 'v');  // new element
    insert(dict, 'm');  // collision with 'b'
    insert(dict, 'z');  // new hash
    insert(dict, 'c');  // simple insert
    insert(dict, 'd');  // simple insert

    display(dict);

    // Membership checks
    printf("\nChecking membership:\n");
    printf("'a' -> %s\n", member(dict, 'a') ? "FOUND" : "NOT FOUND");
    printf("'k' -> %s\n", member(dict, 'k') ? "FOUND" : "NOT FOUND");
    printf("'x' -> %s\n", member(dict, 'x') ? "FOUND" : "NOT FOUND");
    printf("'v' -> %s\n", member(dict, 'v') ? "FOUND" : "NOT FOUND");

    // Deletions
    printf("\nDeleting elements:\n");
    delete(dict, 'a');  // delete prime
    delete(dict, 'k');  // delete synonym
    delete(dict, 'x');  // nonexistent
    delete(dict, 'm');  // delete prime with collision
    delete(dict, 'z');  // delete simple
    display(dict);

    // Re-insert deleted elements
    printf("\nReinserting deleted elements:\n");
    insert(dict, 'a');  // should reuse DELETED slot
    insert(dict, 'k');  // should reuse DELETED slot
    insert(dict, 'm');  // should reuse DELETED slot
    display(dict);

    // Edge case: filling up dictionary
    printf("\nFilling up remaining slots:\n");
    for (char ch = 'e'; ch <= 't'; ch++){
        insert(dict, ch);
    }
    display(dict);

    return 0;
}


void initVar2(Dictionary D){
    for (int i = 0; i < MAX / 2; i++){
        D->dicTable[i].data = EMPTY;
        D->dicTable[i].link = -1;
    }
    
    // this is just for printing purposes since it all becomes weird and such.
    for (int i = MAX / 2; i < MAX ; i++){
        D->dicTable[i].data = '\0';
        D->dicTable[i].link = '\0';
    }
    
    
    
    D->last = (MAX / 2) - 1;  
}


int hash(char data){
    return (data - 'a') % (MAX / 2);
}

void insert(Dictionary D, char data){
    int HASH = hash(data);

    if (D->dicTable[HASH].data != EMPTY){
        if (D->dicTable[HASH].data == DELETED) {
            int* trav;
            for (trav = &(D->dicTable[HASH].link); *trav != -1 && D->dicTable[*trav].data != data; trav = &(D->dicTable[*trav].link)){}
            if (*trav == -1){
                D->dicTable[HASH].data = data;
            }
        } else if (D->dicTable[HASH].data != data){
            int* trav;
            for (trav = &(D->dicTable[HASH].link); *trav != -1 && D->dicTable[*trav].data != data; trav = &(D->dicTable[*trav].link)){}
            if (*trav == -1){
                /*  INSERT LAST IMPLEMENTATION
                *trav = D->last++;
                D->dicTable[*trav].data = data;
                D->dicTable[*trav].link = -1;
                */

                if (D->last != MAX - 1){
                //Insert first  
                    int* temp = &(D->dicTable[HASH].link);
                    D->dicTable[D->last].data = data;
                    D->dicTable[D->last].link = *temp;
                    *temp = D->last++;
                    printf("Inserted element '%c' into dictionary!\n");
                } else {
                    printf("Could not insert element '%c'. Overflow!\n");
                }
               
            } else {
                printf("Element '%c' already exists in the Dictionary!\n", data);
            }
        } else {
            printf("Element '%c' is already present!\n", data);
        }
    } else {
        D->dicTable[HASH].data = data;
    }
}

void delete(Dictionary D, char data){
    int HASH = hash(data);

    if (D->dicTable[HASH].data != EMPTY){
        if (D->dicTable[HASH].data != data){
            int* trav;
            for (trav = &(D->dicTable[HASH].link); *trav != -1 && D->dicTable[*trav].data != data; trav = &(D->dicTable[*trav].link)){}
            if (*trav != -1){
               int temp = *trav;
               *trav = D->dicTable[temp].link;
               D->dicTable[temp].link = -1;
                printf("Element '%c' is deleted.\n", data);
            } else {
                printf("Element '%c' does not exist. Cannot delete!\n");
            }
        } else {
            D->dicTable[HASH].data = DELETED;
            printf("Element '%c' is deleted.\n", data);
        }
    } else {
        printf("Element '%c' is not present in the dictionary!\n", data);
    }
}

bool member(Dictionary D, char data){
    int HASH = hash(data);

    if (D->dicTable[HASH].data != EMPTY){
        if (D->dicTable[HASH].data != data){
            int* trav;
            for (trav = &(D->dicTable[HASH].link); *trav != -1 && D->dicTable[*trav].data != data; trav = &(D->dicTable[*trav].link)){}
            if (*trav != -1){
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void display(Dictionary D){
    printf("\n=== DICTIONARY STATUS ===\n");
    printf("----------------------------------------------\n");
    printf("| IDX |  PRIME TABLE     |  SYNONYM TABLE     |\n");
    printf("|     | Data   Link      | Data   Link        |\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < MAX / 2; i++) {
        int j = i + (MAX / 2);
        printf("| %2d  |  %c     %2d       |  %c     %2d         |\n",
               i,
               D->dicTable[i].data,
               D->dicTable[i].link,
               D->dicTable[j].data,
               D->dicTable[j].link);
    }
    printf("----------------------------------------------\n\n");
}



/*
void display(Dictionary D){
    printf("Prime - Synonym\n");
    for (int i = 0, j = MAX/2 ; j < MAX; i++, j++){
        printf("[ %d ] [ %d ]\n", D->dicTable[i], D->dicTable[j]);
    }
}

*/
