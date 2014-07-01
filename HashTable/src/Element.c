/**
  * @file Element.c
  * @brief Fichier d'implémentation du module \em Element.
  *
  * @author Alexis BRENON
  */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "Element.h"


/* ** *************************************************************** ** */
/* **  Fonctions de création/initialisation.                          ** */
/* ** *************************************************************** ** */


Element* elementCreate (
			const char* name,
			const char num[5]
			)
{
	Element* Elem = NULL;

	Elem = (Element*) malloc(sizeof(Element));
	elementInit(Elem, name, num);

	return Elem;
}

void elementDestroy (
					Element** ppElem
					)
{
	assert(ppElem != NULL);
	assert(*ppElem != NULL);

	elementRelease(*ppElem);
	free(*ppElem);
	*ppElem = NULL;
}


void elementInit (
			Element* pElem,
			const char* name,
			const char num[5]
			)
{
	int i = 0;

	assert(pElem != NULL);

	pElem->name = (char*) malloc((strlen(name)+1)*sizeof(char));
	strcpy(pElem->name, name);
	pElem->key = pElem->name;

	for (i = 0; i < 5; i++)
	{
		pElem->num[i] = num[i];
	}
}

void elementRelease (
			Element* pElem
			)
{
	int i = 0;

	assert(pElem != NULL);

	free(pElem->name);
	pElem->name = NULL;
	pElem->key = NULL;

	for (i = 0; i < 5; i++)
	{
		pElem->num[i] = 0;
	}
}

void elementCopy (
				Element* pElemDest,
				const Element* pElemSourc
				)
{
	assert (pElemDest != NULL);
	assert (pElemSourc != NULL);

	elementInit(pElemDest,
				pElemSourc->name,
				pElemSourc->num);
}

/* ** *************************************************************** ** */
/* **  Accesseurs/Mutateurs                                           ** */
/* ** *************************************************************** ** */


void elementSetName (
			Element* pElem,
			const char* name
			)
{
	assert (pElem != NULL);

	if (pElem->name != NULL)
	{
		free(pElem->name);
		pElem->name = NULL;
	}
	pElem->name = (char*) malloc(strlen(name)*sizeof(char));
	strcpy(pElem->name, name);
}

const char* elementGetName (
			Element* pElem
			)
{
	assert (pElem != NULL);

	return pElem->name;
}


void elementSetNum (
			Element* pElem,
			const char num[5]
			)
{
	int i = 0;

	assert (pElem != NULL);

	for (i = 0; i < 5; i++)
	{
		pElem->num[i] = num[i];
	}
}

const char* elementGetNum (
			Element* pElem
			)
{
	assert (pElem != NULL);

	return pElem->num;
}


/* ** *************************************************************** ** */
/* **  Fonctions relative à la table de hachage                       ** */
/* ** *************************************************************** ** */

int elementKeyCmp (
			const Key key1,
			const Key key2
			)
{
	char* strKey1 = NULL;
	char* strKey2 = NULL;

	strKey1 = (char*) key1;
	strKey2 = (char*) key2;

	return strcmp(strKey1, strKey2);
}

int elementHashExtraction (
			const Key key,
			int iMax
			)
{
	int p = 0;
	int i = 0, j = 0;
	int iLength = 0;
	int iHashValue = 0;
	const char* strKey = (char*) key;

	/* On calcule le nombre de bit à extraire */
	p = (int) log((double)(iMax+1)) / log(2.);
	/* S'il est supérieur au nombre de bits que l'on peut stocker dans un
	int, on le borne. */
	if (p > sizeof(int)*8)
	{
		p = sizeof(int)*8;
	}

	/* On calcule le nombre de bits à extraire, par caractère */
	iLength = strlen(strKey);
	p = p/iLength;

	/* Pour chaque caractère */
	for (i = 0; i < iLength; i++)
	{
		for (j = 0; j < p; j++)
		{
			/* On ajoute le j-ieme bit (en partant de la fin) à la valeur
			de hachage */
			iHashValue =
				iHashValue |
					(((strKey[i] >> (p-1-j))%2) << (((iLength-i)*p)-j-1));
		}
	}

	return iHashValue;
}



int elementHashCompression (
						const Key key,
						int iMax)
{
	int i = 0;
	int iLength = 0;
	char iHashValue = 0;
	const char* strKey = (char*) key;

	iLength = strlen(strKey);
	for (i = 0; i < iLength; i++)
	{
		iHashValue = iHashValue ^ strKey[i];
	}

	return (int) iHashValue%iMax;
}


int elementHashModulo (
				const Key key,
				int iMax
				)
{
	int i = 0;
	const char* strKey = (char*) key;
	int iLength = 0;
	int iNbCharInInt = 0;
	int* piCharToInt = NULL;
	int iHashValue = 0;

	iLength = strlen(strKey);
	iNbCharInInt = sizeof(int)/sizeof(char);

	/* S'il n'y a pas assez de caractère pour coder un entier complet */
	if (iNbCharInInt > iLength)
	{
		piCharToInt = (int*) malloc(sizeof(int));
		*piCharToInt = 0;
		for (i = 0; i < iLength; i++)
		{
			*piCharToInt = *piCharToInt | strKey[i];
			if (i+1 < iLength)
			{
				*piCharToInt = *piCharToInt << (sizeof(char)*8);
			}
		}
		iHashValue = *piCharToInt%iMax;

		free(piCharToInt);
	}
	else
	{
		/* On associe la codage des NbCharInInt derniers caractères à un entier. */
		piCharToInt = (int*) &(strKey[iLength-1-iNbCharInInt]);
		iHashValue = *piCharToInt%iMax;
	}

	return iHashValue;
}

int elementHashMultiplication(
						const Key key,
						int iMax
						)
{
	int i = 0;
	double q = 0.618033989;
	const char* strKey = (char*) key;
	int iLength = 0;
	int iNbCharInInt = 0;
	int* piCharToInt = NULL;
	double dUnused1;
	int iHashValue = 0;

	iLength = strlen(strKey);
	iNbCharInInt = sizeof(int)/sizeof(char);

	/* S'il n'y a pas assez de caractère pour coder un entier complet */
	if (iNbCharInInt > iLength)
	{
		piCharToInt = (int*) malloc(sizeof(int));
		*piCharToInt = 0;
		for (i = 0; i < iLength; i++)
		{
			*piCharToInt = *piCharToInt | strKey[i];
			if (i+1 < iLength)
			{
				*piCharToInt = *piCharToInt << (sizeof(char)*8);
			}
		}

		iHashValue = (int) (
			modf((((double)(*piCharToInt))*q), &dUnused1)
			*(double)iMax);


		free(piCharToInt);
	}
	else
	{
		/* On associe la codage des NbCharInInt derniers caractères à un entier. */
		piCharToInt = (int*) &(strKey[iLength-1-iNbCharInInt]);
		iHashValue = (int) (
			modf((((double)(*piCharToInt))*q), &dUnused1)
			*(double)iMax);
	}

	return iHashValue;
}
































