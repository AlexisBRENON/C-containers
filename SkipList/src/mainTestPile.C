#include "element.H" //type Element
#include "pile.H" //type pile
#include <cstdio>

int main()
{
  pile p1;
  initialisationPile(p1);
  unsigned int i;
  for (i=0;i<5;i++)
    {
      empile(p1,i);
    }

  pile p2;
  initialisationPile(p2,p1);

  for (i=0;i<5;i++)
    {
      empile(p1,2*i);
    }

  while(!testPileVide(p1))
    {
      std::printf("%d ",sommet(p1));
      depile(p1);
    }
  std::putchar('\n');

  affectationPile(p1,p2);

  while(!testPileVide(p2))
    {
      std::printf("%d ",sommet(p2));
      depile(p2);
    }
  std::putchar('\n');

  while(!testPileVide(p1))
    {
      std::printf("%d ",sommet(p1));
      depile(p1);
    }
  std::putchar('\n');
  testamentPile(p2);
  testamentPile(p1);
  return 0;
}
