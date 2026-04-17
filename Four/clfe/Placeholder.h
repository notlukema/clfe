#pragma once

#include "System.h"
#include "InstanceInterface.h"
#include "Attachment.h"

#include "Function.h"

namespace clfe
{

	class Placeholder : public InstanceInterface<Placeholder>
	{
	private:
		static const Attachment PlaceholderAttachment;
		static InstanceList<Placeholder>* PlaceholderList;
		static bool init();
		static void step(float delf, double deld);
		static void term();

	public:
		Function<void()> func1;
		Function<void()> func2;
		Function<void()> func3;
		Placeholder(Function<void()> init, Function<void()> step, Function<void()> term);
		~Placeholder();

		inline static InstanceListHandle<Placeholder> getPlaceholderList()
		{
			return PlaceholderList->getHandle();
		}

	};

}