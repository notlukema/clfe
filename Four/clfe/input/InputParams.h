#ifndef CLFE_INPUT_PARAMS_H
#define CLFE_INPUT_PARAMS_H

#include <cstdint>

namespace clfe
{

	using Inc_t = uint16_t;
	using Key_t = int32_t;
	const uint32_t KEY_COUNT = 512;

	struct InputParams
	{
		bool stickyKeysEnabled = false;
		bool stickyMouseButtonsEnabled = false;
		bool lockKeyMods = false;
	};

}

#endif