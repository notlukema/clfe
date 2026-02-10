#include "CLFE.h"

namespace clfe
{

	// Attachment struct

	Attachment::Attachment(uint32_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), priority(priority)
	{
		addAttachment(this);
	}

	// AttachmentHolder struct

	std::list<Attachment*> AttachmentHolder::attachments = std::list<Attachment*>();

	void AttachmentHolder::sort()
	{
		attachments.sort([](Attachment* a, Attachment* b) {
			return a->priority > b->priority;
			});
	}

	//

	void addAttachment(Attachment* attachment)
	{
		AttachmentHolder::attachments.push_back(attachment);
		AttachmentHolder::attachments.sort();
	}

	void removeAttachment(Attachment* attachment)
	{
		AttachmentHolder::attachments.remove(attachment);
	}

	bool init()
	{
		bool success = true;

		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->init == nullptr)
			{
				continue;
			}
			success = success && attachment->init();
		}

		return success;
	}

	void step()
	{
		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->step == nullptr)
			{
				continue;
			}
			attachment->step(0.0f, 0.0);
		}
	}

	void terminate()
	{
		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->terminate == nullptr)
			{
				continue;
			}
			attachment->terminate();
		}
	}

}