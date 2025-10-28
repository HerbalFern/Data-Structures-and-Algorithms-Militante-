#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 20
#define DELETED '-'
#define EMPTY '~'

typedef struct Dic{
    int dic[MAX];
    int last;
} DICTIONARY, *Dictionary;

int hash(char data){
    char Ldata = tolower(data);
    return ((int)Ldata - 'a') % 10;
}

void initialize(Dictionary D){
    for (int i = 0; i < MAX / 2; i++){
        D->dic[i] = EMPTY;
    }

    D->last = (MAX / 2) - 1;
}

void insert(Dictionary D, char data);
void delete(Dictionary D, char data);
bool member(Dictionary D, char data);

void display(Dictionary D) {
    printf("\n=== DICTIONARY STATUS ===\n");
    printf("--------------------------------------------------\n");
    printf("| Index |  Value  |\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        if (D->dic[i] == EMPTY)
            printf("| %5d |    ~     |\n", i);
        else if (D->dic[i] == DELETED)
            printf("| %5d |    -     |\n", i);
        else
            printf("| %5d |    %c     |\n", i, D->dic[i]);
    }
    printf("--------------------------------------------------\n");
    printf("Last index: %d\n\n", D->last);
}


int main(){
    DICTIONARY D;
    
    // Initialize dictionary
    initialize(&D);
    for (int i = 0; i < MAX; i++) D.dic[i] = EMPTY;

    printf("=== INITIAL DICTIONARY ===\n");
    display(&D);

    printf("=== INSERT TESTS ===\n");
    insert(&D, 'a'); // hash to index 0
    insert(&D, 'k'); // hash to same index (collision -> synonym)
    insert(&D, 'u'); // another collision
    insert(&D, 'b'); // unique hash
    insert(&D, 'z'); // another unique hash
    display(&D);

    printf("=== MEMBER TESTS ===\n");
    printf("'a' present? %s\n", member(&D, 'a') ? "Yes" : "No");
    printf("'k' present? %s\n", member(&D, 'k') ? "Yes" : "No");
    printf("'x' present? %s\n", member(&D, 'x') ? "Yes" : "No");

    printf("\n=== DELETE TESTS ===\n");
    delete(&D, 'a'); // delete main table element
    delete(&D, 'k'); // delete synonym
    delete(&D, 'x'); // try deleting non-existent
    display(&D);

    printf("=== REINSERT AND FINAL STATUS ===\n");
    insert(&D, 'a'); // reinsert after deletion
    insert(&D, 'y');
    display(&D);


    return 0;
}


void insert(Dictionary D, char data){
    int HASH = hash(data);
    
    if (D->dic[HASH] != EMPTY && D->dic[HASH] != DELETED){
        if (D->dic[HASH] != data){
            if (D->last == MAX - 1){
                printf("Overflow. Cannot Insert into Synonyms.\n");
            } else {
                int i;
                for (i = MAX / 2; i <= D->last && D->dic[i] != data; i++){}
                if (i > D->last){
                    D->dic[++D->last] = data;
                    printf("Inserted element '%c' into Dictionary.\n", data);
                } else {
                    printf("Element '%c' is already present!\n", data);
                }
            }
        } else {
            printf("Element '%c' is already present!\n", data);
        }
    } else {
        D->dic[HASH] = data;
        printf("Inserted element '%c' into Dictionary.\n", data);
    }
}

void delete(Dictionary D, char data){
    int HASH = hash(data);
    if (D->dic[HASH] != EMPTY){
        if (D->dic[HASH] != data){
            int i;
            for (i = MAX / 2; i <= D->last && D->dic[i] != data; i++){}
            if (i <= D->last){
                D->dic[i] = D->dic[D->last];
                // NO NEED TO DELETE. ONLY FOR DISPLAY PURPOSES
                D->dic[D->last] = DELETED;
                D->last--;
                printf("Deleted '%c' fromt he Dictionary\n", data);
            } else {
                printf("Could not find '%c'. Cannot Delete\n", data);
            }
        } else {
            D->dic[HASH] = DELETED;
            printf("Deleted '%c' from the Dictionary\n", data);
        }
    } else {
        printf("Could not find '%c'. Cannot Delete\n", data);
    }
}


bool member(Dictionary D, char data){
    int HASH = hash(data);
    if (D->dic[HASH] != EMPTY){
        if (D->dic[HASH] != data){
            int i;
            for (i = MAX / 2; i <= D->last && D->dic[i] != data; i++){}
            if (i <= D->last){
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