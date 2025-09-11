#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bookstoreDetails{
	char storeName[33];
	char address[65];
	char telephone[8];
}bsDetails;

typedef struct bookRecord{
	char bookID[9];
	char bookName[33];
	float price;
	int stocks;
	char shelf[5];
}bookRecord;

typedef struct bookNode{
	bookRecord bkRec;
	int pages;
	struct bookNode* nextBook;
}bookNode, *BookList;

typedef struct bookStore{
	bsDetails details;
	BookList bList;
	int count;
}bookStore;

typedef struct customerDetails{
	char custName[33];
	char telephone[8];
	char email[65];
}custDetails;

typedef struct personalBkNode{
	char bookName[33];
	struct personalBkNode* nextBk;
}personalBkNode, *PersonalBkList;

typedef struct custBkCollection{
	custDetails customer;
	PersonalBkList bkList;
	int count;
}custBkCollection;

/*THESE FUNCTIONS HAVE ALREADY BEEN WRITTEN FOR YOUR CONVENIENCE*/
void populateBookStore(bookStore*);
void displayCustBooks(custBkCollection);
void displayBooksInBS(bookStore);

/*Instructions: Write the code of the given function prototypes
				1) initBookStore() - Initializes a given bookstore
				2) findBook() - Given a bookstore and a book ID, the function will return 1 if the book is found in the bookstore
								and 0 if it is not in the bookstore.
				3) insertBookBS() - Function will insert a new book record into the bookstore if and only if the book record still does
									not exist in the bookstore. Also, the inserted record is inserted in its proper place in the booklist
									sorted in ascending order by book ID.
				4) deleteBooksNoStock() - Function will go through all the book records in a bookstore and delete any book record that 
										  has zero stocks.
				5) initCustBkCollection() - Initializes a customer's book collection.
				6) purchaseBook() - Function will go through the list of book records in a bookstore and check if the certain book the customer
									wants to purchase exists in the bookstore. If it does exist, insert that book into the customer's book collection
									if and only if the book still does not exist in the customer's collection. The book is inserted at the last
									part of the customer's collection. Do the necessary increments and decrements. Finally, if insertion was successful,
									call function deleteBooksNoStock() to remove any books in the bookstore that have no more stocks.
				*/


void initBookStore(bookStore*);
int findBook(bookStore, char[]);
void insertBookBS(bookStore*, bookRecord);
void deleteBooksNoStock(bookStore*);

custBkCollection initCustBkCollection();
void purchaseBook(bookStore*, custBkCollection*, char[]);

int main(void)
{
	/*Expected output: The list of books with their respective values should have been displayed based on the populate function*/
	bookStore NBS;
	initBookStore(&NBS);
	populateBookStore(&NBS);
	displayBooksInBS(NBS);
	getchar();
	system("CLS");
	
	/*Expected output: Error messages: You already have this book in your collection and Book does not exist in the store should have been displayed.
					   Then, display Harry Potter Books 1-4.*/
	custBkCollection myBooks = initCustBkCollection();
	purchaseBook(&NBS, &myBooks, "HP000001");
	purchaseBook(&NBS, &myBooks, "HP000002");
	purchaseBook(&NBS, &myBooks, "HP000003");
	purchaseBook(&NBS, &myBooks, "HP000003");
	purchaseBook(&NBS, &myBooks, "HP000004");
	purchaseBook(&NBS, &myBooks, "HP000004");
	displayCustBooks(myBooks);
	getchar();
	system("CLS");
	
	/*Expected output: Harry Potter Book 4 should have been deleted. HP Books 1, 2 and 3 should have 6, 3, and 5 stocks respectively*/
	displayBooksInBS(NBS);
	getchar();
	system("CLS");
	
	return 0;
	
}

void populateBookStore(bookStore* BS)
{
	int i;
	bookRecord initialBooks[10] = { {"HP000001", "Harry Potter Book 1", 399.99, 7, "H001"},
									{"HP000002", "Harry Potter Book 2", 499.99, 4, "H001"},
									{"HP000003", "Harry Potter Book 3", 499.99, 6, "H001"},
									{"HP000004", "Harry Potter Book 4", 599.99, 1, "H001"},
									{"HP000005", "Harry Potter Book 5", 699.99, 3, "H001"},
									{"HP000006", "Harry Potter Book 6", 599.99, 4, "H001"},
									{"HP000007", "Harry Potter Book 7", 799.99, 5, "H001"},
									{"TL000001", "Twilight", 299.99, 2, "TW01"},
									{"TL000002", "New Moon", 399.99, 14, "TW01"},
									{"TL000003", "Eclipse", 399.99, 7, "TW01"} };	
	for(i = 0 ; i < 10; i++){
		insertBookBS(BS, initialBooks[i]);
	}
}

