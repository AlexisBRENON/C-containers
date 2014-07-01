
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "liste.h"
#include "Element.h"

void initialiseListeDefaut (Liste* pList)
{
	Cellule* pUnusedCell = NULL;

	assert (pList != NULL);

	pUnusedCell = (Cellule*) malloc(sizeof(Cellule));
	pUnusedCell->suivant = pUnusedCell;

	pList->ad = pUnusedCell;
	pList->nb_elem = 0;
}

/*void initialiseListeCopie (Liste* pList1, Liste List2)
{
	assert(pList1 != NULL);

	initialiseListeDefaut(pList1);
	affectationListe(pList1, List2);
}*/

void testamentListe (Liste* pList, void (*fReleaseElmt)(Element))
{
	assert (pList != NULL);

	videListe(pList, fReleaseElmt);
	free(pList->ad);
	pList->ad = NULL;
}

int testListeVide (Liste List)
{
	if (List.nb_elem == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Element premierElementListe(Liste List)
{
	return ((List.ad)->suivant)->info;
}

Cellule* premiereCelluleListe (Liste List)
{
	return (List.ad)->suivant;
}

Cellule* celluleSuivanteListe(const Cellule* c, Liste List)
{
	return c->suivant;
}

Element elementCelluleListe(const Cellule* c)
{
	return c->info;
}

void affichageListe(Liste List, void (*fAfficheElmt)(Element))
{
	Cellule* pTemp = NULL;

	pTemp = (List.ad)->suivant;
	while (pTemp != List.ad)
	{
		fAfficheElmt(pTemp->info);
		pTemp = pTemp->suivant;
	}
	printf("\n");
}

void ajoutEnTeteListe(Element e, Liste* pList,
					void (*fInitElmt)(Element*),
					void (*fCopyElmt)(Element, Element))
{
	Cellule* pNewCell = NULL;
	Cellule* pFirstCell = NULL;
	Element Elem = NULL;

	assert (pList != NULL);

	fInitElmt(&Elem);
	fCopyElmt(Elem, e);
	pNewCell = (Cellule*) malloc(sizeof(Cellule));
	pNewCell->info = Elem;

	pFirstCell = (pList->ad)->suivant;
	pNewCell->suivant = pFirstCell;
	(pList->ad)->suivant = pNewCell;
	pList->nb_elem++;
}

void suppressionEnTeteListe (Liste* pList,
							void (*fFreeElmt)(Element))
{
	Cellule* pReleasedCell = NULL;

	assert (pList != NULL);

	pReleasedCell = pList->ad->suivant;
	pList->ad->suivant = pReleasedCell->suivant;
	pList->nb_elem--;

	fFreeElmt(pReleasedCell->info);
	free(pReleasedCell);
	pReleasedCell = NULL;
}

void videListe(Liste* pList,
			void (*fFreeElmt)(Element))
{
	assert (pList != NULL);

	while (pList->ad->suivant != pList->ad)
	{
		suppressionEnTeteListe(pList, fFreeElmt);
	}

	pList->nb_elem = 0;
}

void ajoutEnQueueListe(Element e, Liste* pList,
					void (*fInitElmt)(Element*),
					void (*fCopyElmt)(Element, Element))
{
	Cellule* pNewCell = NULL;
	Cellule* pLastCell = NULL;
	Element Elem = NULL;

	assert (pList != NULL);

	fInitElmt(&Elem);
	fCopyElmt(Elem, e);
	pLastCell = pList->ad;
	pLastCell->info = Elem;

	pNewCell = (Cellule*) malloc(sizeof(Cellule));
	pNewCell->info = NULL;
	pNewCell->suivant = pList->ad->suivant;
	pList->ad = pNewCell;

	pLastCell->suivant = pNewCell;

	pList->nb_elem++;
}







































