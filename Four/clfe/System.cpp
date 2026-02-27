#include "System.h"

namespace clfe
{

	Attachment System::SystemAttachment = Attachment(AttachmentLayers::System, System::init, nullptr, nullptr);

	clid System::nextID = 0;

	bool System::init()
	{
		nextID = 0;

		return true;
	}

	clid System::genNextID()
	{
		int thisID = nextID;
		nextID++;

		return thisID;
	}

}