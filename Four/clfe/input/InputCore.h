#ifndef CLFE_INPUT_CORE_H
#define CLFE_INPUT_CORE_H

#include "InputParams.h"
#include "Function.h"

namespace clfe
{

	class InputCore
	{
	private:
		bool keysDown[KeyCount];
		Inc_t keys[KeyCount];

		Function<void(Key_t)> OnKeyDown;
		Function<void(Key_t)> OnKeyUp;
		Function<void(Key_t)> RepeatedKeyDown;

	public:
		InputCore();

		void step();

		void trigKeyDown(Key_t key);
		void trigKeyUp(Key_t key);

		void setKeyDownCallback(Function<void(Key_t)> callback);
		void setKeyUpCallback(Function<void(Key_t)> callback);
		void setRepeatedKeyDownCallback(Function<void(Key_t)> callback);

		Inc_t getKeyInc(Key_t key) const;
		bool keyDown(Key_t key) const;
		bool keyUp(Key_t key) const;
		bool keyPressed(Key_t key) const;
		bool keyReleased(Key_t key) const;

	};

}

#endif