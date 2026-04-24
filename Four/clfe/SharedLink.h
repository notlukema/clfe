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


	public:
		{
		}

	{



	};

	{
	private:
		int len;
		SharedLink<This, Other>* first;

		template <typename T, typename U>
		friend class SharedLink;

	public:
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

		{
			if (first != nullptr)
			{
			}
			len++;
		}

	};

	{
	private:
		int len;
		SharedLink<Other, This>* first;

		template <typename T, typename U>
		friend class SharedLink;

	public:
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