#include <iostream>
#include "clfe/Log.h"

#include "clfe/System.h"
#include "clfe/CLFE.h"

//#include "clfe/pipeline/impl/Pipeline.h"

#include "clfe/window/Window.h"

#include "Chrono.h"

#include "clfe/input/KeyTables.h"

#include "clfe/pipeline/Vulkan1_4.h"

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

    Texture<5, float>* tex = new Texture<5, float>(2, 2);
    std::cout << tex->channels() << "\n";
    tex->set(0, 0, 0.0f, 0.1f, 0.2f, 0.3f, 0.4f);
    print(tex->get(0, 0));

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