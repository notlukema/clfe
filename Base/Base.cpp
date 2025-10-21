#include <iostream>

#include "cle/Window.h"
#include "cle/CLE.h"

int main()
{
    std::cout << "Start\n";

    cle::init();
    
    cle::Window* w = cle::cleCreateWindow(WDEFAULT, WDEFAULT, 600, 600, "ting");
    cle::Window* w2 = cle::cleCreateWindow(800, 500, 700, 150, "window number 2");

	std::cout << "TEST windows name: " << w->name() << ", " << w2->name() << "\n";


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // Translates virtual-key messages into character messages
        DispatchMessage(&msg);  // Dispatches the message to the window procedure
    }
    return (int)msg.wParam;
}
