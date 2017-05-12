#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define __MAX_SIZE 256
#define __MAX_LEN 50

typedef struct Book book;
struct Book
{
	char ISBN[14];
	char Author[__MAX_SIZE];
	char Title[__MAX_SIZE];
	int All;
	int Free;
};

book Books[__MAX_LEN];

int readBook(const char *filename); 

int comparingISBN(char a[14]);

void addingNewBook(const char *filename);

void searchingBook(const char *filename);

int main(int argc, char **argv)
{
	//Adding
//	int n = readBook("book.csv");
//	addingNewBook("book.csv");
	searchingBook("book.csv");
	return 0;
}

int readBook(const char *filename)
{
	FILE *fs = fopen(filename, "r");
	if (!fs) 
		return -1;
	
	//Read file
	rewind(fs);
	char tmp[__MAX_SIZE];
	int total = 0;
	int i;
	while(fgets(tmp, __MAX_SIZE, fs))
	{
		for (i = 0; i < 13; i++)
		{
			Books[total].ISBN[i] = tmp[i];
		}
		Books[total].ISBN[13] = '\0';
		total++;
	}
	return total;
}


//Adding
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

void addingNewBook(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	book newbook;
	
	printf("\nISBN: ");
	gets(newbook.ISBN);
	if (comparingISBN(newbook.ISBN) != -1)
		fclose(fs);
	else 
	{
		printf("\nAuthor's name: ");
		gets(newbook.Author);
		printf("\nBook's title: ");
		gets(newbook.Title);
		printf("\nAll: ");
		scanf("%d", &newbook.All);
		printf("\nFree: ");
		scanf("%d", &newbook.Free);
	
		fprintf(fs, "%s, %s, %s, %d, %d\n", newbook.ISBN, newbook.Author, newbook.Title, newbook.All, newbook.Free);
		fclose(fs);
	}
}

//Searching

void searchingBook(const char *filename)
{
	FILE * fs = fopen(filename, "r");
	char searchitem[14];
	
	printf("\nISBN: ");
	gets(searchitem);
	printf("%d", comparingISBN(searchitem));
	// if(comparingISBN(searchitem) == -1)
		// fclose(fs);
	// else
	// {
		// rewind(fs);
		// char tmp[__MAX_SIZE];
		// int total = 0;
		// int j;
		// while(fgets(tmp, __MAX_SIZE, fs))
		// {
			// total++;
		// }
		// printf("%s", tmp[comparingISBN(searchitem)]);
		// fclose(fs);
	// }
	
}
