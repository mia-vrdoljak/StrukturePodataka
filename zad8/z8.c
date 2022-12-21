#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
	int el;
	Position left;
	Position right;
}Tree;

int menu(Position);
int addElement();
int printInorder();
int printPreorder();
int printPostodrer();
int printLevelOrder();
int deleteElement();
int findElement();
int freeTree();

int main(int argc, char** argv)
{
	Position Root = (Position)malloc(sizeof(Tree));
	if (Root != NULL) {
		Root->left = NULL;
		Root->right = NULL;

		while (1)
			menu(&Root);
	}

	freeTree(Root->right);

	return 0;
}

int menu(Position p) {
	char choice;
	
	printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
		"\t\t\tIZBORNIK\n\n"
		"\ta) unos novog elemente\n"
		"\tb) ispis stabla\n"
		"\tc) brisanje elementa\n"
		"\td) trazenje elementa\n"
		"\tx) izlaz\n\n"
		"Vas odabir: ");

	scanf(" %c", &choice);

	switch (tolower(choice))
	{
	case 'a':
		printf("\nUnesite vrijednost koju zelite dodati u stablo: ");
		addElement(&p);
		break;
	case 'b':
		printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
			"\t\ttKako zelite ispisati stablo?\n\n"
			"\ta) inorder\n"
			"\tb) preorder\n"
			"\tc) postorder\n"
			"\td) level order\n"
			"Vas odabir: ");

		scanf(" %c", &choice);

		switch (tolower(choice))
		{
		case 'a':
			printInorder(&p);
			break;
		case 'b':
			printPreorder(&p);
			break;
		case 'c':
			printPostodrer(&p);
			break;
		case 'd':
			printLevelOrder(&p);
			break;
		}

		break;
	case 'c':
		deleteElement(&p);
		break;
	case 'd':
		findElement(&p);
		break;
	case 'x':
		printf("Dovidenja!");
		return 0;
		break;
	default:
		printf("Pogresan odabir.");
		break;
	}
}

int addElement(Position p) {

}

int printInorder(Position p) {

}

int printPreorder(Position p) {

}

int printPostodrer(Position p) {

}

int printLevelOrder(Position p) {

}

int deleteElement(Position p) {

}

int findElement(Position p);

int freeTree(Position p);