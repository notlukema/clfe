#include "Attachment.h"

namespace clfe
{

	// Attachment struct

	Attachment::Attachment(Priority_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), initPriority(priority), stepPriority(priority), termPriority(priority)
	{
		AttachmentHolder::addAttachment(this);
	}

	Attachment::Attachment(Priority_t initPriority, Priority_t stepPriority, Priority_t termPriority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), initPriority(initPriority), stepPriority(stepPriority), termPriority(termPriority)
	{
		AttachmentHolder::addAttachment(this);
	}

	Attachment::Attachment(const Priority_t priorities[3], bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)())
		: init(initFunc), step(stepFunc), terminate(termFunc), initPriority(priorities[0]), stepPriority(priorities[1]), termPriority(priorities[2])
	{
		AttachmentHolder::addAttachment(this);
	}

	Attachment::~Attachment()
	{
		AttachmentHolder::removeAttachment(this);
	}

	// AttachmentHolder struct

	List<Attachment*> AttachmentHolder::attachments = List<Attachment*>();

	//

	void AttachmentHolder::addAttachment(Attachment* attachment)
	{
		attachments.push_back(attachment);
	}

	void AttachmentHolder::removeAttachment(Attachment* attachment)
	{
		attachments.remove(attachment);
	}

	const List<Attachment*>& AttachmentHolder::getAttachmentsSortedByInitPriority()
	{
		attachments.sort([](Attachment* a, Attachment* b) {
			return a->initPriority < b->initPriority;
			});
		return attachments;
	}

	const List<Attachment*>& AttachmentHolder::getAttachmentsSortedByStepPriority()
	{
		attachments.sort([](Attachment* a, Attachment* b) {
			return a->stepPriority < b->stepPriority;
			});
		return attachments;
	}

	const List<Attachment*>& AttachmentHolder::getAttachmentsSortedByTermPriority()
	{
		attachments.sort([](Attachment* a, Attachment* b) {
			return a->termPriority < b->termPriority;
			});
		return attachments;
	}

}