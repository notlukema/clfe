#include "WinWnd.h"

#include "clfe/AttachmentLayers.h"
#include "clfe/InstanceTypes.h"

#include "clu/FlexibleToString.h"

namespace clfe
{
	
	InstanceList<WinClass>* WinClass::ClassList = nullptr;
	const Attachment WinClass::WinWndAttachment = Attachment(AttachmentLayers::WinWindow, WinClass::init, WinClass::step, WinClass::terminate);

	HINSTANCE WinClass::HInstance;
	WinClass* WinClass::DefaultClass = nullptr;

	bool WinClass::init()
	{
		ClassList = new InstanceList<WinClass>(InstanceTypes::WinClass);
		HInstance = GetModuleHandle(NULL);
		DefaultClass = createClass("Default", WinWnd::defWndProc);
		return DefaultClass != nullptr;
	}

	void WinClass::step(float delf, double deld)
	{
		WinWnd::step();
	}

	void WinClass::terminate()
	{
		delete ClassList;
		ClassList = nullptr;
		DefaultClass = nullptr;
	}

	WinClass* WinClass::createClass(UniString name, WNDPROC wndProc)
	{
		UniString className = name + "_clfewinwnd" + toStr(ClassList->length());
		// Default Class -> Default_clfewinwnd0

		WNDCLASS wc = {}; // TODO: Check out WNDCLASSEX later on
		wc.lpfnWndProc = wndProc;
		wc.hInstance = HInstance;
		wc.lpszClassName = className.get_wchar_t();

		ATOM atom = RegisterClass(&wc);
		if (atom == NULL) {
			//DWORD error = GetLastError();
			CLFE_ERROR("Error registering windows class!");
			return nullptr;
		}

		WinClass* wClass = new WinClass(name, className, atom);

		return wClass;
	}

	WinClass::WinClass(UniString name, UniString className, ATOM wClass) : InstanceInterface(ClassList), name(name), className(className), wClass(wClass)
	{
	}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass), HInstance);
	}

}