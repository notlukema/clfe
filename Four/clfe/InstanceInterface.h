#ifndef CLFE_INSTANCEINTERFACE_H
#define CLFE_INSTANCEINTERFACE_H

#include "System.h"

namespace clfe
{

	// Do not use this class directly with InstanceList or reference this class in place of the inherited class because the destructor of the inherited class will not be called.
	template <typename T>
	class InstanceInterface
	{
	protected:
		clid thisid;
		InstanceHandle<T>* instlink;

		InstanceInterface(InstanceList<T>* instlist) : thisid(System::genNextID())
		{
			instlink = instlist->add(static_cast<T*>(this), thisid);
		}

		~InstanceInterface()
		{
			delete instlink;
		}

	public:

		inline clid getID() const
		{
			return thisid;
		}

	};

}

#endif