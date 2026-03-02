#ifndef CLFE_INPUT_CORE_H
#define CLFE_INPUT_CORE_H

#include "InputParams.h"
#include "../Attachment.h"

namespace clfe
{

	class InputCore
	{
	private:
		bool keysDown[KEY_COUNT];
		Inc_t keys[KEY_COUNT];

		// Work on callbacks section later
		//void (*OnKeyDown)(Key_t key);
		//void (*OnKeyUp)(Key_t key);

	public:
		InputCore();

		void step();

		void trigKeyDown(Key_t key);
		void trigKeyUp(Key_t key);

		bool keyDown(Key_t key) const;
		bool keyUp(Key_t key) const;
		bool keyPressed(Key_t key) const;
		bool keyReleased(Key_t key) const;

	};

}

#endif