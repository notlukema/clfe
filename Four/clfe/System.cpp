#include "System.h"

#include "AttachmentLayers.h"

namespace clfe
{

	Attachment System::SystemAttachment = Attachment(AttachmentLayers::System, System::init, nullptr, System::terminate);

	List<InstanceBase*> System::Instances = List<InstanceBase*>();
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
		Instances = List<InstanceBase*>();
		NextID = 1;

		return true;
	}

	void System::terminate()
	{
		// theoretically all instances will be handled by their respective components
		// figure out whether or not to add more priorty types so this function is run last
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