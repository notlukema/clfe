#ifndef CLFE_INPUT_PARAMS_H
#define CLFE_INPUT_PARAMS_H

#include <cstdint>

namespace clfe
{

	using Inc_t = int32_t;
	using Key_t = int32_t; // Would use uint32_t but -1 is used for invalid keys and there isn't that much of a need to preserve memory here
	const uint32_t KeyCount = 50; // Add more later

	struct InputParams // Unused right now, just here for potential reference
	{
		bool stickyKeysEnabled = false;
		bool stickyMouseButtonsEnabled = false;
		bool lockKeyMods = false;
	};

}

#endif