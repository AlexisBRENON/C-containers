#ifndef __SKIP_LIST_HPP__
#define __SKIP_LIST_HPP__

#include "tab_dynamique.H"
#include "cellule.H"

typedef struct sCellule SkipList;

void skipListInit (SkipList& list);
void skipListRelease (SkipList& list);

Cellule* skipListSearch (SkipList list, int dest);
void skipListAdd (SkipList& list, int data);





































#endif
