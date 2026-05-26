#include "MVariable.h"

namespace clfe
{

	MVariableBase::MVariableBase(UniString name, VariableType type, bool deleteOnNoRef) : name_(name), type_(type), deleteOnNoRef(deleteOnNoRef), references_(0)
	{}

	void MVariableBase::addReference()
	{
		references_++;
	}

	void MVariableBase::removeReference()
	{
		references_--;
		if (references_ <= 0 && deleteOnNoRef)
		{
			delete this;
		}
	}

}