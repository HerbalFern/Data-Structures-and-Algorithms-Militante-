#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 10


typedef bool Set[MAX];

void insertElem(Set, int);
void deleteElem(Set, int);

bool* Union(Set, Set);
bool* Intersection(Set, Set);
bool* difference(Set, Set);

bool isSubSet(Set, Set);

void populateSet(Set S, int num[], int numSize);

void displaySet(Set S);


int main(){
		
	Set A = {0};
	Set B = {0};
	

	int arrA[] = {1, 3, 5, 6, 7};
	int arrB[] = {2, 4, 5, 6, 8, 9};

	populateSet(A, arrA, 5);
	populateSet(B, arrB, 6);

	printf("Set A: ");
	displaySet(A);

	printf("\nSet B: ");
	displaySet(B);


	bool* Intersect = Intersection(A, B);
	bool* UNION = Union(A, B);
	bool* Diff = difference(A, B);

	printf("\nSet Intersection: ");
	displaySet(Intersect);


	printf("\nSet Union: ");
	displaySet(UNION);

	printf("\nSet Difference: ");
	displaySet(Diff);

	return 0;
}


// kinda irrelevant


void populateSet(Set S, int num[], int numSize){
	int i;
	for (i = 0; i < numSize; i++){
		S[num[i]] = 1;
	}
}

void insertElem(Set S, int N){
	if (N >=0 && N < MAX)
	S[N] = 1;
}

void deleteElem(Set S, int N){
	if (N >=0 && N < MAX)
	S[N] = 0;
}

bool* Union(Set A, Set B){
	int i;	
	bool* C = (bool*) calloc(MAX, sizeof(bool));
	if (C != NULL){	
		for (i = 0; i < MAX; i++){
			if (A[i] == 1 || B[i] == 1) { C[i] = 1; } 
			else {C[i] = 0;}
		}
	}
	
	return C;
}


bool* Intersection(Set A, Set B){
	int i;
	bool* C = (bool*) calloc(MAX, sizeof(bool));
	if (C != NULL){	
		for (i = 0; i < MAX; i++){
			if (A[i] == 1 && B[i] == 1) { 
			    C[i] = 1;
			} 
			else { 
			    C[i] = 0;
		}
		    
		}
	}
	
	return C;
}


bool* difference(Set A, Set B){
	int i;
	bool* C = (bool*) calloc(MAX, sizeof(bool));
	if (C != NULL){	
		for (i = 0; i < MAX; i++){
			if (A[i] == 1 && B[i] == 0) {
			    C[i] = 1; 
			}
			else {
			    C[i] = 0;
		}
	}
	
	return C;
}


bool isSubSet(Set A, Set Sub){
	for (int i = 0; i < MAX; i++){
		if (Sub[i] == 1){
			if (A[i] != Sub[i]){
				return false;
			}
		}
	}
	return true;
}

void displaySet(Set S){
	int i;
	printf("{");
	for (i = 0; i < MAX; i++){
		if (S[i] == 1){
			printf("%d ", i);
		}
	}
	printf("\}\n");
}

