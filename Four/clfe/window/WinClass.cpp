#include "WinWnd.h"

#include "../Error.h"
#include "../System.h"
#include "../InstanceList.h"
#include "../../clu/StringUtils.h"

#include <string>
#include <Windows.h>

namespace clfe
{
	
	HINSTANCE WinClass::HInstance;
	WinClass* WinClass::DefaultClass = nullptr;
	InstanceList<WinClass>* WinClass::Classes = nullptr;

	Attachment WinClass::WinWndAttachment = Attachment(AttachmentLayers::WinWindow, WinClass::init, WinClass::step, WinClass::terminate);

	bool WinClass::init()
	{
		HInstance = GetModuleHandle(NULL);
		Classes = new InstanceList<WinClass>();
		DefaultClass = createClass("Default", WinWnd::defWndProc);

		return DefaultClass != nullptr;
	}

	void WinClass::step(float delf, double deld)
	{
		WinWnd::step();
	}

	void WinClass::terminate()
	{
		Classes->deleteAll(); // Delete all Windows Classes
		delete Classes;
	}

	WinClass* WinClass::createClass(const WCHAR* name, WNDPROC wndProc)
	{
		const WCHAR* className = concatWide(std::to_wstring(Classes->length() + 1 /* Placeholder ID */).append(L"_clfewnd-").c_str(), name); // TODO: fix Placeholder I guess
		// Class 1 -> 0_clfewnd-Class 1

		WNDCLASS wc = {}; // TODO: Check out WNDCLASSEX later on
		wc.lpfnWndProc = wndProc;
		wc.hInstance = HInstance;
		wc.lpszClassName = className;

		ATOM atom = RegisterClass(&wc);
		if (atom == NULL) {
			DWORD error = GetLastError();
			logError("placeholder error again (class init error)"); // TODO: fix error logging
			return nullptr;
		}

		clid clid = System::genNextID();

		WinClass* wClass = new WinClass(clid, copyWide(name), className, atom);

		Classes->add(clid, wClass);

		return wClass;
	}

	WinClass::WinClass(clid clid, const WCHAR* name, const WCHAR* className, ATOM wClass) : thisid(clid), name(name), className(className), wClass(wClass) {}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass), HInstance);
	}

	clid WinClass::getID() const
	{
		return thisid;
	}

	const WCHAR* WinClass::getName() const
	{
		return name;
	}

	const WCHAR* WinClass::getClassName() const
	{
		return className;
	}

	ATOM WinClass::getClassAtom() const
	{
		return wClass;
	}

}