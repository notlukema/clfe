#include "Key.h"

namespace clfe
{

	// Solve static constexpr inline issue with arrays

	const char* KeyChars::getChar(Key_t key)
	{
		if (key < 0 || key >= KeyCount) {
			return "Unknown";
		}
		return CharMap[key];
	}

}