#include "WinWnd.h"

#include "../Log.h"
#include "../System.h"
#include "../../clu/StringUtils.h"

#include <string>
#include <Windows.h>

namespace clfe
{
	
	HINSTANCE WinClass::HInstance;
	WinClass* WinClass::DefaultClass = nullptr;
	InstanceList<WinClass>* WinClass::Classes = nullptr;

	const Attachment WinClass::WinWndAttachment = Attachment(AttachmentLayers::WinWindow, WinClass::init, WinClass::step, WinClass::terminate);

	bool WinClass::init()
	{
		HInstance = GetModuleHandle(NULL);
		Classes = new InstanceList<WinClass>(InstanceTypes::WinClass);
		DefaultClass = createClass("Default", WinWnd::defWndProc);

		return DefaultClass != nullptr;
	}

	void WinClass::step(float delf, double deld)
	{
		WinWnd::step();
	}

	void WinClass::terminate()
	{
		Classes->deepDelete(); // Delete all Windows Classes
		delete Classes;
		Classes = nullptr;
		DefaultClass = nullptr;
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

		return wClass;
	}

	WinClass::WinClass(clid id, const WCHAR* name, const WCHAR* className, ATOM wClass) : thisid(id), name(name), className(className), wClass(wClass)
	{
		Classes->add(id, this);
	}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass), HInstance);
		Classes->remove(thisid);
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