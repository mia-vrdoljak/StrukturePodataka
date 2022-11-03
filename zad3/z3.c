#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME (1024)
#define MEMORY_ALLOCATION_ERROR (2)

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_NAME];
	char lastName[MAX_NAME];
	int year;
	position next;
}Person;

int menu();

int addFirst(position p);
int addLast(position p);
int addBefore(position p);
int addAfter(position p);
int searchByLastName(position p);
int sortByLastName(position p);
int printList(position p);
int deleteElement(position p);
int addToFile(position p);
int readFile();

int addPerson(position q);
int insertAfter(position p, position q);
int memoryAllocation(position* q);

int main(int argc, char** argv)
{
	Person head{
		.name = {0},
		.lastName = {0},
		.year = 0,
		.next = NULL
	};

	char choice;

	while (1) {

		menu();
		scanf(" %c", &choice);

		switch (tolower(choice))
		{
		case 'a':
			addFirst(&head);
			break;
		case 'b':
			addLast(&head);
			break;
		case 'c':
			addBefore(&head);
			break;
		case 'd':
			addAfter(&head);
			break;
		case 'e':
			searchByLastName(head.next);
			break;
		case 'f':
			sortByLastName(head.next);
			break;
		case 'g':
			printList(head.next);
			break;
		case 'h':
			deleteElement(&head);
			break;
		case 'i':
			addToFile(head.next);
			break;
		case 'j':
			readFile();
			break;
		case 'x':
			printf("Do videnja!");
			return 0;
			break;
		default:
			printf("Pogresan unos!");
			break;
		}
	}
	return 0;
}

int menu() {
	printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
		"\t\t\tIZBORNIK\n\n"
		"\ta) unos na pocetak\n"
		"\tb) unos na kraj\n"
		"\tc) unos ispred\n"
		"\td) unos iza\n"
		"\te) pronadi prezime\n"
		"\tf) sortiranje\n"
		"\tg) ispis\n"
		"\th) brisanje elementa\n"
		"\ti) upis u datoteku\n"
		"\tj) unos iz datoteke\n"
		"\tx) izlaz\n\n"
		"Vas odabir: ");

	return 0;
}

int memoryAllocation(position* q) {
	*q = (position)malloc(sizeof(Person));

	if (*q == NULL) {
		printf("Memorija nije alocirana!\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	return 0;
}

int addPerson(position q) {
	printf("Ime osobe:");
	scanf(" %s", q->name);
	printf("Prezime osobe:");
	scanf(" %s", q->lastName);
	printf("Godina rodenja osobe:");
	scanf(" %d", &q->year);

	return 0;
}

int insertAfter(position p, position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int addFirst(position p) {
	position q = NULL;
	memoryAllocation(&q);

	addPerson(q);
	insertAfter(p, q);

	return 0;
}

int addLast(position p) {
	position q = NULL;
	memoryAllocation(&q);

	addPerson(q);

	while (p->next != NULL)
		p = p->next;

	insertAfter(p, q);

	return 0;
}

int addBefore(position p) {
	char lastNameToFind[MAX_NAME];

	position q = NULL;
	memoryAllocation(&q);

	addPerson(q);

	printf("Unesite prezime osobe ispred koje zelite unijeti novu: ");
	scanf(" %s", lastNameToFind);

	while (p->next != NULL && strcmp(lastNameToFind, p->next->lastName) != 0)
		p = p->next;

	if (p->next != NULL)
		insertAfter(p, q);

	return 0;
}

int addAfter(position p) {
	char lastNameToFind[MAX_NAME];

	position q = NULL;
	memoryAllocation(&q);

	addPerson(q);

	printf("Unesite prezime osobe iza koje zelite unijeti novu: ");
	scanf(" %s", lastNameToFind);

	while (p->next != NULL && strcmp(lastNameToFind, p->lastName) != 0)
		p = p->next;

	insertAfter(p, q);

	return 0;
}

int searchByLastName(position p)
{
	char lastNameToFind[MAX_NAME];
	int i = 0;

	printf("\nUnesite prezime osobe koju zelite pronaci: ");
	scanf(" %s", &lastNameToFind);

	while (p != NULL) {
		if (strcmp(lastNameToFind, p->lastName) == 0) {
			printf("\nAdresa od osobe %s %s je: %p\n", p->name, p->lastName, p);
			i++;
		}
		p = p->next;
	}

	if (i == 0)
		printf("Osoba s trazenim prezimenom nije pronadena!\n");

	return 0;
}

int sortByLastName(position p) {
	position q = NULL;

	while (p != NULL) {
		if (strcmp(p->lastName, p->next->lastName) < 0) {
			q = p->next;
			p->next = p;
			p = q;
		}
		else if (strcmp(p->lastName, p->next->lastName) == 0) {
			if (strcmp(p->name, p->next->name) < 0) {
				q = p->next;
				p->next = p;
				p = q;
			}
		}
	}

	return 0;
}

int printList(position p) {
	int i = 1;

	while (p != NULL) {
		printf(" %d. %s %s (%d)\n", i, p->name, p->lastName, p->year);
		p = p->next;
		i++;
	}

	return 0;
}

int deleteElement(position p) {
	position q = NULL;
	char lastNameToDelete[MAX_NAME];

	printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
	scanf(" %s", lastNameToDelete);

	while (p->next != NULL && strcmp(lastNameToDelete, p->lastName) != 0)
	{
		q = p;
		p = p->next;
	}
	if (q != NULL && strcmp(lastNameToDelete, p->lastName) == 0) {
		p = q->next;
		q->next = p->next;
		free(p);
	}

	return 0;
}

int addToFile(position p) {
	FILE* fp = NULL;
	fp = fopen("lista.txt", "w");

	if (fp == NULL) {
		printf("Error opening file!");
		return 1;
	}

	while (p != NULL) {
		fprintf(fp, "%s %s %d\n", p->name, p->lastName, p->year);
		p = p->next;
	}

	fclose(fp);
	return 0;
}

int readFile() {
	char file[MAX_NAME];
	int lines = 0;

	Person head{
		.name = {0},
		.lastName = {0},
		.year = 0,
		.next = NULL
	};

	position p = &head;
	position q = NULL;

	printf("Unesite ima datoteke iz koje zelite procitati listu: ");
	scanf(" %s", &file);

	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("Error opening file!");
		return 1;
	}

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')
			lines++;
	}
	rewind(fp);

	if (lines != 0) {
		for (int temp = 0; temp < lines; temp++) {
			q = (position)malloc(sizeof(Person));
			if (q == NULL) {
				printf("Memorija nije alocirana!\n");
				return 1;
			}
			fscanf(fp, "%s %s %d\n", p->name, p->lastName, p->year);
			q->next = p->next;
			p->next = q;
			p = p->next;
		}
	}
	fclose(fp);
	printList(head.next);
	return 0;
}