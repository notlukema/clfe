#include "WinWnd.h"

#include "clfe/AttachmentLayers.h"
#include "clfe/InstanceTypes.h"

#include <string> // tenmporary for std::to_wstring, consider replacing with custom implementation later

namespace clfe
{
	
	InstanceList<WinClass>* WinClass::Classes = nullptr;
	const Attachment WinClass::WinWndAttachment = Attachment(AttachmentLayers::WinWindow, WinClass::init, WinClass::step, WinClass::terminate);

	HINSTANCE WinClass::HInstance;
	WinClass* WinClass::DefaultClass = nullptr;

	bool WinClass::init()
	{
		Classes = new InstanceList<WinClass>(InstanceTypes::WinClass);
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
		delete Classes;
		Classes = nullptr;
		DefaultClass = nullptr;
	}

	WinClass* WinClass::createClass(const WCHAR* name, WNDPROC wndProc)
	{
		const WCHAR* className = concatStr(std::to_wstring(Classes->length() + 1 /* Placeholder ID */).append(L"_clfewnd-").c_str(), name); // TODO: fix Placeholder I guess
		// Class 1 -> 0_clfewnd-Class 1

		WNDCLASS wc = {}; // TODO: Check out WNDCLASSEX later on
		wc.lpfnWndProc = wndProc;
		wc.hInstance = HInstance;
		wc.lpszClassName = className;

		ATOM atom = RegisterClass(&wc);
		if (atom == NULL) {
			DWORD error = GetLastError();
			CLFE_ERROR("placeholder error again (class init error)"); // TODO: fix error logging
			return nullptr;
		}

		clid clid = System::genNextID();

		WinClass* wClass = new WinClass(clid, copyStr(name), className, atom);

		return wClass;
	}

	WinClass::WinClass(clid id, const WCHAR* name, const WCHAR* className, ATOM wClass) : thisid(id), name(name), className(className), wClass(wClass)
	{
		instlink = Classes->add(this, id);
	}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass), HInstance);
		delete instlink;
	}

}