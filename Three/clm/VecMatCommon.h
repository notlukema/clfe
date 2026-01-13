#ifndef CLM_VECMAT_COMMON_H
#define CLM_VECMAT_COMMON_H

#include <type_traits>
#include <cstdint>
#include <utility>

namespace clfe
{

	using msize_t = uint16_t;

	// Guarentees that all types are the same as T
	template <typename T, typename... Args>
	concept AllSame = (std::is_same_v<T, Args> && ...);

	// Guarentees that all types can be converted to T
	template <typename T, typename... Args>
	concept AllCompatible = (std::is_convertible_v<Args, T> && ...);

	// Guarentees that T is an arithmetic type
	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	// Guarentees that T and U are arithmetic types and that T can be converted to U
	template <typename T, typename U>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_convertible_v<T, U>;

	// Guarentees that T and U are arithmetic types and that the result of T + U can be converted to T
	template <typename T, typename U>
	concept Arithmetic3 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_convertible_v<decltype(static_cast<T>(0) + static_cast<U>(0)), T>;

	template <typename T, msize_t size>
	class Unpack
	{
	private:
		T values[size];

	public:
		template <typename... Args>
		constexpr Unpack(Args&&... args) : values{ std::forward<Args>(args)... } {}

		// This access operator cannot change values (does not return a reference)
		constexpr T operator[](msize_t i)
		{
			return values[i];
		}

	};

}

#endif