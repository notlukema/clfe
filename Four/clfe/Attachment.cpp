#include "Attachment.h"

namespace clfe
{

	// Attachment struct

	Attachment::Attachment(Priority_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), priority(priority)
	{
		AttachmentHolder::addAttachment(this);
	}

	Attachment::~Attachment()
	{
		AttachmentHolder::removeAttachment(this);
	}

	// AttachmentHolder struct

	List<Attachment*> AttachmentHolder::attachments = List<Attachment*>();

	void AttachmentHolder::sort()
	{
		attachments.sort([](Attachment* a, Attachment* b) {
			return a->priority < b->priority;
		});
	}

	//

	void AttachmentHolder::addAttachment(Attachment* attachment)
	{
		attachments.push_back(attachment);
		sort();
	}

	void AttachmentHolder::removeAttachment(Attachment* attachment)
	{
		attachments.remove(attachment);
	}

}