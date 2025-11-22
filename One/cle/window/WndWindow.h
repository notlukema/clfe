#ifndef CLE_WNDWINDOW_H
#define CLE_WNDWINDOW_H

#include "../Window.h"

#include <Windows.h>

#define WDEFAULT CW_USEDEFAULT

namespace cle {
	class WndWindow : public cle::Window {
	private:
		static LRESULT CALLBACK WndProcWrapper(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		bool active_;

		const WCHAR* className;
		HWND hwnd_;
		ATOM class_;

	public:
		LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		const WCHAR* GenClassName(long id);

		WndWindow(int x, int y, int width, int height, const CHAR* name, long id, WNDPROC wndproc = WndProcWrapper);

		bool isActive() const override;
		bool isVisible() const override;
		const char* name() const override;
		const wchar_t* wname() const override;

		int x() const override;
		int y() const override;
		int width() const override;
		int height() const override;

		void x(int x) override;
		void y(int y) override;
		void width(int width) override;
		void height(int height) override;

		void show() override;
		void hide() override;

		HWND hwnd() const {
			return hwnd_;
		}

		~WndWindow() override;
	};
}

#endif