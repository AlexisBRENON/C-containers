#ifndef _ELEMENT
#define _ELEMENT


typedef void* Element;

void elementInit(Element Elem);
void elementRelease (Element Elem);

void elementCopy (Element Copy, Element Elem);

#endif
