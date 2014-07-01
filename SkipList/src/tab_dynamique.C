#include "element.H"
#include "tab_dynamique.H"
#include <cstdlib> // NULL
#include <cassert> // assert
#include <cstdio> // fprintf

void initialisationTabDyn(TableauDynamique &t,
						void (*fElementsInit)(Element),
						void (*fElementsCopy)(Element, Element),
						void (*fElementRelease)(Element))
{
  initialisationTabDyn(	t,
						CAP_INIT,
						fElementsInit,
						fElementsCopy,
						fElementRelease);
}

void initialisationTabDyn(	TableauDynamique &t,
							unsigned int capacite_initiale,
							void (*fElementsInit)(Element),
							void (*fElementsCopy)(Element, Element),
							void (*fElementRelease)(Element))
{
  t.ad=new Element[capacite_initiale];
  if(t.ad==NULL)
    {std::fprintf(stderr,"Espace memoire insuffisant\n");exit(2);}
  t.capacite=capacite_initiale;
  t.taille_utilisee=0;
  t.fElementsInit = fElementsInit;
}

void initialisationTabDyn(TableauDynamique &t1, const TableauDynamique &t2)
{
  t1.ad=new Element[t2.capacite];
  if(t1.ad==NULL)
    {std::fprintf(stderr,"Espace memoire insuffisant\n");exit(2);}
  t1.capacite=t2.capacite;
  t1.taille_utilisee=t2.taille_utilisee;
  for(unsigned int i=0;i<t2.taille_utilisee;i++)
    elementCopy(t1.ad[i], t2.ad[i]);
}

void testamentTabDyn(TableauDynamique &t)
{
  for(unsigned int i=0;i<t.taille_utilisee;i++)
    elementRelease(t.ad[i]);
  delete [] t.ad;
  t.ad=NULL;
}

void affectationTabDyn(TableauDynamique &t1, const TableauDynamique &t2)
{
  if(&t1!=&t2)
    {
      delete [] t1.ad;
      t1.ad=new Element[t2.capacite];
      if(t1.ad==NULL)
	{std::fprintf(stderr,"Espace memoire insuffisant\n");exit(2);}
      t1.capacite=t2.capacite;
      t1.taille_utilisee=t2.taille_utilisee;
      for(unsigned int i=0;i<t2.taille_utilisee;i++)
	elementCopy(t1.ad[i], t2.ad[i]);
    }
}

unsigned int tailleUtilisee(const TableauDynamique & t)
{
  return t.taille_utilisee;
}

Element valeurIemeElementTableauDynamique(const TableauDynamique &t, unsigned int i)
{
  return t.ad[i];
}

void ajouteElementTableauDynamique(TableauDynamique &t, const Element & e)
{
  if(t.taille_utilisee==t.capacite)
    {
      Element *temp=t.ad;
      t.ad=new Element[2*t.capacite];
      if(t.ad==NULL)
	{std::fprintf(stderr,"Espace memoire insuffisant\n");exit(2);}
      t.capacite*=2;
      for (unsigned int i=0;i<t.taille_utilisee;i++)
	elementCopy(t.ad[i], temp[i]);
      delete [] temp;
    }
  t.ad[t.taille_utilisee]=e;
  t.taille_utilisee++;
}

void supprimeDernierElement(TableauDynamique & t)
{
  elementRelease(t.ad[(t.taille_utilisee)-1]);
  t.taille_utilisee--;
}

void  modifieValeurIemeElementTableauDynamique(TableauDynamique &t, Element e, unsigned int i)
{
  elementCopy(t.ad[i], e);
}

void insereElementTableauDynamique(TableauDynamique & t, const Element & e, unsigned int i)
{
  if(t.taille_utilisee>0)
    ajouteElementTableauDynamique(t,t.ad[t.taille_utilisee-1]);
  for(unsigned int j=t.taille_utilisee-1;j>i;j--)
    elementCopy(t.ad[j], t.ad[j-1]);
  elementCopy(t.ad[i], e);
}
