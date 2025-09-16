#include <stdio.h>
#define MAX 15

typedef struct node {
    int data;
    int link;
} LL;

typedef struct {
    LL elems[MAX];
    int avail;
} vHeap;

typedef int Clist; 

// Only needed functions to memorize
void initList(Clist * CL);
void initVHeap(vHeap* VH);
int allocSpace(vHeap* VH);
void deallocSpace(vHeap* VH, int pos);

// The rest is one to one with Linked list implementation

void insertFirst(Clist* CL, vHeap* VH, int data);
void insertLast(Clist* CL, vHeap* VH, int data);
void insertPost(Clist* CL, vHeap* VH, int data, int pos);

void deleteFirst(Clist* CL, vHeap* VH);
void deleteElem(Clist* CL, vHeap* VH, int data);
void printList(Clist CL, vHeap VH){
    printf("List: ");
    for (Clist trav = CL; trav != -1; trav = VH.elems[trav].link){
        printf("%d -> ", VH.elems[trav].data);
    }
    printf("NULL\n");
}

int main(){
    Clist CL;
    vHeap VH;

    initVHeap(&VH);
    initList(&CL);

    printf("=== Testing Cursor-Based Linked List ===\n");

    // Insert at front
    insertFirst(&CL, &VH, 10);
    insertFirst(&CL, &VH, 20);
    insertFirst(&CL, &VH, 30);
    printList(CL, VH);  // Expected: 30 -> 20 -> 10 -> NULL

    // Insert at last
    insertLast(&CL, &VH, 40);
    insertLast(&CL, &VH, 50);
    printList(CL, VH);  // Expected: 30 -> 20 -> 10 -> 40 -> 50 -> NULL

    // Insert at position (after 2 nodes, so between 20 and 10)
    insertPost(&CL, &VH, 25, 2);
    printList(CL, VH);  // Expected: 30 -> 20 -> 25 -> 10 -> 40 -> 50 -> NULL

    // Delete first
    deleteFirst(&CL, &VH);
    printList(CL, VH);  // Expected: 20 -> 25 -> 10 -> 40 -> 50 -> NULL

    // Delete specific element
    deleteElem(&CL, &VH, 40);
    printList(CL, VH);  // Expected: 20 -> 25 -> 10 -> 50 -> NULL

    // Delete non-existing element
    deleteElem(&CL, &VH, 99);
    printList(CL, VH);  // Expected: same as above

    // Delete until empty
    deleteFirst(&CL, &VH);
    deleteFirst(&CL, &VH);
    deleteFirst(&CL, &VH);
    deleteFirst(&CL, &VH);
    printList(CL, VH);  // Expected: NULL

    // Extra delete on empty list
    deleteFirst(&CL, &VH);

    return 0;
}

void initList(Clist* CL){
    *CL = -1;
}

void initVHeap(vHeap* VH){
    VH->avail = 0;
    int i;
    for (i = 0; i < MAX-1; i++){
        VH->elems[i].link = i + 1;
    }
    VH->elems[MAX-1].link = -1;
}



int allocSpace(vHeap* VH){
    int space = VH->avail;
    if (space != -1){
        VH->avail = VH->elems[space].link;
    }

    return space;
}


void deallocSpace(vHeap* VH, int pos){
    VH->elems[pos].link = VH->avail;
    VH->avail = pos; 
}


void insertFirst(Clist* CL, vHeap* VH, int data){
    Clist temp;

    temp = allocSpace(VH);
    if (temp != -1){
        VH->elems[temp].data = data;
        VH->elems[temp].link = *CL;
        *CL = temp;  
    } else {
        printf("\nMem Alloc Failed (no more space)\n");
    }
}

void insertLast(Clist* CL, vHeap* VH, int data){
    Clist temp;
    temp = allocSpace(VH);
    if(temp != -1){
        VH->elems[temp].data = data;
        VH->elems[temp].link = -1;

        Clist* trav;
        for (trav = CL; *trav != -1; trav = &(VH->elems[*trav].link)){}
        *trav = temp;
    } else {
        printf("\nMem Alloc Failed (no more space)\n");
    }
}


void insertPost(Clist* CL, vHeap* VH, int data, int pos){
    Clist temp;
    temp = allocSpace(VH);
    if(temp != -1){
        
        Clist* trav, i;
        for (i = 0, trav = CL; *trav != -1 && i < pos; trav = &(VH->elems[*trav].link), i++){}
        if (i < pos){
            printf("\nPosition is out of bounds\n");
        } else {
            VH->elems[temp].data = data;
            VH->elems[temp].link = *trav;
            *trav = temp;
        }
    } else {
        printf("\nMem Alloc Failed (no more space)\n");
    }
}

void deleteFirst(Clist* CL, vHeap* VH) {
    if (*CL != -1){
        Clist temp = *CL;
        *CL = VH->elems[temp].link;
        deallocSpace(VH, temp);
    } else {
        printf("\nList is already empty, nothing to delete\n");
    }
}

void deleteElem(Clist* CL, vHeap* VH, int data){
    Clist* trav, temp;
    for (trav = CL; *trav != -1 && VH->elems[*trav].data != data; trav = &(VH->elems[*trav].link)){}
    if (*trav != -1){
        temp = *trav;
        *trav = VH->elems[*trav].link;
        deallocSpace(VH, temp);
    }
}