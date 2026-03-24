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

using namespace clfe;

int main()
{
    std::cout << "Hello World!\n";

    auto time = std::chrono::high_resolution_clock::now();

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");
    
    wnd1->getInput()->setKeyDownCallback([](Key_t key) {
		// figure out how to filter out repeated key down events
        std::cout << "Key down: " << KeyChars::CharMap[key] << "\n";
	});

    wnd1->getInput()->setKeyUpCallback([](Key_t key) {
        std::cout << "Key up: " << KeyChars::CharMap[key] << "\n";
        });


    // r

    std::cout << fastDrawInit((WinWnd*)wnd1) << "-fastdrawinit complete\n";
    
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

        /*
		std::list<InstanceBase*> instances = System::getInstances();
        for (int i = 0; i < instances.size(); i++)
        {
            InstanceBase* instance = instances[i];

        }
        */
    }

    clfe::terminate();
    return 0;
}
