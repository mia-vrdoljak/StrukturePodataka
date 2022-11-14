#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE (1024)
#define ERROR_ALLOCATION (-1)
#define ERORR_OPENING (-2)
#define EXIT_FAIL (-3)

struct _stack;
typedef struct _stack* position;
typedef struct _stack {
	float number;
	position next;
}Stack;

int memoryAllocation(position*);

int insertAfter(position, position);
int deleteAfter(position);

int push(float, position);
float pop(position);

int readFile(position, char*);
int print(position);

int calculate(position, FILE*);
int deleteAll(position);

int main(int argc, char** argv)
{
	Stack Head = {
		.number = 0,
		.next = NULL
	};

	char file[MAX_LINE] = { 0 };
	int check;

	printf("Dear customer, please enter the name of the file:");
	scanf(" %s", file);

	readFile(&Head, file);

	printf("The result of prefix operation is: ");

	if (print(Head.next) == 1)
		print(Head.next);
	else
		printf("Postfix not valid!");

	deleteAll(&Head);

	return 0;
}

int memoryAllocation(position* q) {
	*q = (position)malloc(sizeof(Stack));

	if (*q == NULL) {
		;
		return ERROR_ALLOCATION;
	}

	return 0;
}

int insertAfter(position p, position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int deleteAfter(position p) {
	position q = p->next;
	p->next = p->next->next;
	free(q);

	return 0;
}

int push(float num, position p) {
	position q = NULL;
	memoryAllocation(&q);

	q->number = num;
	insertAfter(p, q);

	return 0;
}

float pop(position p) {
	position q;
	float n;
	if (!p->next == NULL) {
		printf("Postfix not valid!");
		return EXIT_FAIL;
	}

	q = p->next;
	p->next = q->next;
	n = q->number;
	free(q);;

	return n;
}

int readFile(position p, char* file) {
	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (fp == NULL)
		return ERORR_OPENING;

	calculate(p, fp);

	fclose(fp);

	return 0;
}

int calculate(position p, FILE* fp) {
	char buffer[MAX_LINE];
	char* pB = buffer;
	float now;
	float x, y;

	while (!feof) {
		fgets(buffer, MAX_LINE, fp);
		if (sscanf(pB, "%f", &now) != 1) {
			switch (*pB) {
			case'+':
				y = pop(p);
				x = pop(p);
				push(x * y, p);
				break;
			case'-':
				y = pop(p);
				x = pop(p);
				push(x * y, p);
				break;
			case'*':
				y = pop(p);
				x = pop(p);
				push(x * y, p);
				break;
			case'/':
				y = pop(p);
				x = pop(p);
				if (y == 0) {
					printf("Postfix not valid!");
					return EXIT_FAIL;
				}
				push(x * y, p);
				break;
			default:
				printf("Postfix not valid!");
				return EXIT_FAIL;
				break;
			}
		}
		else
			push(now, p);
	}

	return 0;
}

int print(position p) {
	int i = 0;
	while (p != NULL)
	{
		printf("%f\n", p->number);
		i++;
		p = p->next;
	}
	return i;
}

int deleteAll(position p) {
	while (p->next != NULL)
		deleteAfter(p);

	return 0;
}