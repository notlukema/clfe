#ifndef CLFE_ALLOCATION_H
#define CLFE_ALLOCATION_H

#include <cstdlib>
#include <cstdint>

namespace clfe
{

	struct Allocator
	{
	private:
		void* (*mallocFunc)(uint32_t size);
		void* (*callocFunc)(uint32_t count, uint32_t size);
		void (*freeFunc)(void* ptr);
		void* (*reallocFunc)(void* ptr, uint32_t size);

	public:
		Allocator(void* (*mallocFunc)(uint32_t size), void* (*callocFunc)(uint32_t count, uint32_t size), void (*freeFunc)(void* ptr), void* (*realloc)(void* ptr, uint32_t size));

		inline void* malloc(uint32_t size)
		{
			return mallocFunc(size);
		}

		inline void* calloc(uint32_t count, uint32_t size)
		{
			return callocFunc(count, size);
		}

		inline void free(void* ptr)
		{
			freeFunc(ptr);
		}

		inline void* realloc(void* ptr, uint32_t size)
		{
			return reallocFunc(ptr, size);
		}

	};

	extern Allocator DefaultAllocator;

	Allocator getDefaultAllocator();

	void setDefaultAllocator(Allocator allocator);

	inline void* malloc(uint32_t size)
	{
		return DefaultAllocator.malloc(size);
	}

	inline void* calloc(uint32_t count, uint32_t size)
	{
		return DefaultAllocator.calloc(count, size);
	}

	inline void free(void* ptr)
	{
		DefaultAllocator.free(ptr);
	}

	inline void* realloc(void* ptr, uint32_t size)
	{
		return DefaultAllocator.realloc(ptr, size);
	}

}

#endif