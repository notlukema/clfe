#ifndef CLFE_INPUT_CORE_H
#define CLFE_INPUT_CORE_H

#include "InputParams.h"

namespace clfe
{

	class InputCore
	{
	private:
		static InputCore* SystemInput;
		//static inline InputCore* getSystemInput() { return SystemInput; }

	private:
		bool keysDown[KEY_COUNT];
		Inc_t keys[KEY_COUNT];

		void (*OnKeyDown)(Key_t key);
		void (*OnKeyUp)(Key_t key);

	public:
		InputCore();

		void step();

		void keyDown(Key_t key);
		void keyUp(Key_t key);

		bool keyPressed(Key_t key);

	};

}

#endif