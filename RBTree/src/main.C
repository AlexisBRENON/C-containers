// IF5 - Mai 2007 - R. Chaine

#include "element.H"
#include "arbre.H"
#include <cstdio>

int main()
{
  Arbre tilleul;
  initialiseArbre(tilleul);
  insereElement(26,tilleul);
  insereElement(17,tilleul);
  insereElement(34,tilleul);
  insereElement(21,tilleul);
  insereElement(14,tilleul);
  insereElement(30,tilleul);
  insereElement(47,tilleul);
  insereElement(38,tilleul);
  insereElement(39,tilleul);
  insereElement(35,tilleul);
  insereElement(28,tilleul);
  insereElement(23,tilleul);
  insereElement(19,tilleul);
  insereElement(16,tilleul);
  insereElement(10,tilleul);
  insereElement(20,tilleul);
  insereElement(15,tilleul);
  insereElement(7,tilleul);
  insereElement(12,tilleul);
  insereElement(3,tilleul);

  affichageInfixeArbre(tilleul);
  testamentArbre(tilleul);
  return 0;
}
