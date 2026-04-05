#ifndef CLFE_OBJECT_DATA_H
#define CLFE_OBJECT_DATA_H

#include <cstdint>

namespace clfe
{

	using DataID_t = uint16_t;

	struct ObjectDataIDs
	{
#define DID_T static const DataID_t

		DID_T a;
		DID_T b;
		DID_T c;

	};

	struct ObjectData
	{

	};

}

#endif