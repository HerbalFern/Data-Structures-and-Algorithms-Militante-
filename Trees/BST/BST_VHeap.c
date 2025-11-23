#include <stdio.h>
#define MAX 20

typedef struct node {
    int data;
    int link;
} List;

typedef struct vheap {
    List L[MAX];
    int avail;
} VHeap;

void initHeap(VHeap* VH);
void initList(int* list);
int allocSpace(VHeap* VH);
void deallocSpace(VHeap* VH);



int main(){

    return 0;
}


void initHeap(VHeap* VH){
    VH->avail = 0;
    for (int i = 0; i < MAX - 1; i++){
        VH->L[i].link = i + 1;
    }
    VH->L[MAX - 1].link = -1;
}

void initList(int* list){
    *list = -1;
}

int allocSpace(VHeap* VH){
    int space = VH->avail;
    if (space != -1){
        VH->avail = VH->l[space].link;
    }
    return space;
}

void deallocSpace(VHeap* VH, int idx){
    VH->L[idx].link = VH->avail;
    VH->avail = idx;
}

