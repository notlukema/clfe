#ifndef CLFE_ATTACHMENT_LAYERS_H
#define CLFE_ATTACHMENT_LAYERS_H

#include <cstdint>

namespace clfe
{

	struct AttachmentLayers
	{
#define AL_T static const uint32_t

		AL_T System;
		AL_T Window;
		AL_T WinWindow;
		AL_T MacWindow;
		AL_T LnxWindow;
		AL_T SystemInput;

	};

}

#endif