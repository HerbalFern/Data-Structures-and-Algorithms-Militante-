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
    insert(&D, 'A'); // prime slot
    insert(&D, 'B'); // prime slot
    insert(&D, 'C'); // prime slot
    insert(&D, 'K'); // collision with 'A'
    insert(&D, 'L'); // collision with 'B'
    insert(&D, 'Z'); // new prime
    insert(&D, 'V'); // collision or new slot
    insert(&D, 'A'); // duplicate insert
    insert(&D, 'M'); // new prime
    insert(&D, 'N'); // new prime

    printf("\n\n=== AFTER INSERTIONS ===\n");
    display(D);

    printf("\n\n=== MEMBER TESTS ===\n");
    member(&D, 'A'); // should be found
    member(&D, 'K'); // should be found in synonym
    member(&D, 'Z'); // should be found
    member(&D, 'X'); // not found
    member(&D, 'M'); // should be found
    member(&D, 'Y'); // not found

    printf("\n\n=== DELETION TESTS ===\n");
    delete(&D, 'A'); // delete prime
    delete(&D, 'K'); // delete synonym
    delete(&D, 'X'); // nonexistent
    delete(&D, 'Z'); // delete prime
    delete(&D, 'N'); // delete prime

    printf("\n\n=== AFTER DELETIONS ===\n");
    display(D);

    printf("\n\n=== RE-INSERT TESTS ===\n");
    insert(&D, 'A'); // reinsert deleted prime
    insert(&D, 'K'); // reinsert deleted synonym
    insert(&D, 'X'); // insert new element
    insert(&D, 'Y'); // insert new element
    insert(&D, 'Z'); // reinsert deleted prime

    printf("\n\n=== FINAL STATE ===\n");
    display(D);

    printf("\n\n=== EDGE CASE: FILLING HEAP ===\n");
    for (char ch = 'E'; ch <= 'T'; ch++){
        insert(&D, ch);
    }

    printf("\n\n=== FINAL FULL STATE ===\n");
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
    if (D->elems[HASH].data != EMPTY){

        if (D->elems[HASH].data == DELETED){
            int* trav; 
            for (trav = &(D->elems[HASH].link); *trav != -1 && D->elems[*trav].data != data; trav = &(D->elems[*trav].link)){}
            if (*trav == -1){
                D->elems[HASH].data = data; 
            } else {
                printf("Element '%c' is in the synonym table. Cannot Insert!\n");
            }
        }

        else if (D->elems[HASH].data != data){
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

                trav = &(D->elems[HASH].link);

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
