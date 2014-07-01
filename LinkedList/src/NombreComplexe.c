/*  NombreComplexe.c */
/*  Implantation du module NombreComplexe offrant le type Complexe */
/*  -> implantation des operations, procedures et fonctions  */
/*     permettant de manipuler des Complexes, */
/*  -> implantation des variables et constantes globales  */
/*      offertes par le module */


/*  Modules utilises dans l'implantation */
#include <stdio.h>
#include "Reel.h" /* offrant le type Reel */

/* On rajoute : */
#include "NombreComplexe.h" /* contenant la definition du type Complexe */

/*  Definition constantes globales exportees  */
/*  ie. qui pourront etre utilisees dans d'autres modules  */
/*  s'ils importent le module NombreComplexe */
const Reel PI=3.1425;

/*  Definition variables globales exportees  */
/*  Aucune ici */

/*  Definition d'une variable globale non exportee */
/*  (Utilisable uniquement dans le module NombreComplexe) */
static int nbComplexe=0;

void initialisationComplexeParDefaut(Complexe *adc)
{
  adc->x=adc->y=0;
  nbComplexe++;
}

void initialisationComplexeParCopie(Complexe *adc, Complexe c)
{
  adc->x=c.x; adc->y=c.y;  
  nbComplexe++;  
}

void initialisationComplexe2Reels(Complexe *adc, Reel a, Reel b)
{
  adc->x=a;adc->y=b;
  nbComplexe++;
}

void testament(Complexe *adc)
{
  nbComplexe--;  
}

void affectationComplexe(Complexe *adc,Complexe c)
{
  if (adc!=&c)
    {
      adc->x=c.x;
      adc->y=c.y;
    }
}

Complexe addition(Complexe c1,Complexe c2)
{
  Complexe res; 
  /*pas d'appel a initialisation comme on ne pourra pas invoquer testament*/
  res.x=c1.x+c2.x;
  res.y=c1.y+c2.y;  
  return res;
}

void affiche(Complexe c)
{
  printf("Affichage %f+i*%f \n",c.x,c.y);
}

int nbComplexesVivants()
{
  return nbComplexe;
}
