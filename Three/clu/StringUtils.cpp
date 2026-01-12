#include "StringUtils.h"

#include "../clfe/Error.h"

#include <cstdlib>
#include <malloc.h>
#include <corecrt.h>
#include <string.h>
#include <wchar.h>

namespace clfe
{

	const char* toNarrowString(const wchar_t* wstr)
	{
		// Obtain required size of new wide string
		size_t required_size;
		errno_t err = wcstombs_s(&required_size, NULL, 0, wstr, _TRUNCATE);
		if (err != 0) {
			clfe::logError("Error determining required size of new narrow string!");
			return nullptr;
		}

		// Initialize buffer of required size
		char* buffer = (char*)malloc(required_size * sizeof(char));

		// Convert to wide string
		err = wcstombs_s(nullptr, buffer, required_size, wstr, _TRUNCATE);
		if (err != 0) {
			clfe::logError("Error converting wide string to narrow string!");
			return nullptr;
		}

		return buffer;
	}

	const wchar_t* toWideString(const char* str)
	{
		// Obtain required size of new wide string
		size_t required_size;
		errno_t err = mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);
		if (err != 0) {
			clfe::logError("Error determining required size of new wide string!");
			return nullptr;
		}

		// Initialize buffer of required size
		wchar_t* buffer = (wchar_t*)malloc(required_size * sizeof(wchar_t));

		// Convert to wide string
		err = mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);
		if (err != 0) {
			clfe::logError("Error converting narrow string to wide string!");
			return nullptr;
		}

		return buffer;
	}

	const char* concatNarrow(const char* str1, const char* str2)
	{
		size_t len1 = strlen(str1);
		size_t len2 = strlen(str2);

		char* buffer = (char*)malloc((len1 + len2 + 1) * sizeof(char));
		if (!buffer) {
			clfe::logError("Memory allocation failed while concatenating narrow strings!");
			return nullptr;
		}

		errno_t err = strcpy_s(buffer, len1 + 1, str1);
		if (err != 0) {
			clfe::logError("Error copying narrow string!");
			return nullptr;
		}

		err = strcat_s(buffer, len1 + len2 + 1, str2);
		if (err != 0) {
			clfe::logError("Error concatenating narrow string!");
			return nullptr;
		}

		return buffer;
	}

	const wchar_t* concatWide(const wchar_t* str1, const wchar_t* str2)
	{
		size_t len1 = wcslen(str1);
		size_t len2 = wcslen(str2);

		wchar_t* buffer = (wchar_t*)malloc((len1 + len2 + 1) * sizeof(wchar_t));
		if (!buffer) {
			clfe::logError("Memory allocation failed while concatenating wide strings!");
			return nullptr;
		}

		errno_t err = wcscpy_s(buffer, len1 + 1, str1);
		if (err != 0) {
			clfe::logError("Error copying wide string!");
			return nullptr;
		}

		err = wcscat_s(buffer, len1 + len2 + 1, str2);
		if (err != 0) {
			clfe::logError("Error concatenating wide string!");
			return nullptr;
		}

		return buffer;
	}

	const char* copyNarrow(const char* str)
	{
		size_t len = strlen(str) + 1;

		char* buffer = (char*)malloc(len * sizeof(char));
		if (!buffer) {
			clfe::logError("Memory allocation failed while copying narrow string!");
			return nullptr;
		}

		errno_t err = strcpy_s(buffer, len, str);
		if (err != 0) {
			clfe::logError("Error copying narrow string!");
			return nullptr;
		}

		return buffer;
	}

	const wchar_t* copyWide(const wchar_t* str)
	{
		size_t len = wcslen(str) + 1;

		wchar_t* buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
		if (!buffer) {
			clfe::logError("Memory allocation failed while copying wide string!");
			return nullptr;
		}

		errno_t err = wcscpy_s(buffer, len, str);
		if (err != 0) {
			clfe::logError("Error copying wide string!");
			return nullptr;
		}

		return buffer;
	}

}