#ifndef CLFE_INTERFACE_FUNCTION_H
#define CLFE_INTERFACE_FUNCTION_H

#include <functional>

namespace clfe
{

	template <typename T>
	using Function = std::function<T>;

}

#endif