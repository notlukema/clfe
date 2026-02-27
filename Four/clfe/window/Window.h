#ifndef CLFE_WINDOW_H
#define CLFE_WINDOW_H

#include "../CrossPlatform.h"
#include "../Attachment.h"

namespace clfe
{

	static const int WND_DEFAULT = -1; // Any negative (invalid) parameters will be treated as default values

	class Window
	{
	public: // Static functions
		static Attachment WindowAttachment;
		static bool init();
		static void step(float delf, double deld);
		static void terminate();

	public:
		Window(); // Remove eventually if not needed
		virtual ~Window() = 0;

		virtual bool exists() const = 0;
		virtual void destroy() = 0;

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

	inline Window* createWindow(const char* name, int x = WND_DEFAULT, int y = WND_DEFAULT, int width = WND_DEFAULT, int height = WND_DEFAULT)
	{
		return createWindow(x, y, width, height, name);
	}

	inline Window* createWindow(const wchar_t* name, int x = WND_DEFAULT, int y = WND_DEFAULT, int width = WND_DEFAULT, int height = WND_DEFAULT)
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
#warning "Windowing system not implemented for this OS! Or did you forget to include System.h?"

#endif

#endif