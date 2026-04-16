#pragma once
// Example

#include "clfe/System.h"
#include "clfe/Attachment.h"

namespace example
{

	class InstanceExample
	{
	private:
		static InstanceList<InstanceExample>* ExampleList;

	public:
		static const Attachment ExampleAttachment;
		
		static bool init();
		static void step(float delf, double deld);
		static void terminate();

		static inline InstanceListHandle<InstanceExample> getExampleList()
		{
			return ExampleList->getHandle();
		}

	protected:
		clid thisid;
		InstanceLink<InstanceExample>* instlink;

		InstanceExample(clid id) : thisid(id)
		{
			instlink = ExampleList->add(this, id);
		}

	public:
		inline clid getID() const
		{
			return thisid;
		}

		~InstanceExample()
		{
			delete instlink;
		}

	};

}