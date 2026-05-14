#ifndef CLFE_PIPELINE_OPENGL4_6_WINDOWS_H
#define CLFE_PIPELINE_OPENGL4_6_WINDOWS_H

#include "Opengl4_6_i.h"
#include "clfe/window/WinWnd.h"
#include "clfe/SharedLink.h"

#include <Windows.h>

namespace clfe
{

	class GL4_6_Extension_Windows : public GL4_6_Extension
	{
	private:
		LinkPool<WinWnd> pool;

		static void attachWindow(GL4_6_Extension_Windows* this_, WinWnd* window);
		static void detachWindow(GL4_6_Extension_Windows* this_, WinWnd* window);
		
	public:
		GL4_6_Extension_Windows();

		virtual bool compatible(Window* window) override;
		virtual bool initWindow(Window* window) override;

	};

}

#endif