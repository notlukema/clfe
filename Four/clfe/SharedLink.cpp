#include "SharedLink.h"

namespace clfe
{

	LinkBase::LinkBase() : first(nullptr), len(0)
	{
	}

	//

	SharedLink::SharedLink(LinkBase* a, SharedLink* nexta, SharedLink* lasta) : a(a), nexta(nexta), lasta(lasta), b(nullptr), nextb(nullptr), lastb(nullptr)
	{
	}

	SharedLink::~SharedLink()
	{
		if (a != nullptr) { // Always true
			a->len--;
			if (nexta != nullptr)
			{
				nexta->lasta = lasta;
			}
			if (lasta == nullptr)
			{
				a->first = nexta;
			}
			else
			{
				lasta->nexta = nexta;
			}
		}

		if (b != nullptr)
		{
			b->len--;
			if (lastb == nullptr)
			{
				if (nextb != nullptr)
				{
					nextb->lastb = nullptr;
				}
				b->first = nextb;
			}
			else
			{
				lastb->nextb = nextb;
			}
		}
	}

}