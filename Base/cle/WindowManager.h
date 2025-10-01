#ifdef CLE_H
#error "CLE.h should be included last"
#endif

#if !defined(CLE_WINDOW_H)
//#warning "WindowManager.h should be included implicity through Window.h"
//#error "WindowManager.h should be included implicity through Window.h"
#endif

#ifndef CLE_WINDOWMANAGER_H
#define CLE_WINDOWMANAGER_H

#include <Windows.h>
#include <vector>

namespace cle {
	class WindowManagerfffffffffffjgfkiu {
	public:
		static bool init() {
			//list = std::vector<class Window*>();
			return true;
		}
		static void registerWindow(class Window* window) {
			//list.push_back(window);
		}
	private:
		//static std::vector<class Window*> list;
	};
}

#endif