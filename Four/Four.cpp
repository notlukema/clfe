#include <iostream>
#include "clfe/System.h"
#include "clfe/CLFE.h"

#include "clm/CLM.h"

#include "clfe/window/Window.h"

#include "clu/Print.h"

#include <cstdlib>
#include "Chrono.h"

#include "FastDraw.h"

#include "clfe/input/KeyTables.h"

#include "clfe/pipeline/Opengl4_6.h"

using namespace clfe;

int main()
{
    std::cout << "Hello World!\n";

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");
    
    wnd1->getInput()->setKeyDownCallback([wnd1](Key_t key) {
        std::cout << "Key down: " << KeyChars::getChar(key) << " ";
	});

    wnd1->getInput()->setRepeatedKeyDownCallback([](Key_t key) {
        std::cout << KeyChars::getChar(key);
    });

    wnd1->getInput()->setKeyUpCallback([](Key_t key) {
        std::cout << "\nKey up: " << KeyChars::getChar(key) << "\n";
    });

    // f

    Pipeline* pipeline = new Pipeline_OpenGL4_6_Windows();

    std::cout << fastDrawInit((WinWnd*)wnd1) << "-fastdrawinit complete\n";
    
    // Timer, currently unused
    static auto time = chrono::HighResClock::now();

    while (wnd1->exists())
    {
        float deltaTime = step();
        fastDraw((WinWnd*)wnd1, deltaTime);
    }

    clfe::terminate();
    return 0;
}
