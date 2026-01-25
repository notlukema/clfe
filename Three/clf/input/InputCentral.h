#ifndef CLFE_INPUT_CENTRAL_H
#define CLFE_INPUT_CENTRAL_H

#include "InputParams.h"

namespace clfe
{

	class InputCentral
	{
	private:
		static bool keysDown[KEY_COUNT];
		static bool keysUp[KEY_COUNT];
		static IncType keys[KEY_COUNT];

	public:
		static InputParams params;

		static void init();
		static void step();

		static void activateKey(IncType key);
		static void deactivateKey(IncType key);

		static bool keyPressed(IncType key);

	};

}

#endif