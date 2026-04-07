#ifndef CLFE_OBJECT_DATA_H
#define CLFE_OBJECT_DATA_H

#include <cstdint>

namespace clfe
{

	using DataID_t = uint16_t;

	struct ObjectDataIDs
	{
#define DID_T static constexpr DataID_t

		DID_T a = 0;
		DID_T b = 1;
		DID_T c = 2;

	};

	struct ObjectData
	{

	};

}

#endif