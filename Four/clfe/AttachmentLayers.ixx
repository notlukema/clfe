module;
#include <cstdint>
export module AttachmentLayers;

export using AttLayer_t = uint32_t;

#define AL_T static const AttLayer_t
export struct AttachmentLayers
{

	AL_T System = 10;
	AL_T Window = 50;
	AL_T WinWindow = 70;
	AL_T MacWindow = 75;
	AL_T LnxWindow = 80;
	AL_T SystemInput = 100;

};
