
#include "cellule.H"
#include "element.H"

void celluleInit (Cellule* psCel)
{
	psCel->iValue = 0;
	initialisationTabDyn(
		psCel->tab,
		elementInit,
		elementCopy,
		elementRelease);
}

void celluleRelease (Cellule* psCel)
{
	testamentTabDyn(psCel->tab);
}

void celluleCopy (Cellule* psCopy, Cellule psCel)
{
	psCopy->iValue = psCel.iValue;
	initialisationTabDyn(psCopy->tab, psCel.tab);
}
