#ifndef CLFE_ATTACHMENTLAYERS_H
#define CLFE_ATTACHMENTLAYERS_H

#include <cstdint>

namespace clfe
{

	using AttLayer_t = uint32_t;

	struct AttachmentLayers
	{
#define AL_T static const AttLayer_t

		AL_T System;
		AL_T Window;
		AL_T WinWindow;
		AL_T MacWindow;
		AL_T LnxWindow;
		AL_T SystemInput;

	};

}

#endif