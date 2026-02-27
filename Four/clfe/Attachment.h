#ifndef CLFE_ATTACHMENT_H
#define CLFE_ATTACHMENT_H

// Always include the layers because it will most likely be used
#include "AttachmentLayers.h"

#include <List>
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

	struct AttachmentHolder
	{

		static std::list<Attachment*> attachments;

		static void sort();

	};

	static void addAttachment(Attachment* attachment);
	static void removeAttachment(Attachment* attachment);

}

#endif