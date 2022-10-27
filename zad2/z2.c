#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (1024)

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_NAME];
	char lastName[MAX_NAME];
	int year;
	position next;
}Person;

int addFirst(position p);
int printList(position p);
int addLast(position p);
int searchByLastName(position p);
int deleteElement(position p);
int toup(char c);

int main(int argc, char** argv)
{
	Person head = {
		.name = { 0 },
		.lastName = { 0 },
		.year = { 0 },
		.next = NULL
	};
	char ch;

	while (1) {
		printf("Izaberite sto zelite napraviti:\n\t-dodati novi element na pocetak liste(P)\n\t-ispisati listu(I)\n\t-dodati novi element na kraj liste(K)\n\t-trazenje elementa u listi po prezimenu(T)\n\t-brisati element iz liste(B)\n\t-izlaz(X)\nVas odabir(slovo): ");
		scanf(" %c", &ch);

		toup(ch);

		switch (ch)
		{
		case 'P':
			addFirst(&head);
		case 'I':
			printList(head.next);
		case 'K':
			addLast(&head);
		case 'T':
			searchByLastName(head.next);
		case 'B':
			deleteElement(&head);
		case 'X':
			break;
		default:
			printf("Pogresan unos!");
		}
	}

	return 0;
}

int addFirst(position p) 
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Person));

	if (q == NULL) {
		printf("Memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe:");
	scanf("%s", q->name);
	printf("Prezime osobe:");
	scanf("%s", q->surname);
	printf("Godina rodenja osobe:");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;

	return 0;
}
int searchByLastName(position p) 
{
	char pr[MAX_NAME];
	printf("\nUnesite prezime osobe koju zelite pronaci:");
	scanf(" %s", &pr);
	int i = 0;

	while (p != NULL)
	{
		if (strcmp(pr, p->surname) == 0) {
			printf("\nAdresa od osobe %s %s je: %p\n", p->name, p->surname, p);
			i++;
		}

		p = p->next;


	}

	if (i == 0)
		printf("Osoba s trazenim prezimenom nije pronadena!\n");

	return 0;
}
int toup(char c) 
{
	if ('a' <= c <= 'z')
		c -= ('a' - 'A');

	return c;
}
