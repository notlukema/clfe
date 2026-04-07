#ifndef CLFE_OBJECT_H
#define CLFE_OBJECT_H

#include "ObjectData.h"

#include <cstdint>

namespace clfe
{

	inline constexpr uint16_t ObjectDataOptimization = 10;

	class Object
	{
	public:
		struct Node
		{

		};

	private:
		ObjectData* smallData[ObjectDataOptimization];
		Node* first;
		uint16_t dataCount;



	};

}

#endif