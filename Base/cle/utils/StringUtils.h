#ifndef CLE_STRINGUTILS_H
#define CLE_STRINGUTILS_H

#include <stdlib.h>
#include "../Errors.h"

namespace cle {
	const wchar_t* toWChar(const char* str) {
		// Obtain required size of new wide string
		size_t required_size;
		errno_t err = mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);
		if (err != 0) {
			logError("Error determining required size of wide string");
			return nullptr;
		}

		// Initialize buffer of required size
		wchar_t* buffer = (wchar_t*)malloc(required_size * sizeof(wchar_t));

		// Convert to wide string
		err = mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);
		if (err != 0) {
			logError("Error converting string to wide string");
			return nullptr;
		}

		return buffer;
	}

	const char* concat(const char* str1, const char* str2) {
		char* result = (char*)malloc(strlen(str1) + strlen(str2) + 1);
		strcpy_s(result, sizeof(result), str1);
		strcat_s(result, sizeof(result), str2);
		return result;
	}
}

#endif