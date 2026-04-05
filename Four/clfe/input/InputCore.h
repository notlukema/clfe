#ifndef CLFE_INPUT_CORE_H
#define CLFE_INPUT_CORE_H

#include "InputParams.h"

#include <functional>

namespace clfe
{

	class InputCore
	{
	private:
		bool keysDown[KeyCount];
		Inc_t keys[KeyCount];

		//void (*OnKeyDown)(Key_t key);
		std::function<void(Key_t)> OnKeyDown; // decision here
		void (*OnKeyUp)(Key_t key);
		void (*RepeatedKeyDown)(Key_t key);

	public:
		InputCore();

		void step();

		void trigKeyDown(Key_t key);
		void trigKeyUp(Key_t key);

		void setKeyDownCallback(std::function<void(Key_t)> callback);
		void setKeyUpCallback(void (*callback)(Key_t key));
		void setRepeatedKeyDownCallback(void (*callback)(Key_t key));

		Inc_t getKeyInc(Key_t key) const;
		bool keyDown(Key_t key) const;
		bool keyUp(Key_t key) const;
		bool keyPressed(Key_t key) const;
		bool keyReleased(Key_t key) const;

	};

}

#endif