#ifndef CLFE_INTERFACE_CONCEPTS_H
#define CLFE_INTERFACE_CONCEPTS_H

#include <concepts>

namespace clfe
{

	// Perhaps include clm concepts too

	template <typename T, typename U>
	concept SameAs = std::same_as<T, U>;

}

#endif