#include "InputCore.h"

namespace clfe
{

	InputCore::InputCore() : keysDown{ false }, keys{ 1 } {}

	void InputCore::step()
	{
		for (uint32_t i = 0; i < KEY_COUNT; i++)
		{
			keys[i]++;
		}
	}

	void InputCore::trigKeyDown(Key_t key)
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			keysDown[key] = true;
			keys[key] = 0;
		}
	}

	void InputCore::trigKeyUp(Key_t key)
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			keysDown[key] = false;
			keys[key] = 0;
		}
	}

	bool InputCore::keyDown(Key_t key) const
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			return keysDown[key];
		}
		return false;
	}

	bool InputCore::keyUp(Key_t key) const
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			return !keysDown[key];
		}
		return false;
	}

	bool InputCore::keyPressed(Key_t key) const
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			return keysDown[key] && keys[key] == 0;
		}
		return false;
	}

	bool InputCore::keyReleased(Key_t key) const
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			return !keysDown[key] && keys[key] == 0;
		}
		return false;
	}

}