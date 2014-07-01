#include "element.H" //offrant le type Elem
#include "arbre.H" //offrant les types Arbre et Noeud
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cstdlib> // NULL

using namespace std;

//- Declaration Fonctions internes-------------------------------------------------------------

static void initialiseNoeud(Noeud &n, const Elem & e);
//Precondition : n non prealablement initialise, e prealablement initialise
//Postcondition : le noeud initialise est un noeud feuille contenant e

static void copyNoeud (Noeud &nDest, const Noeud &nSour);
//Pre : nDest non prealablement initialiser

// Fonction interne utilisee par initialisation par copie
// et operateur d'affectation :
static void copieSSArbre(Noeud * & ad1, Arbre & a1, const Noeud * ad2, const Arbre & a2);
//Precondition : ad2 sous arbre (éventuellement vide) de a2
//               ad1 sous arbre vide de a1
//Postcondition : une copie de ad2 est realisee puis rangee dans ad1
//                en tant que sous arbre de a1

// Fonction interne utilisee par videArbre, elle meme utilisee dans testament
static void detruitAPartirDe(Noeud * &n, Arbre & a);
//precondition : n ss arbre de a, eventuellement vide
//postcondition : le ss arbre n de a est vide

// Fonction interne utilisee par affichageInfixe
static void affichageInfixeDepuisNoeud(const Noeud *n, const Arbre & a, int prof);

// Fonction interne utilisee par insereElement
static void insereElementDansSSArbre(const Elem & e,
									Noeud * &ad, Arbre & a,
									Noeud* parrPath[], int& iEmpty);
//precondition : a non vide et ad ss arbre de a
//               a est un arbre binaire de recherche et l'insertion de e
//               dans le sous-arbre ad ne viole pas la propriete
//               d'arbre binaire de recherche de a
//postcondition : e insere aux feuilles de a
//				  parrPath contient ts les noeud traverses


//Initialisations-------------------------------------------------------------
static void initialiseNoeud(Noeud &n, const Elem & e)
{
	n.color='r';
    n.info=e;
    n.fg=NULL;
    n.fd=NULL;
}

static void copyNoeud (Noeud &nDest, const Noeud &nSour)
{
	nDest.color=nSour.color;
    nDest.info=nSour.info;
    nDest.fg=NULL;
    nDest.fd=NULL;
}

void initialiseArbre(Arbre & a)
{
    a.adracine=NULL;
    a.nb_elem=0;
}

void initialiseArbre(Arbre & a,const Arbre & b)
{
    a.nb_elem=0;
    copieSSArbre(a.adracine,a,b.adracine,b);
}


//Testament---------------------------------------------------------------
void testamentArbre(Arbre & a)
{
    videArbre(a);
    a.nb_elem=0;
}

//Affectation---------------------------------------------------------------
void affectationArbre(Arbre & a,const Arbre & b)
{
    if(&a!=&b) // Eviter le cas d'une autoaffectation
    {
        videArbre(a);
        copieSSArbre(a.adracine,a,b.adracine,b);
    }
}

static void copieSSArbre(Noeud * & ad1, Arbre & a1, const Noeud * ad2, const Arbre & a2)
{
    assert(ad1==NULL);
    if(ad2==NULL)
        ad1=NULL;
    else
    {
        ad1=new Noeud;
        a1.nb_elem++;
        copyNoeud(*ad1, *ad2);
        copieSSArbre(ad1->fg,a1,ad2->fg,a2);
        copieSSArbre(ad1->fd,a1,ad2->fd,a2);
    }
}

bool testArbreVide(const Arbre & a)
{
    return a.adracine==NULL;
}


Elem elementRacine(const Arbre & a)
{
    assert(a.adracine!=NULL);
    return a.adracine->info;
}

Noeud * noeudRacine(Arbre & a)
{
    return a.adracine;
}


Noeud * ssArbreGauche(const Noeud *c, Arbre & a)
{
    return c->fg;
}

Noeud * ssArbreDroit(const Noeud *c, Arbre & a)
{
    return c->fd;
}

Elem elementNoeud(const Noeud * c)
{
    return c->info;
}

static void affichageInfixeDepuisNoeud(const Noeud *n, const Arbre & a,int prof)
{
    if (n!=NULL)
    {
        affichageInfixeDepuisNoeud(n->fg,a,prof+1);
        putchar('\t');
        for (int i=0; i<prof; i++)
            cout << "\t";
		cout << n->color << " ";
        afficheElement(n->info);
        putchar('\n');
        affichageInfixeDepuisNoeud(n->fd,a,prof+1);
    }
}

void affichageInfixeArbre(const Arbre & a)
{
    printf("Nombre d'elements : %d \n",a.nb_elem);
    affichageInfixeDepuisNoeud(a.adracine,a,0);
    putchar('\n');
}

static void detruitAPartirDe(Noeud * & n, Arbre & a)
{
    if (n!=NULL)
    {
        detruitAPartirDe(n->fg,a);
        detruitAPartirDe(n->fd,a);
        delete(n);
        n=NULL;
    }
}

