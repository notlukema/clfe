#include "Window.h"

// Theoretically, the respective window type class should be included at the end of WndWindow

namespace cle {
	std::map<long, cle::Window*> Window::windows;

	inline Window* cleCreateWindowTrue(int x, int y, int width, int height, const char* name, long id) {
#ifdef CLE_WND
		return new cle::WndWindow(x, y, width, height, name, id);
#else
		return nullptr;
#endif
	}
}