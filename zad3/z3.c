#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME (1024)
#define MEMORY_ALLOCATION_ERROR (-1)
#define NO_LAST_NAME_ERROR (-2)

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_NAME];
	char lastName[MAX_NAME];
	int age;
	position next;
}Person;

int menu(position p);

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
int memoryAllocation(position q);
int findLastName(position p, char lastNameToFind);

int main(int argc, char** argv)
{
	Person head = {
		.name = { 0 },
		.lastName = { 0 },
		.age = { 0 },
		.next = NULL
	};

	while (1) {
		menu(&head);
	}

	return 0;
}

int menu(position p) {
	char ch;

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
	scanf(" %c", &ch);

	tolower(ch);

	switch (ch)
	{
	case 'a':
		addFirst(&head);
	case 'b':
		addLast(&head);
	case 'c':
		addBefore(&head);
	case 'd':
		addAfter(&head);
	case 'e':
		searchByLastName(head.next);
	case 'f':
		sortByLastName(head.next);
	case 'g':
		printList(head.next);
	case 'h':
		deleteElement(&head);
	case 'i':
		addToFile(head.next);
	case 'j':
		readFile();
	case 'x':
		break;
	default:
		printf("Pogresan unos!");
	}
}

int memoryAllocation(position q) {
	q = (position)malloc(sizeof(Person));

	if (q == NULL) {
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
	scanf("% d", &q->year);

	return 0;
}

int insertAfter(position p, position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int addFirst(position p){
	position q = NULL;
	memoryAllocation(q);

	addPerson(q);
	insertAfter(p, q);

	return 0;
}

int addLast(position p) {
	position q = NULL;
	memoryAllocation(q);

	addPerson(q);

	while (p->next != NULL)
		p = p->next;

	p->next = q;
	q->next = NULL;

	return 0;
}

int addBefore(position p) {
	char lastNameToFind[MAX_NAME];
	position q = NULL;
	memoryAllocation(q);
	position r = NULL;

	printf("Unesite prezime osobe ispred koje zelite unijeti novu: ");
	scanf(" %s", lastNameToFind);
	
	r = findLastName(p, lastNameToFind);
	if (r != NO_LAST_NAME_ERROR) {
		addPerson(q);
		insertAfter(q, r);
	}

	return 0;
}

int addAfter(position p) {
	char lastNameToFind[MAX_NAME];
	position q = NULL;
	memoryAllocation(q);
	position r = NULL;

	printf("Unesite prezime osobe iza koje zelite unijeti novu: ");
	scanf(" %s", lastNameToFind);

	r = findLastName(p, lastNameToFind);
	if (r != NO_LAST_NAME_ERROR) {
		addPerson(q);
		insertAfter(r, q);
	}

	return 0;
}

int findLastName(position p, char lastNameToFind) {
	int i = 0;
	position r;

	while (p != NULL)
	{
		if (strcmp(lastNameToFind, p->lastName) == 0) {
			r = p;
			i++;
		}

		p = p->next;
	}

	if (i == 0) {
		return NO_LAST_NAME_ERROR;
	}

	return r;
}

int searchByLastName(position p)
{
	char lastNameToFind[MAX_NAME];
	printf("\nUnesite prezime osobe koju zelite pronaci: ");
	scanf(" %s", &lastNameToFind);
	position r;

	r = findLastName(p, lastNameToFind);

	if (r != NO_LAST_NAME_ERROR)
		printf("Tražena osoba postoji(na adresi %p)!", r);

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
		printf(" %d. %s %s (%d)\n", i,  p->name, p->lastName, p->year);
		p = p->next;
		i++;
	}

	return 0;
}

int deleteElement(position p) {
	position r = NULL;
	char lastNameToDelete[MAX_NAME];

	printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
	scanf(" %s", lastNameToDelete);

	r = findLastName(p, lastNameToDelete);
	if (r != NO_LAST_NAME_ERROR) {
		p = r->next;
		r->next = p->next;
		free(p);
	}

	return 0;
}

int addToFile(position p) {

}

int readFile() {

}