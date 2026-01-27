#ifndef CLFE_WINWND_H
#define CLFE_WINWND_H

#include "Window.h"
#include "../../clfe/System.h"
#include "../../clfe/InstanceList.h"
#include "../../clu/StringUtils.h"
#include "../input/KeyTables.h"
#include "../../clfe/CLFE.h"

#include <Windows.h>

namespace clfe
{

	class WinClass // TODO: Add more utility functions here
	{
	private:
		static HINSTANCE hInstance_;
		static WinClass* defaultClass_;
		static InstanceList<WinClass>* classes_;

	public:
		static inline HINSTANCE getHInstance()
		{
			return hInstance_;
		}

		static inline WinClass* getDefaultClass()
		{
			return defaultClass_;
		}

		static WinClass* createClass(const WCHAR* name, WNDPROC wndProc);

		static inline WinClass* createClass(const char* name, WNDPROC wndProc)
		{
			return createClass(toWideString(name), wndProc);
		}

		static Attachment winWndAttachment;
		static bool init();
		static void step(float delf, double deld);
		static void terminate();

	private:
		clid clid_;
		const WCHAR* name_,* className_;
		ATOM wClass_;

		WinClass(clid clid, const WCHAR* name, const WCHAR* className, ATOM wClass);

	public:
		clid getID() const;
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

		HWND getHWND() const;

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