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

	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <typename T, typename P>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<P> && std::is_convertible_v<T, P>;

}

#endif