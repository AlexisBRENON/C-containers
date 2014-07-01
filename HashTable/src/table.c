/**
  * @file table.c
  * @brief Fichier d'implémentation du module \em Table de hachage.
  *
  * @author Alexis BRENON
  */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "table.h"
#include "Element.h"



/* ** *************************************************************** ** */
/* **  Fonctions de création/initialisation.                          ** */
/* ** *************************************************************** ** */


Table* tableCreate(
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				)
{
	Table* pTab = NULL;

	pTab = (Table*) malloc(sizeof(Table));
	tableInit(
			pTab,
			m,
			fHash,
			fKeyCmp,
			eRehashType,
			fCopyElement,
			fReleaseElement);

	return pTab;
}

void tableDestroy (
				Table** ppTab
				)
{
	assert(ppTab != NULL);
	assert(*ppTab != NULL);

	tableRelease(*ppTab);
	*ppTab = NULL;
}

void tableInit (
				Table* pTab,
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				)
{
	int i = 0;

	assert (pTab != NULL);

	pTab->parrTab = (Element**) malloc(m*sizeof(Element*));
	pTab->iarrEmpty = (int*) malloc(m*sizeof(int));
	pTab->iMaxSize = m;
	pTab->iUsedSize = 0;
	pTab->fHashFunc = fHash;
	pTab->fKeyCmp = fKeyCmp;
	pTab->eRehashType = eRehashType;

	pTab->fCopy = fCopyElement;
	pTab->fRelease = fReleaseElement;

	for (i = 0; i < pTab->iMaxSize; i++)
	{
		pTab->parrTab[i] = NULL;
		pTab->iarrEmpty[i] = 1; /* 1 = Case vide */
	}
}

void tableRelease (
				Table* pTab
				)
{
	int i = 0;

	assert (pTab != NULL);

	/* Avant de libérer la table, il faut la vider */
	if (pTab->iUsedSize != 0)
	{
		for (i = 0; i < pTab->iMaxSize; i++)
		{
			/* Si on est sur une case non vide */
			if (pTab->parrTab[i] != NULL && pTab->iarrEmpty[i] == 0)
			{
				pTab->fRelease(pTab->parrTab[i]);
				free(pTab->parrTab[i]);
				pTab->parrTab[i] = NULL;
				pTab->iarrEmpty[i] = 1;
			}
		}
		pTab->iUsedSize = 0;
	}

	free(pTab->parrTab);
	pTab->parrTab = NULL;

	free(pTab->iarrEmpty);
	pTab->iarrEmpty = NULL;

	pTab->iMaxSize = 0;
	pTab->fCopy = NULL;
	pTab->fRelease = NULL;
}


/* ** *************************************************************** ** */
/* **  Fonctions de lecture/écriture.                                 ** */
/* ** *************************************************************** ** */


