#include "Attachment.h"

namespace clfe
{

	// Attachment struct

	Attachment::Attachment(uint32_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), priority(priority)
	{
		addAttachment(this);
	}

	Attachment::~Attachment()
	{
		removeAttachment(this);
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

}