#ifndef _NB_COMP
#define _NB_COMP

/* NombreComplexe.H  */
/* Interface du module NombreComplexe offrant le type abstrait Complexe */
/* ainsi qu'un jeu d'opérations, de fonctions et de procédures permettant  */
/* de manipuler les Complexes independamment de leur implantation interne. */

/* Modules importes------------------------------------------------------- */
/* (offrant des types, variables, constantes, procedures */
/* ou fonctions intervenant dans l'interface de NombreComplexe) */

#include "Reel.h" /* Module offrant le type reel */

/*  ----------------------------------------------------------------------- */
/*  Types, variables, constantes, procedures et fonctions exportees */

/* declaration constante globale exportee */
extern const Reel PI;

/* declaration variable globale exportee */
/* (aucune ici) */

/* declaration (et definition!) type exporte */
struct complexe
{
  /* donnees membres (champs) */
  Reel x,y;
};

typedef struct complexe Complexe;

/* --declaration procédures d'initialisation--------------------- */
void initialisationComplexeParDefaut(Complexe *adc); 
/*   Precondition : adc adresse non nulle d'un Complexe non initialise */
/*   Postcondition : le Complexe *adc initialise vaut 0  */
/*                   et le nombre de Complexes "vivants" est incremente de 1 */

void initialisationComplexeParCopie(Complexe *adc, Complexe c);
/* Precondition :  adc adresse non nulle d'un Complexe non initialise */
/* Postcondition : le complexe initialise *adc a la meme valeur que c */
/*                 et le nombre de Complexes vivants est incremente de 1 */

void initialisationComplexe2Reels(Complexe *adc, Reel a, Reel b);
/* Precondition : adc adresse non nulle d'un Complexe non initialise */
/* Postcondition : le complexe *adc initialise vaut a+ib  */
/*                 et le nombre de Complexes vivants est incremente de 1  */


/* --declaration procédures testament --------------------- */
void testament(Complexe *adc);
/* Precondition : adc adresse d'un Complexe prealablement initialise  */
/* Postcondition : le complexe *adc est pret a disparaitre */

/* --declaration procédures affectation --------------------- */ 
void affectationComplexe(Complexe *adc, Complexe c);
/* Precondition : adc adresse d'un Complexe prealablement initialise */
/* Postcondition : le complexe *adc a la meme valeur que c */


/* Addition entre Complexes */
Complexe addition(Complexe c1, Complexe c2);
/* Precondition : c1 et c2 initialises */
/* Resultat : renvoie la somme des complexes codes dans c1 et c2 */

/* Affichage d'un Complexe */
void affiche(Complexe c);
/* Precondition : c initialise */
/* Postcondition : Affichage sur la sortie standard du complexe code dans c */

/* Nombre de Complexes "vivants" */
int nbComplexesVivants();
/* Precondition : aucune */
/* Resultat : renvoie le nombre de Complexes "vivants" au moment de l'appel */

#endif
