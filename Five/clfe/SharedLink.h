#ifndef CLFE_SHAREDLINK_H
#define CLFE_SHAREDLINK_H

namespace clfe
{

	template <typename T>
	class LinkBase;

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
		friend class LinkBase;

		template <typename T>
		friend class LinkWell;

		template <typename T>
		friend class LinkPool;

		SharedLink(LinkWell<T>* well, SharedLink<T>* next, SharedLink<T>* last) : well(well), nextw(next), lastw(last), pool(nullptr), nextp(nullptr), lastp(nullptr) {}

		// Check if already connected to pool beforehand
		bool completeLink(LinkPool<T>* pool, SharedLink<T>* next, SharedLink<T>* last)
		{
			if (this->pool != nullptr)
			{
				return false;
			}

			// Same priority calls the pool first
			if (well->priority_ > pool->priority_)
			{
				if (!well->invokeInit())
				{
					return false;
				}
				if (!pool->invokeInit(well->this_))
				{
					return false;
				}
			}
			else
			{
				if (!pool->invokeInit(well->this_))
				{
					return false;
				}
				if (!well->invokeInit())
				{
					return false;
				}
			}

			this->pool = pool;
			nextp = next;
			lastp = last;

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
					well->first_ = nextw;
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
					pool->first_ = nextp;
				}
				else
				{
					lastp->nextp = nextp;
				}
			}
		}

	};

	// LinkBase

	template <typename T>
	class LinkBase
	{
	protected:
		template <typename T>
		friend class SharedLink;
		SharedLink<T>* first_;
		int len;

		// The higher the value, the higher its priority
		const int priority_;

		LinkBase(int priority = 0) : first_(nullptr), len(0), priority_(priority) {}

		~LinkBase()
		{
			releaseAll();
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

		void releaseAll()
		{
			while (first_ != nullptr)
			{
				delete first_;
			}
		}

		T* first()
		{
			if (first_ != nullptr)
			{
				return first_->well->getObj();
			}
			return nullptr;
		}

	};

	// Link Well

	template <typename T>
	class LinkWell : public LinkBase<T>
	{
	private:
		T* this_;
		bool (*initfunc)(T* this_);
		void (*termfunc)(T* this_);

		template <typename T>
		friend class SharedLink;

		bool invokeInit()
		{
			if (initfunc != nullptr)
			{
				return initfunc(this_);
			}
			return true;
		}

		void invokeTerm()
		{
			if (termfunc != nullptr)
			{
				termfunc(this_);
			}
		}

	public:
		LinkWell(T* this_, bool (*initfunc)(T* this_) = nullptr, void (*termfunc)(T* this_) = nullptr, int priority = 0) : LinkBase<T>(priority), this_(this_), initfunc(initfunc), termfunc(termfunc) {}

		SharedLink<T>* pull()
		{
			SharedLink<T>* link = new SharedLink<T>(this, LinkBase<T>::first_, nullptr);
			if (LinkBase<T>::first_ != nullptr)
			{
				LinkBase<T>::first_->lastw = link;
			}
			LinkBase<T>::first_ = link;
			LinkBase<T>::len++;
			return link;
		}

		inline T* getObj()
		{
			return this_;
		}
		
	};
	
	// Link Pool

	template <typename T>
	class VoidLinkFunction
	{
	public:
		virtual void invoke(T* other) = 0;

	};

	template <typename T, typename U>
	class VoidDoubleLinkFunction : public VoidLinkFunction<U>
	{
	private:
		T* this_;
		void (*func)(T* this_, U* other);

	public:
		VoidDoubleLinkFunction(T* this_, void (*func)(T* this_, U* other)) : this_(this_), func(func) {}

		virtual void invoke(U* other) override
		{
			if (func != nullptr) // Should always be true
			{
				func(this_, other);
			}
		}

	};

	template <typename T>
	class BoolLinkFunction
	{
	public:
		virtual bool invoke(T* other) = 0;

	};

	template <typename T, typename U>
	class BoolDoubleLinkFunction : public BoolLinkFunction<U>
	{
	private:
		T* this_;
		bool (*func)(T* this_, U* other);

	public:
		BoolDoubleLinkFunction(T* this_, bool (*func)(T* this_, U* other)) : this_(this_), func(func) {}

		virtual bool invoke(U* other) override
		{
			if (func != nullptr) // Should always be true
			{
				return func(this_, other);
			}
			return true;
		}

	};

	// When priority is the same, the LinkPool functions are always called first
	template <typename T>
	class LinkPool : public LinkBase<T>
	{
	private:
		BoolLinkFunction<T>* initfunc;
		VoidLinkFunction<T>* termfunc;

		template <typename T>
		friend class SharedLink;

		bool invokeInit(T* other)
		{
			if (initfunc != nullptr)
			{
				return initfunc->invoke(other);
			}
			return true;
		}

		void invokeTerm(T* other)
		{
			if (termfunc != nullptr)
			{
				termfunc->invoke(other);
			}
		}

	public:
		LinkPool(BoolLinkFunction<T>* initfunc = nullptr, VoidLinkFunction<T>* termfunc = nullptr, int priority = 0) : LinkBase<T>(priority), initfunc(initfunc), termfunc(termfunc) {}
		
		template <typename U>
		LinkPool(U* this_, bool (*initfunc)(U* this_, T* other), void (*termfunc)(U* this_, T* other), int priority = 0) : LinkBase<T>(priority),
			initfunc(initfunc == nullptr ? nullptr : new BoolDoubleLinkFunction<U, T>(this_, initfunc)),
			termfunc(termfunc == nullptr ? nullptr : new VoidDoubleLinkFunction<U, T>(this_, termfunc))
		{}

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
			if (!link->completeLink(this, LinkBase<T>::first_, nullptr))
			{
				return false;
			}
			if (LinkBase<T>::first_ != nullptr)
			{
				LinkBase<T>::first_->lastp = link;
			}
			LinkBase<T>::first_ = link;
			LinkBase<T>::len++;
			return true;
		}

		bool contains(T* obj)
		{
			SharedLink<T>* link = LinkBase<T>::first_;
			while (link != nullptr)
			{
				if (link->well->getObj() == obj)
				{
					return true;
				}
				link = link->nextp;
			}
			return false;
		}

	};

}

#endif