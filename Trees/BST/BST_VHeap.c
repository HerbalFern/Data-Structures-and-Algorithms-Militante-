#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct node {
    int data;
    int left;
    int right;
} List;

typedef struct vheap {
    List L[MAX];
    int avail;
} VHeap;

typedef int SET; // naming convention rani nila lmao, represents the pointer to the node

void initHeap(VHeap* VH, SET* S); // basically to init heap, set all left links to -1 & for the initialize the right link normally like cursor-based
void initList(int* list); // set to -1 
int allocSpace(VHeap* VH); // get allocation from right links, just do the same with cursor-based
void deallocSpace(VHeap* VH, int idx); // 

void insert(VHeap* VH, SET* num, int elem);
void delete(VHeap* VH, SET* num, int elem);
bool search(VHeap VH, SET num, int elem);

int min(VHeap VH, SET num);
int max(VHeap VH, SET num);

void preorder(VHeap VH, SET num);
void postorder(VHeap VH, SET num);
void inorder(VHeap VH, SET num);
int main(){
    VHeap VH;
    SET root;

    initHeap(&VH, &root);

    // ------- INSERT TESTS -------
    insert(&VH, &root, 50);
    insert(&VH, &root, 30);
    insert(&VH, &root, 70);
    insert(&VH, &root, 20);
    insert(&VH, &root, 40);
    insert(&VH, &root, 60);
    insert(&VH, &root, 80);

    printf("\n=== INITIAL TREE ===\n");
    printf("Preorder: ");
    preorder(VH, root);
    printf("\nPostorder: ");
    postorder(VH, root);
    printf("\nInorder: ");
    inorder(VH, root);
    printf("\n");

    // ------- SEARCH TESTS -------
    printf("\n=== SEARCHING ===\n");
    printf("Search 40: %d\n", search(VH, root, 40));
    printf("Search 90: %d\n", search(VH, root, 90));
    printf("Search 20: %d\n", search(VH, root, 20));

    // ------- DELETION TESTS -------
    delete(&VH, &root, 20);
    delete(&VH, &root, 70);
    delete(&VH, &root, 50);

    printf("\n=== TREE AFTER DELETIONS ===\n");
    printf("Preorder: ");
    preorder(VH, root);
    printf("\nPostorder: ");
    postorder(VH, root);
    printf("\nInorder: ");
    inorder(VH, root);
    printf("\n");

    // ------- SEARCH AGAIN -------
    printf("\n=== SEARCH AFTER DELETIONS ===\n");
    printf("Search 20: %d\n", search(VH, root, 20));
    printf("Search 70: %d\n", search(VH, root, 70));
    printf("Search 50: %d\n", search(VH, root, 50));

    printf("Min: %d\n", min(VH, root));
    printf("Max: %d\n", max(VH, root));

    return 0;
}



void initHeap(VHeap* VH, SET* S){
    *S = -1;
    VH->avail = 0;
    for (int i = 0; i < MAX; i++){
        VH->L[i].left = -1;
        VH->L[i].right = (i < MAX - 1) ? i + 1 : -1;
    }
}

void initList(int* list){
    *list = -1;
}

int allocSpace(VHeap* VH){
    int space = VH->avail;
    if (space != -1){
        VH->avail = VH->L[space].right;
    }
    return space;
}

void deallocSpace(VHeap* VH, int idx){
    VH->L[idx].left = -1;
    VH->L[idx].right = VH->avail;
    VH->avail = idx;
}



void insert(VHeap* VH, SET* num, int elem){
    int* trav;
    for (trav = num; *trav != -1 && VH->L[*trav].data != elem;){
        trav = VH->L[*trav].data < elem ? &VH->L[*trav].right : &VH->L[*trav].left; 
    }

    if (*trav == -1){
        int temp = allocSpace(VH);
        
        if (temp != -1){
            VH->L[temp].data = elem;
            VH->L[temp].left = -1;
            VH->L[temp].right = -1;
            *trav = temp;
        }
    }
}

void delete(VHeap* VH, SET* num, int elem){
    int* trav, temp;
    for (trav = num; *trav != -1 && VH->L[*trav].data != elem;){
        trav = VH->L[*trav].data < elem ? &VH->L[*trav].right : &VH->L[*trav].left; 
    } 
    if (*trav != -1){
        if (VH->L[*trav].right != -1){
            int* successor = &VH->L[*trav].right;
            while (VH->L[*successor].left != -1){
                successor = &VH->L[*successor].left;
            }
            VH->L[*trav].data = VH->L[*successor].data; 
            temp = *successor;
            *successor = VH->L[temp].right;
        } else {
            temp = *trav;
            *trav = VH->L[temp].left;
        }
        deallocSpace(VH, temp);
    }
}


bool search(VHeap VH, SET num, int elem){
    int trav, temp;
    for (trav = num; trav != -1 && VH.L[trav].data != elem;){
        trav = VH.L[trav].data < elem ? VH.L[trav].right : VH.L[trav].left; 
    } return trav != -1;
}

void preorder(VHeap VH, SET num){
    if (num != -1){
        printf("%d ", VH.L[num].data);
        preorder(VH, VH.L[num].left);
        preorder(VH, VH.L[num].right);
    }
}

void postorder(VHeap VH, SET num){
    if (num != -1){
        postorder(VH, VH.L[num].left);
        postorder(VH, VH.L[num].right);
        printf("%d ", VH.L[num].data);
    }
}
void inorder(VHeap VH, SET num){
    if (num != -1){
        inorder(VH, VH.L[num].left);
        printf("%d ", VH.L[num].data);
        inorder(VH, VH.L[num].right);
    }
}

int min(VHeap VH, SET num){
    SET trav;
    for (trav = num; VH.L[trav].left != -1; trav = VH.L[trav].left){}
    return trav == -1 ? -1 : VH.L[trav].data;
}


int max(VHeap VH, SET num){
    SET trav;
    for (trav = num; VH.L[trav].right != -1; trav = VH.L[trav].right){}
    return trav == -1 ? -1 : VH.L[trav].data;
}
