#ifndef CLFE_WINWND_H
#define CLFE_WINWND_H

#include "Window.h"
#include "../../clu/StringUtils.h"
// ARTIFACT1: Should already be included by System.h and Window.h
#include "../../clfe/ISteppable.h"

#include <Windows.h>

namespace clfe
{

	class WinClass // TODO: Add more utility functions here
	{
	private:
		static WinClass* defaultClass_;
		static WinClass** classes_;
		static int classCount, arrLen;
		static HINSTANCE hInstance_;

	public:
		static inline WinClass* getDefaultClass()
		{
			return defaultClass_;
		}

		static WinClass* createClass(const WCHAR* name, WNDPROC wndProc);

		static inline WinClass* createClass(const char* name, WNDPROC wndProc)
		{
			return createClass(clu::toWideString(name), wndProc);
		}

		static void init();
		static void terminate();

	private:
		const WCHAR* name_,* className_;
		ATOM wClass_;

		WinClass(const WCHAR* name, const WCHAR* className, ATOM wClass);

	public:
		const WCHAR* getName() const;
		const WCHAR* getClassName() const;
		ATOM getClassAtom() const;
		~WinClass();

	};

	class WinWnd : public Window
	{
	public: // Window processes
		static LRESULT CALLBACK defWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static void step();

	private:
		const WinClass* wClass_;
		HWND hwnd_;

		void createWindow(int x, int y, int width, int height, const WCHAR* name, const WinClass* wClass);

	public: // Interface implementations
		WinWnd(int x, int y, int width, int height, const char* name);
		WinWnd(int x, int y, int width, int height, const WCHAR* name);
		WinWnd(int x, int y, int width, int height, const char* name, const WinClass* wClass);
		WinWnd(int x, int y, int width, int height, const WCHAR* name, const WinClass* wClass);

		virtual ~WinWnd() override;

		virtual bool exists() const override;
		virtual void destroy() override;

		virtual int getX() const override;
		virtual int getY() const override;
		virtual int getWidth() const override;
		virtual int getHeight() const override;

		virtual void setX(int x) override;
		virtual void setY(int y) override;
		virtual void setWidth(int width) override;
		virtual void setHeight(int height) override;

		virtual void show() override;
		virtual void hide() override;
		virtual void setVisible(bool visible) override;
		virtual bool isVisible() override;

		virtual const char* getNameNarrow() override;
		virtual const WCHAR* getNameWide() override;
		virtual void setName(const char* name) override;
		virtual void setName(const WCHAR* name) override;

	};

}

#endif