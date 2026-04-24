#ifndef CLFE_SHAREDLINK_H
#define CLFE_SHAREDLINK_H

#include "clfe/Log.h"

namespace clfe
{

	class LinkWell;
	class LinkPool;

	class SharedLink
	{
	private:
		LinkWell* well;
		LinkPool* pool;
		SharedLink* nextw;
		SharedLink* nextp;
		SharedLink* lastw;
		SharedLink* lastp;

		friend class LinkWell;
		friend class LinkPool;
		SharedLink(LinkWell* well, SharedLink* next, SharedLink* last);

		bool completeLink(LinkPool* pool, SharedLink* next, SharedLink* last);

	public:
		~SharedLink();

	};

	class LinkFunction
	{
	public:
		// Little overhead but no choice
		virtual ~LinkFunction() = default;
		virtual void invoke() = 0;

	};

	template <typename T>
	class LinkFuncSingle : public LinkFunction
	{
	private:
		T* this_;
		void (*func)(T* this_);

	public:
		LinkFuncSingle(T* this_, void (*func)(T* this_)) : this_(this_), func(func)
		{
		}

		~LinkFuncSingle() override
		{
		}

		virtual void invoke() override
		{
			func(this_);
		}

	};

	template <typename T, typename U>
	class LinkFuncDouble : public LinkFunction
	{
	private:
		T* this_;
		U* other;
		void (*func)(T* this_, U* other);

	public:
		LinkFuncDouble(T* this_, U* other, void (*func)(T* this_, U* other)) : this_(this_), other(other), func(func)
		{
		}

		~LinkFuncDouble() override
		{
		}

		virtual void invoke() override
		{
			func(this_, other);
		}

	};

	// Helper class (do not use)
	class LinkBase
	{
	protected:
		friend class SharedLink;
		SharedLink* first;
		int len;

		// The higher the value, the higher its priority
		const int priority_;
		LinkFunction* initFunc;
		LinkFunction* termFunc;

		LinkBase(LinkFunction* initFunc, LinkFunction* termFunc, int priority = 0);
		~LinkBase();

	public:
		inline int length() const
		{
			return len;
		}

		inline int priority() const
		{
			return priority_;
		}

		void setInitFunc(LinkFunction* func);
		void setTermFunc(LinkFunction* func);

		void invokeInit();
		void invokeTerm();

	};

	// When priority is the same, the LinkWell functions are always called second
	class LinkWell : public LinkBase
	{
	public:
		LinkWell(LinkFunction* initFunc, LinkFunction* termFunc, int priority = 0);

		SharedLink* pull();
		
	};

	// When priority is the same, the LinkPool functions are always called first
	class LinkPool : public LinkBase
	{
	public:
		LinkPool(LinkFunction* initFunc, LinkFunction* termFunc, int priority = 0);

		bool attach(SharedLink* link);

	};

}

#endif