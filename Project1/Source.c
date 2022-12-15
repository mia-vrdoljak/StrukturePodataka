#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define MAX 100

typedef struct Path* Position;

struct Directory {
	char ime[MAX];
	struct Directory* Child;
	struct Directory* Sibling;

};

struct Path {
	struct Directory* Point;
	Position Next;

};

int PushPath(Position p, struct Directory* NaPath)
{
	Position q;

	while (p->Next != NULL)
	{
		p = p->Next;
	}

	q = (Position)malloc(sizeof(struct Path));
	if (q == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return -1;
	}

	q->Next = p->Next;
	p->Next = q;

	q->Point = NaPath;

	return 0;
}

int PopPath(Position p)
{
	Position temp;

	while (p->Next->Next != NULL)
	{
		p = p->Next;
	}
	temp = p->Next;
	p->Next = temp->Next;

	free(temp);


	return 0;
}

int IspisiPath(Position p)
{
	p = p->Next;
	while (p != NULL)
	{
		printf("%s\\", (p->Point)->ime);
		p = p->Next;
	}
	printf(">");
	return 0;
}

int MakeDirectory(struct Directory* current_directory)
{
	struct Directory* novi = NULL;
	char str[MAX];

	printf("\nUnesite naziv direktorija kojeg zelite napraviti:\n");
	scanf("%s", str);

	novi = (struct Directory*)malloc(sizeof(struct Directory));
	if (novi == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return -1;
	}

	strcpy(novi->ime, str);
	novi->Sibling = NULL;
	novi->Child = NULL;

	novi->Sibling = current_directory->Child;
	current_directory->Child = novi;

	printf("Direktorij napravljen.\n");
	return 0;
}

struct Directory* ChangeDirectory(struct Directory* current_dir, Position Path)
{
	char str[MAX];
	struct Directory* P;
	P = current_dir;
	P = P->Child;

	printf("\nUnesite naziv direktorija u kojeg zelite uci:\n");
	scanf("%s", str);

	while (P != NULL && strcmp(P->ime, str) != 0)
	{
		P = P->Sibling;
	}
	if (P == NULL)
	{
		printf("Ne postoji trazeni direktorij u direktoriju %s.\n", current_dir->ime);
		return current_dir;
	}
	else
	{
		PushPath(Path, P);
		return P;
	}


}

int ListDirectory(struct Directory* current_dir)
{
	struct Directory* P;
	P = current_dir;
	P = P->Child;

	if (P == NULL)
		printf("Direktorij %s je prazan.\n", current_dir->ime);
	else
	{
		printf("Direktoriji koji se nalaze u %s su:\n", current_dir->ime);
		while (P != NULL)
		{
			printf("%s\t", P->ime);
			P = P->Sibling;
		}
		printf("\n");
	}

	return 0;

}

struct Directory* UpperDirectory(struct Directory* current_dir, Position Path)
{
	Position P = Path;
	if (strcmp(current_dir->ime, "C:") == 0)
	{
		printf("\nNemoguce se vratiti unazad iz ovog direktorija!\n");
		return current_dir;
	}
	else {
		while (P->Next->Next != NULL)
		{
			P = P->Next;
		}
		PopPath(Path);
		return P->Point;
	}
}


int main()
{
	int n = 0;
	int t = 1;
	char naredba[20];

	struct Directory root;
	struct Path Head;

	Head.Next = NULL;
	strcpy(root.ime, "C:");
	root.Sibling = NULL;
	root.Child = NULL;



	struct Directory* current_dir;
	current_dir = &root;

	PushPath(&Head, &root);

	while (t)
	{
		printf("Unesite naredbu koju zelite izvrsiti (md, cd, cd.., dir i  izlaz): \n");
		IspisiPath(&Head);
		scanf("%s", naredba);


		if (strcmp(naredba, "md") == 0)
		{
			MakeDirectory(current_dir);
		}
		else if (strcmp(naredba, "cd") == 0)
		{
			current_dir = ChangeDirectory(current_dir, &Head);
		}
		else if (strcmp(naredba, "cd..") == 0)				//trebas stavit da ne mos napisat cd.. kada se nalazis u C:
		{
			current_dir = UpperDirectory(current_dir, &Head);
		}
		else if (strcmp(naredba, "dir") == 0)
		{
			ListDirectory(current_dir);
		}
		else if (strcmp(naredba, "izlaz") == 0)
		{
			printf("\nUnijeli ste izlaz.\n");
			t = 0;
		}
		else
			printf("\nTrazena naredba ne postoji.\n");


		printf("\n");
	}



}