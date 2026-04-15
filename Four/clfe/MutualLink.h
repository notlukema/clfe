#ifndef CLFE_MUTUALLINK_H
#define CLFE_MUTUALLINK_H

#include "Concepts.h"
#include "List.h"

#include <cstdint>

namespace clfe
{

	template <typename T, typename U>
	concept Linkable = requires(T a, U b)
	{
		{ a.linkDelete(b) } -> SameAs<void>;
		{ b.linkDelete(a) } -> SameAs<void>;
	};

	// Requires T and U to have linkDelete functions for the other type. The first defined type will be the first to have delete called.
	template <typename T, typename U>
		//requires Linkable<T, U>
	class MutualLink
	{
	public:
		const T* a;
		const U* b;
		MutualLink(const T* a, const U* b) : a(a), b(b) {}
		// Triggers the delete functions for both sides
		~MutualLink() {}

		inline T* getA() const
		{
			return a;
		}

		inline U* getB() const
		{
			return b;
		}

		void deleteA()
		{
			b->linkDelete(a);
		}

		void deleteB()
		{
			a->linkDelete(b);
		}

	};

	inline constexpr uint16_t MutualLinkOptimization = 3;

	template <typename T, typename U>
	class MutualList
	{
	private:
		MutualLink<T, U>* smallData[MutualLinkOptimization];
		List<MutualLink<T, U>*>* overflowData;
		uint16_t dataCount;

	public:
		MutualList() : smallData{}, overflowData(nullptr), dataCount(0)
		{

		}

		~MutualList()
		{
		}



	};

}

#endif