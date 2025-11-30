#include "Template.h"
#include "Thing.h"

#include <iostream>

int main()
{
	// You have to put the definitions in the header file with the declarations

	int f = 5;
	Template<int>* thing = new Template<int>(f);

	std::cout << thing->getObj() << std::endl;

	std::cout << a::blast(6)->getObj();
}