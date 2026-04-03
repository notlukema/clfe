#include "InputCore.h"
#include "../Error.h"

namespace clfe
{

	InputCore::InputCore() : keysDown{ false }, keys{ 1 }, OnKeyDown(nullptr), OnKeyUp(nullptr) {}

	void InputCore::step()
	{
		CLFE_ERROR("called");
		for (uint32_t i = 0; i < KEY_COUNT; i++)
		{
			keys[i]++;
		}
	}

	void InputCore::trigKeyDown(Key_t key)
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			if (!keysDown[key])
			{
				keys[key] = 0;
			}
			else if (keys[key] == 0)
			{
				keys[key] = 1; // Prevent repeated key down events
			}

			keysDown[key] = true;

			if (OnKeyDown != nullptr && keys[key] == 0)
			{
				OnKeyDown(key);
			}
		}
	}

	void InputCore::trigKeyUp(Key_t key)
	{
		if (key >= 0 && key < KEY_COUNT)
		{
			keysDown[key] = false;
			keys[key] = 0;

			if (OnKeyUp != nullptr)
			{
				OnKeyUp(key);
			}
		}
	}

	void InputCore::setKeyDownCallback(void (*callback)(Key_t key))
	{
		OnKeyDown = callback;
	}

	void InputCore::setKeyUpCallback(void (*callback)(Key_t key))
	{
		OnKeyUp = callback;
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