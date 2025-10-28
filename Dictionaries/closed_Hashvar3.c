#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 20
#define EMPTY '*'
#define DELETED '~'



typedef enum {FALSE, TRUE} Boolean; 

typedef struct node {
    char data;
    int link;
} List; 

typedef struct {
    List elems[MAX];
    int avail;
} VirtualHeap, Dictionary;


void initDicV3(Dictionary* D);


void insert(Dictionary* D, char data);
void delete(Dictionary* D, char data);
void member(Dictionary* D, char data);

void display(Dictionary D);

int hash(char data){
    char Ldata = tolower(data);
    return ((int)Ldata - 'a') % 10;
}

int main(){
    Dictionary D;
    initDicV3(&D);

    printf("=== INITIAL DICTIONARY ===\n");
    display(D);

    printf("\n\n=== INSERTION TESTS ===\n");
    insert(&D, 'A');
    insert(&D, 'B');
    insert(&D, 'C');
    insert(&D, 'K'); // should hash to same index as 'A' if hash mod 10
    insert(&D, 'L'); // possible collision too
    insert(&D, 'Z');
    insert(&D, 'V');

    printf("\n\n=== AFTER INSERTIONS ===\n");
    display(D);

    printf("\n\n=== MEMBER TESTS ===\n");
    member(&D, 'A');
    member(&D, 'K');
    member(&D, 'Z');
    member(&D, 'X'); // not inserted, should not be found

    printf("\n\n=== DELETION TESTS ===\n");
    delete(&D, 'A');
    delete(&D, 'K');
    delete(&D, 'X'); // nonexistent element

    printf("\n\n=== AFTER DELETIONS ===\n");
    display(D);

    printf("\n\n=== RE-INSERT TESTS ===\n");
    insert(&D, 'M');
    insert(&D, 'N');
    insert(&D, 'O');
    insert(&D, 'A'); // reinsert deleted value

    printf("\n\n=== FINAL STATE ===\n");
    display(D);

    return 0;
}



void initDicV3(Dictionary* D){
    int i;
    for (i = 0; i < MAX - 1; i++){
        if (i < MAX/2){
            D->elems[i].link = -1;
            D->elems[i].data = EMPTY;
        } else {
            D->elems[i].link = i + 1;
        } 
    } 
    D->elems[MAX - 1].link = -1;
    D->avail = MAX / 2;
}

void insert(Dictionary* D, char data){
    
    // hash the data first and check index
    int HASH = hash(data);
    if (D->elems[HASH].data != EMPTY && D->elems[HASH].data != DELETED){
        if (D->elems[HASH].data != data){
            int* trav; 
            for (trav = &(D->elems[HASH].link); *trav != -1 && D->elems[*trav].data != data; trav = &(D->elems[*trav].link)){}
            if (*trav == -1){
                int temp = D->avail;
                if (temp != -1){
                    D->avail = D->elems[temp].link; 
                } else {
                    printf("No more space in virtual heap!\n");
                    return;
                }

                D->elems[temp].data = data; 
                D->elems[temp].link = -1;

                D->elems[temp].link = *trav;
                *trav = temp;
                printf("Element '%c' inserted in HASH[%d]\n", data, HASH);
            } else {
                printf("Element is already present!\n");
            }
        } else {
            printf("Element is already present!\n");
        }
    } else if (D->elems[HASH].data == data){
        printf("Element is already present!\n");
    } else {
        D->elems[HASH].data = data;
        D->elems[HASH].link = -1;
        printf("Element '%c' inserted in HASH[%d]\n", data, HASH);
    }    
    // check if naay 

    //cursor-based mem allocation
    /*
        int space = D->avail;
        if (space != -1){
            D->avail = D->elems[space].link; 
        } else {
            printf("No more space in virtual heap!\n");
            return;
        }
    */
}

void delete(Dictionary* D, char data){
    int HASH = hash(data);

    if (D->elems[HASH].data != EMPTY){
        if (D->elems[HASH].data != data){
            int* trav;
            for (trav = &(D->elems[HASH].link); *trav != -1 && D->elems[*trav].data != data; trav = &(D->elems[*trav].link)){}
            if (*trav != -1){
                int temp = *trav;
                *trav = D->elems[temp].link;

                // equivalent of deallocSpace
                D->elems[temp].link = D->avail;
                D->avail = temp;
                
                printf("'%c' has been deleted from HASH[%d]\n", data, HASH);

            } else {
                printf("'%c' Cannot be found. Could not be deleted.\n", data);        
            }

        } else { 
            D->elems[HASH].data = DELETED;
            printf("'%c' has been deleted from HASH[%d]\n", data, HASH);
        }
    } else {
        printf("'%c' Cannot be found. Could not be deleted.\n", data);
    }    
}

void member(Dictionary* D, char data){
    int HASH = hash(data);

    if (D->elems[HASH].data != EMPTY){
        if (D->elems[HASH].data == data){
            printf("'%c' is in HASH[%d]\n", data, HASH);     
        } else {
            int trav;
            for (trav = D->elems[HASH].link; trav != -1 && D->elems[trav].data != data; trav = D->elems[trav].link){}
            if (trav == -1){
                printf("Element '%c' is not present in the dictionary.\n", data);
            } else {
                printf("'%c' is in HASH[%d]\n", data, HASH);        
            }
        }
    } else {
        printf("Element '%c' is not present in the dictionary.\n", data);
    }
}


void display(Dictionary D){

    List* HPTR = D.elems;
    List* VPTR = D.elems;
    

    printf("\nDICTIONARY STATUS");
    printf("\n%-32s", "--------------------------------------------");
    printf("\n| %-4s | %-15s | %-15s |", "BASE", "Prime Table", "Synonym Table");
    printf("\n| %-4s | %-7s %-7s | %-7s %-7s |", "NDX", "Data", "Link", "Data", "Link");
    for(int i = 0, j = MAX/2; i < MAX / 2 && j < MAX; i++, j++){
        printf("\n| %-4d | %-7c %-7d | %-7c %-7d |",
            i, 
            (HPTR[i].data == EMPTY || HPTR[i].data == DELETED) ? '-' : HPTR[i].data,
            HPTR[i].link,
            (VPTR[j].data == EMPTY || VPTR[j].data == DELETED) ? '-' : VPTR[j].data,
            VPTR[j].link
        );
    }
    printf("\n%-32s", "--------------------------------------------");
}
