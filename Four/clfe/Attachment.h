#ifndef CLFE_ATTACHMENT_H
#define CLFE_ATTACHMENT_H

#include "Attachment.h"
#include "List.h"

#include <cstdint>

namespace clfe
{

	// Lower number = higher priority (0 = highest priority)
	using priority_t = uint32_t;

	struct Attachment
	{

		bool (* const init)();
		void (* const step)(float delf, double deld);
		void (* const terminate)();

		const uint32_t priority; // Lower number = higher priority (0 = highest priority)

		Attachment(uint32_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)());
		~Attachment();

	};

	class AttachmentHolder
	{
	private:
		friend struct Attachment;

		static List<Attachment*> attachments;

		static void sort();
		static void addAttachment(Attachment* attachment);
		static void removeAttachment(Attachment* attachment);

	public:
		static inline const List<Attachment*>& getAttachments()
		{
			return attachments;
		}

	};

}

#endif