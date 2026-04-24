#ifndef CLFE_SHAREDLINK_H
#define CLFE_SHAREDLINK_H

#include "clfe/Log.h"

namespace clfe
{

	template <typename This, typename Other>
	class LinkWell;

	template <typename This, typename Other>
	class LinkPool;

	template <typename T, typename U>
	class SharedLink
	{
	private:
		LinkWell<T, U>* well;
		LinkPool<U, T>* pool;
		SharedLink<T, U>* nextw;
		SharedLink<T, U>* nextp;
		SharedLink<T, U>* lastw;
		SharedLink<T, U>* lastp;

		template <typename This, typename Other>
		friend class LinkWell;
		template <typename This, typename Other>
		friend class LinkPool;
		SharedLink(LinkWell<T, U>* well, SharedLink<T, U>* next, SharedLink<T, U>* last) : well(well), nextw(next), lastw(last), pool(nullptr), nextp(nullptr), lastp(nullptr)
		{
		}

		bool completeLink(LinkPool<U, T> pool, SharedLink<T, U>* next, SharedLink<T, U>* last)
		{
			if (this->pool != nullptr)
			{
				return false;
			}

			this->pool = pool;
			nextp = next;
			lastp = last;

			if (well->priority >= pool->priority)
			{
				well->invokeInit(pool->this_);
				pool->invokeInit(well->this_);
			}
			else
			{
				pool->invokeInit(well->this_);
				well->invokeInit(pool->this_);
			}

			return true;
		}

		~SharedLink()
		{
			if (well != nullptr && pool != nullptr) // The link is complete
			{
				if (well->priority >= pool->priority)
				{
					well->invokeTerm(pool->this_);
					pool->invokeTerm(well->this_);
				}
				else
				{
					pool->invokeTerm(well->this_);
					well->invokeTerm(pool->this_);
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

	};

	template <typename This, typename Other>
	class LinkBase
	{
	protected:
		// The higher the number, the more priority
		int priority;
		This* this_;
		void (*init)(This this_, Other other);
		void (*term)(This this_, Other other);

		LinkBase(int priority, This* this_, void (*initFunc)(This* this_, Other* other), void (*termFunc)(This* this_, Other* other)) : priority(priority), this_(this_), init(initFunc), term(termFunc)
		{
		}

	public:
		void setInitFunc(void (*initFunc)(This* this_, Other* other))
		{
			init = initFunc;
		}

		void setTermFunc(void (*termFunc)(This* this_, Other* other))
		{
			term = termFunc;
		}

		void invokeInit(Other* other)
		{
			CLFE_LOG("link invoke init");
			if (init != nullptr)
			{
				init(this_, other);
			}
		}

		void invokeTerm(Other* other)
		{
			CLFE_LOG("link invoke term");
			if (term != nullptr)
			{
				term(this_, other);
			}
		}

	};

	template  <typename This, typename Other>
	class LinkWell : public LinkBase<This, Other>
	{
	private:
		int len;
		SharedLink<This, Other>* first;

		template <typename T, typename U>
		friend class SharedLink;

	public:
		LinkWell(This* this_, void (*initFunc)(This* this_, Other* other), void (*termFunc)(This* this_, Other* other), int priority = 0) : LinkBase(priority, this_, initFunc, termFunc), len(0), first(nullptr)
		{
		}

		~LinkWell()
		{
			CLFE_LOG("Linkwell destroyed");
			while (first != nullptr)
			{
				delete first;
			}
		}

		SharedLink<This, Other>* pull()
		{
			SharedLink<This, Other>* link = new SharedLink<This, Other>(this, first, nullptr);
			if (first != nullptr)
			{
				first->lastw = link;
			}
			first = link;
			len++;
			return link;
		}

	};

	template  <typename This, typename Other>
	class LinkPool : public LinkBase<This, Other>
	{
	private:
		int len;
		SharedLink<Other, This>* first;

		template <typename T, typename U>
		friend class SharedLink;

	public:
		LinkPool(This* this_, void (*initFunc)(This* this_, Other* other), void (*termFunc)(This* this_, Other* other), int priority = 0) : LinkBase(priority, this_, initFunc, termFunc), len(0), first(nullptr)
		{
		}

		~LinkPool()
		{
			CLFE_LOG("Linkpool destroyed");
			while (first != nullptr)
			{
				delete first;
			}
		}
		
		bool attach(SharedLink<Other, This>* link)
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

	};

}

#endif