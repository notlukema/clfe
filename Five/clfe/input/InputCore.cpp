#include "InputCore.h"

namespace clfe
{

	InputCore::InputCore() : keysDown{ false }, keys{}, OnKeyDown(nullptr), OnKeyUp(nullptr)
	{
		// Could just throw in a step()
		for (uint32_t i = 0; i < KeyCount; i++)
		{
			keys[i] = 1;
		}
	}

	void InputCore::step()
	{
		for (uint32_t i = 0; i < KeyCount; i++)
		{
			keys[i]++;
		}
	}

	void InputCore::trigKeyDown(Key_t key)
	{
		if (key < 0 || key >= KeyCount)
		{
			return;
		}

		if (!keysDown[key])
		{
			keys[key] = 0;
		}
		else if (keys[key] == 0)
		{
			keys[key] = 1; // Prevent repeated key down events
		}

		keysDown[key] = true;

		if (keys[key] == 0)
		{
			if (OnKeyDown != nullptr)
			{
				OnKeyDown(key);
			}
		}
		else
		{
			if (RepeatedKeyDown != nullptr)
			{
				RepeatedKeyDown(key);
			}
		}
	}

	void InputCore::trigKeyUp(Key_t key)
	{
		if (key < 0 || key >= KeyCount)
		{
			return;
		}

		keys[key] = 0; // No need to prevent repeated key up events since they shouldn't be possible in any way, shape, or form
		keysDown[key] = false;

		if (OnKeyUp != nullptr)
		{
			OnKeyUp(key);
		}
	}

	void InputCore::setKeyDownCallback(Function<void(Key_t)> callback)
	{
		OnKeyDown = callback;
	}

	void InputCore::setKeyUpCallback(Function<void(Key_t)> callback)
	{
		OnKeyUp = callback;
	}

	void InputCore::setRepeatedKeyDownCallback(Function<void(Key_t)> callback)
	{
		RepeatedKeyDown = callback;
	}

	Inc_t InputCore::getKeyInc(Key_t key) const
	{
		if (key < 0 || key >= KeyCount)
		{
			return 0;
		}

		return keys[key];
	}

	bool InputCore::keyDown(Key_t key) const
	{
		if (key < 0 || key >= KeyCount)
		{
			return false;
		}
		return keysDown[key];
	}

	bool InputCore::keyUp(Key_t key) const
	{
		if (key < 0 || key >= KeyCount)
		{
			return false;
		}
		return !keysDown[key];
	}

	bool InputCore::keyPressed(Key_t key) const
	{
		if (key < 0 || key >= KeyCount)
		{
			return false;
		}
		return keysDown[key] && keys[key] == 0;
	}

	bool InputCore::keyReleased(Key_t key) const
	{
		if (key < 0 || key >= KeyCount)
		{
			return false;
		}
		return !keysDown[key] && keys[key] == 0;
	}

}