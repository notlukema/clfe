#include "System.h"

namespace clfe
{

	Attachment System::systemAttachment = Attachment(10, System::init, nullptr, nullptr);

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