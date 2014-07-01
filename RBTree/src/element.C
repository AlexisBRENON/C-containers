#include <iostream>
#include "element.H"

void afficheElement(const Elem & e)
{
	std::cout.width(2);
    std::cout << e;
}

bool estSuperieurOuEgal(const Elem & e1,const Elem & e2)
{
    return (e1<e2?false:true);
}
