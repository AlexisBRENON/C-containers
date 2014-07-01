#include <stdio.h>
#include <stdlib.h>

#include "Skip_List.H"


int main (void)
{
	SkipList sl;
	Cellule* p;


	printf("Initialisation...\n");
	skipListInit(sl);
	printf("\tDone.\n\n");

	printf("Add '5'...\n");
	skipListAdd(sl, 5);
	printf("Add '7'...\n");
	skipListAdd(sl, 7);
	printf("Add '2'...\n");
	skipListAdd(sl, 2);
	printf("Add '6'...\n");
	skipListAdd(sl, 6);
	printf("Add '3'...\n");
	skipListAdd(sl, 3);
	printf("\tDone.\n\n");

	printf("Search '6'\n");
	p = skipListSearch(sl, 6);
	printf("\t6 is at : %lX\n", (unsigned long int) p);
	printf("\tDone.\n\n");

	printf("Search '4'\n");
	p = skipListSearch(sl, 6);
	printf("\t4 is at : %lX\n", (unsigned long int) p);
	printf("\tDone.\n\n");

	printf("Release...\n");
	skipListRelease(sl);
	printf("\tDone.\n\n");

	return 0;
}
