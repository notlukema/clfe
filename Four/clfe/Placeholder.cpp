#include "Placeholder.h"

namespace clfe
{
	const Attachment Placeholder::PlaceholderAttachment = Attachment(1, init, step, term);
	InstanceList<Placeholder>* Placeholder::PlaceholderList = nullptr;
	bool Placeholder::init()
	{
		PlaceholderList = new InstanceList<Placeholder>(99);
		return true;
	}
	void Placeholder::term()
	{
		delete PlaceholderList;
		PlaceholderList = nullptr;
	}

	void Placeholder::step(float delf, double deld)
	{
		for (Placeholder* obj : *PlaceholderList)
		{
			if (obj->func2 != nullptr)
			{
				obj->func2();
			}
		}
	}

	Placeholder::Placeholder(Function<void()> init, Function<void()> step, Function<void()> term) : InstanceInterface(PlaceholderList), func1(init), func2(step), func3(term)
	{
		if (func1 != nullptr)
		{
			func1();
		}
	}

	Placeholder::~Placeholder()
	{
		if (func3 != nullptr)
		{
			func3();
		}
	}

}