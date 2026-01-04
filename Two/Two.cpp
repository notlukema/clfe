#include <iostream>
#include "clfe/System.h"
#include "clf/window/Window.h"

#include "clf/math/Mathf.h"
#include "clf/math/vec/Vector.h"
#include "clf/math/vec/Vector2.h"
#include "clf/math/vec/Vector3.h"
#include "clf/math/vec/Vector4.h"

#include "clf/math/mat/Matrix.h"

#include "clfe/CLFE.h"

#include "clu/Print.h"

#include <cstdlib>

using namespace clfe;
using namespace clu;

int main()
{
    std::cout << "Hello World!\n";

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");
    Window* wnd2 = createWindow("thing2");
    Window* wnd3 = createWindow("tig");


    Window* wnd12 = createWindow(0, 0, 300, 300, "eat some ethane gas");

    // r
    /*
    Vector2<float> vec2f_1(1.0f);
    print(vec2f_1);
    Vector<3, double> vec3i_1(3, 4, -15);
    print(vec3i_1);

    Vector<3, double> vec_1 = vec2f_1 + vec3i_1;
	Vector2f vec2_1 = operator+(vec2f_1, Vector2f(5.0f, 6.0f));
    print(vec_1);
    print(vec2_1);

    std::cout << "LINE SPLIT\n";

	Vector2f vec2f_2(2.5f, 3.0f);
	vec2f_2 += Vector2f(1.5f, -1.0f);
    print(vec2f_2);

    print(vec2f_2 / 0.15f);
    print(vec2f_2);

    std::cout << "LINE SPLIT\n";
    */

    const int f[] = {5, 2, 5};
    Vector2<int> vec2i(f);
    print(vec2i);

    const int size = 12;
    for (int i = 0; i < 100; i++) {
        int arr[size];
        std::cout << "arr(" << size << "): {";
        for (int j = 0; j < size; j++) {
            arr[j] = std::rand() % 2001 - 1000;
            std::cout << arr[j];
            if (j < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}\n";

        std::cout << "size comp: " << sizeof(arr) << " vs " << sizeof(Vector<size, int>(arr));

        std::cout << "\n\n";
    }


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
