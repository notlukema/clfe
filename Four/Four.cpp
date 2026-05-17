#include <iostream>
#include "clfe/Log.h"

#include "clfe/System.h"
#include "clfe/CLFE.h"

//#include "clfe/pipeline/impl/Pipeline.h"

#include "clm/CLM.h"

#include "clfe/window/Window.h"

#include "Chrono.h"

#include "clfe/input/KeyTables.h"

//#include "clfe/pipeline/Vulkan1_4.h"

#include "clfe/Placeholder.h"


#include "clu/Print.h"

using namespace clfe;

int main()
{
	ApplicationInfo appInfo("Four", 1, 0, 0);
    if (!clfe::init(appInfo)) {
        return -1;
    }

    Window* wnd1 = createWindow("thing");

    std::cout << Global::getApplicationInfo().ApplicationName << "\n";


    //Pipeline* pipeline = new Pipeline_Vulkan1_4();
    //pipeline->attachWindow(wnd1);

    //print(pipeline->getData());

    while (wnd1->exists())
    {
        float deltaTime = step();
        //std::cout << "   delta time: " << deltaTime << "\n";
        //std::cout << "   fps: " << 1 / deltaTime << "\n";

    }

    clfe::terminate();
    return 0;
}