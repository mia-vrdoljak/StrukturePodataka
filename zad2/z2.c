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
	int age;
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
		.age = { 0 },
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

int printList(position p) {
	while (p != NULL) {
		printf(" %s %s (%d)", p->name, p->lastName, p->age);
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
	scanf(" %s %s %d", q->name, q->lastName, &q->age);

	p->next = q;
	q->next = NULL;

	return 0;
}

int deleteElement(position p) {
	position pToDelete;
	char nameToDelete[MAX_NAME], lastNameToDelete[MAX_NAME];
	int ageToDelete;

	printf("Unesite ime, prezime i godinu rodenja osobe koju zelite izbrisati iz liste(u obliku I P G): ");
	scanf(" %s %s %d", nameToDelete, lastNameToDelete, &ageToDelete);

	while (p->next != NULL) {
		p = p->next;
		if (p->name == nameToDelete && p->lastName == lastNameToDelete && p->age == ageToDelete) {
			pToDelete = p;
			p->next = pToDelete->next;
			free(pToDelete);
		}
	}
		
	return 0;
}