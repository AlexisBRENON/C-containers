#include "element.H" //type Element
#include "tab_dynamique.H" //type TableauDynamique
#include <cstdio>

int main()
{
  unsigned int i;
  TableauDynamique tata;
  initialisationTabDyn(tata,3);
  for (i=0;i<10;i++)
    {
      ajouteElementTableauDynamique(tata,i);
    }
  TableauDynamique toto;
  initialisationTabDyn(toto,tata);
  for (i=0;i<10;i++)
    {
      ajouteElementTableauDynamique(toto,2*i);
    }
  std::printf("Affichage tata\n");
  for (i=0;i<tailleUtilisee(tata);i++)
    {
      std::printf("%d ",valeurIemeElementTableauDynamique(tata,i)); 
    }
  std::putchar('\n');
  std::printf("Affichage toto\n");
  for (i=0;i<tailleUtilisee(toto);i++)
    { 
      std::printf("%d ",valeurIemeElementTableauDynamique(toto,i)); 
    }  
  std::putchar('\n');
  affectationTabDyn(tata,toto);
  insereElementTableauDynamique(tata,55,tailleUtilisee(tata)-2);
  modifieValeurIemeElementTableauDynamique(tata,56,2);
  std::printf("Affichage tata\n");
  for (i=0;i<tailleUtilisee(tata);i++)
    { 
      std::printf("%d ",valeurIemeElementTableauDynamique(tata,i)); 
    }  
  std::putchar('\n');
  testamentTabDyn(toto);
  testamentTabDyn(tata);
  return 0;
}
