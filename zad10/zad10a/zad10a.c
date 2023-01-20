#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_CHAR (100)

struct _Countrys;
struct _Tree;

typedef struct _Tree* PositionT;
typedef struct _Tree
{
	int NumberOfCitizens;
	char TownName[MAX_CHAR];
	PositionT left;
	PositionT right;
}tree;

typedef struct _Countrys* PositionC;
typedef struct _Countrys
{
	char CountryName[MAX_CHAR];
	PositionC next;
	PositionT root;
}countrys;

int ReadingFromFile(PositionC head);
int ReadingTownsFromFile(PositionC Country, char* FileName);

void SortedInsertCountry(PositionC head, PositionC newCountry);
void FreeList(PositionC head);
void Search(PositionC head);
void Print(PositionT root, int Citizens);

PositionC CreateNewCountry(char* name);
PositionT CreateNewTown(char* name);
PositionT SortedInsertTown(PositionT root, PositionT newGrad);

int main()
{
	int check = 0;

	countrys head = {
	.CountryName = "",
	.next = NULL, 
	.root = NULL };

	check = ReadingFromFile(&head);

	Search(head.next);

	FreeList(&head);

	return check;
}

int ReadingFromFile(PositionC head)
{
	int check = 0;
	char buffer[MAX_LINE] = "";
	FILE* f = fopen("drzave.txt", "r");

	if (!f)
	{
		return -1;
	}

	while (!feof(f) && check == 0)
	{
		fgets(buffer, MAX_LINE, f);
		buffer[strcspn(buffer, "\n")] = 0;
		PositionC temp = CreateNewCountry(buffer);

		if (!temp)
		{
			fclose(f);
			return -2;
		}
		SortedInsertCountry(head, temp);

		fgets(buffer, MAX_LINE, f);
		buffer[strcspn(buffer, "\n")] = 0;
		check = ReadingTownsFromFile(temp, buffer);
	}
	fclose(f);
	return 0;
}

int ReadingTownsFromFile(PositionC Country, char* FileName)
{
	char buffer[MAX_LINE] = "";
	FILE* f = fopen(FileName, "r");

	if (f == NULL)
	{
		return -3;
	}

	while (!feof(f))
	{
		fgets(buffer, MAX_LINE, f);
		buffer[strcspn(buffer, "\n")] = 0;
		PositionT temp = CreateNewTown(buffer);
		if (NULL == temp)
		{
			fclose(f);
			return -4;
		}
		fgets(buffer, MAX_LINE, f);
		sscanf(buffer, "%d", &temp->NumberOfCitizens);
		Country->root = SortedInsertTown(Country->root, temp);
	}
	fclose(f);
	return 0;
}

void SortedInsertCountry(PositionC head, PositionC newCountry)
{
	while (head->next != NULL && _strcmpi(head->next->CountryName, newCountry->CountryName) > 0)
	{
		head = head->next;
	}

	newCountry->next = head->next;
	head->next = newCountry;
}

void FreeList(PositionC head)
{
	PositionC temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}

void Search(PositionC head)
{
	int Citizens = 0;
	char buffer[MAX_LINE] = "";

	printf("Wich country do you wish to check?\n");
	fgets(buffer, MAX_LINE, stdin);
	buffer[strcspn(buffer, "\n")] = 0;
	while (head != NULL && _strcmpi(buffer, head->CountryName) != 0)
	{
		head = head->next;
	}
	if (head == NULL)
	{
		printf("Sorry, but there is no such a country.\n");
	}
	else
	{
		printf("How many citizens does wanted town have?\n");
		fgets(buffer, MAX_LINE, stdin);
		sscanf(buffer, "%d", &Citizens);
		Print(head->root, Citizens);
	}
}

void Print(PositionT root, int Citizens)
{
	if (root != NULL && Citizens <= root->NumberOfCitizens)
	{
		Print(root->left, Citizens);
		printf("%s \t %d\n", root->TownName, root->NumberOfCitizens);
		Print(root->right, Citizens);
	}
	else if (root == NULL)
	{
		;
	}
	else
	{
		Print(root->left, Citizens);
		printf("%s \t %d\n", root->TownName, root->NumberOfCitizens);
		Print(root->right, Citizens);
	}
}

PositionC CreateNewCountry(char* name)
{
	PositionC newCountry = NULL;

	newCountry = (PositionC)malloc(sizeof(countrys));
	if (!newCountry)
	{
		return NULL;
	}

	strcpy(newCountry->CountryName, name);
	newCountry->next = NULL;
	newCountry->root = NULL;

	return newCountry;
}

PositionT CreateNewTown(char* name)
{
	PositionT newGrad = NULL;

	newGrad = (PositionT)malloc(sizeof(tree));
	if (!newGrad)
	{
		return NULL;
	}
	strcpy(newGrad->TownName, name);
	newGrad->NumberOfCitizens = 0;
	newGrad->left = NULL;
	newGrad->right = NULL;

	return newGrad;
}

PositionT SortedInsertTown(PositionT root, PositionT newGrad)
{
	if (root == NULL)
	{
		root = newGrad;
	}
	else if (root->NumberOfCitizens > newGrad->NumberOfCitizens)
	{
		root->left = SortedInsertTown(root->left, newGrad);
	}
	else if (root->NumberOfCitizens <= newGrad->NumberOfCitizens)
	{
		root->right = SortedInsertTown(root->right, newGrad);
	}

	return root;
}