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