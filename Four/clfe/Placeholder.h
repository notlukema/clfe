#ifndef CLFE_PLACEHOLDER_H
#define CLFE_PLACEHOLDER_H

#include "System.h"
#include "InstanceInterface.h"
#include "Attachment.h"

#include "Function.h"

namespace clfe
{

	// Used for testing InstanceList and attachments and as a generic example of usage, though it may also have functionality as a "mini and offset attachment"
	class Placeholder : public InstanceInterface<Placeholder>
	{
	private:
		static const Attachment PlaceholderAttachment;
		static InstanceList<Placeholder>* PlaceholderList;
		static bool init();
		static void step(float delf, double deld);
		static void term();

	public:
		Function<void()> initFunc;
		Function<void(float delf, double deld)> stepFunc;
		Function<void()> termFunc;
		Placeholder(Function<void()> initFunc, Function<void(float delf, double deld)> stepFunc, Function<void()> termFunc);
		~Placeholder();

		inline static InstanceListHandle<Placeholder> getInstanceList()
		{
			return PlaceholderList->getHandle();
		}

	};

	inline InstanceListHandle<Placeholder> getPlaceholderList()
	{
		return Placeholder::getInstanceList();
	}

}

#endif