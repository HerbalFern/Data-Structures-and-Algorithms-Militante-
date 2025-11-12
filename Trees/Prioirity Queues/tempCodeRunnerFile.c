#include <stdio.h>
#define SIZE 10


typedef struct heap {
    int elem[SIZE];
    int lastidx;
} Heap;

void initHeap(Heap* H);
void makeNull(Heap* H);

void insert(Heap* H, int data);

// shift elements version (this is better so use)
int deleteMaxV1(Heap* H);

// original swap version (non-recursive)
int deleteMaxV2(Heap* H);

// Max heap heapification recursive 
void heapify(int arr[], int size, int largest);

// ill try to implement this non-recursively 
void heapifyV2(int arr[], int size);

// heapsort
void heapsort(int arr[], int size);


// helper function for element swapping
void swap(int*, int*);


void display(Heap H){
    printf("Starting from root (%d): ", H.elem[0]);
    while (H.lastidx >= 0) printf("%d ", deleteMaxV1(&H));
}

int main(){  
    Heap H;
    initHeap(&H);

    printf("=== TEST 1: INSERTION TEST ===\n");
    int testData1[] = {15, 3, 17, 10, 84, 19, 6, 22, 9};
    for (int i = 0; i < 9; i++){
        insert(&H, testData1[i]);
        printf("Inserted %d\n", testData1[i]);
    }

    printf("\nHeap elements (Level-order):\n");
    for (int i = 0; i <= H.lastidx; i++){
        printf("%d ", H.elem[i]);
    }
    printf("\n\n");

    printf("=== TEST 2: DELETE MAX (SHIFT VERSION) ===\n");
    Heap H2 = H; // Copy heap for delete test
    while (H2.lastidx >= 0){
        int max = deleteMaxV1(&H2);
        if (max != -1)
            printf("Deleted max: %d\n", max);
    }
    printf("\n");

    printf("=== TEST 3: DELETE MAX (SWAP VERSION) ===\n");
    Heap H3;
    initHeap(&H3);
    for (int i = 0; i < 9; i++){
        insert(&H3, testData1[i]);
    }
    while (H3.lastidx >= 0){
        int max = deleteMaxV2(&H3);
        printf("Deleted max: %d\n", max);
    }
    printf("\n");

    printf("=== TEST 4: HEAPSORT TEST ===\n");
    int arr1[] = {4, 10, 3, 5, 1};
    int size1 = 5;
    printf("Original array: ");
    for (int i = 0; i < size1; i++) printf("%d ", arr1[i]);
    printf("\n");

    heapsort(arr1, size1);

    printf("After heapsort: ");
    for (int i = 0; i < size1; i++) printf("%d ", arr1[i]);
    printf("\n\n");

    printf("=== TEST 5: HEAPSORT ON REVERSED ARRAY ===\n");
    int arr2[] = {50, 40, 30, 20, 10, 0};
    int size2 = 6;
    printf("Original array: ");
    for (int i = 0; i < size2; i++) printf("%d ", arr2[i]);
    printf("\n");

    heapsort(arr2, size2);

    printf("After heapsort: ");
    for (int i = 0; i < size2; i++) printf("%d ", arr2[i]);
    printf("\n\n");

    printf("=== TEST 6: HEAPSORT ON RANDOM DATA ===\n");
    int arr3[] = {9, 1, 14, 7, 3, 8, 2, 11, 5};
    int size3 = 9;
    printf("Original array: ");
    for (int i = 0; i < size3; i++) printf("%d ", arr3[i]);
    printf("\n");

    heapsort(arr3, size3);

    printf("After heapsort: ");
    for (int i = 0; i < size3; i++) printf("%d ", arr3[i]);
    printf("\n\n");

    printf("=== TEST 7: INSERTION EDGE CASES ===\n");
    Heap H4;
    initHeap(&H4);
    printf("Inserting ascending numbers (1 to 10):\n");
    for (int i = 1; i <= 10; i++) insert(&H4, i);
    for (int i = 0; i <= H4.lastidx; i++) printf("%d ", H4.elem[i]);
    printf("\n\n");

    makeNull(&H4);
    printf("Inserting descending numbers (10 to 1):\n");
    for (int i = 10; i >= 1; i--) insert(&H4, i);
    for (int i = 0; i <= H4.lastidx; i++) printf("%d ", H4.elem[i]);
    printf("\n\n");

    printf("=== TEST 8: DISPLAY FUNCTION (AUTO-DELETION DEMO) ===\n");
    Heap H5;
    initHeap(&H5);
    int testData5[] = {12, 7, 25, 15, 10, 8, 20};
    for (int i = 0; i < 7; i++) insert(&H5, testData5[i]);
    display(H5);
    printf("\n");

    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initHeap(Heap* H){
    H->lastidx = -1;
}

void makeNull(Heap* H){
    H->lastidx = -1;
}

void insert(Heap* H, int data){
    if (H->lastidx < SIZE - 1){
        H->elem[++H->lastidx] = data;

        int i = H->lastidx;
        int parent = (i - 1)/2;
       
        while (parent >= 0 && H->elem[i] > H->elem[parent]){
            swap(&H->elem[i], &H->elem[parent]);            
            i = parent;
            parent = (i - 1)/2;
        }
    }
}

int deleteMaxV1(Heap* H){
    int temp = -1;
    int data = H->elem[H->lastidx--];

    
    if (H->lastidx >= 0){
        
        temp = H->elem[0];

        int priority, LC, RC, previous; 
        priority = 0;
        LC = 2 * priority + 1;
        RC = LC + 1;

        previous = -1;
        
        // almost forgot to add a condition that stops in the right place when data is lesser than the priority
        while (priority <= H->lastidx && previous != priority && H->elem[priority] > data){
        // priority election process algorithm ; so basically this first checks if left child is lesser than the parent/current priority
        // if so, then new priority is the Left child then it is then compared to the right child. But if it is not, parent is still compared to right child either way
        // the last one checks if the parent changed, meaning kung ni-change ang parent kay di pa siya priority queue therefore shift elements napud.
            previous = priority;
            if (LC <= H->lastidx && H->elem[priority] < H->elem[LC]){
                priority = LC;
            } 
            if (RC <= H->lastidx && H->elem[priority] < H->elem[RC]){
                priority = RC;
            }
            if (previous != priority){
                H->elem[previous] = H->elem[priority];
                LC = 2 * priority + 1;
                RC = LC + 1;
            }
        }    
        H->elem[priority] = data;

    }
    return temp;
}

int deleteMaxV2(Heap* H){
    int temp = H->elem[0];
    H->elem[0] = H->elem[H->lastidx--];

    int priority = 0;
    int LC = (2*priority) + 1;
    int RC = LC + 1;

    int previous = -1;
    while (priority <= H->lastidx && priority != previous){
        previous = priority; 

        if (LC <= H->lastidx && H->elem[priority] < H->elem[LC]){
            priority = LC;
        } 
        if (RC <= H->lastidx && H->elem[priority] < H->elem[RC]){
            priority = RC;
        }

        if (previous != priority){
            swap(&H->elem[priority], &H->elem[previous]);
            LC = 2 * priority + 1;
            RC = LC + 1;
        }
    }
}


// recursive
void heapify(int arr[], int size, int i){
    int largest = i, LC = (2*i) + 1, RC = (2*i) + 2;
    
    if (LC <= size && arr[LC] > arr[i]){
        i = LC;
    }
    if (RC <= size && arr[RC] > arr[i]){
        i = RC;
    }

    if (i != largest){
        swap(&arr[largest], &arr[i]);
        heapify(arr, size, i);
    }
}

// non-recursive
void heapifyV2(int arr[], int size){
    int largest = 0; 
    int LC = (2*largest) + 1;
    int RC = (2*largest) + 2;
    
    int previous = -1;

    // as long as the largest element is not a out of bounds from the heap
    // and as long as the parent did not change (previous == largest) which indicates a swap needed
    while (largest < size && previous != largest){
        previous = largest;
        if (LC <= size && arr[LC] > arr[largest]){
            largest = LC;
        }
        if (RC <= size && arr[RC] > arr[largest]){
            largest = RC;
        }
        if (previous != largest){
            swap(&arr[previous], &arr[largest]);
            int LC = (2*largest) + 1;
            int RC = (2*largest) + 2;
        }
    }

}

void heapsort(int arr[], int size){
    for (int i = (size/2)-1; i >= 0; i--){
        heapify(arr, size, i);
    } 
    
    for (int i = size - 1; i >= 0; i--){
        swap(&arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

