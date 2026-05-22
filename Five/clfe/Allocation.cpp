#include "Allocation.h"

namespace clfe
{

	Allocator::Allocator(void* (*mallocFunc)(uint32_t size), void* (*callocFunc)(uint32_t count, uint32_t size), void (*freeFunc)(void* ptr), void* (*reallocFunc)(void* ptr, uint32_t size)) :
		mallocFunc(mallocFunc), callocFunc(callocFunc), freeFunc(freeFunc), reallocFunc(reallocFunc)
	{}

	inline static void* mallocFunc(uint32_t size)
	{
		return std::malloc(size);
	}
	
	inline static void* callocFunc(uint32_t count, uint32_t size)
	{
		return std::calloc(count, size);
	}

	inline static void freeFunc(void* ptr)
	{
		std::free(ptr);
	}

	inline static void* reallocFunc(void* ptr, uint32_t size)
	{
		return std::realloc(ptr, size);
	}

	Allocator DefaultAllocator = Allocator(mallocFunc, callocFunc, freeFunc, reallocFunc);

	Allocator getDefaultAllocator()
	{
		return DefaultAllocator;
	}

	void setDefaultAllocator(Allocator allocator)
	{
		DefaultAllocator = allocator;
	}

}