/*
1) initBookStore() - Initializes a given bookstore
2) findBook() - Given a bookstore and a book ID, the function will return 1 if the 
book is found in the bookstore and 0 if it is not in the bookstore.
*/

void initBookStore(bookStore* BS)
{
	BS->count = 0;
	BS->bList = NULL;
	strcpy(BS->details.address, " ");
	strcpy(BS->details.storeName, " ");
	strcpy(BS->details.telephone, " ");

}

int findBook(bookStore BS, char bookID[])
{
	int i;
	BookList trav;
	for (i = 0, trav = BS.bList; i < BS.count && strcmp(bookID, trav->bkRec.bookID) == 0; trav = trav->nextBook, i++){}
	if (i < BS.count) {
		return 1;
	}
	return 0;
}

/*
3) insertBookBS() - Function will insert a new book record into the bookstore if and only if the book record 
still does not exist in the bookstore. Also, the inserted record is inserted in its proper place in the 
booklist sorted in ascending order by book ID.
*/

void insertBookBS(bookStore* BS, bookRecord newBk)
{
	BookList temp = malloc(sizeof(bookNode));
	if (temp != NULL) {
		temp->bkRec = newBk;
		BookList* trav;
		for (trav = &BS->bList; *trav != NULL && strcmp((*trav)->bkRec.bookID, newBk.bookID) > 0; trav = &(*trav)->nextBook){}

		if (*trav == NULL){
			temp->nextBook = NULL;
			*trav = temp;
		} else {
			temp->nextBook = *trav;
			*trav = temp;
		}


	} 
}
/*
4) deleteBooksNoStock() - Function will go through all the book records in a bookstore and delete any book 
record that has zero stocks.
*/
void deleteBooksNoStocks(bookStore* BS)
{
	BookList* trav, temp;
	for (trav = &BS->bList; *trav != NULL;){
		if ((*trav)->bkRec.stocks == 0){
			temp = *trav;
			*trav = temp->nextBook;
			free(temp);
		} else {
		trav = &(*trav)->nextBook;
		}
}

}

void displayBooksInBS(bookStore BS)
{
	printf("Bookstore Name: %s\n\n", BS.details.storeName);
	
	for(; BS.bList != NULL; BS.bList = BS.bList->nextBook){
		printf("Book ID: %s\nBook: %s\nPrice: %.2f\nStocks: %d\nShelf: %s\n\n", BS.bList->bkRec.bookID,
				BS.bList->bkRec.bookName, BS.bList->bkRec.price, BS.bList->bkRec.stocks, BS.bList->bkRec.shelf);
	}
}
/*
5) initCustBkCollection() - Initializes a customer's book collection.
*/

custBkCollection initCustBkCollection()
{
	custBkCollection temp;
	temp.count = 0;
	temp.bkList = NULL;
	strcpy (temp.customer.custName, " ");
	strcpy (temp.customer.telephone, " ");
	strcpy (temp.customer.email, " ");
	
	return temp;
}

/*
	6) purchaseBook() - Function will go through the list of book records in a bookstore and check if the 
	certain book the customer wants to purchase exists in the bookstore. If it does exist, insert that book 
	into the customer's book collection if and only if the book still does not exist in the customer's 
	collection. The book is inserted at the last part of the customer's collection. Do the necessary 
	increments and decrements. Finally, if insertion was successful, call function deleteBooksNoStock() to remove any books in the bookstore that have no more stocks.
*/

void purchaseBook(bookStore* BS, custBkCollection* CBC, char bookID[])
{
	BookList trav;
	PersonalBkList *pTrav;
	for (trav = BS->bList; trav != NULL && strcmp(trav->bkRec.bookID, bookID) != 0; trav = trav->nextBook){}
	if (trav != NULL){
		for (pTrav = &(CBC->bkList); *pTrav != NULL && strcmp((*pTrav)->bookName, trav->bkRec.bookName) != 0; pTrav = &(*pTrav)->nextBk){}
		if (*pTrav == NULL){
			PersonalBkList temp = malloc(sizeof(personalBkNode));
			temp->nextBk = NULL;
			
			strcpy(temp->bookName, trav->bkRec.bookName);			
			*pTrav = temp;
			CBC->count++;
			trav->bkRec.stocks--;

			printf("\nBook added to your collection\n");
			deleteBooksNoStocks(BS);
		} else {
			printf("\nThis book already exists\n");
		}
	} else {
		printf("\nBook does not exist in Store.\n");
	}

}

void displayCustBooks(custBkCollection CBC)
{
	PersonalBkList trav;
	
	printf("Name: %s\n\n", CBC.customer.custName);
	
	for(trav = CBC.bkList; trav != NULL; trav = trav->nextBk){
		printf("%s\n", trav->bookName);
	}
}

