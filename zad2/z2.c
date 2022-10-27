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
	int t = 0;

	while (t==0) {
		printf("Izaberite sto zelite napraviti:\n\t-dodati novi element na pocetak liste(P)\n\t-ispisati listu(I)\n\t-dodati novi element na kraj liste(K)\n\t-trazenje elementa u listi po prezimenu(T)\n\t-brisati element iz liste(B)\n\t-izlaz(X)\nVas odabir(slovo): ");
		scanf(" %c", &ch);

		switch (toup(ch))
		{
		case 'P':
			addFirst(&head);
			break;
		case 'I':
			printList(head.next);
			break;
		case 'K':
			addLast(&head);
			break;
		case 'T':
			searchByLastName(head.next);
			break;
		case 'B':
			deleteElement(&head);
			break;
		case 'X':
			t++;
			break;
		default:
			printf("Pogresan unos!");
			break;
		}
	}

	return 0;
}

int addFirst(position p) 
{
	position q = NULL;
	q = (position)malloc(sizeof(Person));

	if (q == NULL) {
		printf("Memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe:");
	scanf("%s", q->name);
	printf("Prezime osobe:");
	scanf("%s", q->lastName);
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
		if (strcmp(pr, p->lastName) == 0) {
			printf("\nAdresa od osobe %s %s je: %p\n", p->name, p->lastName, p);
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
	if ('a' <= c && c <= 'z')
		c -= 'a'-'A';
	
	return c;
}

int printList(position p) {
	while (p != NULL) {
		printf(" %s %s (%d)", p->name, p->lastName, p->year);
		p = p->next;
	}

	return 0;
}

int addLast(position p) {
	position q;

	while (p->next != NULL)
		p = p->next;
	
	q = (position)malloc(sizeof(Person));

	printf("Unesite ime, prezime i godinu rodenja osobe koju zelite unijeti na kraj liste(u obliku I P G): ");
	scanf(" %s %s %d", q->name, q->lastName, &q->year);

	p->next = q;
	q->next = NULL;

	return 0;
}

int deleteElement(position p) {
	position pToDelete;
	char nameToDelete[MAX_NAME], lastNameToDelete[MAX_NAME];
	int yearToDelete;

	printf("Unesite ime, prezime i godinu rodenja osobe koju zelite izbrisati iz liste(u obliku I P G): ");
	scanf(" %s %s %d", nameToDelete, lastNameToDelete, &yearToDelete);

	while (p->next != NULL) {
		p = p->next;
		if (p->name == nameToDelete && p->lastName == lastNameToDelete && p->year == yearToDelete) {
			pToDelete = p;
			p->next = pToDelete->next;
			free(pToDelete);
		}
	}
		
	return 0;
}

