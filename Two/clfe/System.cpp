#include "System.h"

namespace clfe
{

	clid System::nextID = 0;

	void System::init()
	{
		nextID = 0;
	}

	clid System::genNextID()
	{
		int thisID = nextID;
		nextID++;

		return thisID;
	}

}