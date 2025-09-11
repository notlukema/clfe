#include <iostream>
#include "cle/Window.h"

int main()
{
    std::cout << "Hello World!\n";

    cle::Window* w = new cle::Window(0, 0, 800, 800, "ting");
}
