#include "WinWnd.h"

#include "../../clfe/Error.h"
#include "../../clfe/System.h"
#include "../../clfe/InstanceList.h"
#include "../../clu/StringUtils.h"

#include <string>
#include <Windows.h>

namespace clfe
{
	
	HINSTANCE WinClass::hInstance_;
	WinClass* WinClass::defaultClass_ = nullptr;
	InstanceList<WinClass>* WinClass::classes_ = nullptr;

	Attachment WinClass::winWndAttachment = Attachment(70, WinClass::init, WinClass::step, WinClass::terminate);

	bool WinClass::init()
	{
		hInstance_ = GetModuleHandle(NULL);
		classes_ = new InstanceList<WinClass>();
		defaultClass_ = createClass("Default", WinWnd::defWndProc);

		return defaultClass_ != nullptr;
	}

	void WinClass::step(float delf, double deld)
	{
		WinWnd::step();
	}

	void WinClass::terminate()
	{
		delete classes_;
	}

	WinClass* WinClass::createClass(const WCHAR* name, WNDPROC wndProc)
	{
		const WCHAR* className = concatWide(std::to_wstring(classes_->length() + 1 /* Placeholder ID */).append(L"_clfewnd-").c_str(), name); // TODO: fix Placeholder I guess
		// Class 1 -> 0_clfewnd-Class 1

		WNDCLASS wc = {}; // TODO: Check out WNDCLASSEX later on
		wc.lpfnWndProc = wndProc;
		wc.hInstance = hInstance_;
		wc.lpszClassName = className;

		ATOM atom = RegisterClass(&wc);
		if (atom == NULL) {
			DWORD error = GetLastError();
			logError("placeholder error again (class init error)"); // TODO: fix error logging
			return nullptr;
		}

		clid clid = System::genNextID();

		WinClass* wClass = new WinClass(clid, copyWide(name), className, atom);

		classes_->add(clid, wClass);
		//classes_->add(wClass->getID(), wClass);

		return wClass;
	}

	WinClass::WinClass(clid clid, const WCHAR* name, const WCHAR* className, ATOM wClass) : clid_(clid), name_(name), className_(className), wClass_(wClass) {}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass_), hInstance_);
	}

	clid WinClass::getID() const
	{
		return clid_;
	}

	const WCHAR* WinClass::getName() const
	{
		return name_;
	}

	const WCHAR* WinClass::getClassName() const
	{
		return className_;
	}

	ATOM WinClass::getClassAtom() const
	{
		return wClass_;
	}

}