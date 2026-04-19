#ifndef CLFE_INTERFACE_TYPETRAITS_H
#define CLFE_INTERFACE_TYPETRAITS_H

#include <type_traits>

namespace clfe
{

	template <typename T, typename U>
	concept IsSame = std::is_same_v<T, U>;

	template <typename T>
	concept IsIntegral = std::is_integral_v<T>;

	template <typename T>
	concept IsFloatingPoint = std::is_floating_point_v<T>;

	template <typename T>
	concept IsArithmetic = std::is_arithmetic_v<T>;

	template <typename T>
	concept IsSigned = std::is_signed_v<T>;

	template <typename T>
	concept IsUnsigned = std::is_unsigned_v<T>;

}

#endif