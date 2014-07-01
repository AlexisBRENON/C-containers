#ifndef __ELEMENT_H__
#define __ELEMENT_H__

typedef void* Element;

void InitEltInt (Element* e1);
void InitEltCplx (Element* e1);

void ReleaseEltInt (Element e1);
void ReleaseEltCplx (Element e1);

void CopyEltInt (Element e1, Element e2);
void CopyEltCplx (Element e1, Element e2);

int CompareEltInt (Element e1, Element e2);
int CompareEltCplx (Element e1, Element e2);

void AfficheEltInt (Element e1);
void AfficheEltCplx (Element e1);

#endif
