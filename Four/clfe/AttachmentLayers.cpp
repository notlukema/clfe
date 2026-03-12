#include "AttachmentLayers.h"

namespace clfe
{
#define AL_T2 const AttLayer_t

	AL_T2 AttachmentLayers::System = 10;
	/*
	* Init: Prepare for instance lists and reset id counter
	* Step: unused
	* Terminate: unused
	*/

	AL_T2 AttachmentLayers::Window = 50;
	/*
	* Init: Create Windows instance list
	* Step: unused
	* Terminate: Delete all Windows
	*/

	AL_T2 AttachmentLayers::WinWindow = 70;
	/*
	* Init: Create Windows Class instance list
	* Step: unused
	* Terminate: Delete all Windows Classes
	*/

	AL_T2 AttachmentLayers::MacWindow = 75; // unused
	AL_T2 AttachmentLayers::LnxWindow = 80; // unused
	AL_T2 AttachmentLayers::SystemInput = 100; // unused

}