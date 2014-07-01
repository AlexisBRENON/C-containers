#include "Element.h"
#include "NombreComplexe.h"
#include "liste.h"

int main (void)
{
	Liste l;
	Element Elem;
	int i = 15;

	initialiseListeDefaut(&l);
	InitEltInt(&Elem);
	AfficheEltInt(Elem);
	CopyEltInt(Elem, &i);
	AfficheEltInt(Elem);
	for (i = 0; i < 15; i++)
	{
		ajoutEnTeteListe(&i, &l, InitEltInt, CopyEltInt);
		ajoutEnTeteListe(Elem, &l, InitEltInt, CopyEltInt);
	}

	affichageListe(l, AfficheEltInt);

	testamentListe(&l, ReleaseEltInt);
	ReleaseEltInt(Elem);

	return 0;
}
