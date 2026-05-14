#ifndef CLFE_SHAREDLINK_H
#define CLFE_SHAREDLINK_H

namespace clfe
{

	template <typename T>
	class LinkWell;

	template <typename T>
	class LinkPool;

	template <typename T>
	class SharedLink
	{
	private:
		LinkWell<T>* well;
		LinkPool<T>* pool;
		SharedLink<T>* nextw;
		SharedLink<T>* nextp;
		SharedLink<T>* lastw;
		SharedLink<T>* lastp;

		template <typename T>
		friend class LinkWell;
		template <typename T>
		friend class LinkPool;

		SharedLink(LinkWell<T>* well, SharedLink<T>* next, SharedLink<T>* last) : well(well), nextw(next), lastw(last), pool(nullptr), nextp(nullptr), lastp(nullptr) {}

		bool completeLink(LinkPool<T>* pool, SharedLink<T>* next, SharedLink<T>* last)
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
				pool->invokeInit(well->this_);
			}
			else
			{
				pool->invokeInit(well->this_);
				well->invokeInit();
			}

			return true;
		}

	public:
		~SharedLink()
		{
			if (well != nullptr && pool != nullptr) // The link is complete
			{
				// Same priority calls the pool first
				if (well->priority_ > pool->priority_)
				{
					well->invokeTerm();
					pool->invokeTerm(well->this_);
				}
				else
				{
					pool->invokeTerm(well->this_);
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

	};

	// Helper class (do not use)
	template <typename T>
	class LinkBase
	{
	protected:
		template <typename T>
		friend class SharedLink;
		SharedLink<T>* first;
		int len;

		// The higher the value, the higher its priority
		const int priority_;

		LinkBase(int priority = 0) : first(nullptr), len(0), priority_(priority) {}

		~LinkBase()
		{
			while (first != nullptr)
			{
				delete first;
			}
		}

	public:
		inline int length() const
		{
			return len;
		}

		inline int priority() const
		{
			return priority_;
		}

	};

	// When priority is the same, the LinkWell functions are always called second
	template <typename T>
	class LinkWell : public LinkBase<T>
	{
	private:
		T* this_;
		void (*initfunc)(T* this_);
		void (*termfunc)(T* this_);

		template <typename T>
		friend class SharedLink;

		void invokeInit()
		{
			if (initfunc != nullptr)
			{
				initfunc(this_);
			}
		}

		void invokeTerm()
		{
			if (termfunc != nullptr)
			{
				termfunc(this_);
			}
		}

	public:
		LinkWell(T* this_, void (*initfunc)(T* this_) = nullptr, void (*termfunc)(T* this_) = nullptr, int priority = 0) : LinkBase<T>(priority), this_(this_), initfunc(initfunc), termfunc(termfunc) {}

		SharedLink<T>* pull()
		{
			SharedLink<T>* link = new SharedLink<T>(this, LinkBase<T>::first, nullptr);
			if (LinkBase<T>::first != nullptr)
			{
				LinkBase<T>::first->lastw = link;
			}
			LinkBase<T>::first = link;
			LinkBase<T>::len++;
			return link;
		}
		
	};
	
	template <typename T>
	class LinkFunction
	{
	public:
		virtual void invoke(T* other) = 0;

	};

	template <typename T, typename U>
	class DoubleLinkFunction : public LinkFunction<U>
	{
	private:
		T* this_;
		void (*func)(T* this_, U* other);

	public:
		DoubleLinkFunction(T* this_, void (*func)(T* this_, U* other)) : this_(this_), func(func) {}

		virtual void invoke(U* other) override
		{
			if (func != nullptr) // Should always be true
			{
				func(this_, other);
			}
		}

	};

	// When priority is the same, the LinkPool functions are always called first
	template <typename T>
	class LinkPool : public LinkBase<T>
	{
	private:
		LinkFunction<T>* initfunc;
		LinkFunction<T>* termfunc;

		template <typename T>
		friend class SharedLink;

		void invokeInit(T* other)
		{
			if (initfunc != nullptr)
			{
				initfunc->invoke(other);
			}
		}

		void invokeTerm(T* other)
		{
			if (termfunc != nullptr)
			{
				termfunc->invoke(other);
			}
		}

	public:
		LinkPool(LinkFunction<T>* initfunc = nullptr, LinkFunction<T>* termfunc = nullptr, int priority = 0) : LinkBase<T>(priority), initfunc(initfunc), termfunc(termfunc) {}
		
		template <typename U>
		LinkPool(U* this_, void (*initfunc)(U* this_, T* other), void (*termfunc)(U* this_, T* other), int priority = 0) : LinkBase<T>(priority),
			initfunc(initfunc == nullptr ? nullptr : new DoubleLinkFunction<U, T>(this_, initfunc)), termfunc(termfunc == nullptr ? nullptr : new DoubleLinkFunction<U, T>(this_, termfunc)) {}

		~LinkPool()
		{
			if (initfunc != nullptr)
			{	
				delete initfunc;
			}
			if (termfunc != nullptr)
			{
				delete termfunc;
			}
		}

		bool attach(SharedLink<T>* link)
		{
			if (!link->completeLink(this, LinkBase<T>::first, nullptr))
			{
				return false;
			}
			if (LinkBase<T>::first != nullptr)
			{
				LinkBase<T>::first->lastp = link;
			}
			LinkBase<T>::first = link;
			LinkBase<T>::len++;
			return true;
		}

	};

}

#endif