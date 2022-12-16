#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (1024)
#define MEMORY_ALLOCATION_ERROR (-1)

typedef struct _stog* Position;

typedef struct _directory {
	char name[MAX_NAME];
	struct _directory* child;
	struct _directory* sibling;
}Directory;

typedef struct _stog {
	Directory* point;
	Position next;
}Stog;

int insertAfter(Position, Position);

int PushStog(Position, Directory*);
int PopStog(Position);
int PrintStog(Position);
int MakeDirectory(Directory*);
Directory* ChangeDirectory(Directory*, Position);
int DirectoryList(Directory*);
Directory* UpperDirectory(Directory*, Position);

int main(void)
{
	Directory* Root = (Directory*)malloc(sizeof(Directory));
	strcpy(Root->name, "C:");
	Root->child = NULL;
	Root->sibling = NULL;

	Stog* Head = (Stog*)malloc(sizeof(Stog));
	Head->next = NULL;

	Menu(Root, Head);

	return 0;
}

int Menu(Directory* Root, Stog* Head) {
	Directory* currentDirectory = Root;
	char command[MAX_NAME] = { 0 };
	
	while (1) {
		printf("Unesite naredbu koju zelite izvrsiti (md, cd, cd.., dir i  izlaz): \n");
		PrintStog(&Head);
		scanf(" %s", command);

		if (strcmp(command, "md") == 0)
			MakeDirectory(currentDirectory);
		else if (strcmp(command, "cd") == 0)
			currentDirectory = ChangeDirectory(currentDirectory, Head);
		else if (strcmp(command, "cd..") == 0)
			currentDirectory = UpperDirectory(currentDirectory, Head);
		else if (strcmp(command, "dir") == 0)
			DirectoryList(currentDirectory);
		else if (strcmp(command, "izlaz") == 0)
			return 1;
		else
			printf("Naredba nije pronadena.");

		printf("\n");
	}

	return 0;
}

int insertAfter(Position p, Position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int PushStog(Position p, Directory* onStog) {
	Position q = NULL;

	while (p->next != NULL)
		p = p->next;

	q = (Position)malloc(sizeof(Stog));

	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return MEMORY_ALLOCATION_ERROR;
	}

	insertAfter(p, q);

	q->point = onStog;
}

int PopStog(Position p) {
	Position temp = NULL;
	while(p->next->next != NULL)
		p = p->next;

	temp = p->next;
	p->next = temp->next;
	free(temp);

	return 0;
}

int PrintStog(Position p) {
	p = p->next;
	while (p != NULL)
	{
		printf("%s\\", (p->point)->name);
		p = p->next;
	}

	printf(">");

	return 0;
}

int MakeDirectory(Directory* currentDirectory) {
	Directory* newDirectory = NULL;
	char newDirectoryName[MAX_NAME];

	printf("\nUnesite ime direktorija koji zelite izraditi: \n");
	scanf(" %s", newDirectoryName);

	newDirectory = (Directory*)malloc(sizeof(Directory));
	if (newDirectory == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return MEMORY_ALLOCATION_ERROR;
	}

	strcpy(newDirectory->name, newDirectoryName);
	newDirectory->sibling = NULL;
	newDirectory->child = NULL;

	newDirectory->sibling = currentDirectory->child;
	currentDirectory->child = newDirectory;

	printf("Novi direktorij napravljen.");

	return 0;

}
Directory* ChangeDirectory(Directory* currentDirectory, Position stog) {
	Directory* p = NULL;
	char directoryName[MAX_NAME];

	p = currentDirectory;
	p = p->child;

	printf("\nUnesite ime direktorija u koji zelite uci: \n");
	scanf(" %s", directoryName);

	while (p != NULL && strcmp(p->name, directoryName) != 0)
		p = p->sibling;

	if (p == NULL)
	{
		printf("Trazeni direktorij ne postoji u direktoriju %s.\n", currentDirectory->name);
		return currentDirectory;
	}
	else
	{
		PushStog(stog, p);
		return p;
	}
}

int DirectoryList(Directory* currentDirectory) {
	Directory* p = NULL;
	p = currentDirectory;
	p = p->child;

	if (p == NULL)
		printf("Direktorij %s je prazan.\n", currentDirectory->name);
	else
	{
		printf("Direktoriji koji se nalaze u direktoriju %s su: \n", currentDirectory->name);
		
		while (p != NULL)
		{
			printf("%s\t", p->name);
			p = p->sibling;
		}
		printf("\n");
	}

	return 0;
}

Directory* UpperDirectory(Directory* currentDirectory, Position stog) {
	Position p = stog;

	if (strcmp(currentDirectory->name, "C:") == 0)
	{
		printf("\nNije moguce vratiti se iz ovog direktorija.\n");
		return currentDirectory;
	}
	else
	{
		while (p->next->next != NULL)
			p = p->next;

		PopStog(stog);

		return p->point;
	}
}
