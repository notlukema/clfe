#ifndef CLFE_ATTACHMENTLAYERS_H
#define CLFE_ATTACHMENTLAYERS_H

#include <cstdint>

namespace clfe
{

	using AttLayer_t = uint32_t;

	struct AttachmentLayers
	{
#define AL_T static constexpr AttLayer_t

		AL_T System[3] = { 10, 10, 99999 };

		AL_T Pipeline = 30;

		AL_T Window = 50;

		AL_T WinWindow = 70;

		AL_T MacWindow = 75;

		AL_T LnxWindow = 80;

		AL_T SystemInput = 100;

	};

}

#endif