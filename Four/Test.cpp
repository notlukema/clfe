#include <iostream>

#include "clfe/object/Object.h"

using namespace clfe;

void printPos(Object* obj)
{
	std::cout << "Object position: (" << obj->getX() << ", " << obj->getY() << ", " << obj->getZ() << ")\n";
}

int mainf()
{

	Object* obj = new Object(5.0f, -12.0f, 3);
	printPos(obj);

	Vector3f f = obj->getPosition();
	f.x(10);
	printPos(obj);

	Vector3f newPos = Vector3f(1, 2, 3);
	obj->setPosition(newPos);
	newPos += 5;
	printPos(obj);

	obj->getPositionRef() *= 5;
	printPos(obj);

	std::cout << "Hello World!\n";
	return 0;
}