#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Element.h"
#include "table.h"
#include "display.h"



int main()
{
	Table sTable;

	int iMenuAnswer = 0;

	printf("%d", 'a');

	do
	{
		system("clear");
		printTitle("Bienvenue dans votre annuaire !");

		printf("Voulez-vous...:\n");
		printf("\t1/ Remplir manuellement?\n");
		printf("\t2/ Remplir automatiquement?\n");
		printf("\t3/ Calculer les performances?\n");
		printf(" ->");
		scanf("%d", &iMenuAnswer);
	} while (iMenuAnswer != 1 &&
			 iMenuAnswer != 2 &&
			 iMenuAnswer != 3);


	switch (iMenuAnswer)
	{
		case 1:
			printManualCreation(&sTable);
			break;
		case 2:
			printAutomaticCreation(&sTable);
			break;
		case 3:
			printPerfTests(&sTable);
			break;
		default:
			break;
	}

	while (iMenuAnswer != 9)
	{
		do
		{
			system("clear");
			printTitle("Bienvenue dans votre annuaire !");

			printf("Voulez-vous...:\n");
			printf("\t1/ Afficher l'annuaire?\n");
			printf("\t2/ Rechercher un numero?\n");
			printf("\t3/ Ajouter un contact?\n");
			printf("\t4/ Supprimer un contact?\n\n");
			printf("\t9/ Quitter?\n");
			printf(" ->");
			scanf("%d", &iMenuAnswer);
		} while (iMenuAnswer != 1 &&
				 iMenuAnswer != 2 &&
				 iMenuAnswer != 3 &&
				 iMenuAnswer != 4 &&
				 iMenuAnswer != 9);

		switch (iMenuAnswer)
		{
			case 1:
				printTable(&sTable);
				break;
			case 2:
				printSearch(&sTable);
				break;
			case 3:
				printAdd(&sTable);
				break;
			case 4:
				printDel(&sTable);
			default:
				break;
		}
	}

	tableRelease(&sTable);

	return 0;
}






