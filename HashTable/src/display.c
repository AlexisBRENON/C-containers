/**
  * @file display.c
  * @brief Fichier d'implémentation du module \em d'affichage.
  *
  * @author Alexis BRENON
  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "display.h"
#include "Element.h"
#include "table.h"


static void HashFuncChoose (
    int iHashFuncAnswer,
    int (**fHashFunc) (const Key, int),
    char** strHashFuncName);
static void RehashTypeChoose (
    int iRehashType,
    enum RehashType* eRehashType);
static void printPerfOutput (Table* pTable);

void printLine (void)
{
    int i = 0;

    for (i = 0; i < 10; i++)
    {
        printf(" ");
    }
    for (i = 10; i < 16; i++)
    {
        printf("-");
    }
    for (i = 16; i < 27; i++)
    {
        printf("%c", 126);
    }
    for (i = 27; i < 46; i++)
    {
        printf("=");
    }
    for (i = 49; i < 60; i++)
    {
        printf("%c", 126);
    }
    for (i = 60; i < 71; i++)
    {
        printf("-");
    }
    printf("\n\n");
}


void printTitle (const char* title)
{
    int length = 0;
    int margin = 0;
    int i = 0;

    printLine();

    length = strlen(title);
    if (length <= 80)
    {
        margin = (80-length)/2;
        for (i = 0; i < margin; i++)
        {
            printf(" ");
        }
        printf("%s\n\n", title);
    }

    printLine();
}

void printManualCreation(Table* pTable)
{
    int iTableSize = 0;
    int iHashFuncAnswer = 0;
    char* strHashFuncName = NULL;
    int (*fHashFunc) (Key, int);
    int iRehashType = 0;
    enum RehashType eRehashType;

    char cContinue = 'O';
    int iNbEntry = 0;

    do
    {
        system("clear");
        printTitle("Bienvenue dans votre annuaire !");

        printf("Combien de contacts allez-vous avoir?\n\t->");
        scanf("%d", &iTableSize);
    }
    while (iTableSize <= 0);

    do
    {
        system("clear");
        printTitle("Bienvenue dans votre annuaire !");
        printf ("\tNb. max. de contact : %d\n\n", iTableSize);

        printf("Quelle fonction de hachage voulez vous?\n");
        printf("\t1/ Extraction?\n");
        printf("\t2/ Compression?\n");
        printf("\t3/ Modulo?\n");
        printf("\t4/ Multiplication?\n");
        printf(" ->");
        scanf("%d", &iHashFuncAnswer);
    }
    while (iHashFuncAnswer < 1 || iHashFuncAnswer > 4);

    HashFuncChoose(iHashFuncAnswer, &fHashFunc, &strHashFuncName);

    do
    {
        system("clear");
        printTitle("Bienvenue dans votre annuaire !");
        printf ("\tNb. max. de contact : %d\n", iTableSize);
        printf ("\tFonction de hachage : %s\n\n", strHashFuncName);

        printf("Quelle type de rehachage voulez vous?\n");
        printf("\t1/ Linéaire?\n");
        printf("\t2/ Quadratique?\n");
        printf("\t3/ Double hachage?\n");
        printf(" ->");
        scanf("%d", &iRehashType);
    }
    while (	iRehashType != 1 &&
			iRehashType != 2 &&
			iRehashType != 3);

    RehashTypeChoose(iRehashType, &eRehashType);

    tableInit(
        pTable,
        iTableSize,
        fHashFunc,
        elementKeyCmp,
        eRehashType,
        elementCopy,
        elementRelease);

    while (cContinue == 'O' && iNbEntry < iTableSize)
    {
        system("clear");
        printTitle("Bienvenue dans votre annuaire !");
        printf ("\tNb. max. de contact : %d\n", iTableSize);
        printf ("\tFonction de hachage : %s\n", strHashFuncName);
        printf ("\tNb d'entrées : %d\n\n", iNbEntry);

        printf("Voulez-vous inserer un contact? (O/n)\n\t");
        scanf("\n%c", &cContinue);

        if (cContinue == 'O')
        {
            iNbEntry = printAdd(pTable);
        }
    }

    free(strHashFuncName);
}

void printAutomaticCreation (Table* pTable)
{
    int iTableSize = 0;
    int iHashFuncAnswer = 0;
    char* strHashFuncName = NULL;
    int (*fHashFunc) (const Key, int);
    int iRehashType = 0;
    enum RehashType eRehashType;
    char cUnused;

    int iContinue = 9;
    int iNbEntry = 0;

    srand(time(NULL));

    printf("Tirage du nombre maximum de contact...\n");
    iTableSize = (rand()%49)+1;
    printf("\tFait.\n\n");

    printf("Tirage aléatoire de la fonction de hachage...\n");
    iHashFuncAnswer = (rand()%4)+1;
    HashFuncChoose(iHashFuncAnswer, &fHashFunc, &strHashFuncName);
    printf("\tFait.\n\n");

    printf("Tirage au sort du type de rehachage...\n");
    iRehashType = (rand()%3)+1;
    RehashTypeChoose(iRehashType, &eRehashType);
    printf("\tFait.\n\n");

    printf("Création de la table...\n");
    tableInit(
        pTable,
        iTableSize,
        fHashFunc,
        elementKeyCmp,
        eRehashType,
        elementCopy,
        elementRelease);
    printf("\tFait.\n\n");

    system("clear");
    printTitle("Bienvenue dans votre annuaire !");
    printf ("\tNb. max. de contact : %d\n", iTableSize);
    printf ("\tFonction de hachage : %s\n", strHashFuncName);
    printf ("\tType de rahachage : %d\n\n", iRehashType);

    while (iContinue >= 1 && iNbEntry < iTableSize)
    {
        iContinue = (rand()%10);

        if (iContinue >= 1)
        {
            Element sElem;
            /** @todo Supprimer ce tableau statique en tableau dynamique,
            ou au moins surveiller que le nom ne fasse pas plus de 50 caractères. */
            char strName[11];
            char strNum[5];
            int i;

            for (i = 0; i < 10; i++)
            {
                strName[i] = (char) ((rand()%('z'-'a'+1))+'a');
            }
            strName[10] = '\0';
            for (i = 0; i < 5; i++)
            {
                strNum[i] = (char) ((rand()%100));
            }
            elementInit(&sElem,
                        strName,
                        strNum);

            iNbEntry = tableInsert(pTable, &sElem);
            elementRelease(&sElem);
        }
    }

    printf("\nFin du remplissage automatique.\n");
    printf("\tNombre de contact(s) ajouté(s) : %d\n\n", iNbEntry);

    free(strHashFuncName);

    scanf("\n%c", &cUnused);
}