void videArbre(Arbre & a)
{
    detruitAPartirDe(a.adracine,a);
    a.nb_elem=0;
}

static void insereElementDansSSArbre(const Elem & e,
									Noeud * &ad, Arbre & a,
									Noeud* parrPath[], int& iEmpty)
{
    if(ad==NULL)
    {
        a.nb_elem++;
        ad=new Noeud;
        initialiseNoeud(*ad,e);
        if (ad == a.adracine)
        {
        	ad->color = 'n';
        }
        iEmpty--;
        parrPath[iEmpty] = ad;
    }
    else if (!estSuperieurOuEgal(e,ad->info))
    {
    	parrPath[iEmpty] = ad->fg;
    	iEmpty++;
        insereElementDansSSArbre(e,
								ad->fg,a,
								parrPath, iEmpty);
    }
    else
    {
    	parrPath[iEmpty] = ad->fd;
    	iEmpty++;
        insereElementDansSSArbre(e,
								ad->fd,a,
								parrPath, iEmpty);
    }
}

void insereElement(const Elem & e, Arbre & a)
{
	Noeud** parrPath = NULL;
	int iEmpty = 0;

	Noeud* pQ = NULL;
	Noeud* pP = NULL;
	Noeud* pPP = NULL;
	Noeud* pO = NULL;

	parrPath = (Noeud**) malloc((a.nb_elem + 1)*sizeof(Noeud*));
	parrPath[0] = a.adracine;
	iEmpty++;

    insereElementDansSSArbre(e,a.adracine,a, parrPath, iEmpty);

	while (iEmpty > 1)
	{
		pP = parrPath[iEmpty-1];
		if (pP->color == 'n')
		{
			iEmpty = 0;
		}
		else
		{
			pQ = parrPath[iEmpty];
			pPP = parrPath[iEmpty-2];
			pO = pPP->fd;
			if (pO == pP)
			{
				pO = pPP->fg;
			}

			if (pO != NULL && pO->color == 'r')
			{
				pP->color = 'n';
				pO->color = 'n';
				pPP->color = 'r';
				iEmpty -= 2;
			}
			else
			{
				Noeud* pAPP = NULL;
				Noeud* p = NULL;

				if (iEmpty > 2)
				{
					pAPP = parrPath[iEmpty-3];
				}

				if (pP->fg == pQ && pPP->fg == pP)
				// Q est le fils gauche du fils gauche
				{
					p = pP->fd;
					pP->fd = pPP;
					if (pAPP != NULL && pAPP->fd == pPP)
					{
						pAPP->fd = pP;
					}
					else if (pAPP != NULL && pAPP->fg == pPP)
					{
						pAPP->fg = pP;
					}
					else
					{
						a.adracine = pP;
					}
					pPP->fg = p;

					pP->color = 'n';
					pPP->color = 'r';

					iEmpty = 0;
				}
				else if (pP->fd == pQ && pPP->fg == pP)
				// Q est le fils droit du fils gauche
				{
					p = pQ->fg;
					pQ->fg = pP;
					pPP->fg = pQ;
					pP->fd = p;

					p = pP;
					pP = pQ;
					pQ = pP;

					p = pP->fd;
					pP->fd = pPP;
					if (pAPP != NULL && pAPP->fd == pPP)
					{
						pAPP->fd = pP;
					}
					else if (pAPP != NULL && pAPP->fg == pPP)
					{
						pAPP->fg = pP;
					}
					else
					{
						a.adracine = pP;
					}
					pPP->fg = p;

					pP->color = 'n';
					pPP->color = 'r';

					iEmpty = 0;
				}
				else if (pP->fd == pQ && pPP->fd == pP)
				// Q est le fils droit du fils droit de PP
				{
					p = pP->fg;
					pP->fg = pPP;
					if (pAPP != NULL && pAPP->fg == pPP)
					{
						pAPP->fg = pP;
					}
					else if (pAPP != NULL && pAPP->fd == pPP)
					{
						pAPP->fd = pP;
					}
					else
					{
						a.adracine = pP;
					}
					pPP->fd = p;

					pP->color = 'n';
					pPP->color = 'r';

					iEmpty = 0;
				}
				else if (pP->fd == pQ && pPP->fg == pP)
				// Q est le fils gauche du fils droit
				{
					p = pQ->fd;
					pQ->fd = pP;
					pPP->fd = pQ;
					pP->fg = p;

					p = pP;
					pP = pQ;
					pQ = pP;

					p = pP->fg;
					pP->fg = pPP;
					if (pAPP != NULL && pAPP->fd == pPP)
					{
						pAPP->fd = pP;
					}
					else if (pAPP != NULL && pAPP->fg == pPP)
					{
						pAPP->fg = pP;
					}
					else
					{
						a.adracine = pP;
					}
					pPP->fd = p;

					pP->color = 'n';
					pPP->color = 'r';

					iEmpty = 0;
				}
			}
		}
	}

	a.adracine->color = 'n';
	free(parrPath);
}

