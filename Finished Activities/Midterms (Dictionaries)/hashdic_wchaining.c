#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
	int data;
	struct node* next;
} *SET;

typedef SET Dictionary[MAX];
typedef enum {FALSE, TRUE} Boolean;

void initDict(Dictionary D);
int hash(Dictionary D, int elem);
void insertUniqueSorted(Dictionary D, int elem);
void deleteElem(Dictionary D, int elem);
Boolean isMember(Dictionary D, int elem);
void display(Dictionary D); // This function is completed for you
void makeNull(Dictionary D);

int main(){
	Dictionary D;
	
	initDict(D);
	
	insertUniqueSorted(D, 10);
	insertUniqueSorted(D, 11);
	insertUniqueSorted(D, 12);
	insertUniqueSorted(D, 13);
	insertUniqueSorted(D, 14);
//	insertUniqueSorted(D, 15); Check if display works as intended
	insertUniqueSorted(D, 16);
	insertUniqueSorted(D, 17);
	insertUniqueSorted(D, 18);
	insertUniqueSorted(D, 19);
	printf("\n");
	
	// Check if insertUniqueSorted works as intended
	insertUniqueSorted(D, 80);
	insertUniqueSorted(D, 30);
	insertUniqueSorted(D, 90);
	insertUniqueSorted(D, 50);
	insertUniqueSorted(D, 60);
	printf("\n");
	
	// Check if duplicate element can be inserted
	insertUniqueSorted(D, 30);
	printf("\n");
	
	// Check if deleteElem works as intended (both cases)
	deleteElem(D, 10);
	deleteElem(D, 10);
	printf("\n");
	
	// Check if isMember works as intended (both cases)
	printf("The member %d %s in the dictionary.\n", 30, (isMember(D, 30) == TRUE) ? "exists" : "does not exist");
	printf("The member %d %s in the dictionary.\n", 69, (isMember(D, 69) == TRUE) ? "exists" : "does not exist");
	printf("\n");
	
	display(D);
	
	// Check if makeNull works as intended
	makeNull(D);
	printf("\n");
	
	display(D);
	
	return 0;
}

// This functions initalizes the dictionary
// Set each indices of the dictionary to be NULL
void initDict(Dictionary D){
  for (int i = 0; i < MAX; i++){
    D[i] = NULL;
  }
}

// This function will return a key based on the ONES digit of the passed elem
// For example, the passed elem is 10. This function will return 0 since the ONES digit of elem is 0.
int hash(Dictionary D, int elem){
  return elem  % 10;
}

// This function inserts an element into the dictionary in ascending order
// Ensures no duplicates are inserted
void insertUniqueSorted(Dictionary D, int elem){

  int i = hash(D, elem);
  
  SET temp = malloc(sizeof(struct node));
  
  if (temp == NULL) return;
  
  temp->next = NULL;
  temp->data = elem;
  
  
  SET* trav;
  for (trav = &D[i]; *trav != NULL && (*trav)->data < elem && (*trav)->data != elem; trav = &(*trav)->next){}
  
  if (*trav != NULL) {
    if ((*trav)->data == elem){
      printf("Element %d is already in the dictionary.\n", elem);
      return;
    } 
  }
  
  temp->next = *trav;
  *trav = temp; 

  printf("Inserted %d in the dictionary.\n", elem);
  
}

// This function will delete an element in the dictionary
// If element is found, delete the element and print a message that it is deleted
// Else, print a message that the element does not exist in the dictionary
void deleteElem(Dictionary D, int elem){

  int i = hash(D, elem);
  SET* trav, temp;
  for (trav = &D[i]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->next){}
  if (*trav != NULL){
    temp = *trav;
    *trav = (*trav)->next;
    free(temp);
    printf("Deleted %d in the dictionary.\n", elem);
  } else {
    printf("The element %d does not exist in the dictionary.\n", elem);
  }
  
}

// This function will check if the passed elem exists in the dictionary
// If the elem exists, return TRUE
// else, return FALSE
Boolean isMember(Dictionary D, int elem){
  int i = hash(D, elem);
  SET* trav, temp;
  for (trav = &D[i]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->next){}
  return (*trav != NULL) ? TRUE : FALSE;

}

// This function is completed for you
void display(Dictionary D){
	SET trav;
	int i, temp;
	
	printf("Dictionary:\n");
	
	for(i = 0; i < MAX; i++){
		printf("[%d]: ", i);
		
		if(D[i] == NULL){
			printf("EMPTY");
		} else {
			for(trav = D[i]; trav != NULL; trav = trav->next){
				if(trav->next != NULL){
					printf("%d -> ", trav->data);
				} else {
					printf("%d", trav->data);
				}	
			}
		}
		
		printf("\n");
	}
	
	printf("\n");
}

// This function empties the dictionary
// Frees all allocated nodes in every bucket
// After execution, all indices will point to NULL
// Once done, print a message that the dictionary is now empty
void makeNull(Dictionary D){
  int i, j; 
  SET trav, temp; 
  for (i = 0; i < MAX; i++){
    for (trav = D[i]; trav != NULL;){
      temp = trav;
      trav = trav->next; 
      free(temp);
    }
    D[i] = NULL;
  }
  printf("Dictionary is now empty.\n");
}