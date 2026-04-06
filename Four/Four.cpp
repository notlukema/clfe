#include <iostream>
#include "clfe/System.h"
#include "clfe/CLFE.h"

#include "clm/CLM.h"

#include "clfe/window/Window.h"

#include "clu/Print.h"
#include "clfe/string/UniString.h"

#include <cstdlib>
#include <chrono>

#include "FastDraw.h"

#include "clfe/input/KeyTables.h"

using namespace clfe;

int main()
{
    std::cout << "Hello World!\n";

    auto time = std::chrono::high_resolution_clock::now();

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");
    
    wnd1->getInput()->setKeyDownCallback([wnd1](Key_t key) { // TODO: decide whether to use std::function or just function pointers
		// figure out how to filter out repeated key down events
        std::cout << "Key down: " << KeyChars::CharMap[key] << " ";

        // funky lambda stuff
        if (key == Key::W)
        {
			//wnd1->setY(wnd1->getY() - 10);
        }
        if (key == Key::S)
        {
            //wnd1->setY(wnd1->getY() + 10);
        }
        if (key == Key::A)
        {
            //wnd1->setX(wnd1->getX() - 10);
        }
        if (key == Key::D)
        {
            //wnd1->setX(wnd1->getX() + 10);
        }
	});

    wnd1->getInput()->setRepeatedKeyDownCallback([](Key_t key) {
        std::cout << KeyChars::CharMap[key];
    });

    wnd1->getInput()->setKeyUpCallback([](Key_t key) {
        std::cout << "\nKey up: " << KeyChars::CharMap[key] << "\n";
    });

    // r

    std::cout << fastDrawInit((WinWnd*)wnd1) << "-fastdrawinit complete\n";
    
    // Timer, currently unused
    static auto lastTime = std::chrono::steady_clock::now();

    while (wnd1->exists())
    {
        float deltaTime = step();
        fastDraw((WinWnd*)wnd1, deltaTime);

    }

    clfe::terminate();
    return 0;
}
