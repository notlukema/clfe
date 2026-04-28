#include "Placeholder.h"

namespace clfe
{

	const Attachment Placeholder::PlaceholderAttachment = Attachment(1, init, step, term);
	InstanceList<Placeholder>* Placeholder::PlaceholderList = nullptr;

	bool Placeholder::init()
	{
		PlaceholderList = new InstanceList<Placeholder>();
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
			if (obj->stepFunc != nullptr)
			{
				obj->stepFunc(delf, deld);
			}
		}
	}

	Placeholder::Placeholder(Function<void()> initFunc, Function<void(float delf, double deld)> stepFunc, Function<void()> termFunc) : InstanceInterface(PlaceholderList), initFunc(initFunc), stepFunc(stepFunc), termFunc(termFunc)
	{
		if (initFunc != nullptr)
		{
			initFunc();
		}
	}

	Placeholder::~Placeholder()
	{
		if (termFunc != nullptr)
		{
			termFunc();
		}
	}

}