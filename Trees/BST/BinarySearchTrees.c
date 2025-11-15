#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node, *Tree;

Tree createNode(int data){
    Tree N = malloc(sizeof(Node));
    N->data = data;
    N->left = N->right = NULL;
    return N;
}

void initTree(Tree);
bool search(Tree, int );
void inorder(Tree);
void preorder(Tree);
void postorder(Tree);

void insertNode(Tree, int);
void deleteNode(Tree, int);

int main(){



    return 0;
}


