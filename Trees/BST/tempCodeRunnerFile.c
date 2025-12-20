#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* left, *right;
} *BST, Tree; 

BST insertNode(BST T, int key);
BST searchNode(BST T, int key);
BST deleteNode(BST T, int key);

void preorder(BST T);
void inorder(BST T);
void postorder(BST T);

int main() {
    BST root = NULL;

    // Test case 1: Insert nodes
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);
    for(int i = 0; i < n; i++){
        root = insertNode(root, keys[i]);
    }

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Test case 2: Search nodes
    int searchKeys[] = {40, 90};
    for(int i = 0; i < 2; i++){
        BST found = searchNode(root, searchKeys[i]);
        if(found){
            printf("Key %d found in the tree.\n", searchKeys[i]);
        } else {
            printf("Key %d not found in the tree.\n", searchKeys[i]);
        }
    }

    // Test case 3: Delete nodes
    int deleteKeys[] = {20, 30, 50};  // delete leaf, node with 1 child, node with 2 children
    for(int i = 0; i < 3; i++){
        printf("Deleting key %d...\n", deleteKeys[i]);
        root = deleteNode(root, deleteKeys[i]);
        printf("Inorder after deletion: ");
        inorder(root);
        printf("\n");
    }

    return 0;
}

BST insertNode(BST T, int key){ 
    if (T == NULL){
        T = calloc(1, sizeof(struct node));
        T->key = key;
        return T;
    }
    if (key < T->key){
        T->left = insertNode(T->left, key);
    } else if (key > T->key){
        T->right = insertNode(T->right, key);
    } 
    return T; 
}

BST searchNode(BST T, int key){
    if (T == NULL || T->key == key){
        return T;
    }
    if (key < T->key){
        return searchNode(T->left, key);
    } else {
        return searchNode(T->right, key);
    }
}

BST deleteNode(BST T, int key){
    if (T == NULL) return T;

    if (key < T->key){
        T->left = deleteNode(T->left, key);
    } else if (key > T->key){
        T->right = deleteNode(T->right, key);
    } else {
        BST temp, successor;
        if (T->right == NULL){    
            temp = T;
            T = T->left;
            free(temp);
            return T;      
        } else if (T->left == NULL){
            temp = T;
            T = T->right;
            free(temp);
            return T;
        } 
        successor = T->right;
        while (successor && successor->left != NULL){
            successor = successor->left;
        }
        T->key = successor->key;
        T->right = deleteNode(T->right, successor->key);        
    }
    return T;
}

void preorder(BST T){
    if (T != NULL){
        printf("%d ", T->key);
        preorder(T->left);
        preorder(T->right);
    }
}

void inorder(BST T){
    if (T != NULL){
        inorder(T->left);
        printf("%d ", T->key);
        inorder(T->right);
    }
}

void postorder(BST T){
    if (T != NULL){
        postorder(T->left);
        postorder(T->right);
        printf("%d ", T->key);
    }
}
