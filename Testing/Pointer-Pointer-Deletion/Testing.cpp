#include "stdio.h"
#include <iostream>

struct obj
{
	int f;

	obj(int f) : f(f) {}
};

//int main()
void f()
{
	std::cout << "thing" << std::endl;

	// Testing if deleting a pointer to a pointer to an object will delete the object too

	obj** arr = new obj* [1];
	obj* obj1 = new obj(5);
	arr[0] = obj1;

	std::cout << (*arr[0]).f << std::endl;

	delete arr;

	std::cout << obj1->f; // It does not!

	// It only deletes the pointers, not the object. It will delete the objects if they are directly stored inside the array, however.
}