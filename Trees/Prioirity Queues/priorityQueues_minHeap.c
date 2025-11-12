#include <stdio.h>
#define SIZE 15

typedef struct heap {
    int elem[SIZE];
    int last;
} Heap; 

void initTree(Heap*);
void MakeNull(Heap*);
void insert(Heap*, int);
int deleteminV1(Heap*);

void swap(int*, int*); // this is for V2
int deleteminV2(Heap*);

void displayHeap(Heap H){
    if (H.last != -1){
        printf("Starting at root (%d): ", H.elem[0]);
        while (H.last != -1){
            printf("%d ", deleteminV1(&H));
        }
        printf("\n");
    } else {
        printf("Heap is empty.\n");
    }
}

void heapify(int arr[], int size, int i){
    
    int priority = i;
    int LC = (i * 2) + 1;
    int RC = LC + 1; 
    
    if (LC < size && arr[LC] < arr[priority]){
        priority = LC;
    }

    if (RC < size && arr[RC] < arr[priority]){
        priority = RC;
    }
    
    if (priority != i){
        swap(&arr[i], &arr[priority]);
        heapify(arr, size, priority);
    }
    
}

void heapsort(int arr[], int n){
    int i;
    for (i = (n/2) - 1; i>=0; i--){
        heapify(arr, n, i);
    }

    for (i = n - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
int main() {
    Heap H;
    initTree(&H);

    // ========== HEAP TEST ==========
    printf("=== Heap Insertion Test ===\n");
    insert(&H, 25);
    insert(&H, 10);
    insert(&H, 15);
    insert(&H, 30);
    insert(&H, 5);
    insert(&H, 20);

    printf("Deleting min values (using deleteminV1): ");
    displayHeap(H);
    printf("\n");

    // ========== HEAPSORT TESTS ==========
    printf("=== Heapsort Tests ===\n");

    int arr1[] = {25, 10, 15, 30, 5, 20};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    heapsort(arr1, n1);
    printf("Test 1 (random values): ");
    for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    heapsort(arr2, n2);
    printf("Test 2 (descending order): ");
    for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    printf("\n");

    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    heapsort(arr3, n3);
    printf("Test 3 (already sorted): ");
    for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
    printf("\n");

    int arr4[] = {5, 5, 5, 5, 5};
    int n4 = sizeof(arr4)/sizeof(arr4[0]);
    heapsort(arr4, n4);
    printf("Test 4 (all duplicates): ");
    for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\n");

    int arr5[] = {42};
    int n5 = sizeof(arr5)/sizeof(arr5[0]);
    heapsort(arr5, n5);
    printf("Test 5 (single element): ");
    for (int i = 0; i < n5; i++) printf("%d ", arr5[i]);
    printf("\n");

    printf("\nAll heapsort test cases completed.\n");

    return 0;
}

void initTree(Heap * H){
    H->last = -1;
}

void MakeNull(Heap* H){
    H->last = -1; // just indicate array is empty, diff implementation if ang array kay dynamic
}


void insert(Heap* H, int data){
    
    if (H->last < SIZE - 1){
        H->elem[++H->last] = data;
        int i = H->last, temp; // temp is just for swapping
        
        while (i >= 0 && H->elem[i] < H->elem[(i-1)/2]){
            temp = H->elem[i];
            H->elem[i] = H->elem[(i-1)/2];
            H->elem[(i-1)/2] = temp;
            i = (i-1)/2;
        }
    }
}


int deleteminV1(Heap* H){
    int temp = -1; 
    if (H->last != -1){
        temp = H->elem[0];
        int lastElm = H->elem[H->last--];

        int parent = 0, LC = (parent * 2) + 1, RC = LC + 1;
        int child = (H->elem[LC] < H->elem[RC]) ? LC : RC; 
        
        while (child <= H->last && H->elem[child] < lastElm){
            H->elem[parent] = H->elem[child];
            parent = child;
            LC = (parent * 2) + 1;
            RC = LC + 1;

            child = (H->elem[LC] < H->elem[RC]) ? LC : RC;
        }
        
        H->elem[parent] = lastElm; 
    }
    return temp;
}


void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ts mostly correct pero apparently bati daw ana gpt :(
int deleteminV2(Heap* H){
    int temp = -1;
    if (H->last != -1){
        temp = H->elem[0];
        int parent = 0, LC = 2 * parent + 1, RC = LC + 1;
        int child = (H->elem[LC] < H->elem[RC]) ? LC : RC;

        H->elem[0] = H->elem[H->last--];

        while (child <= H->last){
            if (H->elem[child] < H->elem[parent]){
                swap(&H->elem[child], &H->elem[parent]);
            } else {
                break;
            }
            
            parent = child;
            LC = 2 * parent + 1;
            RC = LC + 1;
                    
            if (LC > H->last) break;

            if (RC <= H->last)
            child = (H->elem[LC] < H->elem[RC]) ? LC : RC;
            else child = LC;

        }
    }
    return temp;
}

// work on heapsort later