void printTable (const Table* pTable)
{
    int iMaxSize = 0;
    int i = 0;
    char cUnused;
    Element* pElem = NULL;

    assert (pTable != NULL);

    system("clear");
    printTitle("Annuaire");

    iMaxSize = tableMaxSize(pTable);
    for (i = 0; i < iMaxSize; i++)
    {
        pElem = tableGetElementbyIndex(pTable, i);
        if (pElem != NULL)
        {
            printf("%03d - %s\t\t\t%02d.%02d.%02d.%02d.%02d\n",
                   i,
                   pElem->name,
                   pElem->num[0],
                   pElem->num[1],
                   pElem->num[2],
                   pElem->num[3],
                   pElem->num[4]);
        }
    }
    scanf("\n%c", &cUnused);
}

void printSearch (const Table* pTable)
{
    char strName[50] = {0};
    char cUnused;
    Element* pElem = NULL;

    assert (pTable != NULL);

    system("clear");
    printTitle("Annuaire");

    printf("Comment s'appelle votre contact?\n ->");
    scanf("\n%s", strName);

    pElem = tableGetElement(pTable, (Key) strName);

    if (pElem != NULL)
    {
        printf("\nVous pouvez joindre %s au numéro suivant:\n", pElem->name);
        printf("\t%02d.%02d.%02d.%02d.%02d\n\n",
               pElem->num[0],
               pElem->num[1],
               pElem->num[2],
               pElem->num[3],
               pElem->num[4]);
    }
    else
    {
        printf("\nDésolé, aucun contact ne correspond...\n\n");
    }

    scanf("\n%c", &cUnused);
}

