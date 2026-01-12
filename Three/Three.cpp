#include <iostream>
#include "clfe/System.h"
#include "clf/window/Window.h"

#include "clm/vec/Vector.h"
#include "clm/vec/Vector2.h"
#include "clm/vec/Vector3.h"
#include "clm/vec/Vector4.h"

#include "clm/mat/Matrix.h"

#include "clfe/CLFE.h"

#include "clu/Print.h"

#include <cstdlib>

using namespace clfe;

int main()
{
    std::cout << "Hello World!\n";

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");

    // r

    
    Vector2<float> vec2f(1.0f);
    print(vec2f);

    Matrix<2, 3, int> mat23i(
        5, 9, 12,
        5, 8, -89
    );
    print(mat23i);

    print(mat23i + Matrix<4, 4, float>(5));

    std::cout << "LINE SPLIT\n";




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
