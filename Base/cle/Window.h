#ifndef CLE_WINDOW_H
#define CLE_WINDOW_H

#include "CrossPlatform.h"

#include <string>
#include <map>

namespace cle {
	class Window {
	private:
		const long id_;

	protected:
		bool active_;
		int x_, y_, width_, height_;

	public:
		Window(long id) : id_(id) {
			windows.insert({ id, this });
		}

		long id() const {
			return id_;
		}

		bool isActive() const {
			return active_;
		}

		virtual bool isVisible() const = 0;
		virtual const char* name() const = 0;

		int x() const {
			return x_;
		}

		int y() const {
			return y_;
		}

		int width() const {
			return width_;
		}

		int height() const {
			return height_;
		}

		virtual void x(int x) = 0;
		virtual void y(int y) = 0;
		virtual void width(int width) = 0;
		virtual void height(int height) = 0;
		virtual void show() = 0;
		virtual void hide() = 0;

		virtual ~Window() {
			windows.erase(id_);
		}

	private: // Static methods
		static std::map<long, Window*> windows;

	public:
		static void init() {
			windows = std::map<long, Window*>();
		}

		static long genID() {
			// Placeholder
			return (long)rand();
		}

		static Window* findWindow(long id) {
			auto it = windows.find(id);
			if (it != windows.end()) {
				return it->second;
			}
			return nullptr;
		}
	};

	Window* cleCreateWindowTrue(int x, int y, int width, int height, const char* name, long id);

	Window* cleCreateWindow(int x, int y, int width, int height, std::string name);
	Window* cleCreateWindow(int x, int y, int width, int height, const char* name);
	// TODO: Add creation functions for wide strings
}

#ifdef CLE_WND
#include "window/WndWindow.h"
#endif
/*
#ifndef WDEFAULT
#define WDEFAULT 0
#endif
*/

#endif