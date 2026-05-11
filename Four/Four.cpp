#include <iostream>
#include "clfe/Log.h"

#include "clfe/System.h"
#include "clfe/CLFE.h"

//#include "clfe/pipeline/impl/Pipeline.h"

#include "clm/CLM.h"

#include "clfe/window/Window.h"

#include <cstdlib>
#include "Chrono.h"

#include "FastDraw.h"

#include "clfe/input/KeyTables.h"

#include "clfe/pipeline/Opengl4_6.h"

#include "clfe/Placeholder.h"


#include "clu/Print.h"

using namespace clfe;

int main()
{

    if (!clfe::init()) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");


    Pipeline* pipeline = new Pipeline_OpenGL4_6_Windows();
    pipeline->attachWindow(wnd1);

    std::cout << fastDrawInit((WinWnd*)wnd1) << "-fastdrawinit complete\n";


    while (wnd1->exists())
    {
        float deltaTime = step();
        std::cout << "   delta time: " << deltaTime << "\n";
        std::cout << "   fps: " << 1 / deltaTime << "\n";
        fastDraw((WinWnd*)wnd1, deltaTime);
    }

    clfe::terminate();
    return 0;
}