int tableInsert (
				Table* pTab,
				const Element* Elem
				)
{
	Element* pAddedElem = NULL;
	int iIndex = -1;

	printf("Insertion\n");
	assert (pTab != NULL);

	/* On calcule la valeur de hachage correspondant à la clé. */
	iIndex = pTab->fHashFunc(Elem->key, pTab->iMaxSize);
	/* On s'assure que la valeur calculée est entre 0 et la taille max. */
	iIndex = iIndex%pTab->iMaxSize;


	/* Si la position dans le tableau est vide, on stocke */
	if (pTab->iarrEmpty[iIndex] == 1)
	{
		/* On copie l'élément à ajouter (l'utilisateur peut donc supprimer
		sa copie de l'élément) */
		pAddedElem = (Element*) malloc(sizeof(Element));
		pTab->fCopy(pAddedElem, Elem);
		pTab->parrTab[iIndex] = pAddedElem;
		pTab->iUsedSize++;
		pTab->iarrEmpty[iIndex] = 0;
		printf("\tAjouter à l'entrée #%d\n", iIndex);
	}
	/* Sinon, s'il existe un élément avec la même clé */
	else if (
		pTab->fKeyCmp(pTab->parrTab[iIndex]->key, Elem->key) == 0)
	{
		printf("\tL'élément est déja présent.\n");
	}
	/* Sinon, il faut rehacher */
	else
	{
		int iAdded = 0;
		int iRehashTry = 2;
		int iRehashedIndex = (iIndex+1) % pTab->iMaxSize;

		printf("\tRehachage..\n");

		while (iRehashedIndex != iIndex && iAdded == 0 && iRehashTry <= pTab->iMaxSize)
		{
			if (pTab->iarrEmpty[iRehashedIndex] == 1)
			{
				/* On copie l'élément à ajouter (l'utilisateur peut donc
				supprimer sa copie de l'élément) */
				pAddedElem = (Element*) malloc(sizeof(Element));
				pTab->fCopy(pAddedElem, Elem);
				pTab->parrTab[iRehashedIndex] = pAddedElem;
				pTab->iUsedSize++;
				pTab->iarrEmpty[iRehashedIndex] = 0;
				printf("\tAjouter à l'entrée #%d\n", iRehashedIndex);
				iAdded = 1;
			}
			else if (
				pTab->fKeyCmp(
						pTab->parrTab[iRehashedIndex]->key,
						Elem->key) == 0
					)
			{
					printf("\tL'élément est déja présent.\n");
					iAdded = 1;
			}
			else
			{
				switch (pTab->eRehashType)
				{
					case LINEAR_REHASH:
						iRehashedIndex = (iIndex + iRehashTry) % pTab->iMaxSize;
						break;
					case QUADRATIC_REHASH:
						iRehashedIndex =
							(iIndex + (iRehashTry*iRehashTry)) % pTab->iMaxSize;
						break;
					case DOUBLE_HASH:
						iRehashedIndex =
							(iIndex +
							iIndex * iRehashTry)
							% pTab->iMaxSize;
						break;
				}
				iRehashTry++;
			}
		}

		/* Si l'élément n'a pas été ajouté, il y a un problème */
		if (iAdded == 0)
		{
			fprintf(stderr, "Impossible d'ajouter la donnée...\n\
					Il existe déja %d données dans la table qui ne peut\
					en accepter que %d...\n",
					pTab->iUsedSize,
					pTab->iMaxSize);
		}
	}

	return pTab->iUsedSize;
}


int tableRemoveElement (
				Table* pTab,
				const Element* Elem
				)
{
	printf("\nSuppression par Element...\n");

	assert (pTab != NULL);
	assert (Elem != NULL);

	return tableRemoveKey(pTab, Elem->key);
}


int tableRemoveKey (
				Table* pTab,
				const Key key
				)
{
	int iIndex = -1;

	printf("\nSuppression par clé...\n");

	assert (pTab != NULL);

	/* On calcule la valeur de hachage correspondant à la clé. */
	iIndex = pTab->fHashFunc(key, pTab->iMaxSize);
	/* On s'assure que la valeur calculée est entre 0 et la taille max. */
	iIndex = iIndex%pTab->iMaxSize;

	/* Si l'emplacement est NULL, il n'y a jamais rien eu ici, donc on a
	fini de chercher */
	if (pTab->parrTab[iIndex] == NULL)
	{
		printf("\tAucun élément ne correspond...\n");
	}
	/* Sinon, si l'emplacement n'est pas libre ET que les clés sont les
	mêmes. */
	else if (pTab->iarrEmpty[iIndex] == 0 &&
			pTab->fKeyCmp(pTab->parrTab[iIndex]->key, key) == 0)
	{
		pTab->fRelease(pTab->parrTab[iIndex]);
		free(pTab->parrTab[iIndex]);
		pTab->iarrEmpty[iIndex] = 1;
		pTab->iUsedSize--;
		printf("\tElement supprimé à l'emplacement #%d\n", iIndex);
	}
	/* Sinon, soit la case est vide mais libérée (donc possible collisions
	antérieures), soit les clés n'étaient pas les mêmes, on cherche encore.
	*/
	else
	{
		int iFound = 0;
		int iRehashTry = 2;
		int iRehashedIndex = (iIndex+1) % pTab->iMaxSize;

		printf("\tRehachage..\n");

		while (iFound == 0 && iRehashedIndex != iIndex && iRehashTry <= pTab->iMaxSize)
		{
			if (pTab->parrTab[iRehashedIndex] == NULL)
			{
				printf("\tAucun élément ne correspond...\n");
				iFound = 1;
			}
			else if (pTab->iarrEmpty[iRehashedIndex] == 0 &&
					pTab->fKeyCmp(
						pTab->parrTab[iRehashedIndex]->key,
						key) == 0)
			{
				pTab->fRelease(pTab->parrTab[iRehashedIndex]);
				free(pTab->parrTab[iRehashedIndex]);
				pTab->iarrEmpty[iRehashedIndex] = 1;
				pTab->iUsedSize--;
				printf("\tElement supprimé à l'emplacement #%d\n", iRehashedIndex);
				iFound = 1;
			}
			else
			{
				switch (pTab->eRehashType)
				{
					case LINEAR_REHASH:
						iRehashedIndex = (iIndex + iRehashTry) % pTab->iMaxSize;
						break;
					case QUADRATIC_REHASH:
						iRehashedIndex =
							(iIndex + (iRehashTry*iRehashTry)) % pTab->iMaxSize;
						break;
					case DOUBLE_HASH:
						iRehashedIndex =
							(iIndex +
							iIndex * iRehashTry)
							% pTab->iMaxSize;
						break;
				}
				iRehashTry++;
			}
		}
	}

	return pTab->iUsedSize;
}


