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
    print((vec2i.normalized() * 12));

    Matrix<3, 3, float> mat33f(
        1.0f, 2.0f, 3.0f,
        0.0f, 1.0f, 4.0f,
        5.0f, 6.0f, 0.0f
	);
    print(mat33f);
    mat33f.transpose();
    print(mat33f);

    std::cout << "\nLINE SPLIT\n\n";

    Matrix<2, 4, float> mat24f(
		{ 1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f }
	);
    print(mat24f);
	auto mat42f = mat24f.transposed();
	print(mat42f);


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
