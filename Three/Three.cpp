#include <iostream>
#include "clfe/System.h"
#include "clf/window/Window.h"

#include "clm/CLM.h"

#include "clfe/CLFE.h"

#include "clu/Print.h"
#include "clfe/string/UniString.h"

#include <cstdlib>
#include <chrono>

#include "FastDraw.h"

using namespace clfe;

int main()
{
    std::cout << "Hello World!\n";

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");

    // r

	std::cout << fastDrawInit((WinWnd*)wnd1) << "-complete\n";

    static auto lastTime = std::chrono::steady_clock::now();

    while (wnd1->exists())
    {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = currentTime - lastTime;
        lastTime = currentTime;
        double deltaTime = duration.count();
        //std::cout << deltaTime << "\n";

        step();
        fastDraw((WinWnd*)wnd1, (float)deltaTime);
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
