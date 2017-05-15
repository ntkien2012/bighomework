#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define __MAX_SIZE 256

typedef struct Book book;
struct Book
{
	char ISBN[14];
	char Author[__MAX_SIZE];
	char Title[__MAX_SIZE];
	int All;
	int Free;
};

typedef struct User user;
struct User
{
	char Username[__MAX_SIZE];
	char Password[__MAX_SIZE];
	int ADbook;
	int ADstudent;
};

book Books[__MAX_SIZE];

user Users[__MAX_SIZE];


//Part: Book
void part_1();

int readBook(const char *filename); 

int comparingISBN(char a[14]);

void addingNewBook(const char *filename);

void searchingBook(const char *filename);

void deletingBook(const char *filename);

void editingBook(const char *filename);


//Part: User
int readUser(const char *filename);

int main(int argc, char **argv)
{
//	part_1();
	return 0;
}

void part_1()
{
	int n = readBook("book.csv");
	if (n == -1)
	{
		printf("ERROR #1: empty file");
	}
	else
	{
		int x;
		printf("MENU:");
		printf("\n1) Add");
		printf("\n2) Delete");
		printf("\n3) Search");
		printf("\n4) Edit");
		
		printf("\nYou want:");
		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				addingNewBook("book.csv");
				break;
			}
			case 2:
			{
				deletingBook("book.csv");
				break;				
			}
			case 3:
			{
				searchingBook("book.csv");
				break;
			}
			case 4:
			{
				editingBook("book.csv");
				break;
			}
			default:;
		}
	}
}

int readBook(const char *filename)
{
	FILE *fs = fopen(filename, "r+");
	if (!fs) 
		return -1;
	
	//Read file
	rewind(fs);
	char tmp[__MAX_SIZE];
	int total = 0;
	int i;
	while(fgets(tmp, __MAX_SIZE, fs))
	{
		fscanf(fs, "%[^,], %[^,], %[^,], %d , %d", Books[total].ISBN, Books[total].Author, Books[total].Title, &Books[total].All, &Books[total].Free);
		total++;
	}
	return total;
}

int comparingISBN(char a[14]) //compare which new ISBN existed or not
{
	int i;
	int temp = -1;
	for (i = 0; i < readBook("book.csv"); i++)
	{
		if(strcmp(a, Books[i].ISBN) == 0)
			temp = i;
	}
	return temp;
}

//Add
void addingNewBook(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	book newbook;
	
	printf("ISBN:");
	gets(newbook.ISBN);
	if (comparingISBN(newbook.ISBN) != -1)
		fclose(fs);
	else 
	{
		printf("\nAuthor's name:");
		gets(newbook.Author);
		printf("\nBook's title:");
		gets(newbook.Title);
		printf("\nAll:");
		scanf("%d", &newbook.All);
		printf("\nFree:");
		scanf("%d", &newbook.Free);
	
		fprintf(fs, "%s, %s, %s, %d, %d\n", newbook.ISBN, newbook.Author, newbook.Title, newbook.All, newbook.Free);
		fclose(fs);
	}
}

//Search
void searchingBook(const char *filename)
{
	FILE * fs = fopen(filename, "r");
	char searchitem[14];
	
	rewind(fs);
	printf("ISBN:");
	gets(searchitem);
	
	int n = comparingISBN(searchitem);
	
	if(n == -1)
		fclose(fs);
	else
	{
		printf("%s, %s, %s, %d, %d\n", Books[n].ISBN, Books[n].Author, Books[n].Title, Books[n].All, Books[n].Free);
		fclose(fs);
	}
}

//Delete
void deletingBook(const char *filename)
{
	FILE *fs;
	char deleteitem[__MAX_SIZE];
	printf("ISBN:");
	gets(deleteitem);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingISBN(deleteitem); 
	int n = readBook(filename);
	fclose(fs);
	if (k != -1)
	{
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)
				//printf("%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
				fprintf(fs, "%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
		}
		fclose(fs);
	}
	else
		printf(" ");
}

//Edit
void editingBook(const char *filename)
{
	FILE *fs;
	book edititem;
	printf("\nISBN:");
	gets(edititem.ISBN);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingISBN(edititem.ISBN); 
	int n = readBook(filename);
	fclose(fs);
	if (k != -1)
	{
		printf("\nAuthor's name:");
		gets(edititem.Author);
		printf("\nBook's title:");
		gets(edititem.Title);
		printf("\nAll:");
		scanf("%d", &edititem.All);
		printf("\nFree:");
		scanf("%d", &edititem.Free);
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)
				//printf("%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
				fprintf(fs, "%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
		}
		fprintf(fs, "%s, %s, %s, %d, %d\n", edititem.ISBN, edititem.Author, edititem.Title, edititem.All, edititem.Free);
		fclose(fs);
	}
	else
		printf(" ");
}
