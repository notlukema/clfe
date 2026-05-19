#ifndef INTERFACE_FUNCTION_H
#define INTERFACE_FUNCTION_H

#include <functional>

namespace clfe
{

	template <typename T>
	using Function = std::function<T>;

}

#endif