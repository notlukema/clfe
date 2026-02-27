#include "SystemInput.h"

namespace clfe
{

	Attachment SystemInput::SystemInputAttachment = Attachment(AttachmentLayers::SystemInput, SystemInput::init, nullptr, nullptr);

	bool SystemInput::init()
	{
		//InputCore::SystemInput = 
		return true;
	}

}