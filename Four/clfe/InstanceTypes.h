#ifndef CLFE_INSTANCETYPES_H
#define CLFE_INSTANCETYPES_H

#include <cstdint>

namespace clfe
{

	using InsType_t = uint16_t;

	struct InstanceTypes // Purely a utility system, used for more dynamic (though restricted) runtime instancelist type identification. Using template types is the preferred method for actual functional code.
	{
#define IT_T static constexpr InsType_t

		IT_T Invalid = 0;
		IT_T Window = 1;
		IT_T WinClass = 2;
		IT_T Pipeline = 3;

	};

	struct InstanceNames
	{

		static constexpr const char* getTypeName(InsType_t type)
		{
			if (type < 0 || type >= Size)
			{
				return Unknown;
			}
			return InstanceTypeNames[type];
		}

		static constexpr int Size = 4;
		static constexpr const char* Unknown = "Unknown";

		// Avoid direct access to discourage inline code bloat
		static constexpr const char* InstanceTypeNames[Size] = {
			Unknown,
			"Window",
			"WinClass",
			"Pipeline",
		};

	};

}

#endif