#include "SharedLink.h"

namespace clfe
{

	// SharedLink

	SharedLink::SharedLink(LinkWell* well, SharedLink* next, SharedLink* last) : well(well), nextw(next), lastw(last), pool(nullptr), nextp(nullptr), lastp(nullptr)
	{}

	SharedLink::~SharedLink()
	{
		if (well != nullptr && pool != nullptr) // The link is complete
		{
			// Same priority calls the pool first
			if (well->priority_ > pool->priority_)
			{
				well->invokeTerm();
				pool->invokeTerm();
			}
			else
			{
				pool->invokeTerm();
				well->invokeTerm();
			}
		}

		if (well != nullptr) // Should always be true
		{
			well->len--;
			if (nextw != nullptr)
			{
				nextw->lastw = lastw;
			}
			if (lastw == nullptr)
			{
				well->first = nextw;
			}
			else
			{
				lastw->nextw = nextw;
			}
		}
		if (pool != nullptr)
		{
			pool->len--;
			if (nextp != nullptr)
			{
				nextp->lastp = lastp;
			}
			if (lastp == nullptr)
			{
				pool->first = nextp;
			}
			else
			{
				lastp->nextp = nextp;
			}
		}
	}

	bool SharedLink::completeLink(LinkPool* pool, SharedLink* next, SharedLink* last)
	{
		if (this->pool != nullptr)
		{
			return false;
		}

		this->pool = pool;
		nextp = next;
		lastp = last;

		// Same priority calls the pool first
		if (well->priority_ > pool->priority_)
		{
			well->invokeInit();
			pool->invokeInit();
		}
		else
		{
			pool->invokeInit();
			well->invokeInit();
		}

		return true;
	}

	// LinkBase

	LinkBase::LinkBase(LinkFunction* initFunc, LinkFunction* termFunc, int priority) : first(nullptr), len(0), priority_(priority), initFunc(initFunc), termFunc(termFunc)
	{
	}

	LinkBase::~LinkBase()
	{
		while (first != nullptr)
		{
			delete first;
		}
		if (initFunc != nullptr)
		{
			delete initFunc;
		}
		if (termFunc != nullptr)
		{
			delete termFunc;
		}
	}

	void LinkBase::setInitFunc(LinkFunction* func)
	{
		if (initFunc != nullptr)
		{
			delete initFunc;
		}
		initFunc = func;
	}

	void LinkBase::setTermFunc(LinkFunction* func)
	{
		if (termFunc != nullptr)
		{
			delete termFunc;
		}
		termFunc = func;
	}

	void LinkBase::invokeInit()
	{
		if (initFunc != nullptr)
		{
			initFunc->invoke();
		}
	}

	void LinkBase::invokeTerm()
	{
		if (termFunc != nullptr)
		{
			termFunc->invoke();
		}
	}

	// LinkWell

	LinkWell::LinkWell(LinkFunction* initFunc, LinkFunction* termFunc, int priority) : LinkBase(initFunc, termFunc, priority)
	{
	}

	SharedLink* LinkWell::pull()
	{
		SharedLink* link = new SharedLink(this, first, nullptr);
		if (first != nullptr)
		{
			first->lastw = link;
		}
		first = link;
		len++;
		return link;
	}

	// LinkPool

	LinkPool::LinkPool(LinkFunction* initFunc, LinkFunction* termFunc, int priority) : LinkBase(initFunc, termFunc, priority)
	{
	}

	bool LinkPool::attach(SharedLink* link)
	{
		if (!link->completeLink(this, first, nullptr))
		{
			return false;
		}
		if (first != nullptr)
		{
			first->lastp = link;
		}
		first = link;
		len++;
		return true;
	}

}