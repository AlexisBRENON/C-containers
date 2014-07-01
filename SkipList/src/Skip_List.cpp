/**
  * @brief
  *
  *
  * @author
  * @file
  */

#define PROBA 0.5f

#include <stdlib.h>

#include "Skip_List.H"
#include "tab_dynamique.H"
#include "cellule.H"

void skipListInit (SkipList& list)
{
	initialisationTabDyn(list.tab,
						elementInit,
						elementCopy,
						elementRelease);
	list.iValue = 0;
}


void skipListRelease (SkipList& list)
{
	Cellule* p = NULL;
	Cellule* p1 = NULL;

	p = (Cellule*) valeurIemeElementTableauDynamique(list.tab, 0);
	while (p != NULL)
	{
		p1 = p;
		p = (Cellule*) valeurIemeElementTableauDynamique(p->tab, 0);
		celluleRelease(p1);
		free(p1);
	}
	testamentTabDyn(list.tab);
	list.iValue = 0;
}

Cellule* skipListSearch (SkipList list, int dest)
{
	int etage = 0;
	Cellule* p1 = NULL;
	Cellule* p2 = NULL;

	etage = (list.iValue)-1;
	if (etage == -1) /* Aucun étage ==> Aucune valeur */
	{
		return NULL;
	}
	else
	{
		p1 = (Cellule*) &list;
		p2 = (Cellule*) valeurIemeElementTableauDynamique(p1->tab, etage);
		while (etage >= 0)
		{
			while (p2 != NULL && p2->iValue < dest)
			{
				p1 = p2;
				p2 = (Cellule*) valeurIemeElementTableauDynamique(p1->tab, etage);
			}
			etage--;
		}
	}

	if (p1->iValue == dest)
	{
		return p1;
	}
	else
	{
		return NULL;
	}
}

void skipListAdd (SkipList& list, int data)
{
	int etage = 0;
	TableauDynamique tab;
	Cellule* p1 = NULL;
	Cellule* p2 = NULL;

	initialisationTabDyn(tab, elementInit, elementCopy, elementRelease);

	etage = (list.iValue)-1;

	if (etage == -1) /* Aucune donnée */
	{
		Element elem;
		int nouveletage = 0;

		elem = (Cellule*) malloc(sizeof(Cellule));
		elementInit(elem);
		((Cellule*)elem)->iValue = data;
		ajouteElementTableauDynamique(((Cellule*)elem)->tab, NULL);
		ajouteElementTableauDynamique(list.tab, elem);
		while ((rand()%100) <= PROBA)
		{
			Element elem2;
			nouveletage++;

			elem2 = (Cellule*) malloc (sizeof(Cellule));
			ajouteElementTableauDynamique(((Cellule*)elem)->tab, elem2);
			ajouteElementTableauDynamique(list.tab, elem);
		}
		list.iValue = nouveletage+1;
	}
	else
	{
		while (etage >= 0)
		{
			p1 = (Cellule*) &list;
			p2 = (Cellule*) valeurIemeElementTableauDynamique(p1->tab, etage);
			while (p2 != NULL && p2->iValue < data)
			{
				p1 = p2;
				p2 = (Cellule*) valeurIemeElementTableauDynamique(p1->tab, etage);
			}
			ajouteElementTableauDynamique(tab, (Element) p1);
			etage--;
		}
		Element elem = NULL;
		Cellule* previous = NULL;
		unsigned int nouveletage = 0;

		elem = (Cellule*) malloc(sizeof(Cellule));
		elementInit(elem);
		((Cellule*)elem)->iValue = data;

		nouveletage = 0;
		previous = (Cellule*) valeurIemeElementTableauDynamique(tab, 0);
		ajouteElementTableauDynamique(
			((Cellule*)elem)->tab,
			valeurIemeElementTableauDynamique(previous->tab, 0));
		modifieValeurIemeElementTableauDynamique(previous->tab, elem, 0);

		while ((rand()%100) <= PROBA)
		{
			nouveletage++;
			if (nouveletage < tailleUtilisee(tab))
			{
				previous = (Cellule*) valeurIemeElementTableauDynamique(
											tab,
											nouveletage);
				ajouteElementTableauDynamique(
					((Cellule*)elem)->tab,
					valeurIemeElementTableauDynamique(
									previous->tab,
									nouveletage));
				modifieValeurIemeElementTableauDynamique(
						previous->tab, elem, nouveletage);
			}
			else
			{
				(list.iValue)++;
				previous = (Cellule*) &list;
				ajouteElementTableauDynamique(
					((Cellule*)elem)->tab,
					NULL);
				ajouteElementTableauDynamique(previous->tab, elem);
			}
		}
	}

}
































