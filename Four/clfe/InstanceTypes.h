#ifndef CLFE_INSTANCETYPES_H
#define CLFE_INSTANCETYPES_H

#include <cstdint>

namespace clfe
{

	using InsType_t = uint16_t;

	struct InstanceTypes
	{
#define IT_T static constexpr InsType_t

		IT_T Invalid = 0;
		IT_T Window = 1;
		IT_T WinClass = 2;

	};

}

#endif