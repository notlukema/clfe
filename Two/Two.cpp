#include <iostream>
#include "clfe/System.h"
#include "clf/window/Window.h"

#include "clf/math/Mathf.h"
#include "clf/math/vec/Vector.h"
#include "clf/math/vec/Vector2.h"
#include "clf/math/vec/Vector3.h"
#include "clf/math/vec/Vector4.h"

#include "clfe/CLFE.h"

#include "clu/Print.h"

using namespace clfe;
using namespace clu;

template <typename T>
void thig(T val)
{
    std::cout << val << "\n";
}

int main()
{
    std::cout << "Hello World!\n";

    if (!init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");
    Window* wnd2 = createWindow("thing2");
    Window* wnd3 = createWindow("tig");


    Window* wnd12 = createWindow(0, 0, 300, 300, "eat some ethane gas");

    // r


	Vector2f v2f(1.0f, 2.0f);

	//Vector<float, 2>* v = &static_cast<Vector<float, 2>>(v2f);

    print(v2f);


    while (wnd1->exists())
    {
        step();
    }

    clfe::terminate();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