Element* tableGetElement (
				const Table* pTab,
				const Key key
				)
{
	Element* Elem = NULL;
	int iIndex = -1;

	printf("\nRecherche par clé...\n");

	assert (pTab != NULL);

	/* On calcule la valeur de hachage correspondant à la clé. */
	iIndex = pTab->fHashFunc(key, pTab->iMaxSize);
	/* On s'assure que la valeur calculée est entre 0 et la taille max. */
	iIndex = iIndex%pTab->iMaxSize;

	/* Si l'emplacement est NULL, il n'y a jamais rien eu ici, donc on a
	fini de chercher */
	if (pTab->parrTab[iIndex] == NULL)
	{
		printf("\tAucun élément ne correspond...\n");
	}
	/* Sinon, si l'emplacement n'est pas libre ET que les clés sont les
	mêmes. */
	else if (pTab->iarrEmpty[iIndex] == 0 &&
			pTab->fKeyCmp(pTab->parrTab[iIndex]->key, key) == 0)
	{
		Elem = pTab->parrTab[iIndex];
		printf("\tElement trouvé à l'emplacement #%d\n", iIndex);
	}
	/* Sinon, soit la case est vide mais libérée (donc possible collisions
	antérieures), soit les clés n'étaient pas les mêmes, on cherche encore.
	*/
	else
	{
		int iFound = 0;
		int iRehashTry = 2;
		int iRehashedIndex = (iIndex+1) % pTab->iMaxSize;

		printf("\tRehachage..\n");

		while (iFound == 0 && iRehashedIndex != iIndex && iRehashTry <= pTab->iMaxSize)
		{
			if (pTab->parrTab[iRehashedIndex] == NULL)
			{
				printf("\tAucun élément ne correspond...\n");
				iFound = 1;
			}
			else if (pTab->iarrEmpty[iRehashedIndex] == 0 &&
					pTab->fKeyCmp(
						pTab->parrTab[iRehashedIndex]->key,
						key) == 0)
			{
				Elem = pTab->parrTab[iRehashedIndex];
				printf("\tElement trouvé à l'emplacement #%d\n", iRehashedIndex);
				iFound = 1;
			}
			else
			{
				switch (pTab->eRehashType)
				{
					case LINEAR_REHASH:
						iRehashedIndex = (iIndex + iRehashTry) % pTab->iMaxSize;
						break;
					case QUADRATIC_REHASH:
						iRehashedIndex =
							(iIndex + (iRehashTry*iRehashTry)) % pTab->iMaxSize;
						break;
					case DOUBLE_HASH:
						iRehashedIndex =
							(iIndex +
							iIndex * iRehashTry)
							% pTab->iMaxSize;
						break;
				}
				iRehashTry++;
			}
		}
	}

	return Elem;
}

Element* tableGetElementbyIndex (
				const Table* pTab,
				int i
				)
{
	if (pTab->iarrEmpty[i] == 0)
	{
		return pTab->parrTab[i];
	}
	else
	{
		return NULL;
	}
}


int tableIsEmpty (
				const Table* pTab
				)
{
	assert(pTab != NULL);

	if (pTab->iUsedSize == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int tableGetNbElement (
				const Table* pTab
				)
{
	assert (pTab != NULL);

	return pTab->iUsedSize;
}


int tableMaxSize (
				const Table* pTab
				)
{
	assert(pTab != NULL);

	return pTab->iMaxSize;
}










