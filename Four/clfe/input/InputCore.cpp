#include "InputCore.h"

namespace clfe
{

	InputCore* InputCore::SystemInput = nullptr;

	InputCore::InputCore() : keysDown{ false }, keys{ 0 } {}

	void InputCore::step()
	{
		for (uint32_t i = 0; i < KEY_COUNT; i++)
		{
			if (keysDown[i])
			{
				keys[i]++;
			}
			else
			{
				keys[i] = 0;
			}
		}
	}

	void InputCore::keyDown(Key_t key)
	{
		if (SystemInput && SystemInput != this)
		{
			SystemInput->keyDown(key);
		}
		if (key >= 0 && key < KEY_COUNT)
		{
			keysDown[key] = true;
		}
	}

	void InputCore::keyUp(Key_t key)
	{
		if (SystemInput && SystemInput != this)
		{
			SystemInput->keyUp(key);
		}
		if (key >= 0 && key < KEY_COUNT)
		{
			keysDown[key] = false;
		}
	}

	bool InputCore::keyPressed(Key_t key)
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			return keysDown[key];
		}
		return false;
	}

}