#include "WinWnd.h"

#include "../../clfe/Error.h"

#include <string>

// ARTIFACT1: Should already be included by Window.h
#include "../../clu/StringUtils.h"
#include <Windows.h>

#include <iostream>

namespace clfe
{

	// Current implementation uses a basic array thingamajig
	WinClass* WinClass::defaultClass_ = nullptr;
	WinClass** WinClass::classes_ = nullptr;
	int WinClass::arrLen = 0;
	int WinClass::classCount = 0;
	HINSTANCE WinClass::hInstance_ = NULL;

	void WinClass::init()
	{
		arrLen = 1;
		classes_ = new WinClass*[arrLen];
		classCount = 0;
		defaultClass_ = createClass("Default", WinWnd::defWndProc);

		hInstance_ = GetModuleHandle(NULL);
	}

	void WinClass::terminate()
	{
		for (int i = 0; i < classCount; i++) {
			delete classes_[i];
		}
	}

	WinClass* WinClass::createClass(const WCHAR* name, WNDPROC wndProc)
	{
		const WCHAR* className = clu::concatWide(std::to_wstring(classCount).append(L"_clfewnd-").c_str(), name); // TODO: fix Placeholder I guess
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

		WinClass* wClass = new WinClass(clu::copyWide(name), className, atom);

		if (classCount >= arrLen) {  // TODO: fix warnings
			arrLen = classCount + 3; // Increment array size 3 at a time (2 extra slots)
			WinClass** newArr = new WinClass*[arrLen];
			for (int i = 0; i < classCount; i++) {
				newArr[i] = classes_[i];
			}
			newArr[classCount] = wClass; // It doesn't?
			delete classes_;
			classes_ = newArr;
		}
		else {
			classes_[classCount] = wClass;
		}
		classCount++;

		return wClass;
	}

	WinClass::WinClass(const WCHAR* name, const WCHAR* className, ATOM wClass)
	{
		name_ = name;
		className_ = className;
		wClass_ = wClass;
	}

	WinClass::~WinClass()
	{
		UnregisterClassW(MAKEINTATOM(wClass_), hInstance_);
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