int printAdd (Table* pTable)
{
    Element sElem;
    /** @todo Supprimer ce tableau statique en tableau dynamique,
    ou au moins surveiller que le nom ne fasse pas plus de 50 caractères. */
    char strName[50];
    int arrNum[5];
    char strNum[5];
    int i;
    int iNbEntry = 0;

    printf("\n");
    printf("Donnez son nom:\n\t");
    scanf("\n%s", strName);
    printf("\nDonnez son numéro: xx xx xx xx xx\n\t");
    scanf("%d %d %d %d %d",
			&(arrNum[0]),
			&(arrNum[1]),
			&(arrNum[2]),
			&(arrNum[3]),
			&(arrNum[4]));
    for (i = 0; i < 5; i++)
    {
        strNum[i] = (char) arrNum[i];
    }
    elementInit(&sElem,
                strName,
                strNum);

    iNbEntry = tableInsert(pTable, &sElem);
    elementRelease(&sElem);

    return iNbEntry;
}

int printDel (Table* pTable)
{
	int iNewNbEntry = 0;
	int iOldNbEntry = 0;
	char strName[50] = {0};
    char cUnused;

    assert (pTable != NULL);

    system("clear");
    printTitle("Annuaire");

    printf("Comment s'appelle votre contact?\n ->");
    scanf("\n%s", strName);

	iOldNbEntry = tableGetNbElement(pTable);
	iNewNbEntry = tableRemoveKey(pTable, (Key) strName);

	if (iOldNbEntry == iNewNbEntry)
	{
		printf("\nDésolé, aucun contact ne correspond...\n\n");
	}
	else
	{
		printf("\nLe contact a été supprimé.\n\n");
	}

    scanf("\n%c", &cUnused);

    return iNewNbEntry;
}

void printPerfTests (Table* pTable)
{
	int iTableSize = 0;
    int iHashFuncAnswer = 0;
    char* strHashFuncName = NULL;
    int (*fHashFunc) (const Key, int);
    int iRehashType = 0;
    enum RehashType eRehashType;
    int insert = 0;
    int iNewNbEntry = 0;
    int iOldNbEntry = 0;

    srand(time(NULL));

    iTableSize = 6007;
    iHashFuncAnswer = 4;
    HashFuncChoose(iHashFuncAnswer, &fHashFunc, &strHashFuncName);

	do
    {
        system("clear");
        printTitle("Bienvenue dans votre annuaire !");
        printf ("\tNb. max. de contact : %d\n", iTableSize);
        printf ("\tFonction de hachage : %s\n\n", strHashFuncName);

        printf("Quelle type de rehachage voulez vous?\n");
        printf("\t1/ Linéaire?\n");
        printf("\t2/ Quadratique?\n");
        printf("\t3/ Double hachage?\n");
        printf(" ->");
        scanf("%d", &iRehashType);
    }
    while (	iRehashType != 1 &&
			iRehashType != 2 &&
			iRehashType != 3);

    RehashTypeChoose(iRehashType, &eRehashType);

    tableInit(
        pTable,
        iTableSize,
        fHashFunc,
        elementKeyCmp,
        eRehashType,
        elementCopy,
        elementRelease);

   for (insert = 1; insert < 5025; insert++)
   {
		Element sElem;
		/** @todo Supprimer ce tableau statique en tableau dynamique,
		ou au moins surveiller que le nom ne fasse pas plus de 50 caractères. */
		char strName[4];
		char strNum[5];
		int i;

		printf("%d\n", insert);
		/* Génère une clé sur 3 caractères choisis parmis 18
		Ce qui donne un peu plus de 5000 clés différentes */
		for (i = 0; i < 3; i++)
		{
			strName[i] = (char) ((rand()%((18+'a')-'a'+1))+'a');
		}
		strName[3] = '\0';
		for (i = 0; i < 5; i++)
		{
			strNum[i] = (char) ((rand()%100));
		}
		elementInit(&sElem,
					strName,
					strNum);

		iNewNbEntry = tableInsert(pTable, &sElem);
		elementRelease(&sElem);

		if ((iNewNbEntry == 1000 ||
			iNewNbEntry == 2000 ||
			iNewNbEntry == 3000 ||
			iNewNbEntry == 4000 ||
			iNewNbEntry == 5000) &&
			iNewNbEntry != iOldNbEntry)
		{
			printPerfOutput(pTable);
		}
		if (iOldNbEntry == iNewNbEntry)
		{
			insert--;
		}
		else
		{
			iOldNbEntry = iNewNbEntry;
		}

    }

    free(strHashFuncName);
}


