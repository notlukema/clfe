#include "StringUtils.h"

// ARTIFACT1: Should already be included by System.h
#include "../clfe/Error.h"

#include <stdlib.h>
#include <cstdlib>
#include <malloc.h>
#include <corecrt.h>

namespace clu
{
	const wchar_t* toWideString(const char* str)
	{
		// Obtain required size of new wide string
		size_t required_size;
		errno_t err = mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);
		if (err != 0) {
			cle::logError("Error determining required size of new wide string!");
			return nullptr;
		}

		// Initialize buffer of required size
		wchar_t* buffer = (wchar_t*)malloc(required_size * sizeof(wchar_t));

		// Convert to wide string
		err = mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);
		if (err != 0) {
			cle::logError("Error converting narrow string to wide string!");
			return nullptr;
		}

		return buffer;
	}

	const char* toNarrowString(const wchar_t* wstr)
	{
		// Obtain required size of new wide string
		size_t required_size;
		errno_t err = wcstombs_s(&required_size, NULL, 0, wstr, _TRUNCATE);
		if (err != 0) {
			cle::logError("Error determining required size of new narrow string!");
			return nullptr;
		}

		// Initialize buffer of required size
		char* buffer = (char*)malloc(required_size * sizeof(char));

		// Convert to wide string
		err = wcstombs_s(nullptr, buffer, required_size, wstr, _TRUNCATE);
		if (err != 0) {
			cle::logError("Error converting wide string to narrow string!");
			return nullptr;
		}

		return buffer;
	}

}