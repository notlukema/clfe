#ifndef CLFE_INTERFACE_UNORDEREDMAP_H
#define CLFE_INTERFACE_UNORDEREDMAP_H

#include <unordered_map>

namespace clfe
{

	template <typename Key, typename T>
	using UnorderedMap = std::unordered_map<Key, T>;

}

#endif