void RehashTypeChoose (int iRehashType, enum RehashType* eRehashType)
{
    switch (iRehashType)
    {
    case 1:
        *eRehashType = LINEAR_REHASH;
        break;
    case 2:
        *eRehashType = QUADRATIC_REHASH;
        break;
	case 3:
		*eRehashType = DOUBLE_HASH;
		break;
    default:
        *eRehashType = LINEAR_REHASH;
        break;
    }
}


void HashFuncChoose (
    int iHashFuncAnswer,
    int (**fHashFunc) (const Key, int),
    char** strHashFuncName)
{
    switch (iHashFuncAnswer)
    {
    case 1:
        *fHashFunc = elementHashExtraction;
        *strHashFuncName = (char*) malloc((strlen("Extraction")+1)*sizeof(char));
        strcpy(*strHashFuncName, "Extraction");
        break;
    case 2:
        *fHashFunc = elementHashCompression;
        *strHashFuncName = (char*) malloc((strlen("Compression")+1)*sizeof(char));
        strcpy(*strHashFuncName, "Compression");
        break;
    case 3:
        *fHashFunc = elementHashModulo;
        *strHashFuncName = (char*) malloc((strlen("Modulo")+1)*sizeof(char));
        strcpy(*strHashFuncName, "Modulo");
        break;
    case 4:
        *fHashFunc = elementHashMultiplication;
        *strHashFuncName = (char*) malloc((strlen("Multiplication")+1)*sizeof(char));
        strcpy(*strHashFuncName, "Multiplication");
        break;
    default:
        *fHashFunc = elementHashExtraction;
        *strHashFuncName = (char*) malloc((strlen("Extraction")+1)*sizeof(char));
        strcpy(*strHashFuncName, "Extraction");
        break;
    }
}

void printPerfOutput (Table* pTable)
{
	FILE* pFile = NULL;
	int iSearch;
	int iFound = 0;
	clock_t Time1;
	clock_t Time2;

	pFile = fopen("performance.txt", "a");
	assert(pFile != NULL);

	Time1 = clock();
	printf("%ld\n", Time1);

	for (iSearch = 0; iSearch < 5000; iSearch++)
	{
		int i;
		Element* pElem = NULL;
		char strKey[4] = {0};

		for (i = 0; i < 3; i++)
		{
			strKey[i] = (char) ((rand()%((18+'a')-'a'+1))+'a');
		}
		strKey[3] = '\0';
		pElem = tableGetElement(pTable, strKey);
		if (pElem != NULL)
		{
			iFound++;
		}
	}

	Time2 = clock();
	printf("%ld\n", Time2);

	printf("%d trouvé sur %d\n", iFound, tableGetNbElement(pTable));
	fprintf(pFile, "%d %d\n",
			tableGetNbElement(pTable),
			(int) (Time2-Time1));
	fclose(pFile);
}

