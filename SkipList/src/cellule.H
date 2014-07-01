#ifndef __CELLULE_HPP__
#define __CELLULE_HPP__

#include "tab_dynamique.H"

struct sCellule
{
	int iValue;
	TableauDynamique tab;
};
typedef struct sCellule Cellule;


void celluleInit (Cellule* psCel);

void celluleInitValue (Cellule* psCel, int iValue);


void celluleRelease (Cellule* psCel);

void celluleCopy (Cellule* psCopy, Cellule psCel);































#endif
