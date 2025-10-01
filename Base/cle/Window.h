#ifndef CLE_WINDOW_H
#define CLE_WINDOW_H

#include <string>

namespace cle {
	class Window {
	private:
	protected:
		int x, y, width, height;
		bool active;
	public:
		/*
		Window(int x, int y, int width, int height, std::string name);
		Window(int x, int y, int width, int height, std::wstring name);
		Window(int x, int y, int width, int height, const CHAR* name);
		Window(int x, int y, int width, int height, const WCHAR* name);
		*/

		bool isActive() const {
			return active;
		}

		// create destructor to free items such as the name
	};
}

#if defined(_WIN32) || defined(_WIN64)
// Make sure Window class is defined beforehand
#include "window/WndWindow.h"
#endif

#endif