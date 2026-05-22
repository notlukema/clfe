#ifndef CLFE_WINDOW_I_H
#define CLFE_WINDOW_I_H

#include "clfe/System.h"
#include "clfe/Attachment.h"
#include "clfe/UniString.h"

#include "clfe/input/InputCore.h"

#include "clm/VectorImpl.h"

#include "Function.h"

namespace clfe
{

	static const int WindowDefault = -1; // Any negative (invalid) parameters will be treated as default values

	class Window : public InstanceInterface<Window>
	{
	private:
		static const Attachment WindowAttachment;
		static InstanceList<Window>* WindowList;

	public:
		static bool init();
		static void step(float delf, double deld);
		static void terminate();

		static inline InstanceListHandle<Window> getInstanceList()
		{
			return WindowList->getHandle();
		}

	protected:
		Window();

		bool exists_;
		bool destroyRequested;
		InputCore* inputCore;

		virtual void innerDestroy() = 0;

		// bool return decides whether or not the window closes
		Function<bool()> CloseCallback;
		Function<void(int x, int y)> MoveCallback;
		Function<void(int width, int height)> ResizeCallback;
		//Function<void(bool visible)> VisibilityCallback;
		// bool return decides whether or not to do action
		Function<bool(bool minimized)> MinimizeCallback;
		// bool return decides whether or not to do action
		Function<bool(bool maximized)> MaximizeCallback;

	public: // Callbacks
		void setCloseCallback(Function<bool()> callback);
		void setMoveCallback(Function<void(int x, int y)> callback);
		void setResizeCallback(Function<void(int width, int height)> callback);
		//void setVisibilityCallback(Function<void(bool visible)> callback);
		void setMinimizeCallback(Function<bool(bool minimized)> callback);
		void setMaximizeCallback(Function<bool(bool maximized)> callback);

	public:
		virtual ~Window();

		void destroy();
		// Bypasses the close callback
		void hardDestroy();
		// Doesn't do anything functional
		void requestDestroy();

		inline InputCore* getInput() const
		{
			return inputCore;
		}
		
		inline bool exists() const
		{
			return exists_;
		}

		inline bool isDestroyRequested() const
		{
			return destroyRequested;
		}

		virtual UniString getName() = 0;
		virtual void setName(UniString name) = 0;

		inline const char* getNameNarrow()
		{
			return getName().get_char();
		}

		inline const wchar_t* getNameWide()
		{
			return getName().get_wchar_t();
		}

		virtual int getX() const = 0;
		virtual int getY() const = 0;
		virtual Vector<2, int> getPosition() const = 0;
		virtual void setX(int x) = 0;
		virtual void setY(int y) = 0;
		virtual void setPosition(int x, int y) = 0;
		virtual void setPosition(const Vector<2, int>& pos) = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual Vector<2, int> getSize() const = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual void setSize(int width, int height) = 0;
		virtual void setSize(const Vector<2, int>& size) = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		// Does not invoke a callback
		virtual void setVisible(bool visible) = 0;
		virtual bool isVisible() = 0;

		virtual void minimize() = 0;
		virtual void unminimize() = 0;
		// Does not invoke the callback
		virtual void setMinimized(bool minimize) = 0;
		virtual bool isMinimized() = 0;

		virtual void maximize() = 0;
		virtual void unmaximize() = 0;
		// Does not invoke the callback
		virtual void setMaximized(bool maximize) = 0;
		virtual bool isMaximized() = 0;

		// Other stuff later
		// Vector position finding with vec2 and stuff
		// Icons, cursors, fullscreen, borderless, resizable, etc.
	};

	inline InstanceListHandle<Window> getWindowList()
	{
		return Window::getInstanceList();
	}

}

#endif