#ifndef CLE_WINDOW_H
#define CLE_WINDOW_H

#include <string>
#include <windows.h>

namespace cle {
	class Window {
	protected:
		HWND hwnd;
		int x, y, width, height;
		bool active;
	public:
		static const WCHAR* toWChar(const CHAR* str);
		Window(int x, int y, int width, int height, std::string name);
		Window(int x, int y, int width, int height, std::wstring name);
		Window(int x, int y, int width, int height, const CHAR* name);
		Window(int x, int y, int width, int height, const WCHAR* name);
		HWND gethwnd() const;
		bool isActive() const;
	};
}

#endif