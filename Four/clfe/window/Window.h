#ifndef CLFE_WINDOW_H
#define CLFE_WINDOW_H

#include "clfe/CrossPlatform.h"
#include "clfe/Attachment.h"
#include "clfe/System.h"
#include "clfe/input/InputCore.h"
#include "Function.h"

namespace clfe
{

	static const int WindowDefault = -1; // Any negative (invalid) parameters will be treated as default values

	class Window
	{
	private:
		static InstanceList<Window>* WindowsList;

	public:
		static const Attachment WindowAttachment;
		static InstanceListWrapper<Window>* getWindowsList();

		static bool init();
		static void step(float delf, double deld);
		static void terminate();

	protected:
		clid thisid;
		InstanceLink<Window>* instanceLink;

		InputCore* inputCore;

		Window(clid id);
		void instanceDelete();

		virtual void innerDestroy() = 0;

		//Function<void()> CloseCallback;
		// + others

	public:
		virtual ~Window();
		clid getID() const;

		InputCore* getInput() const;
		
		inline bool exists() const
		{
			return instanceLink != nullptr;
		}

		inline void destroy() const
		{
			if (exists())
			{
				delete instanceLink;
			}
		}

		virtual int getX() const = 0;
		virtual int getY() const = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void setX(int x) = 0;
		virtual void setY(int y) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void setVisible(bool visible) = 0;
		virtual bool isVisible() = 0;

		inline const char* const getName()
		{
			return getNameNarrow();
		}
		virtual const char* getNameNarrow() = 0;
		virtual const wchar_t* getNameWide() = 0;
		virtual void setName(const char* name) = 0;
		virtual void setName(const wchar_t* name) = 0;

		// Other stuff later
		// Vector position finding with vec2 and stuff
		// Icons, cursors, fullscreen, borderless, resizable, etc.
	};

	Window* createWindow(int x, int y, int width, int height, const char* name);
	Window* createWindow(int x, int y, int width, int height, const wchar_t* name);

	inline Window* createWindow(const char* name, int x = WindowDefault, int y = WindowDefault, int width = WindowDefault, int height = WindowDefault)
	{
		return createWindow(x, y, width, height, name);
	}

	inline Window* createWindow(const wchar_t* name, int x = WindowDefault, int y = WindowDefault, int width = WindowDefault, int height = WindowDefault)
	{
		return createWindow(x, y, width, height, name);
	}

}

// Header guards defend against include loops if user chooses to include a platform-specific header directly instead
#if defined(CLFE_OS_WIN)
#include "WinWnd.h"

#elif defined(CLFE_OS_MAC)
//#include "MacWnd.h"

#elif defined(CLFE_OS_LNX)
//#include "LnxWnd.h"

#else
#warning "Windowing system not implemented for this OS!"

#endif

#endif