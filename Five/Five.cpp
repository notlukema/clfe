#include <iostream>
#include "clfe/Log.h"

#include "clfe/System.h"
#include "clfe/CLFE.h"

//#include "clfe/pipeline/impl/Pipeline.h"

#include "clfe/window/Window.h"

#include "Chrono.h"

#include "clfe/input/KeyTables.h"

#include "clfe/pipeline/Vulkan1_4.h"

#include "clfe/object/Model.h"
#include "clfe/object/Material.h"
#include "clfe/object/Texture.h"
#include "clfe/Allocation.h"


#include "clu/Print.h"

using namespace clfe;

int main()
{
    if (!clfe::init(ApplicationInfo("Five", 1, 0, 0)))
    {
        return -1;
    }

    Window* wnd1 = createWindow("thing");

    std::cout << Global::getApplicationInfo().ApplicationName << "\n";

    //Pipeline* pipeline = new Pipeline_Vulkan1_4();
    //pipeline->attachWindow(wnd1);

    //print(pipeline->getData());

    Scene* scene = new Scene();

    Model* rect = createRectModel(100, 100, 100, RedMaterial());

    scene->createObject(rect);

    while (wnd1->exists())
    {
        float deltaTime = step();
        //std::cout << "   delta time: " << deltaTime << "\n";
        //std::cout << "   fps: " << 1 / deltaTime << "\n";

    }

    clfe::terminate();
    return 0;
}