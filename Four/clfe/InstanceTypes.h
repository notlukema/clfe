#ifndef CLFE_INSTANCETYPES_H
#define CLFE_INSTANCETYPES_H

#include <cstdint>

namespace clfe
{

	using InsType_t = uint16_t;

	struct InstanceTypes
	{
#define IT_T static const InsType_t

		IT_T Window;
		IT_T WinClass;

	};

}

#endif