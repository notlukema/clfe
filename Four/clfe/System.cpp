#include "System.h"

namespace clfe
{

	Attachment System::SystemAttachment = Attachment(AttachmentLayers::System, System::init, nullptr, System::terminate);

	std::list<InstanceBase*> System::Instances = std::list<InstanceBase*>();
	clid System::NextID = 0;

	void System::addInstance(InstanceBase* instance)
	{
		Instances.push_back(instance);
	}

	void System::removeInstance(InstanceBase* instance)
	{
		Instances.remove(instance);
	}

	bool System::init()
	{
		Instances = std::list<InstanceBase*>();
		NextID = 0;

		return true;
	}

	void System::terminate()
	{
		// theoretically all instances will be handled by their respective components
	}

	clid System::genNextID()
	{
		clid thisID = NextID;
		NextID++;

		return thisID;
	}

	InsType_t System::getInstanceType(clid id)
	{
		for (InstanceBase* instance : Instances)
		{
			if (instance->hasInstance(id))
			{
				return instance->getType();
			}
		}

		return InstanceTypes::Invalid;
	}

	InstanceBase::InstanceBase(InsType_t type) : type(type)
	{
		System::addInstance(this);
	}

	InstanceBase::~InstanceBase()
	{
		System::removeInstance(this);
	}

}