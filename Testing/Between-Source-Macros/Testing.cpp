// MACRO_1 changes the typedef for this source file, but the source file defining b::func doesn't have this macro, resulting in a different-type function

//#define MACRO_1

#include "a/TypeDefine.h"
#include "b/thingamajig.h"

#include <iostream>

//int main()
void f()
{
    std::cout << "Hello World!\n";

    std::cout << b::func(5);
}
