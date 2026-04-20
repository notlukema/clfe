#include "StringUtils.h"

#include "../clfe/Log.h"

#include <cstdlib>
#include <malloc.h>
#include <corecrt.h>
#include <string.h>
#include <wchar.h>

namespace clfe
{

	// Convert

	char* toStrNarrow(const wchar_t* wstr)
	{
		size_t required_size;
		errno_t err = wcstombs_s(&required_size, NULL, 0, wstr, _TRUNCATE);
		if (err != 0) {
			CLFE_ERROR("Error determining required size of new narrow string!");
			return nullptr;
		}

		char* buffer = (char*)malloc(required_size * sizeof(char));

		err = wcstombs_s(nullptr, buffer, required_size, wstr, _TRUNCATE);
		if (err != 0) {
			CLFE_ERROR("Error converting wide string to narrow string!");
			return nullptr;
		}

		return buffer;
	}

	wchar_t* toStrWide(const char* str)
	{
		size_t required_size;
		errno_t err = mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);
		if (err != 0) {
			CLFE_ERROR("Error determining required size of new wide string!");
			return nullptr;
		}

		wchar_t* buffer = (wchar_t*)malloc(required_size * sizeof(wchar_t));

		err = mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);
		if (err != 0) {
			CLFE_ERROR("Error converting narrow string to wide string!");
			return nullptr;
		}

		return buffer;
	}

	// Concatenation

	char* concatStr(const char* str1, const char* str2)
	{
		size_t len1 = strlen(str1);
		size_t len2 = strlen(str2);

		char* buffer = (char*)malloc((len1 + len2 + 1) * sizeof(char));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while concatenating narrow strings!");
			return nullptr;
		}

		errno_t err = strcpy_s(buffer, len1 + 1, str1);
		if (err != 0) {
			CLFE_ERROR("Error copying narrow string!");
			return nullptr;
		}

		err = strcat_s(buffer, len1 + len2 + 1, str2);
		if (err != 0) {
			CLFE_ERROR("Error concatenating narrow string!");
			return nullptr;
		}

		return buffer;
	}

	wchar_t* concatStr(const wchar_t* str1, const wchar_t* str2)
	{
		size_t len1 = wcslen(str1);
		size_t len2 = wcslen(str2);

		wchar_t* buffer = (wchar_t*)malloc((len1 + len2 + 1) * sizeof(wchar_t));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while concatenating wide strings!");
			return nullptr;
		}

		errno_t err = wcscpy_s(buffer, len1 + 1, str1);
		if (err != 0) {
			CLFE_ERROR("Error copying wide string!");
			return nullptr;
		}

		err = wcscat_s(buffer, len1 + len2 + 1, str2);
		if (err != 0) {
			CLFE_ERROR("Error concatenating wide string!");
			return nullptr;
		}

		return buffer;
	}

	// Length

	size_t strLen(const char* str)
	{
		return strlen(str);
	}

	size_t strLen(const wchar_t* str)
	{
		return wcslen(str);
	}

	// Copy

	char* copyStr(const char* str)
	{
		size_t len = strlen(str) + 1;

		char* buffer = (char*)malloc(len * sizeof(char));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while copying narrow string!");
			return nullptr;
		}

		errno_t err = strcpy_s(buffer, len, str);
		if (err != 0) {
			CLFE_ERROR("Error copying narrow string!");
			return nullptr;
		}

		return buffer;
	}

	wchar_t* copyStr(const wchar_t* str)
	{
		size_t len = wcslen(str) + 1;

		wchar_t* buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while copying wide string!");
			return nullptr;
		}

		errno_t err = wcscpy_s(buffer, len, str);
		if (err != 0) {
			CLFE_ERROR("Error copying wide string!");
			return nullptr;
		}

		return buffer;
	}

	// Cut

	char* cutStr(const char* str, size_t a, size_t b)
	{
		if (a < 0 || b < 0)
		{
			return nullptr;
		}
		if (b < a)
		{
			return cutStr(str, b, a);
		}

		size_t len = strlen(str);
		if (a > len || b > len)
		{
			return nullptr;
		}

		size_t newlen = b - a + 1;

		char* buffer = (char*)malloc(newlen * sizeof(char));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while cutting narrow string!");
			return nullptr;
		}

		strncpy_s(buffer, newlen, str + a, newlen - 1);
		return buffer;
	}

	wchar_t* cutStr(const wchar_t* str, size_t a, size_t b)
	{
		if (a < 0 || b < 0)
		{
			return nullptr;
		}
		if (b < a)
		{
			return cutStr(str, b, a);
		}

		size_t len = wcslen(str);
		if (a > len || b > len)
		{
			return nullptr;
		}

		size_t newlen = b - a + 1;

		wchar_t* buffer = (wchar_t*)malloc(newlen * sizeof(wchar_t));
		if (!buffer) {
			CLFE_ERROR("Memory allocation failed while cutting wide string!");
			return nullptr;
		}

		wcsncpy_s(buffer, newlen, str + a, newlen - 1);
		return buffer;
	}

}