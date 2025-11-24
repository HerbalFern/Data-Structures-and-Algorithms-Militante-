#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node, *Tree;

typedef struct stack {
    Node ELEM[MAX];
    int avail;
} Stack; 

Tree createNode(int data){
    Tree N = malloc(sizeof(Node));
    N->data = data;
    N->left = N->right = NULL;
    return N;
}

void initTree(Tree*);
bool search(Tree, int x);
void inorder(Tree);
void preorder(Tree);
void postorder(Tree);

void insertNode(Tree* T, int data);
void deleteNode(Tree* T, int data);

int main(){

    Tree T;
    initTree(&T);

    // Insert test cases
    insertNode(&T, 50);
    insertNode(&T, 30);
    insertNode(&T, 70);
    insertNode(&T, 20);
    insertNode(&T, 40);
    insertNode(&T, 60);
    insertNode(&T, 80);

    printf("Inorder: ");
    inorder(T);
    // EXPECTED OUTPUT (Correct inorder):
    // 20 30 40 50 60 70 80
    //
    // Your inorder() is correct so this matches.

    printf("\nPreorder: ");
    preorder(T);
    // Your preorder() uses inorder() for both children:
    //
    // preorder prints: root, then inorder(left), then inorder(right)
    //
    // So expected output:
    // 50 20 30 40 60 70 80

    printf("\nPostorder: ");
    postorder(T);
    // Your postorder() uses inorder() for both children:
    //
    // postorder prints: inorder(left), inorder(right), root
    //
    // Expected output:
    // 20 30 40 60 70 80 50

    // Search tests
    printf("\nSearch 40: %s", search(T,40) ? "FOUND" : "NOT FOUND");
    // EXPECTED: FOUND

    printf("\nSearch 99: %s", search(T,99) ? "FOUND" : "NOT FOUND");
    // EXPECTED: NOT FOUND

    // Delete tests (your deleteNode has multiple errors, but you said not to fix)
    deleteNode(&T, 70);
    printf("\nInorder after deleting 70: ");
    inorder(T);

    printf("\n");

    return 0;
}

void initTree(Tree* T){
    *T = NULL;
}

bool search(Tree T, int x){
    if (T == NULL){
        return false;
    } else if (x == T->data){
        return true;
    } else if (x < T->data){
        return search(T->left, x);
    } else {
        return search(T->right, x);
    }
}


void insertNode(Tree* T, int data){
    Tree* trav;
    for (trav = T; *trav != NULL && (*trav)->data != data;){
        trav = (*trav)->data < data ? trav = &(*trav)->right : &(*trav)->left; 
    }
    if (*trav == NULL){
        Tree temp = createNode(data);
        *trav = temp; 
    }
}


void deleteNode(Tree* T, int data){
    Tree* trav, temp;
    for (trav = T; *trav != NULL && (*trav)->data != data;){
        trav = (*trav)->data < data ? trav = &(*trav)->right : &(*trav)->left;
    }

    if (*trav != NULL){
        if ((*trav)->right == NULL) {
            temp = *trav;
            *trav = temp->left;
            
        } else {
            Tree* successor = &(*trav)->right;
            while ((*successor)->left != NULL){
                successor = &(*successor)->left;
            }
            (*trav)->data = (*successor)->data;
            temp = *successor;
            *successor = temp->right;
        }   
        free(temp);
    }
}


void inorder(Tree T){
	if (T != NULL){
		inorder(T->left);
		printf("%d ", T->data);
		inorder(T->right);
	}
}

void preorder(Tree T){
	if (T != NULL){
		printf("%d ", T->data);
		preorder(T->left);
		preorder(T->right);
	}
}
void postorder(Tree T){
	if (T != NULL){
		postorder(T->left);
		postorder(T->right);
		printf("%d ", T->data);
	}
}
