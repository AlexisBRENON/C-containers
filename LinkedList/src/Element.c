
#include <stdlib.h>
#include <stdio.h>

#include "NombreComplexe.h"
#include "Element.h"


void InitEltInt(Element* e1)
{
	(*e1) = malloc(sizeof(int));
	*((int*)(*e1)) = 0;
}

void InitEltCplx(Element* e1)
{
	*e1 = (Complexe*) malloc(sizeof(Complexe));
	(*(Complexe*)*e1).x = 0;
	(*(Complexe*)*e1).y = 0;
}


void ReleaseEltInt(Element e1)
{
	free(e1);
	e1 = NULL;
}

void ReleaseEltCplx(Element e1)
{
	free(e1);
	e1 = NULL;
}


void CopyEltInt (Element e1, Element e2)
{
	*(int*)e1 = *(int*)e2;
}

void CopyEltCplx (Element e1, Element e2)
{
	(*(Complexe*)e1).x = (*(Complexe*)e2).x;
	(*(Complexe*)e1).y = (*(Complexe*)e2).y;
}

int CompareEltInt(Element e1, Element e2)
{
	if (*(int*)e1 > *(int*)e2)
	{
		return -1;
	}
	else if (*(int*)e1 == *(int*)e2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CompareEltCplx (Element e1, Element e2)
{
	if ((*(Complexe*)e1).x > (*(Complexe*)e2).x)
	{
		return -1;
	}
	else if ((*(Complexe*)e1).x == (*(Complexe*)e2).x)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void AfficheEltInt (Element e1)
{
	printf("%d\n", *(int*)e1);
}

void AfficheEltCplx(Element e1)
{
	printf("%d + %di\n", (int) (*(Complexe*)e1).x, (int) (*(Complexe*)e1).y);
}














