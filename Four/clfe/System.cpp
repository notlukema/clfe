#include "System.h"

namespace clfe
{

	Attachment System::SystemAttachment = Attachment(AttachmentLayers::System, System::init, nullptr, System::terminate);
	clid System::NextID = 0;

	std::list<InstanceBase*> System::Instances = std::list<InstanceBase*>();

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
		NextID = 0;

		return true;
	}

	void System::terminate()
	{
		while (!Instances.empty())
		{
			// Also delete all the recorded components?
			// Not sure which steps should be made necessary since the inner components are most likely handled by their respective attachments and the system deleting them all too feels a bit intrusive
			// 
			// Instances.front()->deepDelete();
			delete Instances.front(); // Deletion also causes the instance list to remove itself from the big list
		}
	}

	clid System::genNextID()
	{
		clid thisID = NextID;
		NextID++;

		return thisID;
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