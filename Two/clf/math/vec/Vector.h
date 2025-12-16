#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

#include <type_traits>
#include <concepts>

namespace clfe
{

	template <typename T, int Size >
	requires std::is_arithmetic_v<T> && (Size > 0)
	class Vector
	{
	protected:
		T array[Size];

	public:
		Vector() : array{} {} // Unnecessary due to variadic constructor, but helps with clarity
		template <typename... Args>
		requires (sizeof...(Args) <= Size)
		Vector(Args... args) : array{ static_cast<T>(args)... } {} // Study "concepts" and other stuff later to constrain number of args

		const T* get() const
		{
			return static_cast<const T*>(array);
		}

		T get(int i) const
		{
			return array[i];
		}

	};

}

#endif