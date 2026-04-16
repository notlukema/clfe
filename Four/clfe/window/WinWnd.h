#ifndef CLFE_WINWND_H
#define CLFE_WINWND_H

#include "Window.h"
#include "clu/StringUtils.h"

#include <Windows.h>

namespace clfe
{

	class WinClass
	{
	private:
		static InstanceList<WinClass>* Classes;

		static HINSTANCE HInstance;
		static WinClass* DefaultClass;

	public:
		static const Attachment WinWndAttachment;

		static bool init();
		static void step(float delf, double deld);
		static void terminate();

		static InstanceListHandle<WinClass> getClassesList()
		{
			return Classes->getHandle();
		}

		static inline HINSTANCE getHInstance()
		{
			return HInstance;
		}

		static inline WinClass* getDefaultClass()
		{
			return DefaultClass;
		}

		static WinClass* createClass(const WCHAR* name, WNDPROC wndProc);

		static inline WinClass* createClass(const char* name, WNDPROC wndProc)
		{
			return createClass(toWideString(name), wndProc);
		}

	private:
		clid thisid;
		InstanceHandle<WinClass>* instlink;

		const WCHAR* name,* className;
		ATOM wClass;

		WinClass(clid id, const WCHAR* name, const WCHAR* className, ATOM wClass);

	public:
		inline clid getID() const
		{
			return thisid;
		}

		~WinClass();

		inline const WCHAR* getName() const
		{
			return name;
		}

		inline const WCHAR* getClassName() const
		{
			return className;
		}

		inline ATOM getClassAtom() const
		{
			return wClass;
		}

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

		virtual void innerDestroy() override;

	public: // Interface implementations
		WinWnd(int x, int y, int width, int height, const char* name);
		WinWnd(int x, int y, int width, int height, const WCHAR* name);
		WinWnd(int x, int y, int width, int height, const char* name, const WinClass* wClass);
		WinWnd(int x, int y, int width, int height, const WCHAR* name, const WinClass* wClass);

		virtual ~WinWnd() override;

		inline HWND getHWND() const
		{
			return hwnd_;
		}

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