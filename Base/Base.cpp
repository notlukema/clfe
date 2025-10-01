#include <iostream>
//#include "cle/WindowManager.h"
#include "cle/Window.h"
#include "cle/CLE.h"
int main()
{
    std::cout << "Start\n";

    cle::init();

    cle::Window* w = new cle::WndWindow(WDEFAULT, WDEFAULT, 600, 600, "ting");
    cle::Window* w2 = new cle::WndWindow(800, 500, 700, 150, "window number 2");

    // TODO: create base abstraction class for windows, then rename current window to "WndWindow" 
    // The others will be "MacWindow" and "LnxWindow" or maybe "X11Window"/"WylWindow"

    // Remove windowmanager and rename as Window class, then derive it from an option of the different OS window classes
	// Note: use preprocessor directives to change which OS window class is used to derive from
    // This makes a base abstraction windows class unnecessary but it can greatly organize code and make sure each class contains the correct functions

    // github copilot is so nosy with code suggestions lol


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // Translates virtual-key messages into character messages
        DispatchMessage(&msg);  // Dispatches the message to the window procedure
    }
    return (int)msg.wParam;
}
