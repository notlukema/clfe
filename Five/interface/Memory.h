#ifndef INTERFACE_MEMORY_H
#define INTERFACE_MEMORY_H

#include <memory>

namespace clfe
{

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T>
	using WeakPtr = std::weak_ptr<T>;

}

#endif