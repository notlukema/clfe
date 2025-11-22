#ifndef CLFE_WINWND_H
#define CLFE_WINWND_H

#include "Window.h"

namespace clfe
{
	class WinWnd : public Window
	{
	private:
		// variables and stuff

	public:
		WinWnd(int x, int y, int width, int height, const char* name);
		WinWnd(int x, int y, int width, int height, const wchar_t* name);
		virtual ~WinWnd();

		virtual const bool exists() const override;
		virtual void destroy() override;

		virtual const int getX() const override;
		virtual const int getY() const override;
		virtual const int getWidth() const override;
		virtual const int getHeight() const override;

		virtual void setX(int x) override;
		virtual void setY(int y) override;
		virtual void setWidth(int width) override;
		virtual void setHeight(int height) override;

		virtual void show() override;
		virtual void hide() override;
		virtual void setVisible(bool visible) override;
		virtual const bool isVisible() override;

		virtual const char* getNameNarrow() override;
		virtual const wchar_t* getNameWide() override;
		virtual void setName(const char* name) override;
		virtual void setName(const wchar_t* name) override;

	};

}

#endif