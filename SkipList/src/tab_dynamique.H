#ifndef _TAB_DYN
#define _TAB_DYN

#include "element.H"


#define CAP_INIT 5

struct TableauDynamique
{
  //donnees membres
  // (ne sont pas censees etre connues par l'utilisateur d'un module :
  //     SI ON AVAIT PU NE PAS LES FAIRE FIGURER DANS L'INTERFACE, on l'aurait fait!)
  unsigned int capacite;
  unsigned int taille_utilisee;
  Element * ad;

  void (*fElementsInit)(Element);
  void (*fElementsCopy)(Element, Element);
  void (*fElementRelease)(Element);
};

void initialisationTabDyn(TableauDynamique &t,
						void (*fElementsInit)(Element),
						void (*fElementsCopy)(Element, Element),
						void (*fElementRelease)(Element));
// Precondition : t non prealablement initialise
// Postcondition : t initialise en tableau vide (taille utilisee nulle)

void initialisationTabDyn(TableauDynamique &t,
						unsigned int capacite_initiale,
						void (*fElementsInit)(Element),
						void (*fElementsCopy)(Element, Element),
						void (*fElementRelease)(Element));
// Precondition : t non prealablement initialise,
// Postcondition : t initialise en tableau vide (taille utilisee nulle),
//                 mais de capacite capacite_initiale

void initialisationTabDyn(TableauDynamique &t1,
						const TableauDynamique &t2);
// Precondition : t1 non prealablement initialise, t2 initialise
// Postcondition : t1 et t2 contiennent des sequence d'Element identiques
//                 (t1 correspond a une copie de t2, les 2 tableaux ont meme capacite,
//                  meme taille utilisee, mais sont independants)

void testamentTabDyn(TableauDynamique &t);
// Precondition : t prealablement initialise
// Postcondition : t pret a disparaitre

void affectationTabDyn(TableauDynamique &t1, const TableauDynamique &t2);
// Precondition : t1 et t2 initialises
// Postcondition : t1 et t2 contiennent des sequence d'Element identiques
//                 (t1 correspond a une copie de t2, les 2 tableaux ont meme capacite,
//                  meme taille utilisee, mais sont independants)

unsigned int tailleUtilisee(const TableauDynamique &t);
//precondition : t prealablement initialise
//resultat : nombre d'Elements stockes dans t

Element valeurIemeElementTableauDynamique(const TableauDynamique &t, unsigned int i);
//precondition : t prealablement initialise, i < tailleUtilisee(t)
//resultat : retourne le i+1eme Element de t

void ajouteElementTableauDynamique(TableauDynamique &t, const Element & e);
//precondition : t prealablement initialise
//postcondition : L'element e est ajoute dans la premiere case inutilisee du tableau,
//                taille utilisee est incrementee de 1
//                Doublement de la capacite de t, si necessaire

void supprimeDernierElement(TableauDynamique & t);
//precondition : t prealablement initialise et non vide
//postcondition : la taille utilisée du tableau est décrémentée de 1


void modifieValeurIemeElementTableauDynamique(TableauDynamique &t, Element e, unsigned int i);
//precondition : t prealablement initialise et i < tailleUtilisee(t)
//postcondition : le i+1eme Element de t vaut e

void insereElementTableauDynamique(TableauDynamique & t, const Element & e, unsigned int i);
//precondition : t prealablement initialise et i < tailleUtilisee(t)
//postcondition : e est insere en i+1 ieme position et tailleUtilisee est incrementee de 1

#endif
