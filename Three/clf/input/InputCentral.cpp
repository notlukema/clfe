#include "InputCentral.h"

namespace clfe
{

	IncType InputCentral::keys[KEY_COUNT] = { 0 };
	bool InputCentral::keysDown[KEY_COUNT];
	bool InputCentral::keysUp[KEY_COUNT];
	InputParams InputCentral::params = InputParams{};

	void InputCentral::init()
	{
		for (uint32_t i = 0; i < KEY_COUNT; ++i)
		{
			keysDown[i] = false;
			keysUp[i] = false;
			keys[i] = 0;
		}
	}

	void InputCentral::step()
	{
		for (uint32_t i = 0; i < KEY_COUNT; ++i)
		{
			keysUp[i] = false;

			if (keysDown[i])
			{
				keys[i] += 1;
			}
			else
			{
				if (keys[i] > 0)
				{
					keysUp[i] = true;
				}

				keys[i] = 0;
			}
		}
	}

	void InputCentral::activateKey(IncType key)
	{
		keysDown[key] = true;
	}

	void InputCentral::deactivateKey(IncType key)
	{
		keysDown[key] = false;
	}

	bool InputCentral::keyPressed(IncType key)
	{
		if (key >= KEY_COUNT)
		{
			return false;
		}
		return keysDown[key];
	}

}