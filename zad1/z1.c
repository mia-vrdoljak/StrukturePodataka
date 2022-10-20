#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_BROJ_BODOVA (100)

typedef struct {
	char ime[10];
	char prezime[10];
	double bodovi;
}_student;

void ispisStudenata(FILE* fp, _student* s, int n)
{
	int i;
	double relativni;

	for (i = 0; i < n; i++) {
		fscanf(fp, " %s %s %lf\n", s[i].ime, s[i].prezime, &s[i].bodovi);
		relativni = s[i].bodovi / MAX_BROJ_BODOVA * 100;
		printf("Ime i prezime: %s \t%s\t Bodovi: %.2lf\t  Relativni bodovi: %.2lf\n", s[i].ime, s[i].prezime, s[i].bodovi, relativni);
	}
}

int main()
{
	FILE* fp = NULL;
	int filename[MAX_FILE_NAME] = { 0 };
	int count = 0;
	char buffer[MAX_LINE] = { 0 };
	_student* studenti = NULL;
	
	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Nije moguce otvoriti datoteku!");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (feof(fp) != "\n")
		if (strcmp("\n", buffer) != 0)
			count++;

	printf("Broj studenata u datoteci %s je %d", filename, count);

	studenti = (_student*)malloc(count * sizeof(_student));
	if (studenti == NULL)
		printf("Neuspjesna alokacija memorije!");

	rewind(fp);

	ispisStudenata(filename, studenti, count);

	fclose(fp);

	return 0;
}