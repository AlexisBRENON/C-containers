/**
  * @brief
  *
  *
  * @author
  * @file
  */


#include "element.H"
#include "cellule.H"

void elementInit(Element Elem)
{
	celluleInit((Cellule*)Elem);
}

void elementRelease (Element Elem)
{
	celluleRelease((Cellule*)Elem);
}

void elementCopy(Element Copy, Element Elem)
{
	celluleCopy((Cellule*)Copy, *(Cellule*)Elem);
}
