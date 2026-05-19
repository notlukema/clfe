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
		// Delete all instances, although it should technically already all be deleted
		if (!Instances.empty())
		{
			CLFE_LOG("System is terminating with non-empty instance list(s)! It is recommended to handle instance list termination upon the termination call.");
		}
		while (!Instances.empty())
		{
			delete Instances.front();
		}
	}

	clid System::genNextID()
	{
		clid thisID = NextID;
		NextID++;

		return thisID;
	}

	// InstanceBase

	InstanceBase::InstanceBase(UniString name) : name(name), first(nullptr), len(0)
	{
		System::addInstance(this);
	}

	InstanceBase::~InstanceBase()
	{
		System::removeInstance(this);
	}

	// InstanceLink

	InstanceLink::InstanceLink(clid id, InstanceBase* parent) : id(id), parent(parent), next(parent->first), last(nullptr)
	{
		if (parent->first != nullptr)
		{
			parent->first->last = this;
		}
		parent->first = this;
		parent->len++;
	}

	InstanceLink::~InstanceLink()
	{
		parent->len--;
		if (next != nullptr)
		{
			next->last = last;
		}
		if (last == nullptr)
		{
			parent->first = next;
		}
		else
		{
			last->next = next;
		}
	}

}