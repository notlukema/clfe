#include "Window.h"

// Theoretically, the respective window type class should be included at the end of WndWindow

namespace cle {
	std::map<long, cle::Window*> Window::windows;

	Window* cleCreateWindowTrue(int x, int y, int width, int height, const char* name, long id) {
#ifdef CLE_WND
		return new cle::WndWindow(x, y, width, height, name, id);
#else
		return nullptr;
#endif
	}
	Window* cleCreateWindow(int x, int y, int width, int height, std::string name) {
		return cleCreateWindowTrue(x, y, width, height, name.c_str(), Window::genID());
	}

	Window* cleCreateWindow(int x, int y, int width, int height, const char* name) {
		return cleCreateWindowTrue(x, y, width, height, name, Window::genID());
	}
}