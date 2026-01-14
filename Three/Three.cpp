#include <iostream>
#include "clfe/System.h"
#include "clf/window/Window.h"

#include "clm/CLM.h"

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


    std::cout << "LINE SPLIT\n";


    Matrix<2, 2, float> mat22f(
        1.0f, 2.0f,
        3.0f, 4.0f
	);

    print(mat22f);

    mat22f.transpose();

    print(mat22f);

    Matrix<3, 3, float> mat33f(
        5, 5, 5,
        2, 1, 3,
        7, 4, 2
    );
    print(mat33f);
    std::cout << mat33f.determinant() << "\n";


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
