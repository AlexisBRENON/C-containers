#ifndef _ARBRE
#define _ARBRE

#include "element.H" //offrant le type Elem, les fonctions afficheElement
// et estSuperieurOuEgal

struct Noeud
{
	char color;
    Elem info;
    Noeud * fg;
    Noeud * fd;
};

struct Arbre
{
    //Donnees membres-----------------------------------------------------------
    Noeud * adracine;
    int nb_elem;
};

//Initialisations-------------------------------------------------------------

void initialiseArbre(Arbre & a);
//Precondition : a non prealablement initialise
//Postcondition : a est vide

void initialiseArbre(Arbre & a,const Arbre & b);
//Precondition : a non prealablement initialise, b prealablement initialise
//Postcondition : a et b correspondent a des arbres identiques
//                (mais ils sont totalement independants l'un de l'autre)
//                (a copie de b-)

//Testament---------------------------------------------------------------
void testamentArbre(Arbre & a);
//Precondition : a prealablement initialise
//Postcondition : a pret a disparaitre (ne doit plus etre utilise)

//Affectation---------------------------------------------------------------
void affectationArbre(Arbre & a,const Arbre & b);
//Precondition : a et b prealablement initialises
//Postcondition : a et b correspondent a des arbres identiques
//                (mais ils sont totalement independants l'un de l'autre)
//                (a copie de b-)

bool testeArbreVide(const Arbre & a);
//Precondition : aucune
//               (a initialise et manipule uniquement a travers les
//                operations du module)
//Resultat : true si a est vide, false sinon

Elem elementRacine(const Arbre & a);
//Precondition : testArbreVide(a)==false
//Resultat : valeur de l'Elem contenu dans le noeud racine

Noeud * noeudRacine(Arbre & a);
//Precondition : aucune
//               (a initialise et manipule uniquement a travers les
//                operations du module)
//Resultat : adresse du noeud racine de a si testArbreVide(a)==false
//           O sinon
//           Attention : l'arbre a pourra ensuite etre modifie a travers
//           la connaissance de l'adresse de son noeud racine

Noeud * ssArbreGauche(const Noeud *c, Arbre & a);
//Precondition : c adresse valide d'un Noeud de l'arbre a
//Resultat : adresse de noeud racine du ss arbre gauche de *c
//           O sinon
//           Attention : l'arbre a pourra ensuite etre modifie a travers
//           la connaissance de l'adresse d'un de ses noeuds

Noeud * ssArbreDroit(const Noeud *c, Arbre & a);
//Precondition : c adresse valide d'un Noeud de l'arbre a
//Resultat : adresse de noeud racine du ss arbre droit de *c
//           O sinon
//           Attention : l'arbre a pourra ensuite etre modifie a travers
//           la connaissance de l'adresse d'un de ses noeuds

Elem elementNoeud(const Noeud * c);
//Precondition : c adresse valide d'un Noeud d'un Arbre
//Resultat : valeur de l'Elem contenu dans le Noeud

void affichageInfixeArbre(const Arbre & a);
//Precondition : aucune
//               (a initialise et manipule uniquement a travers les
//                operations du module)
//Postcondition : Affichage prefixe de tous les elements de a

void videArbre(Arbre & a);
//Precondition : aucune
//               (a initialise et manipule uniquement a travers les
//                operations du module)
//Postcondition : a est vide

void insereElement(const Elem & e, Arbre & a);
//Precondition : a est un arbre binaire de recherche
//               (a et e initialises et manipules uniquement a travers les
//                operations de leurs modules respectifs)
//Postcondition : L'Elem e est ajoute dans l'arbre binaire de recherche a
//                au niveau d'une feuille

#endif
