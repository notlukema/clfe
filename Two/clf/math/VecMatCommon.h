#ifndef CLFE_VECMAT_COMMON_H
#define CLFE_VECMAT_COMMON_H

#include <type_traits>
#include <cstdint>

namespace clfe
{

	using msize_t = uint16_t;

	using lowp = float;
	using mediump = double;
	using highp = long double;

	// Guarentees that T is an arithmetic type
	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	// Guarentees that T and U are arithmetic types and that T can be converted to U
	template <typename T, typename U>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_convertible_v<T, U>;

	// Guarentees that T and U are arithmetic types and that the result of T + U can be converted to T
	template <typename T, typename U>
	concept Arithmetic3 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_convertible_v<decltype(static_cast<T>(0) + static_cast<U>(0)), T>;

}

#endif