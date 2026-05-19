#ifndef INTERFACE_UNORDEREDMAP_H
#define INTERFACE_UNORDEREDMAP_H

#include <unordered_map>

namespace clfe
{

	template <typename Key, typename T>
	using UnorderedMap = std::unordered_map<Key, T>;

}

#endif