#include <iostream>
#include "clfe/Log.h"

#include "clfe/System.h"
#include "clfe/CLFE.h"

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

    std::cout << fastDrawInit((WinWnd*)wnd1) << "-fastdrawinit complete\n";


    //a
    /*
    Placeholder* a = new Placeholder([]() {
        std::cout << "init\n";
     }, nullptr, []() {
         std::cout << "term\n";
     });

    Placeholder* b = new Placeholder(nullptr, nullptr, nullptr);
    Placeholder* c = new Placeholder(nullptr, nullptr, nullptr);
    Placeholder* d = new Placeholder(nullptr, nullptr, nullptr);

    print(Window::getWindowsList());
    print(Placeholder::getPlaceholderList());

    delete a;
    delete d;
    delete c;

    print(Placeholder::getPlaceholderList());
    */
    //a

    // test stringutils

    const char* f = "Hello World!";
    std::cout << strLen(f) << "\n";
    const char* f2 = concatStr(f, " oof");
    std::cout << f2 << " - " << strlen(f2) << "\n";

    const char* funky = cutStr(f2, 0, 10);
    std::cout << funky << " - " << strlen(funky) << "\n";


    while (wnd1->exists())
    {
        float deltaTime = step();
        fastDraw((WinWnd*)wnd1, deltaTime);
    }

    clfe::terminate();
    return 0;
}
