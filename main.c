#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define __MAX_SIZE 256
#define __MAX_LEN 50

typedef struct Book book;
struct Book{
	char ISBN[14];
	char Author[__MAX_SIZE];
	char Title[__MAX_SIZE];
	int All;
	int Free;
};

// typedef struct Student student;
// struct Student{
	// char Student_Code[6];			
	// char Family_Name[__MAX_SIZE];
	// char Name[__MAX_SIZE];
	// char Father_Name[__MAX_SIZE];
	// char Faculty[2];
	// char Speciality[__MAX_SIZE];
// };

book Books[__MAX_LEN];
//student Students[__MAX_LEN];

int readBook(const char *filename); 

int main(int argc, char **argv)
{
	int n = readBook(argv[1]);	
	
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
	int j;
	while(fgets(tmp, __MAX_SIZE, fs))
	{
		//ISBN
		for (j = 0; j < 13; j++)
		{
			Books[total].ISBN[j] = tmp[j + 1];
		}
		Books[total].ISBN[13] = '\0';
//		printf("%s\n", Books[total].ISBN);
//		printf("%c\n", tmp[15]);
		//Author
		int count_to_author = 15;
		for (j = 15; tmp[j] != ';'; j++)
		{
			Books[total].Author[j - 15] = tmp[j];
			count_to_author++;
		}
		Books[total].Author[count_to_author - 14] = '\0';
//		printf("%s\n", Books[total].Author);
		//Title
		int count_to_title = count_to_author + 1;
		for (j = count_to_author + 1; tmp[j] != ';'; j++)
		{
			Books[total].Title[j - count_to_author - 1] = tmp[j];
			count_to_title++;
		}
//		printf("%s\n", Books[total].Title);
		//All
		char number_all[__MAX_SIZE];
		int count_to_all = count_to_title + 1;
		for (j = count_to_title + 1; tmp[j] != ';'; j++)
		{
			number_all[j - count_to_title - 1] = tmp[j];
			count_to_all++;
		}
		Books[total].All = 0;
		int number = 0;
		for (j = count_to_all - count_to_title - 1; j >= 1; j--)
		{
			Books[total].All += number_all[number] * pow(10, j - 1);
			printf("%d\n", Books[total].All);
			number++;
		}
//		printf("%d\n", Books[total].All);
		printf("\n");
		total++;
		
	}
}