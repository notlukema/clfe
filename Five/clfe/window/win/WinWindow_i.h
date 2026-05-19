#ifndef CLFE_WINDOW_WIN_I_H
#define CLFE_WINDOW_WIN_I_H

#include "../Window_i.h"

#include "clfe/System.h"
#include "clfe/Attachment.h"
#include "clfe/UniString.h"
#include "clfe/SharedLink.h"

#include <Windows.h>

namespace clfe
{

	class WinClass : public InstanceInterface<WinClass>
	{
	private:
		static InstanceList<WinClass>* ClassList;

		static HINSTANCE HInstance;
		static WinClass* DefaultClass;

	public:
		static const Attachment WinWindowAttachment;

		static bool init();
		static void step(float delf, double deld);
		static void terminate();

		static InstanceListHandle<WinClass> getInstanceList()
		{
			return ClassList->getHandle();
		}

		static inline HINSTANCE getHInstance()
		{
			return HInstance;
		}

		static inline WinClass* getDefaultClass()
		{
			return DefaultClass;
		}

		static WinClass* createClass(UniString name, WNDPROC wndProc);
		static WinClass* createClass(UniString name, WNDCLASSEX wndClass);

	private:
		UniString name, className;
		ATOM wClass;

		WinClass(UniString name, UniString className, ATOM wClass);

	public:
		~WinClass();

		inline UniString getName() const
		{
			return name;
		}

		inline UniString getClassName() const
		{
			return className;
		}

		inline ATOM getClassAtom() const
		{
			return wClass;
		}

	};

	inline InstanceListHandle<WinClass> getWinClassList()
	{
		return WinClass::getInstanceList();
	}

	class WinWindow : public Window
	{
	public: // Window processes
		static LRESULT CALLBACK defWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static void step();

	// SharedLink
	private: LinkWell<WinWindow> well;
	public: inline SharedLink<WinWindow>* pullLink() { return well.pull(); }

	private:
		const WinClass* wClass_;
		HWND hwnd_;
		HDC hdc_;

		void createWindow(UniString name, const WinClass* wClass, int x, int y, int width, int height);

		virtual void innerDestroy() override;

	public: // Interface implementations
		WinWindow(UniString name, int x, int y, int width, int height);
		WinWindow(UniString name, const WinClass* wClass, int x, int y, int width, int height);

		virtual ~WinWindow() override;

		inline HWND getHWND() const
		{
			return hwnd_;
		}

		inline HDC getHDC() const
		{
			return hdc_;
		}

		virtual UniString getName() override;
		virtual void setName(UniString name) override;

		virtual int getX() const override;
		virtual int getY() const override;
		virtual Vector2i getPosition() const override;
		virtual void setX(int x) override;
		virtual void setY(int y) override;
		virtual void setPosition(int x, int y) override;
		virtual void setPosition(const Vector2i& pos) override;

		virtual int getWidth() const override;
		virtual int getHeight() const override;
		virtual Vector2i getSize() const override;
		virtual void setWidth(int width) override;
		virtual void setHeight(int height) override;
		virtual void setSize(int width, int height) override;
		virtual void setSize(const Vector2i& size) override;

		virtual void show() override;
		virtual void hide() override;
		virtual void setVisible(bool visible) override;
		virtual bool isVisible() override;

		virtual void minimize() override;
		virtual void unminimize() override;
		virtual void setMinimized(bool minimize) override;
		virtual bool isMinimized() override;

		virtual void maximize() override;
		virtual void unmaximize() override;
		virtual void setMaximized(bool maximize) override;
		virtual bool isMaximized() override;

	};

}

#endif