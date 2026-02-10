#ifndef CLFE_INPUT_PARAMS_H
#define CLFE_INPUT_PARAMS_H

#include <cstdint>

namespace clfe
{

	using IncType = uint16_t;
	const uint32_t KEY_COUNT = 512; // "Placeholder"

	struct InputParams
	{
		bool stickyKeysEnabled = false;
		bool stickyMouseButtonsEnabled = false;
		bool lockKeyMods = false;
	};

}

#endif